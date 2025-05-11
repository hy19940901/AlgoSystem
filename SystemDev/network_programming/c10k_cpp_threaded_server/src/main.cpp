#include "../include/threaded_server.h"
#include <iostream>

int main() {
    ThreadedServer server(8080, 8);
    ThreadedServer::instance = &server;
    server.Run();
    return 0;
}
