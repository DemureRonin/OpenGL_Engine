#pragma once

class ConsoleDebug
{
    public:
    static void PrintFileError(const char* actor, const char* file, const char* message);
    static void PrintDirectoryError(const char* actor, const char* directory, const char* message);
    static void PrintFallback(const char* actor);
    static void PrintError(const char* actor, const char* message);
    static void PrintMessage(const char* actor, const char* message); 
};


