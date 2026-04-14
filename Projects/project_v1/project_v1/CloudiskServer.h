#ifndef __WD_CloudiskServer_HPP__ 
#define __WD_CloudiskServer_HPP__ 

#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>
#include <functional>
class CloudiskServer
{
public:
    CloudiskServer(int cnt) 
    : _waitGroup(cnt)
    {}

    ~CloudiskServer() {}

    void start(unsigned short port);

    void loadModules();

private:
    //模块化的思维方式写代码
    //加载静态资源
    void loadStaticResourceModule();
    //用户系统
    void loadUserRegisterModule();
    void loadUserLoginModule();
    void loadUserInfoModule();
    //文件系统
    void loadFileQueryModule();
    void loadFileUploadModule();
    void loadFileDownloadModule();
// ==========================================
    // 新增：提取出来的 HTTP 路由处理成员函数
    // ==========================================
    
    // 1. 静态资源处理
    void handleSignupPage(const wfrest::HttpReq *req, wfrest::HttpResp *resp);
    void handleSigninPage(const wfrest::HttpReq *req, wfrest::HttpResp *resp);
    void handleHomePage(const wfrest::HttpReq *req, wfrest::HttpResp *resp);
    void handleAuthJs(const wfrest::HttpReq *req, wfrest::HttpResp *resp);
    void handleAvatar(const wfrest::HttpReq *req, wfrest::HttpResp *resp);
    void handleUploadPage(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

    // 2. 业务逻辑处理 (带 SeriesWork)
    void handleUserSignup(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series);
    void handleUserSignin(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series);
    void handleUserInfo(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series);
    void handleFileQuery(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series);
    void handleFileUpload(const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series);
    void handleFileDownloadUrl(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

private:
    WFFacilities::WaitGroup _waitGroup;
    wfrest::HttpServer _httpserver;
};

#endif

