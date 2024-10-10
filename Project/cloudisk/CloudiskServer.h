#ifndef __WD_CloudiskServer_HPP__
#define __WD_CloudiskServer_HPP__

#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>

#define RETRY_MAX 1
#define REDIRECT_MAX 5
#define LOCAL_NGINX_URL "localhost:8080"

/* OSS 相关 */
#define EndPoint "xxxxx.com"  // 外网访问地域节点
#define AccessKeyID "xxxxxx"
#define ACCESSS_KEY_SECRET "XXXXXX"
#define BUCKET "XXXXX"            // 存储空间名称
#define CloudFilePath "newFile/"  // 云端文件路径

class CloudiskServer {
   public:
    CloudiskServer(int cnt) : _waitGroup(cnt) {}
    ~CloudiskServer() {}
    void start(unsigned short port);
    void loadModules();

   private:
    // 模块化的思维方式写代码
    void loadStaticResourceModule();  // 静态资源
    void loadUserRegisterModule();    // 注册
    void loadUserLoginModule();       // 登录
    void loadUserInfoModule();        // 用户信息
    void loadFileQueryModule();       // 文件查询
    void loadFileUploadModule();      // 文件上传
    void loadFileDownloadModule();    // 文件下载
   private:
    WFFacilities::WaitGroup _waitGroup;  // 时间等待
    wfrest::HttpServer _httpserver;
};

#endif
