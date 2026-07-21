#include "password.h"

#include <functional>

std::string HashPassword(const std::string& password)
{
    std::hash<std::string> hasher;

    return std::to_string(
        hasher(password));
}

bool VerifyPassword(
    const std::string& password,
    const std::string& hash)
{
    return HashPassword(password)==hash;
}