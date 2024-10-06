/*************************************************************************
    > File Name: 03_code_add_comments.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月06日 星期日 09时42分24秒
    > Mail: JiaZiChunQiu@163.com
    > Title:
    > Content:
 ************************************************************************/

#include <iostream>
#include <signal.h>
#include <workflow/MySQLResult.h>
#include <workflow/MySQLUtil.h>
#include <workflow/WFFacilities.h>
using std::cerr;
using std::string;
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    std::cout << "signum = " << signum << "\n";
    waitGroup.done();
}
void mysqlCallback(WFMySQLTask *mysqlTask) {
    /* 状态码判断 */
    if (mysqlTask->get_state() != WFT_STATE_SUCCESS) {
        // 在系统层面报错，权限or密码
        cerr << "error_msg =  "
             << WFGlobal::get_error_string(mysqlTask->get_state(),
                                           mysqlTask->get_error())
             << "\n";
        return;
    }
    protocol::MySQLResponse *resp = mysqlTask->get_resp(); // 获取响应对象
    /* 响应报错判断  */
    if (resp->get_packet_type() == MYSQL_PACKET_ERROR) {
        // 在SQL语句报错
        cerr << "error_code = " << resp->get_error_code()
             << " error_msg = " << resp->get_error_msg()
             << "\n"; // 输出报错代码和信息
        return;
    }
    protocol::MySQLResultCursor cursor(resp); // 相当于遍历器
    /* 循环遍历 */
    do {
        /*  */
        if (cursor.get_cursor_status() == MYSQL_STATUS_OK) {
            // 写类型的SQL语句
            cerr << "write \n";
            cerr << cursor.get_affected_rows() << " rows affected\n";
        } else if (cursor.get_cursor_status() == MYSQL_STATUS_GET_RESULT) {
            // 读类型的SQL语句
            cerr << "read \n";
            // 读表头 列的信息 field
            const protocol::MySQLField *const *fieldArr;
            fieldArr = cursor.fetch_fields();
            for (int i = 0; i < cursor.get_field_count(); ++i) {
                cerr << "db = " << fieldArr[i]->get_db()
                     << " table = " << fieldArr[i]->get_table()
                     << " name = " << fieldArr[i]->get_name()
                     << " type = " << datatype2str(fieldArr[i]->get_data_type())
                     << "\n";
            }
            // 读表的内容 每一行每一列
            // bool fetch_all(std::vector<std::vector<MySQLCell>>& rows);
            std::vector<std::vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows);
            for (auto &row : rows) {
                for (auto &cell : row) {
                    if (cell.is_int()) {
                        cerr << cell.as_int();
                    } else if (cell.is_string()) {
                        cerr << cell.as_string();
                    } else if (cell.is_datetime()) {
                        cerr << cell.as_datetime();
                    }
                    cerr << "\t";
                }
                cerr << "\n";
            }
        }
    } while (cursor.next_result_set()); // mysql 任务支持一个任务处理多个SQL语句
}
int main() {
    signal(SIGINT, sighandler); // 注册信号函数
    WFMySQLTask *mysqlTask = WFTaskFactory::create_mysql_task(
        "mysql://root:123456@localhost", 1, mysqlCallback); // 创建mysql任务
    string sql = "insert into mycloud.tbl_user_token (user_name,user_token) "
                 "values ('Caixukun','singdancerap');"; // 创建sql语句
    // string sql;
    sql += "select * from mycloud.tbl_user_token;"; // 追加命令
    mysqlTask->get_req()->set_query(sql); // 获取请求并添加sql命令
    mysqlTask->start();                   // 执行
    waitGroup.wait();
    return 0;
}
