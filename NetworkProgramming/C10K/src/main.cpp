#include "ThreadedServer.h"
#include <iostream>

int main() {
    ThreadedServer server(8080, 8);
    ThreadedServer::instance = &server;
    server.run();
    return 0;
}
