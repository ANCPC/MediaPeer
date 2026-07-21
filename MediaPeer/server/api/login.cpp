#include "login.h"

#include "../auth/login.h"

#include <string>

std::string ApiLogin(
    const std::string& body)
{
    std::string username;
    std::string password;

    auto u=body.find("\"username\":\"");

    if(u!=std::string::npos)
    {
        u+=12;
        auto e=body.find("\"",u);
        username=body.substr(u,e-u);
    }

    auto p=body.find("\"password\":\"");

    if(p!=std::string::npos)
    {
        p+=12;
        auto e=body.find("\"",p);
        password=body.substr(p,e-p);
    }

    if(AuthLogin(username,password))
    {
        return R"({"success":true,"message":"Welcome admin"})";
    }

    return R"({"success":false,"message":"Invalid username or password"})";
}