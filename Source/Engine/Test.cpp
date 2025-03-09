#include "Test.h"
#include <filesystem>
#include <iostream>

void Test::PrintFilePath()
{
    std::filesystem::path exePath = std::filesystem::current_path();

    std::cout << exePath << std::endl;
}
