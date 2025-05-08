#include "server.h"
#include "threadpool.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_EVENTS 10000
#define BUF_SIZE 1024

const char* RESPONSE =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 13\r\n"
    "Connection: close\r\n"
    "\r\n"
    "Hello, World!";

void handle_client(int fd) {
    char buf[1024];
    while (read(fd, buf, sizeof(buf)) > 0); // 清空数据

    ssize_t total = 0;
    ssize_t len = strlen(RESPONSE);

    while (total < len) {
        ssize_t n = write(fd, RESPONSE + total, len - total);
        if (n <= 0) break;  // 写失败
        total += n;
    }

    close(fd);
}


void run_server(int port, int thread_count) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(port)
    };
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, SOMAXCONN);
    set_nonblocking(server_fd);

    int epfd = epoll_create1(0);
    struct epoll_event ev = {.events = EPOLLIN | EPOLLET, .data.fd = server_fd};
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

    threadpool_t* pool = threadpool_create(thread_count);

    printf("Threaded server running on port %d...\n", port);
    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int n = epoll_wait(epfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; ++i) {
            if (events[i].data.fd == server_fd) {
                while (1) {
                    int client_fd = accept(server_fd, NULL, NULL);
                    if (client_fd < 0) break;
                    set_nonblocking(client_fd);
                    struct epoll_event ev = {.events = EPOLLIN | EPOLLET, .data.fd = client_fd};
                    epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
                }
            } else {
                int client_fd = events[i].data.fd;
                threadpool_add_task(pool, handle_client, client_fd);
            }
        }
    }
}
