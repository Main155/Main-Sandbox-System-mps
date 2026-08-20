module;
#include <Windows.h>
#include <cstdlib>
#include <chrono>

export module clear;
import delay;
namespace clear
{
    bool ClearScreen()
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

        if (hStdOut == INVALID_HANDLE_VALUE || hStdOut == NULL)
        {
            return false;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            return false;
        }

        COORD coord = { 0, 0 };
        DWORD count;

        FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
        return true;
    }
    void clear_two()
    {
        system("cls");
    }
    export class ScopedClearer
    {
    private:
        std::chrono::milliseconds delay_;
    public:
        explicit ScopedClearer(std::chrono::milliseconds delay = std::chrono::milliseconds(0)) noexcept
            : delay_(delay) {
        }
        ~ScopedClearer() noexcept
        {

            if (delay_ > std::chrono::milliseconds(0))
            {

                delay_time(static_cast<int>(delay_.count()));
            }

            if (!ClearScreen()) clear_two();
        }

        ScopedClearer(const ScopedClearer&) = delete;
        ScopedClearer& operator=(const ScopedClearer&) = delete;
    };
}

export void clear_max()
{
    if (!clear::ClearScreen())
    {
        clear::clear_two();
    }
}
//Clear screen
