#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <fcntl.h>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#define MAX_EVENTS 10000
#define PORT 8888
#define NUM_THREADS 1

static int listen_fd;
static int epoll_fd;
static bool running = true;

std::queue<int> conn_queue;
std::mutex queue_mutex;
std::condition_variable queue_cv;

void* worker_thread(void* arg) {
    while (running) {
        int conn_fd = -1;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (conn_queue.empty()) {
                queue_cv.wait(lock);
                continue;
            }
            conn_fd = conn_queue.front();
            conn_queue.pop();
        }

        if (conn_fd >= 0) {
            char buffer[1024];
            int len = recv(conn_fd, buffer, sizeof(buffer) - 1, 0);
            if (len > 0) {
                usleep(10000);

                const char *response = "HTTP/1.1 200 OK\r\n"
                                       "Content-Type: text/plain\r\n"
                                       "Content-Length: 13\r\n"
                                       "Connection: keep-alive\r\n"
                                       "\r\n"
                                       "Hello, World!";
                send(conn_fd, response, strlen(response), 0);
            }
            close(conn_fd);
        }
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    struct epoll_event events[MAX_EVENTS], event;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket");
        return -1;
    }

    int yes = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(listen_fd, 10240) == -1) {
        perror("listen");
        return -1;
    }

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return -1;
    }

    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    printf("Epoll+ThreadPool server (port %d, IO wait: 10ms, %d threads)\n", PORT, NUM_THREADS);

    std::vector<pthread_t> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, worker_thread, NULL);
        threads.push_back(tid);
    }

    while (running) {
        int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 100);
        if (event_count == -1) {
            if (errno == EINTR) continue;
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < event_count; i++) {
            if (events[i].data.fd == listen_fd) {
                int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addr_len);
                if (conn_fd >= 0) {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    conn_queue.push(conn_fd);
                    queue_cv.notify_one();
                }
            }
        }
    }

    close(listen_fd);
    close(epoll_fd);
    return 0;
}