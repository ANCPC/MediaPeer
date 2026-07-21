#include "server.h"
#include "api/login.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string Server::readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
        return "";

    std::stringstream ss;

    ss << file.rdbuf();

    return ss.str();
}

std::string Server::getRouteFile(const std::string& route)
{
    if(route=="/")
        return "website/pages/login/login.html";

    if(route=="/login")
        return "website/pages/login/login.html";

    if(route.rfind("/css/",0)==0)
        return "website"+route;

    if(route.rfind("/js/",0)==0)
        return "website"+route;

    return "";
}

std::string Server::getContentType(const std::string& file)
{
    if(file.find(".html")!=std::string::npos)
        return "text/html";

    if(file.find(".css")!=std::string::npos)
        return "text/css";

    if(file.find(".js")!=std::string::npos)
        return "application/javascript";

    return "text/plain";
}

void Server::handleClient(
    SOCKET clientSocket,
    sockaddr_in client)
{
    char buffer[8192]={0};

    int received=
        recv(
            clientSocket,
            buffer,
            sizeof(buffer)-1,
            0);

    if(received<=0)
    {
        closesocket(clientSocket);
        return;
    }

    std::string request(buffer);

    std::string route="/";

    size_t a=request.find(' ');
    size_t b=request.find(' ',a+1);

    if(a!=std::string::npos &&
       b!=std::string::npos)
    {
        route=request.substr(a+1,b-a-1);
    }

    std::string body;

    size_t bodyStart=
        request.find("\r\n\r\n");

    if(bodyStart!=std::string::npos)
    {
        body=request.substr(bodyStart+4);
    }

    std::cout
        <<inet_ntoa(client.sin_addr)
        <<" "
        <<route
        <<std::endl;

    //--------------------------------------------------
    // LOGIN API
    //--------------------------------------------------

    if(route=="/api/login")
    {
        std::string json=
            ApiLogin(body);

        std::stringstream response;

        response
        <<"HTTP/1.1 200 OK\r\n";

        response
        <<"Content-Type: application/json\r\n";

        response
        <<"Content-Length: "
        <<json.size()
        <<"\r\n";

        response
        <<"Connection: close\r\n\r\n";

        response<<json;

        std::string data=response.str();

        send(
            clientSocket,
            data.c_str(),
            (int)data.size(),
            0);

        closesocket(clientSocket);
        return;
    }

    //--------------------------------------------------
    // STATIC FILES
    //--------------------------------------------------

    std::string file=getRouteFile(route);

    std::string page;

    std::string status;

    if(file.empty())
    {
        status="404 Not Found";
        page="<h1>404 Not Found</h1>";
    }
    else
    {
        page=readFile(file);

        if(page.empty())
        {
            status="404 Not Found";
            page="<h1>File Missing</h1>";
        }
        else
        {
            status="200 OK";
        }
    }

    std::stringstream response;

    response
    <<"HTTP/1.1 "
    <<status
    <<"\r\n";

    response
    <<"Content-Type: "
    <<getContentType(file)
    <<"\r\n";

    response
    <<"Content-Length: "
    <<page.size()
    <<"\r\n";

    response
    <<"Connection: close\r\n\r\n";

    response<<page;

    std::string data=response.str();

    send(
        clientSocket,
        data.c_str(),
        (int)data.size(),
        0);

    closesocket(clientSocket);
}

void Server::run(int port)
{
    WSADATA wsa;

    WSAStartup(
        MAKEWORD(2,2),
        &wsa);

    SOCKET serverSocket=
        socket(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP);

    sockaddr_in addr;

    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);

    bind(
        serverSocket,
        (sockaddr*)&addr,
        sizeof(addr));

    listen(serverSocket,10);

    std::cout<<"========================\n";
    std::cout<<"MediaPeer Server\n";
    std::cout<<"http://127.0.0.1:"<<port<<"\n";
    std::cout<<"========================\n";

    while(true)
    {
        sockaddr_in client;

        int size=sizeof(client);

        SOCKET clientSocket=
        accept(
            serverSocket,
            (sockaddr*)&client,
            &size);

        if(clientSocket==INVALID_SOCKET)
            continue;

        handleClient(
            clientSocket,
            client);
    }

    closesocket(serverSocket);

    WSACleanup();
}