#ifndef __WD_OSS_BACKUP_HPP__
#define __WD_OSS_BACKUP_HPP__

#include <string>
#include <memory>
#include <alibabacloud/oss/OssClient.h>

class OssBackup {
public:
    OssBackup(const std::string& endpoint,
              const std::string& accessKeyId,
              const std::string& accessKeySecret,
              const std::string& bucket);
    ~OssBackup();

    bool uploadFile(const std::string& localFilePath, const std::string& ossKey);
    bool uploadData(const std::string& data, const std::string& ossKey);
    bool downloadFile(const std::string& ossKey, const std::string& localFilePath);
    std::string getSignedUrl(const std::string& ossKey, int expiresSeconds = 3600);

private:
    std::shared_ptr<AlibabaCloud::OSS::OssClient> _client;
    std::string _bucket;
};

#endif