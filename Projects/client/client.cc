#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char* argv[]) {
    // 默认连接本地 8080 端口
    string ip = "127.0.0.1";
    int port = 8888;

    if (argc == 3) {
        ip = argv[1];
        port = stoi(argv[2]);
    }

    // 1. 创建 Socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // 2. 连接到 Reactor 服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    cout << "Connected to Reactor server at " << ip << ":" << port << endl;
    cout << "Type message to send (type 'quit' to exit):" << endl;

    string input;
    char buffer[4096] = {0};

    // 3. 循环通信
    while (true) {
        cout << "Client> ";
        getline(cin, input);

        if (input == "quit") {
            break;
        }

        if (input.empty()) continue;

        // 发送数据
        send(sock, input.c_str(), input.length(), 0);

        // 接收 Reactor 的响应
        memset(buffer, 0, sizeof(buffer));
        int valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
        
        if (valread > 0) {
            cout << "Reactor> " << buffer << endl;
        } else if (valread == 0) {
            cout << "[Server Disconnected]" << endl;
            break;
        } else {
            perror("recv error");
            break;
        }
    }

    close(sock);
    return 0;
}