#include "ConsoleDebug.h"

#include <iostream>
#include <ostream>

#include "DebugUtils.h"

void ConsoleDebug::PrintFileError(const char* actor, const char* file, const char* message = "")
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ":" << " Could not open file:" << file << message <<
        CONSOLE_COLOR_RESET << '\n';
}

void ConsoleDebug::PrintDirectoryError(const char* actor, const char* directory, const char* message = "")
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ":" << " Directory does not exist:" << directory <<
        message <<
        CONSOLE_COLOR_RESET << '\n';
}

void ConsoleDebug::PrintFallback(const char* actor)
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ":" << " Falling back to default" << CONSOLE_COLOR_RESET <<'\n';
}


void ConsoleDebug::PrintError(const char* actor, const char* message = "")
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ": " << message <<
        CONSOLE_COLOR_RESET << '\n';
}


void ConsoleDebug::PrintMessage(const char* actor, const char* message)
{
    std::cout << CONSOLE_COLOR_BLUE "Message: " << actor << ":" << " " << message << CONSOLE_COLOR_RESET << '\n';
}
