#ifndef __WD_CONFIG_HPP__
#define __WD_CONFIG_HPP__

#include <string>

struct RabbitMQConfig {
    std::string host;
    int port;
    std::string username;
    std::string password;
    std::string exchange;
    std::string routing_key;
    std::string queue;
};

struct OssConfig {
    std::string endpoint;
    std::string access_key_id;
    std::string access_key_secret;
    std::string bucket;
};

class Config {
public:
    static RabbitMQConfig getRabbitMQConfig() {
        RabbitMQConfig config;
        config.host = "127.0.0.1";
        config.port = 5672;
        config.username = "guest";
        config.password = "guest";
        config.exchange = "uploadserver.trans";
        config.routing_key = "oss";
        
        config.queue = "uploadserver.trans.oss";
        return config;
    }

    static OssConfig getOssConfig() {
        OssConfig config;
        config.endpoint = "oss-cn-guangzhou.aliyuncs.com";
        config.access_key_id = "";
        config.access_key_secret = "";
        config.bucket = "yxl-cplusplus";
        return config;
    }
};

#endif