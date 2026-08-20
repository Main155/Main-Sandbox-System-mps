module;
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <sstream>
#include <chrono>

export module MPS_ROOT_USER;

import ROOT;
import getline;
import clear;
import MPS;

namespace find
{
	export bool find_MPS(const std::string& find_X)
	{
		auto it_1 = MPS::ROOT_MPS.find(find_X);
		if (it_1 != MPS::ROOT_MPS.end())
		{
			std::vector<std::string> arge = { find_X };
			it_1->second(arge);
			return true;
		}
		else
		{
			std::cerr << "[ERR]\n";
			return false;
		}
	}
}
namespace Match_MPS
{
	export class Match_command_MPS
	{
	public:
		static bool command_find(const std::string& find_my)
		{
			std::istringstream iss(find_my);
			std::vector <std::string> find;
			std::string token;
			while (iss >> token)
			{
				find.push_back(token);
			}
			if (find.empty())
			{
				std::cerr << "[ERR]\n";
				return false;
			}
			auto it_x = MPS::ROOT_MPS.find(find[0]);
			if (it_x != MPS::ROOT_MPS.end())
			{
				it_x->second(find);
				return true;
			}
			auto it_y = ROOT::ROOT_MAIN.find(find[0]);
			if (it_y != ROOT::ROOT_MAIN.end())
			{
				std::cout << "Matching ROOT user operation command detected. Please enter the command to switch to the ROOT user.\n";
				return true;
			}
			return false;
		}
		~Match_command_MPS() = default;
	};
}
export bool option()
{
	std::string command;
	while (true)
	{
		if (!getline::Mygetline::M("\n[\*MPS_]Please enter a command:", command) || command.empty())
		{
			std::cerr << "Input error\n";
			continue;
		}
		if (command == "sudo su")
		{
			clear_max();
			root_main();
			continue;
		}
		if (command == "exit")
		{
			std::cout << "exit....\n";
			clear_max();
			return true;
		}
		if (find::find_MPS(command))
		{
			continue;
		}
		if (Match_MPS::Match_command_MPS::command_find(command))
		{
			continue;
		}
		std::cout << "[ERR].\n";
		continue;
	}
}
//User