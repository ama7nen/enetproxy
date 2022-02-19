#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include "enet/include/enet.h"
#include "http.h"
#include "server.h"

server* g_server = new server();

int main() {
#ifdef _WIN32
    SetConsoleTitleA("proxy by ama");
#endif
    printf("enet proxy by ama\n");

    // this causes seg fault on linux idk.........
#ifdef _WIN32
    std::thread http(http::run, "178.20.230.208", "17191");
    http.detach();
    printf("HTTP server is running.\n");
#endif

    enet_initialize();
    if (g_server->start()) {
        printf("Server & client proxy is running.\n");
        while (true) {
            g_server->poll();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    } else
        printf("Failed to start server or proxy.\n");
}
