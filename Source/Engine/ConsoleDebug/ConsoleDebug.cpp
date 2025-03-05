#include "ConsoleDebug.h"

#include <iostream>
#include <ostream>

#include "DebugUtils.h"

void ConsoleDebug::PrintFileError(const char* actor, const char* file, const char* message = "")
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ":" << " Could not open file:" << file << "; " << message <<
        CONSOLE_COLOR_RESET << '\n';
}

void ConsoleDebug::PrintError(const char* actor, const char* message = "")
{
    std::cerr << CONSOLE_COLOR_RED "Error: " << actor << ":" << "; " << message <<
        CONSOLE_COLOR_RESET << '\n';
}


void ConsoleDebug::PrintMessage(const char* actor, const char* message)
{
    std::cout << CONSOLE_COLOR_BLUE "Message: " << actor << ":" << " " << message << CONSOLE_COLOR_RESET << '\n';
}
