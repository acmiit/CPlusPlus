# Install script for directory: /home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/auth" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/auth/Credentials.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/auth/CredentialsProvider.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/client" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/client/AsyncCallerContext.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/client/ClientConfiguration.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/client/Error.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/client/RateLimiter.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/client/RetryStrategy.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/http" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpClient.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpInterceptor.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpMessage.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpResponse.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/HttpType.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/http/Url.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/utils" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/utils/Executor.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/utils/Outcome.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/utils/Runnable.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/model" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/AbortBucketWormRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/AbortMultipartUploadRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/AppendObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/AppendObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/Bucket.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CORSRule.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CompleteBucketWormRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CompleteMultipartUploadRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CompleteMultipartUploadResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CopyObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CopyObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CreateBucketRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CreateSelectObjectMetaRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CreateSelectObjectMetaResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CreateSymlinkRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/CreateSymlinkResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketCorsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketEncryptionRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketInventoryConfigurationRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketLifecycleRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketLoggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketPolicyRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketQosInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteBucketWebsiteRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteLiveChannelRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectTaggingResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectVersionsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectVersionsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DeleteObjectsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/DownloadObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ExtendBucketWormRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GeneratePresignedUrlRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GenerateRTMPSignedUrlRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketAclRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketAclResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketCorsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketCorsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketEncryptionRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketEncryptionResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketInfoResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketInventoryConfigurationRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketInventoryConfigurationResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLifecycleRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLifecycleResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLocationRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLocationResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLoggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketLoggingResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketPaymentRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketPaymentResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketPolicyRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketPolicyResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketQosInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketQosInfoResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketRefererRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketRefererResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketStatRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketStatResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketStorageCapacityRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketStorageCapacityResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketTaggingResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketVersioningRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketVersioningResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketWebsiteRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketWebsiteResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketWormRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetBucketWormResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelHistoryRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelHistoryResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelInfoResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelStatRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetLiveChannelStatResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectAclRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectAclResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectByUrlRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectMetaRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetObjectTaggingResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetSymlinkRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetSymlinkResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetUserQosInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetUserQosInfoResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetVodPlaylistRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/GetVodPlaylistResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/HeadObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InitiateBucketWormRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InitiateBucketWormResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InitiateMultipartUploadRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InitiateMultipartUploadResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InputFormat.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/InventoryConfiguration.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/LifecycleRule.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListBucketInventoryConfigurationsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListBucketInventoryConfigurationsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListBucketsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListBucketsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListLiveChannelRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListLiveChannelResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListMultipartUploadsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListMultipartUploadsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectVersionsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectVersionsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectsV2Request.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListObjectsV2Result.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListPartsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ListPartsResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/MultiCopyObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/MultipartUploadCryptoContext.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ObjectCallbackBuilder.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ObjectMetaData.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/OutputFormat.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/Owner.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/Part.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PostVodPlaylistRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/ProcessObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutLiveChannelRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutLiveChannelResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutLiveChannelStatusRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutObjectByUrlRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/PutObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/QosConfiguration.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/RestoreObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/RestoreObjectResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SelectObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketAclRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketCorsRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketEncryptionRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketInventoryConfigurationRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketLifecycleRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketLoggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketPaymentRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketPolicyRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketQosInfoRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketRefererRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketStorageCapacityRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketVersioningRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetBucketWebsiteRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetObjectAclRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetObjectAclResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetObjectTaggingRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/SetObjectTaggingResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/Tagging.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/UploadObjectRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/UploadPartCopyRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/UploadPartCopyResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/UploadPartRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/model/VoidResult.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss/encryption" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/encryption/Cipher.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/encryption/ContentCryptoMaterial.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/encryption/CryptoConfiguration.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/encryption/EncryptionMaterials.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/alibabacloud/oss" TYPE FILE FILES
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/Config.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/Const.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/Export.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/Global.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssClient.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssEncryptionClient.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssError.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssFwd.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssResponse.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/OssResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/ServiceRequest.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/ServiceResult.h"
    "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/sdk/include/alibabacloud/oss/Types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/build/lib/libalibabacloud-oss-cpp-sdk.a")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/yuanxuliang/Cplusplus/aliyun-oss-cpp-sdk-1.10.1/build/sdk/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
