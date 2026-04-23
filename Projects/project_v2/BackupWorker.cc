#include "RabbitMQConsumer.h"
#include "OssBackup.h"
#include "Config.h"
#include <iostream>
#include <thread>
#include <chrono>

#include <alibabacloud/oss/OssClient.h>
#include <wfrest/json.hpp>

struct BackupMessage {
    std::string username;
    std::string filename;
    std::string filepath;
    std::string filehash;
    size_t filesize;
};

BackupMessage parseMessage(const std::string& jsonStr) {
    BackupMessage msg;
    try {
        auto j = nlohmann::json::parse(jsonStr);
        msg.username = j.value("username", "");
        msg.filename = j.value("filename", "");
        msg.filepath = j.value("filepath", "");
        msg.filehash = j.value("filehash", "");
        msg.filesize = j.value("filesize", 0);
    } catch (const std::exception& e) {
        
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    return msg;
}

int main(int argc, char* argv[]) {
    AlibabaCloud::OSS::InitializeSdk();

    RabbitMQConfig mqConfig = Config::getRabbitMQConfig();
    OssConfig ossConfig = Config::getOssConfig();

    RabbitMQConsumer consumer(mqConfig.host, mqConfig.port, mqConfig.username, mqConfig.password,
                              mqConfig.queue, mqConfig.exchange, mqConfig.routing_key);

    OssBackup backup(ossConfig.endpoint, ossConfig.access_key_id, ossConfig.access_key_secret, ossConfig.bucket);

    if (!consumer.connect()) {
        std::cerr << "Failed to connect to RabbitMQ" << std::endl;
        return 1;
    }

    std::cout << "Backup Worker started, waiting for messages..." << std::endl;

    consumer.consume([&](const std::string& message) {
        std::cout << "Received message: " << message << std::endl;

        BackupMessage msg = parseMessage(message);
        std::cout << "Parsed message - username: " << msg.username
                  << ", filename: " << msg.filename
                  << ", filepath: " << msg.filepath
                  << ", filehash: " << msg.filehash
                  << ", filesize: " << msg.filesize << std::endl;

        if (msg.filepath.empty()) {
            std::cerr << "Error: filepath is empty, skipping backup" << std::endl;
            return;
        }

        std::string ossKey = "backups/" + msg.username + "/" + msg.filehash + "_" + msg.filename;
        std::cout << "Uploading to OSS with key: " << ossKey << std::endl;

        if (backup.uploadFile(msg.filepath, ossKey)) {
            std::cout << "Backup completed: " << ossKey << std::endl;
        } else {
            std::cerr << "Backup failed for: " << msg.filepath << std::endl;
        }
    });

    AlibabaCloud::OSS::ShutdownSdk();
    return 0;
}