#include "login.h"
#include "password.h"

bool AuthLogin(
    const std::string& username,
    const std::string& password)
{
    if(username!="admin")
        return false;

    std::string storedHash=
        HashPassword("Creature123");

    return VerifyPassword(
        password,
        storedHash);
}