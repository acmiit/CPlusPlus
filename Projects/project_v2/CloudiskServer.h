#ifndef __WD_CloudiskServer_HPP__
#define __WD_CloudiskServer_HPP__

#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>
#include <functional>
#include <string>
#include <memory>
#include "RabbitMQPublisher.h"
#include "OssBackup.h"
#include "Config.h"

class CloudiskServer
{
public:
    CloudiskServer(int cnt)
    : _waitGroup(cnt)
    {
        RabbitMQConfig mqConfig = Config::getRabbitMQConfig();
        OssConfig ossConfig = Config::getOssConfig();

        _rabbitMQPublisher = std::make_shared<RabbitMQPublisher>(
            mqConfig.host, mqConfig.port, mqConfig.username, mqConfig.password,
            mqConfig.exchange, mqConfig.routing_key);
        if (!_rabbitMQPublisher->connect()) {
            std::cerr << "Failed to connect to RabbitMQ in constructor" << std::endl;
        } else {
            std::cout << "RabbitMQ Publisher connected successfully" << std::endl;
        }

        _ossBackup = std::make_shared<OssBackup>(
            ossConfig.endpoint, ossConfig.access_key_id,
            ossConfig.access_key_secret, ossConfig.bucket);
    }

    ~CloudiskServer() {}

    void start(unsigned short port);
    void loadMiddlewares();
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
    std::shared_ptr<RabbitMQPublisher> _rabbitMQPublisher;
    std::shared_ptr<OssBackup> _ossBackup;
};

#endif

