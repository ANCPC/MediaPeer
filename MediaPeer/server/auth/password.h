#pragma once

#include <string>

std::string HashPassword(const std::string& password);

bool VerifyPassword(
    const std::string& password,
    const std::string& hash);