#include "CloudiskServer.h"
#include "Hash.h"
#include "Token.h"
#include "unixHeader.h"

#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <wfrest/json.hpp>

#include <alibabacloud/oss/OssClient.h>  // 备份 OSS

#include <iostream>

using namespace wfrest;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void CloudiskServer::start(unsigned short port) {
    if (_httpserver.track().start(port) == 0) {
        _httpserver.list_routes();
        _waitGroup.wait();
        _httpserver.stop();
    } else {
        printf("Cloudisk Server Start Failed!\n");
    }
}

void CloudiskServer::loadModules() {
    loadStaticResourceModule();  // 用于静态资源的请求
    loadUserRegisterModule();    // 用户注册
    loadUserLoginModule();       // 用户登录
    loadUserInfoModule();        // 查询注册时间
    loadFileQueryModule();       // 文件列表查询
    loadFileUploadModule();      // 文件上传
    loadFileDownloadModule();    // 文件下载
}

void CloudiskServer::loadStaticResourceModule() {
    _httpserver.GET("/user/signup", [](const HttpReq*, HttpResp* resp) { resp->File("static/view/signup.html"); });
    _httpserver.GET("/static/view/signin.html",
                    [](const HttpReq*, HttpResp* resp) { resp->File("static/view/signin.html"); });
    _httpserver.GET("/static/view/home.html",
                    [](const HttpReq*, HttpResp* resp) { resp->File("static/view/home.html"); });
    _httpserver.GET("/static/js/auth.js", [](const HttpReq*, HttpResp* resp) { resp->File("static/js/auth.js"); });
    _httpserver.GET("/static/img/avatar.jpeg",
                    [](const HttpReq*, HttpResp* resp) { resp->File("static/img/avatar.jpeg"); });
    _httpserver.GET("/file/upload", [](const HttpReq*, HttpResp* resp) { resp->File("static/view/index.html"); });
    _httpserver.Static("/file/upload_files",
                       "static/view/upload_files");  // http中的url -> 服务端项目路径开始的文件路径
}

/*
    用户注册
    TODO: 二次密码确认
*/
void CloudiskServer::loadUserRegisterModule() {
    _httpserver.POST("/user/signup", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        /* APPLICATION_URLENCODED = application/x-www-form-urlencoded = 14 */
        if (req->content_type() == APPLICATION_URLENCODED) {
            /* 1. 解析请求, 获取用户名和密码 */
            auto formKV = req->form_kv();  // map 类型
            string username = formKV["username"];
            string password = formKV["password"];
            // cout << "username:" << username << endl;
            // cout << "password:" << password << endl;

            /* 2. 对密码进行加密 */
            string salt("12345678");                                        // 这里应该是随机生成
            string encodedPassword(crypt(password.c_str(), salt.c_str()));  // crypt加密
            // cout << "mi wen:" << encodedPassword << endl;

            /* 3. 将用户信息存储到数据库MySQL中 */
            string mysqlurl("mysql://root:123456@localhost");  // 连接数据库字段
            /* 创建 mysql 语句, lambda中为直接结束后回调处理 */
            auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, RETRY_MAX, [resp](WFMySQLTask* mysqltask) {
                // 0. 对任务的状态进行检测
                int state = mysqltask->get_state();
                int error = mysqltask->get_error();
                if (state != WFT_STATE_SUCCESS) {
                    printf("%s\n", WFGlobal::get_error_string(state, error));
                    return;
                }

                auto mysqlResp = mysqltask->get_resp();  // 获取请求

                // 1. SQL引用层面是否存在语法错误 (语法,唯一键等)
                if (mysqlResp->get_packet_type() == MYSQL_PACKET_ERROR) {
                    printf("ERROR %d: %s\n", mysqlResp->get_error_code(), mysqlResp->get_error_msg().c_str());
                    resp->String("Signup Failed");
                    return;
                }

                // 2. 判断结果
                using namespace protocol;
                MySQLResultCursor cursor(mysqlResp);  // 执行mysql语句
                if (cursor.get_cursor_status() == MYSQL_STATUS_OK) {
                    // 2. 成功写入数据库了
                    printf("Query OK. %llu row affected.\n", cursor.get_affected_rows());
                    resp->String("SUCCESS");
                } else {
                    resp->String("Signup Failed");
                }
            });

            /* 完整插入语句
            "insert into cloudisk.tbl_user(user_name, user_pwd)
            VALUES('username', encodedPassword')
            */
            string sql(
                "INSERT INTO cloudisk.tbl_user(user_name, user_pwd) "
                "VALUES('");                                    // sql 语句
            sql += username + "', '" + encodedPassword + "')";  // 补充
            // cout << "sql:\n" << sql << endl;

            mysqlTask->get_req()->set_query(sql);  // 获取请求, 设置执行
            series->push_back(mysqlTask);          // 添加序列
        }
    });
}

/*
    用户登录
    Fix bug : 段错误, 如果用户名不再user_table 中, 存在越界访问
    TODO : Token应该存放在Redis中
*/
void CloudiskServer::loadUserLoginModule() {
    _httpserver.POST("/user/signin", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        if (req->content_type() == APPLICATION_URLENCODED) {
            /* 1. 解析请求, 获取用户名和密码 */
            auto formKV = req->form_kv();
            string username = formKV["username"];
            string password = formKV["password"];
            // cout << "username:" << username << endl;
            // cout << "password:" << password << endl;

            /* 2. 对密码进行加密 */
            string salt("12345678");  // 这里应该是随机生成, 且与注册加密相同
            string encodedPassword(crypt(password.c_str(), salt.c_str()));  // crypt 加密函数
            // cout << "mi wen:" << encodedPassword << endl;

            /* 3. 从数据库MySQL中读取用户信息进行登录验证 */
            string mysqlurl("mysql://root:123456@localhost");
            auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, [=](WFMySQLTask* mysqltask) {
                // 0. 对任务的状态进行检测
                int state = mysqltask->get_state();
                int error = mysqltask->get_error();
                if (state != WFT_STATE_SUCCESS) {
                    printf("%s\n", WFGlobal::get_error_string(state, error));
                    return;
                }

                // 1. SQL引用层面是否存在语法错误 (语法,唯一键等)
                auto mysqlResp = mysqltask->get_resp();
                if (mysqlResp->get_packet_type() == MYSQL_PACKET_ERROR) {
                    printf("ERROR %d: %s\n", mysqlResp->get_error_code(), mysqlResp->get_error_msg().c_str());
                    resp->String("Singup Failed");
                    return;
                }

                using namespace protocol;
                MySQLResultCursor cursor(mysqlResp);
                /* 写入语句 */
                if (cursor.get_cursor_status() == MYSQL_STATUS_OK) {
                    // 2. 成功写入数据库了
                    printf("Query OK. %llu row affected.\n", cursor.get_affected_rows());
                    resp->String("Login Failed");
                    /* 查询语句 */
                } else if (cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT) {
                    // 3. 读取数据
                    vector<vector<MySQLCell>> matrix;  // 创建存放表格内容的容器
                    cursor.fetch_all(matrix);          // 获取到所有表格内容
                    // 如果内容为null,
                    if (!matrix.empty()) {
                        string M = matrix[0][0].as_string();  // 将获取的内容转换为 string, 如果为null, 这里存在访问越界
                        // cout << "M:" << M << endl;
                        if (encodedPassword == M) {
                            // 3.1 登录成功的情况, 生成Token信息
                            Token token(username, salt);         // 根据用户和盐值, 创建Token信息
                            string tokenStr = token.genToken();  // 获取到token值

                            // 3.2 构造一个 JSON 对象，发送给客户端, 返回JSON对象是与前端约定的规则
                            // { "data":{"Token":xxx, "Username":xxx, "Location":xxx} }; JSON类型：{ {} }
                            using Json = nlohmann::json;
                            Json msg;
                            Json data;
                            data["Token"] = tokenStr;
                            data["Username"] = username;
                            data["Location"] = "/static/view/home.html";  // 跳转到用户个人中心页面
                            msg["data"] = data;
                            resp->String(msg.dump());  // 序列化之后，发送给客户端

                            // 3.3 将Token保存到数据库中
                            auto nextTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, nullptr);
                            // 插入/更新 replace into 语句
                            string sql("REPLACE INTO cloudisk.tbl_user_token(user_name, user_token) VALUES('");
                            sql += username + "', '" + tokenStr + "')";
                            nextTask->get_req()->set_query(sql);
                            series->push_back(nextTask);
                        } else {
                            resp->String("PWD is Error");  // 密码验证失败的情况
                        }
                    } else {
                        resp->String("Login Failed");  // 无该用户, 查询结果为null
                    }
                }
            });
            string sql("select user_pwd from cloudisk.tbl_user where user_name = '");  // 查询语句
            sql += username + "' limit 1";                                             // limit 分页子查询
            // cout << "sql:\n" << sql << endl;
            mysqlTask->get_req()->set_query(sql);
            series->push_back(mysqlTask);
        }
    });
}

/*
    根据用户名查询数据库tbl_user得到注册时间
    TODO : token 校验
*/
void CloudiskServer::loadUserInfoModule() {
    _httpserver.GET("/user/info", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        // 1. 解析请求
        string username = req->query("username");  // 用户名
        string tokenStr = req->query("token");     // 获取请求体中的token
        // cout << "username:" << username << endl;
        // cout << "token:" << tokenStr << endl;

        /* 2. 根据用户名查找用户的注册时间 */
        string mysqlurl("mysql://root:123456@localhost");
        auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, [=](WFMySQLTask* mysqltask) {
            using namespace protocol;
            auto mysqlResp = mysqltask->get_resp();  // 获取响应
            MySQLResultCursor cursor(mysqlResp);
            if (cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT) {
                // 读操作,获取用户的注册时间
                vector<vector<MySQLCell>> matrix;
                cursor.fetch_all(matrix);
                string signupAt = matrix[0][0].as_string();
                // 创建 JSON 对象
                using Json = nlohmann::json;
                Json msg;
                Json data;
                data["Username"] = username;
                data["SignupAt"] = signupAt;
                msg["data"] = data;
                resp->String(msg.dump());  // 序列化后发送给客户端
            } else {
                resp->String("error");  // 没有读取到正确的信息
            }
        });
        string sql("select signup_at from cloudisk.tbl_user where user_name = '");  // 根据用户名查找注册日期
        sql += username + "'";
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });
}

/*
    根据用户的名查询文件列表
    TODO : token 校验
*/
void CloudiskServer::loadFileQueryModule() {
    _httpserver.POST("/file/query", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        // 1. 解析请求: 查询词
        string username = req->query("username");
        string tokenStr = req->query("token");
        // cout << "username:" << username << endl;
        // cout << "token:" << tokenStr << endl;

        // 2. 解析请求：消息体
        string limitCnt = req->form_kv()["limit"];  // 获取文件数, 前端提供 { data : value }
        string mysqlurl("mysql://root:123456@localhost");
        auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, [=](WFMySQLTask* mysqltask) {
            using namespace protocol;
            auto mysqlResp = mysqltask->get_resp();
            MySQLResultCursor cursor(mysqlResp);
            if (cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT) {
                // 读操作, 获取用户的
                vector<vector<MySQLCell>> matrix;
                cursor.fetch_all(matrix);
                using Json = nlohmann::json;
                Json msgArr;
                for (size_t i = 0; i < matrix.size(); ++i) {
                    Json row;
                    row["FileHash"] = matrix[i][0].as_string();
                    row["FileName"] = matrix[i][1].as_string();
                    row["FileSize"] = matrix[i][2].as_ulonglong();
                    row["UploadAt"] = matrix[i][3].as_datetime();
                    row["LastUpdated"] = matrix[i][4].as_datetime();
                    msgArr.push_back(row);  // 在数组中添加一个元素,使用push_back即可
                }
                resp->String(msgArr.dump());  // 返回客户端
            } else {
                resp->String("error");  // 没有读取到正确的信息
            }
        });
        string sql(
            "select file_sha1, file_name, file_size, upload_at, last_update from cloudisk.tbl_user_file where "
            "user_name = '");
        sql += username + "' limit " + limitCnt;
        // cout << "\nsql:\n" << sql << endl;
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });
}

/*
    文件上传功能
    TODO : token 校验
*/
void CloudiskServer::loadFileUploadModule() {
    _httpserver.POST("/file/upload", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        // 1. 解析请求
        string username = req->query("username");
        string tokenStr = req->query("token");
        // cout << "username:" << username << endl;
        // cout << "token:" << tokenStr << endl;

        // 2. 对token进行验证

        // 3. 解析请求：消息体
        if (req->content_type() == MULTIPART_FORM_DATA) {
            auto form = req->form();               // 获取post请求的body
            string filename = form["file"].first;  // 文件名
            string content = form["file"].second;  // 文件内容

            // 4. 将数据写入服务器本地
            mkdir("tmp", 0755);                                       // 创建 tmp 目录
            string filepath = "tmp/" + filename;                      // 文件路径 + 文件名字
            int fd = open(filepath.c_str(), O_CREAT | O_RDWR, 0664);  // 打开文件, 无则创建文件
            if (fd < 0) {
                perror("open");
                return;
            }
            write(fd, content.c_str(), content.size());  // 写入内容
            close(fd);                                   // 关闭文件描述符

            // 5. 生成 SHA1 值, 并存入文件表
            Hash hash(filepath);
            string filehash = hash.sha1();  // 获取文件哈希值
            // cout << "filehash:" << filehash << endl;

            // 6.将文件相关信息写入数据库MySQL中
            string mysqlurl("mysql://root:123456@localhost");
            auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 1, nullptr);
            string sql("INSERT INTO cloudisk.tbl_user_file(user_name, file_sha1, file_size, file_name) VALUES('");
            sql += username + "','" + filehash + "', " + std::to_string(content.size()) + ",'" + filename + "')";
            // cout << "\nsql:\n" << sql << endl;
            mysqlTask->get_req()->set_query(sql);
            series->push_back(mysqlTask);

            // 7. 备份到 OSS
            std::string cloudObjectName = CloudFilePath + filename;  // 云端路径
            AlibabaCloud::OSS::InitializeSdk();                      /* 初始化网络等资源。*/
            AlibabaCloud::OSS::ClientConfiguration conf;             /* 配置测录 */
            AlibabaCloud::OSS::OssClient client(EndPoint, AccessKeyID, ACCESSS_KEY_SECRET,
                                                conf);  // 创建客户端对象
            AlibabaCloud::OSS::PutObjectOutcome outCome = client.PutObject(BUCKET, cloudObjectName, filepath);  // 上传
            if (!outCome.isSuccess()) {
                std::cerr << "PutObject fail" << ", code:" << outCome.error().Code()
                          << ", message:" << outCome.error().Message() << ", requestId:" << outCome.error().RequestId()
                          << "\n";
            } else {
                resp->String("upload Success");  // 返回上传成功给客户端
            }
            AlibabaCloud::OSS::ShutdownSdk();  // 释放网络等资源
        }
    });
}

/*
    文件下载, 返回url, 使再次请求nginx下载文件
    TODO : token 校验
*/
void CloudiskServer::loadFileDownloadModule() {
    _httpserver.GET("/file/downloadurl", [](const HttpReq* req, HttpResp* resp, SeriesWork* series) {
        string filename = req->query("filename");
        // cout << "filename: " << filename << endl;

        /*
            创建 http请求, 访问 nginx, 判断是否开启,
            若开启则返回 nginx 的连接
            否则返回 OSS 的下载链接
        */
        WFHttpTask* httpTask = WFTaskFactory::create_http_task(
            LOCAL_NGINX_URL, REDIRECT_MAX, RETRY_MAX, [filename, resp, series](WFHttpTask* httpTask) {
                if (httpTask->get_state() == WFT_STATE_SUCCESS) {
                    // 将下载业务从服务器中分离出去，之后只需要产生一个下载链接就可以了
                    // 这要求我们还需要去部署一个下载服务器
                    std::string downloadURL = "http://192.168.225.129:8080/" + filename;
                    resp->String(downloadURL);
                } else {
                    std::string cloudObjectName = CloudFilePath + filename;  // 云端路径

                    AlibabaCloud::OSS::InitializeSdk();          /* 初始化网络等资源。*/
                    AlibabaCloud::OSS::ClientConfiguration conf; /* 配置测录 */
                    AlibabaCloud::OSS::OssClient client(EndPoint, AccessKeyID, ACCESSS_KEY_SECRET,
                                                        conf);  // 创建客户端对象
                    /* 获取下载链接 */
                    time_t expire = time(nullptr) + 600;
                    AlibabaCloud::OSS::StringOutcome outCome =
                        client.GeneratePresignedUrl(BUCKET, cloudObjectName, expire);
                    if (!outCome.isSuccess()) {
                        std::cout << "PutObject fail" << ", code:" << outCome.error().Code()
                                  << ", message:" << outCome.error().Message()
                                  << ", requestId:" << outCome.error().RequestId() << "\n";
                        return;
                    } else {
                        resp->String(outCome.result());  // 给客户端返回链接
                        // std::cout << "return URL is " << outCome.result() << "\n";
                    }
                    /* 释放网络等资源。*/
                    AlibabaCloud::OSS::ShutdownSdk();
                }
            });
        series->push_back(httpTask);
    });
}
