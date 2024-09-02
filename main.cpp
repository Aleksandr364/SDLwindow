#include "SDL.h"

#define WINDOWS_OS

#ifdef WINDOWS_OS
int WinMain()
#else
int main()
#endif
{
    Main_Window();
    return 0;
}