module;
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include <algorithm>
#include <chrono>
#include <fstream>

export module MPS;

import clear; 
import delay;
import getline;

namespace MPS
{
	export std::unordered_map<std::string,
		std::function<void(std::vector<std::string>&)>> ROOT_MPS =
	{
		{"mkdir", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: mkdir <dirname>\n";
				return;
			}
			std::error_code ec;
			if (std::filesystem::create_directory(args[1], ec))
			{
			   std::cout << "Directory created: " << args[1] << "\n";
			}
			else
			{
				std::cerr << "Error: " << ec.message() << "\n";
			}
		}},

		{"ls",[](const std::vector<std::string>&)
		{
			for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
			{
			   std::cout << entry.path().filename().string() << "\n";
			}
		}},

		{"pwd", [](const std::vector<std::string>&)
		{
			std::error_code ec;
			auto path = std::filesystem::current_path(ec);
			if (ec)
			{
				std::cerr << "Error: " << ec.message() << "\n";
				return;
			}
			std::cout << path.string() << "\n";
		}},

		{"help", [](const std::vector<std::string>&)
		{
			std::cout << "Available commands:\n";
			std::cout << "  mkdir <dir>  - Create directory\n";
			std::cout << "  ls           - List files\n";
			std::cout << "  pwd          - Show current path\n";
			std::cout << "  touch <file> - Create empty file\n";
			std::cout << "  cat <file>   - Show file content\n";
			std::cout << "  rm <file>    - Remove file\n";
			std::cout << "  rmdir <dir>  - Remove empty directory\n";
			std::cout << "  cd <path>    - Change directory\n";
			std::cout << "  echo <text>  - Print text\n";
			std::cout << "  whoami       - Show current user\n";
			std::cout << "  date         - Show current date\n";
			std::cout << "  cls          - Clear screen\n";
			std::cout << "  sleep <s>    - Sleep for seconds\n";
			std::cout << "/*MPS*/_*\n";
		}},

		{"cls",[](const std::vector<std::string>&)
		{
			clear_max();
		}},

		{"sleep",[](const std::vector<std::string>&)
		{
			std::unique_ptr<int> time = std::make_unique<int>();
			if (!getline_math::A("Please enter sleep lock time (s):",*time))
			{
				std::cerr << "[ERR]Exception\n";
			}
			delay_time(std::chrono::seconds(*time));
		}},

		{"touch", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: touch <filename>\n";
				return;
			}
			std::ofstream(args[1]).close();
			std::cout << "File created: " << args[1] << "\n";
		}},

		{"cd", [](const std::vector<std::string>& args)
		{
		   if (args.size() < 2) {
		   std::cerr << "Usage: cd <path>\n";
		   return;
		}
		   std::error_code ec;
		   std::filesystem::current_path(args[1], ec);
		   if (ec)
		   {
			   std::cerr << "Error: " << ec.message() << "\n";
		   }
		   else
		   {
			   std::cout << "Changed directory to: " << args[1] << "\n";
		   }
		}},

		{"cat", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: cat <filename>\n";
				return;
			}
			std::ifstream file(args[1]);
			if (!file)
			{
				std::cerr << "Error: cannot open " << args[1] << "\n";
				return;
			}
			std::string line;
			while (std::getline(file, line))
			{
				std::cout << line << "\n";
			}
		}},

		{"rm", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: rm <filename>\n";
				return;
			}
			std::error_code ec;
			if (std::filesystem::remove(args[1], ec))
			{
				std::cout << "Removed: " << args[1] << "\n";
			}
			else
			{
				std::cerr << "Error: " << ec.message() << "\n";
			}
		}},

		{"rmdir", [](const std::vector<std::string>& args)
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: rmdir <dirname>\n";
				return;
			}
			std::error_code ec;
			if (std::filesystem::remove(args[1], ec))
			{
				std::cout << "Directory removed: " << args[1] << "\n";
			}
			else
			{
				std::cerr << "Error: " << ec.message() << "\n";
			}
		}},

		{"echo", [](const std::vector<std::string>& args)
		{
			for (size_t i = 1; i < args.size(); ++i)
			{
				std::cout << args[i] << " ";
			}
		   std::cout << "\n";
		}},

		{"whoami", [](const std::vector<std::string>&)
		{
			std::cout << "mps\n";
		}},

		{ "date", [](const std::vector<std::string>&)
		{
			auto now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(now);
			char buffer[26];
			ctime_s(buffer, sizeof(buffer), &time);
			std::cout << buffer;
		}},
	};
}
//Regular user