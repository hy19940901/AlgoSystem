// utils.c
#include "../include/utils.h"
#include <fcntl.h>

int SetNonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
