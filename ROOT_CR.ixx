module;
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>

export module ROOT_CR;

import clear;
import getline;

namespace CR
{
	static bool read_line_name(const std::string& option_txt, std::string& out)
	{
		if (!getline::Mygetline::M(option_txt, out) || out.empty())
		{
			std::cerr << "[ERR]Input error\n";
			return false;
		}
		return true;
	}
	static void return_error()
	{
		std::cerr << "[ERR]Input error\n";
		return;
	}
}

namespace ROOT_CR
{
	static std::string file_name;
	static std::string input;

	std::unordered_map<std::string,
		std::function<void(const std::vector<std::string>&)>> rootoption =
	{
		{"[ROOT][CR] --help",[](const std::vector<std::string>& Mytxt_help)
		{
			std::cout << "[ERR]:\n";
			std::cout << "Please check if the agreement is valid.\n";
			std::cout << "why_?\n";
			std::cout << "File creation\n";
		}},

		{"[ROOT][CR] --open",[](const std::vector<std::string>& Mytxt_name)
		{
			if (!CR::read_line_name("Please enter the file name:",file_name))
			{
				CR::return_error();
				return;
			}
			std::ofstream open(file_name);
			if (!open.is_open())
			{
				std::cout << "Failed to create file？\n";
				return;
			}
			std::cout << "File created successfully!!!\n";
			std::cout << "Enter a command to write or delete\n";
		}},
		{"[ROOT][CR] --overwrite",[](const std::vector<std::string>& Mytxt_overwrite)
		{
			if (!CR::read_line_name("Please enter the file name to overwrite:",file_name))
			{
				CR::return_error();
				return;
			}
			if (std::filesystem::exists(file_name))
			{
				std::cout << "Warning! Overwriting files is irreversible!!!\n";
				std::cout << "Enter T to continue the operation\n";
				std::string option_T;
				if (!getline::Mygetline::M("Input:", option_T) || option_T != "T")
				{
					std::cout << "Aborted!\n";
					return;
				}
			}
			std::ofstream out(file_name, std::ios::trunc);
			if (!out.is_open())
			{
				std::cerr << "[ERR]file error\n";
				return;
			}
			while (getline::Mygetline::M("*",input))
			{
				if (input == "[CR] --end")
				{
					break;
				}
				out << input << "\n";
			}
			std::cout << "File written successfully.\n";
		}},
		{"[ROOT][CR] --append",[](const std::vector<std::string>& Mytxt_append)
		{
			if (!CR::read_line_name("Please enter the file name to append:",file_name))
			{
				CR::return_error();
				return;
			}
			if (!std::filesystem::exists(file_name))
			{
				std::cout << "[ERR]file error\n";
				return;
			}
			std::ofstream out(file_name, std::ios::app);
			if (!out.is_open()) {
				std::cerr << "[ERR]file error\n";
				return;
			}
			std::string line;
			while (getline::Mygetline::M("*", line)) {
				if (line == "[CR] --end") break;
				out << line << "\n";
			}
			std::cout << "File appended successfully.\n";
		}},
		{"[ROOT][CR] --delete",[](const std::vector<std::string>& Mytxt_delete)
		{
			if (!CR::read_line_name("Please enter the file name to delete:",file_name))
			{
				CR::return_error();
				return;
			}
			if (!std::filesystem::exists(file_name))
			{
				std::cout << "File does not exist.\n";
				return;
			}
			std::cout << "The operation is irreversible.\n";
			std::string option;
			if (!(getline::Mygetline::M("Please enter true/false:", option)))
			{
				std::cerr << "Input error\n";
				return;
			}
			std::error_code ec;
			if (option == "true")
			{
				if (!std::filesystem::remove(file_name, ec))
				{
					std::cerr << "[ERR]Delete error\n";
					return;
				}
				std::cout << "Operation successful!\n";
			}
			else if (option == "false")
			{
				std::cout << "Block success!\n";
				return;
			}
			else
			{
				std::cerr << "Please enter the correct command\n";
				return;
			}
		}},
		{ "[ROOT][CR] --read",[](const std::vector<std::string>& Mytxt_read)
		{
			if (!CR::read_line_name("Please enter the file name to read:",file_name))
			{
				CR::return_error();
				return;
			}
			if (!std::filesystem::exists(file_name)) {
				std::cout << "File does not exist.\n";
				return;
			}
			std::ifstream in(file_name);
			if (!in.is_open()) {
				std::cerr << "[ERR]Cannot open file for reading\n";
				return;
			}
			std::string line_F;
			while (std::getline(in, line_F)) {
			std::cout << line_F << "\n";
			}
		}},
	};

	export bool Myoption()
	{
		std::string ROOT_INPUT;
		while (true)
		{
			if (!getline::Mygetline::M("\n[ROOT][CR]Input option:", ROOT_INPUT))
			{
				std::cerr << "[ERR]\n";
				continue;
			}
			if (ROOT_INPUT.empty())
			{
				std::cout << "[ERR]\n";
				continue;
			}
			if (ROOT_INPUT == "[ROOT][CR] --exit")
			{
				std::cout << "[STBN][CR] --now\n";
				std::cout << "Exiting...\n";
				clear_max();
				return true;
			}
			auto it = rootoption.find(ROOT_INPUT);
			if (it != rootoption.end())
			{
				std::vector<std::string> arge = { ROOT_INPUT };
				it->second(arge);
				continue;
			}
			else
			{
				std::cerr << "[ERR].\n";
				continue;
			}
		}
	}
}
//ROOT User file operations