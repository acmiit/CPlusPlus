#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

// 定义服务器端口
const int PORT = 8080;

// 读取本地图片文件到内存
std::vector<char> readImageFile(const std::string& filepath) {
    // 必须使用 std::ios::binary 以二进制模式打开，防止非预期的字符转换
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "无法打开图片文件: " << filepath << std::endl;
        return {};
    }

    // 获取文件大小
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // 读取文件内容到 vector 中
    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        return buffer;
    }
    return {};
}

int main() {
    // 1. 创建 Socket (IPv4, TCP)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket 创建失败!" << std::endl;
        return -1;
    }

    // 允许端口复用（防止重启服务器时提示端口被占用）
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. 绑定 IP 和 端口
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    std::string ip="172.22.195.222";
    server_addr.sin_addr.s_addr =inet_addr(ip.c_str()) ; // 监听所有网卡
    server_addr.sin_port = htons(PORT);       // 端口号转换为网络字节序

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind 失败!" << std::endl;
        close(server_fd);
        return -1;
    }

    // 3. 开始监听
    if (listen(server_fd, 10) < 0) {
        std::cerr << "Listen 失败!" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "服务器已启动，正在监听端口 " << PORT << "..." << std::endl;

    // 4. 进入事件循环，等待客户端连接
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        
        // 阻塞等待客户端连接
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Accept 失败!" << std::endl;
            continue;
        }

        // 读取客户端请求 (这里为了演示简化处理，仅读取不做复杂的 HTTP 解析)
        char req_buffer[1024] = {0};
        read(client_fd, req_buffer, sizeof(req_buffer) - 1);
        std::cout << "收到请求:\n" << req_buffer << "-------------------\n";

        // 5. 准备响应内容
        std::string image_path = "image.png"; // 确保同目录下有这张图片
        std::vector<char> img_data = readImageFile(image_path);

        if (!img_data.empty()) {
            // 构建 HTTP 200 OK 响应头
            // 注意：\r\n\r\n 是 HTTP 协议中头部和请求体（Body）的分隔符
            std::string header = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: image/png\r\n"
                "Content-Length: " + std::to_string(img_data.size()) + "\r\n"
                "Connection: close\r\n\r\n";

            // 发送响应头
            send(client_fd, header.c_str(), header.length(), 0);
            
            // 发送图片二进制数据 (Body)
            send(client_fd, img_data.data(), img_data.size(), 0);
            
            std::cout << "图片发送成功，大小: " << img_data.size() << " 字节\n";
        } else {
            // 如果图片不存在，返回 404
            std::string not_found_msg = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n\r\n"
                "Image not found!";
            send(client_fd, not_found_msg.c_str(), not_found_msg.length(), 0);
        }

        // 6. 关闭与该客户端的连接
        close(client_fd);
    }

    close(server_fd);
    return 0;
}