module;
#include <iostream>
#include <string>
export module FS_OPS;

import clear;
import STBN;
import MPS_ROOT_USER;
import std;
import getline;

namespace root
{
	class My_OPS
	{
	private:
		std::string My_input;
		std::string input_LS = "LS";
		std::string input_STBN = "STBN";
	public:
		~My_OPS() = default;
		bool input(const std::string& option_m)
		{
			if (option_m == input_LS)
			{
				clear_max();
				if (!option())
				{
					std::cout << "[ERR]\n";
					return false;
				}
				return true;
			}
			else
			{
				std::cerr << "[ERR]Input error\n";;
				return false;
			}
		}
		bool My_option()
		{
			while (true)
			{
				std::cout << "--->~Menu bar=============\n";
				std::cout << "———————————\n";
				std::cout << "[\*MPS_]   LS     Terminal operation\n";
				std::cout << "[STBN]    STBN    Shutdown\n";
				if (!getline::Mygetline::M("Input option:", My_input))
				{
					std::cerr << "[ERR]Input error\n";
					continue;
				}
				if (My_input == input_STBN)
				{
					clear_max();
					return true;
				}
				if (input(My_input))
				{
					continue;
				}
				clear_max();
				continue;
			}
		}
	};
}
export void FS_OPS()
{
	root::My_OPS open;
	open.My_option();
}
//Action Center