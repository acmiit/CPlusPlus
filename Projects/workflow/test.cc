#include <workflow/WFHttpServer.h>
#include <iostream>

int main() {
    WFHttpServer server([](WFHttpTask *task) {
        task->get_resp()->append_output_body("<html>Hello Workflow!</html>");
    });

    if (server.start(8888) == 0) {
        std::cout << "Server start success! Port: 8888" << std::endl;
        getchar(); // 按回车退出
        server.stop();
    }
    return 0;
}