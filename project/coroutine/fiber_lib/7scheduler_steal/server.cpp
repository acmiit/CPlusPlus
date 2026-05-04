#include "ioscheduler.h"
#include "hook.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>

static int sock_listen_fd = -1;

void test_accept();

void test_accept()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
    int fd = accept(sock_listen_fd, (struct sockaddr *)&addr, &len);
    if (fd >= 0)
    {
        fcntl(fd, F_SETFL, O_NONBLOCK);
        sylar::IOManager::GetThis()->addEvent(fd, sylar::IOManager::READ, [fd]()
        {
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            int ret = recv(fd, buffer, sizeof(buffer) - 1, 0);
            if (ret > 0)
            {
                usleep(10000);

                const char *response = "HTTP/1.1 200 OK\r\n"
                                       "Content-Type: text/plain\r\n"
                                       "Content-Length: 13\r\n"
                                       "Connection: keep-alive\r\n"
                                       "\r\n"
                                       "Hello, World!";
                send(fd, response, strlen(response), 0);
                close(fd);
            }
            else
            {
                close(fd);
            }
        });
    }
    sylar::IOManager::GetThis()->addEvent(sock_listen_fd, sylar::IOManager::READ, test_accept);
}

void test_iomanager()
{
    int portno = 8080;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portno);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    sock_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_listen_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    int yes = 1;
    setsockopt(sock_listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    if (bind(sock_listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    if (listen(sock_listen_fd, 10240) < 0)
    {
        perror("listen");
        exit(1);
    }

    printf("Coroutine server listening on port: %d (IO wait: 10ms, 1 thread)\n", portno);
    fcntl(sock_listen_fd, F_SETFL, O_NONBLOCK);

    sylar::IOManager iom(1);
    iom.addEvent(sock_listen_fd, sylar::IOManager::READ, test_accept);
}

int main(int argc, char *argv[])
{
    test_iomanager();
    return 0;
}