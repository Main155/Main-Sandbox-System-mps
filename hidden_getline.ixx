
module;
#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>

export module hidden_input;
import getline;

export namespace Input_f
{
    std::string get_hidden()
    {
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        DWORD old_mode;
        GetConsoleMode(hIn, &old_mode);
        SetConsoleMode(hIn, old_mode & (~ENABLE_ECHO_INPUT));
        std::string result;
        std::getline(std::cin, result);
        SetConsoleMode(hIn, old_mode);
        std::cout << "\n";
        return result;
    }
    std::string get_hidden_stars()
    {
        std::string result;
        char ch;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b') {
                if (!result.empty())
                {
                    result.pop_back();
                    std::cout << "\b \b";
                }
            }
            else if (ch >= 32 && ch <= 126)
            {
                result.push_back(ch);
                std::cout << '*';
            }
        }
        std::cout << "\n";
        return result;
    }
    std::string get_visible()
    {
        std::string result;
        if (!getline::Mygetline::M("*", result))
        {
            std::cerr << "[ERR]\n";
            return "";
        }
        return result;
    }
}
//Return to hidden