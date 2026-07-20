#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#pragma comment(lib,"ws2_32.lib")

const int PORT = 8080;

std::string readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
        return "<h1>404 - File Not Found</h1>";

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main()
{
    WSADATA wsa;

    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET)
    {
        std::cout << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if(bind(serverSocket,
            (sockaddr*)&serverAddr,
            sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "Bind failed\n";

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    listen(serverSocket, 10);

    std::cout << "=====================================\n";
    std::cout << "        MediaPeer Server\n";
    std::cout << "=====================================\n";
    std::cout << "Listening on:\n";
    char hostname[256];
gethostname(hostname, sizeof(hostname));

hostent* host = gethostbyname(hostname);

if (host)
{
    std::cout << "http://"
              << inet_ntoa(*(in_addr*)host->h_addr_list[0])
              << ":8080\n";
}
else
{
    std::cout << "http://127.0.0.1:8080\n";
}
    std::cout << "=====================================\n\n";

    while (true)
    {
        sockaddr_in client;
        int clientSize = sizeof(client);

        SOCKET clientSocket = accept(
            serverSocket,
            (sockaddr*)&client,
            &clientSize);

        if (clientSocket == INVALID_SOCKET)
            continue;

        char request[4096] = {0};

        int received = recv(
            clientSocket,
            request,
            sizeof(request) - 1,
            0);

        if (received <= 0)
        {
            closesocket(clientSocket);
            continue;
        }

        std::cout << "=========================\n";
        std::cout << "Client: "
                  << inet_ntoa(client.sin_addr)
                  << "\n";
        std::cout << request << "\n";

        std::string html =
            readFile("website/pages/login/login.html");

        if (html == "<h1>404 - File Not Found</h1>")
        {
            html =
            "<!DOCTYPE html>"
            "<html>"
            "<body>"
            "<h1>MediaPeer</h1>"
            "<p>login.html not found.</p>"
            "</body>"
            "</html>";
        }

        std::ostringstream response;

        response
            << "HTTP/1.1 200 OK\r\n"
            << "Server: MediaPeer\r\n"
            << "Content-Type: text/html; charset=UTF-8\r\n"
            << "Content-Length: " << html.size() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << html;

        std::string data = response.str();

        send(
            clientSocket,
            data.c_str(),
            (int)data.size(),
            0);

        shutdown(clientSocket, SD_SEND);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);

    WSACleanup();

    return 0;
}