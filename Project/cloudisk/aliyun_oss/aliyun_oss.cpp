/*************************************************************************
    > File Name: aliyun_oss.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年10月10日 星期四 20时24分16秒
    > Mail: JiaZiChunQiu@163.com
    > Title: aliyun_oss 备份
    > Content:
 ************************************************************************/

#include <alibabacloud/oss/OssClient.h>
#include <iostream>

using namespace AlibabaCloud::OSS;

#define EndPoint "xxxxxx"  // 外网访问地域节点
#define AccessKeyID "xxxxxx"
#define ACCESSS_KEY_SECRET "XXXXXX"
#define BUCKET "XXXXX"            // 存储空间名称
#define CloudFilePath "newFile/"  // 云端文件路径

// typedef struct {
//     std::string EndPoint = "xxxxxxx";  // 外网访问地域节点
//     std::string AccessKeyID "xxxxxx";
//     std::string ACCESSS_KEY_SECRET "XXXXXX";
//     std::string BUCKET "XXXXX";  // 存储空间名称
// } OSS_INFO;

/* =============== test =============== */
void test0() {
    /* 资源 */
    // OSS_INFO ossInfo;
    std::string localPath = "../tmp/123.pdf";                   // 本地路径
    std::string cloudObjectName = "newFile/google_study.pdf ";  // 云端路径

    /* 初始化网络等资源。*/
    InitializeSdk();

    /* 配置测录 */
    ClientConfiguration conf;
    // conf.signatureVersion = SignatureVersionType::V4;  // 使用给定的配置

    /* 创建 client 对象 */
    OssClient client(EndPoint, AccessKeyID, AccessKeySecret, conf);                   // 创建客户端对象
    PutObjectOutcome outcome = client.PutObject(Bucket, cloudObjectName, localPath);  // 上传
    if (!outcome.isSuccess()) {
        std::cout << "PutObject fail" << ", code:" << outcome.error().Code()
                  << ", message:" << outcome.error().Message() << ", requestId:" << outcome.error().RequestId() << "\n";
        return;
    } else {
        std::cout << "Success\n";
    }

    /* 释放网络等资源。*/
    ShutdownSdk();
}
/* =============== main =============== */
int main(int argc, char* argv[]) {
    test0();
    return 0;
}
