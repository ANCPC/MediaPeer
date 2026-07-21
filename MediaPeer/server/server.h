#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>

#pragma comment(lib,"ws2_32.lib")

class Server
{
public:

    void run(int port);

private:

    std::string readFile(const std::string& filename);

    std::string getRouteFile(const std::string& route);

    std::string getContentType(const std::string& filename);

    void handleClient(
        SOCKET clientSocket,
        sockaddr_in client);

};