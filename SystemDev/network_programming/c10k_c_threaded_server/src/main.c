#include "../include/server.h"

int main() {
    RunServer(8080, 4);  // 启动服务端，4线程线程池
    return 0;
}
