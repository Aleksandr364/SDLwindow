#include <windows.h>
#include "Global.h"

bool IntEquality(int x, int y, int d) { return x >= y - d && x <= y + d; }

// Функции для записи логов при отладке.
//***************************************
void LogDebug1(const char* message)
{
    std::wstring wmessage = std::wstring(message, message + strlen(message));
    OutputDebugString(wmessage.c_str());
    OutputDebugString(L"\n");
}
void LogDebug2(uint32_t message)
{
    std::wstring wmessage = std::to_wstring(message);
    OutputDebugString(wmessage.c_str());
    OutputDebugString(L"\n");
}

// Функция для перевода из string в int.
//***************************************
unsigned int from_str_to_uint(std::string str)
{
    try
    {
        unsigned int number = static_cast<unsigned int>(std::stoul(str));
        return number;
    }
    catch (const std::invalid_argument& e)
    {
        LogDebug1("Invalid argument: ");
        LogDebug1(e.what());
        return 0;
    }
    catch (const std::out_of_range& e)
    {
        LogDebug1("Out of range: ");
        LogDebug1(e.what());
        return 0;
    }
}