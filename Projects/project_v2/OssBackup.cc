#include "OssBackup.h"
#include <fstream>
#include <sstream>
#include <iostream>

OssBackup::OssBackup(const std::string& endpoint,
                     const std::string& accessKeyId,
                     const std::string& accessKeySecret,
                     const std::string& bucket)
    : _bucket(bucket) {
    AlibabaCloud::OSS::ClientConfiguration conf;
    _client = std::make_shared<AlibabaCloud::OSS::OssClient>(
        endpoint, accessKeyId, accessKeySecret, conf);
}

OssBackup::~OssBackup() {
}

bool OssBackup::uploadFile(const std::string& localFilePath, const std::string& ossKey) {
    AlibabaCloud::OSS::PutObjectOutcome outcome = _client->PutObject(_bucket, ossKey, localFilePath);

    if (!outcome.isSuccess()) {
        std::cerr << "Failed to upload file: " << outcome.error().Code() << " - " << outcome.error().Message() << std::endl;
        return false;
    }

    std::cout << "File uploaded successfully: " << ossKey << std::endl;
    return true;
}

bool OssBackup::uploadData(const std::string& data, const std::string& ossKey) {
    std::shared_ptr<std::iostream> content = std::make_shared<std::stringstream>();
    *content << data;

    AlibabaCloud::OSS::PutObjectRequest request(_bucket, ossKey, content);
    auto outcome = _client->PutObject(request);

    if (!outcome.isSuccess()) {
        std::cerr << "Failed to upload data: " << outcome.error().Code() << " - " << outcome.error().Message() << std::endl;
        return false;
    }

    std::cout << "Data uploaded successfully: " << ossKey << std::endl;
    return true;
}

bool OssBackup::downloadFile(const std::string& ossKey, const std::string& localFilePath) {
    AlibabaCloud::OSS::GetObjectOutcome outcome = _client->GetObject(_bucket, ossKey, localFilePath);

    if (!outcome.isSuccess()) {
        std::cerr << "Failed to download file: " << outcome.error().Code() << " - " << outcome.error().Message() << std::endl;
        return false;
    }

    std::cout << "File downloaded successfully: " << ossKey << " -> " << localFilePath << std::endl;
    return true;
}

std::string OssBackup::getSignedUrl(const std::string& ossKey, int expiresSeconds) {
    AlibabaCloud::OSS::GeneratePresignedUrlRequest request(_bucket, ossKey);
    request.setExpires(expiresSeconds);

    auto outcome = _client->GeneratePresignedUrl(request);
    if (outcome.isSuccess()) {
        return outcome.result();
    }

    std::cerr << "Failed to generate signed URL: " << outcome.error().Code() << std::endl;
    return "";
}