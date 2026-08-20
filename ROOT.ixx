module;
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <Windows.h>

export module ROOT;

import ROOT_CR;
import getline;
import clear;
import MPS;

namespace ROOT
{
	export std::unordered_map<std::string,
		std::function<void(std::vector<std::string>&)>> ROOT_MAIN =
	{
		{"sudo su",[](const std::vector<std::string>&)
		{
		   std::cout << "[ROOT]\n";
		}},
		{"[ROOT][CR]",[](const std::vector<std::string>&)
		{
			ROOT_CR::Myoption();
		}},
		{"[ROOT] --sysinfo", [](const std::vector<std::string>&)
		{
			MEMORYSTATUSEX memInfo;
			memInfo.dwLength = sizeof(memInfo);
			GlobalMemoryStatusEx(&memInfo);
			std::cout << "Total RAM: " << memInfo.ullTotalPhys / 1024 / 1024 << " MB\n";
			std::cout << "Available RAM: " << memInfo.ullAvailPhys / 1024 / 1024 << " MB\n";

			SYSTEM_INFO sysInfo;
			GetSystemInfo(&sysInfo);
			std::cout << "Processors: " << sysInfo.dwNumberOfProcessors << "\n";
		}},

		{"[ROOT] --kill", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: kill <pid>\n";
				return;
			}
			DWORD pid = std::stoul(args[1]);
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
			if (hProcess)
			{
				TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
				std::cout << "Process " << pid << " terminated\n";
			}
			else
			{
			std::cerr << "Error: cannot open process " << pid << "\n";
			}
		}},
	};
}
namespace Match_ROOT
{
	export class Match_command_ROOT
	{
	public:
		static bool command_find(const std::string& MAIN_ROOT_FIND)
		{
			std::istringstream iss(MAIN_ROOT_FIND);
			std::vector <std::string> find_ro;
			std::string token;
			while (iss >> token)
			{
				find_ro.push_back(token);
			}
			if (find_ro.empty())
			{
				std::cerr << "[ERR]\n";
				return false;
			}
			auto it_rx = ROOT::ROOT_MAIN.find(find_ro[0]);
			if (it_rx != ROOT::ROOT_MAIN.end())
			{
				it_rx->second(find_ro);
				return true;
			}
			auto it_ry = MPS::ROOT_MPS.find(find_ro[0]);
			if (it_ry != MPS::ROOT_MPS.end())
			{
				it_ry->second(find_ro);
				return true;
			}
			return false;
		}
		~Match_command_ROOT() = default;
	};
}
export bool root_main()
{
	while (true)
	{
		std::string a;
		if (!getline::Mygetline::M("\n[ROOT]Input option:", a))
		{
			std::cerr << "[ERR]";
			continue;
		}
		if (a == "[ROOT] --exit")
		{
			clear_max();
			return true;
		}
		auto it_1 = ROOT::ROOT_MAIN.find(a);
		if (it_1 != ROOT::ROOT_MAIN.end())
		{
			std::vector<std::string> arge = { a };
			it_1->second(arge);
			continue;
		}
		if (Match_ROOT::Match_command_ROOT::command_find(a))
		{
			continue;
		}
		std::cout << "[ERR]\n";
		continue;
	}
}
//ROOT User