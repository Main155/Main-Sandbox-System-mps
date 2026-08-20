module;

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

export module password;
import getline;
import clear;
import delay;
import std;
import hidden_input;

constexpr int input_max = 5;
namespace my_log
{
	static void log()
	{
		std::cout << "  Entering system.... || passworld....\n";
		std::cout << "           main.cpp...open..\n";
		std::cout << "============MAIN_PASSWORLD============\n";
		std::cout << "        [OK]...passworld[now]\n";
	}
}
namespace hash_util
{
	static std::string hash(const std::string& password) {
		std::string salt = "root_cr_salt";
		size_t h = std::hash<std::string>{}(salt + password);
		std::ostringstream oss;
		oss << std::hex << h;
		return oss.str();
	}
	static bool verify(const std::string& input, const std::string& stored_hash) {
		return hash(input) == stored_hash;
	}
}

namespace PIN
{

	class myclass_PIN
	{
	private:
		std::string help_PIN;
		std::string input_PIN;
		std::string input_newPIN;
		std::string y = "123456";
		std::string_view name = "password.bin";
		bool load_pin()
		{
			std::ifstream in(name.data());
			if (!in.is_open())
			{
				y = hash_util::hash("123456");
				std::ofstream out(name.data(), std::ios::trunc);
				out << hash_util::hash("123456");
				return true;
			}
			std::getline(in, y);
			return true;
		}
	public:
		myclass_PIN()
		{
			load_pin();
		}
		std::string input_help = "Help";
		bool fallout_password()
		{

			for (int i = 0;i < input_max;++i)
			{
				std::cout << "password_";
				std::string input_PIN = Input_f::get_hidden_stars();
				if (hash_util::verify(input_PIN, y))
				{
					std::cout << "Password correct！！!\n";
					delay_time d(std::chrono::milliseconds(2));
					clear_max();
					return true;
				}
				std::cout << "[HELP]Incorrect password!!! --- Input => Help <= to open help,\n";
				if (input_PIN == input_help)
				{
					std::cerr << "[ERR]If the system or codebook is abnormal, or if you are registering a new account, please enter the original password.\n";
					std::cout << "Re-enter password:";
				}
			}
			std::cout << "Re-enter password:";
			return false;
		}
		bool Mypassword()
		{
			if (!(fallout_password()))
			{
				std::cerr << "Password verification seems to have encountered a slight issue?\n";
				return false;
			}
			for (int retry = 0; retry < input_max; ++retry)
			{
				std::cout << "Please enter a 6-12 digit password\n";
				std::cout << "new_";
				std::string input_newPIN = Input_f::get_hidden_stars();
				if (input_newPIN.size() < 6 || input_newPIN.size() > 12)
				{
					std::cerr << "[ERR]Please enter a 6-12 digit password!!!\n";
					continue;
				}
				std::ofstream open(name.data(), std::ios::trunc);
				if (!open)
				{
					std::cerr << "[ERR]Is there a problem with the password file?";
					return false;
				}
				open << hash_util::hash(input_newPIN);
				y = hash_util::hash(input_newPIN);
				std::cout << "Modification successful!!!\n";
				delay_time d(std::chrono::seconds(2));
				clear_max();
				return true;
			}
			std::cout << "[ERR]\n";
			return false;
		}

		~myclass_PIN() = default;
	};
}
export void MyFunc(bool& success)
{
	success = false;
	PIN::myclass_PIN in;
	std::string input;
	std::string one = "Input password";
	std::string two = "Change password";
	std::cout << "\n================== welcome to main OS =================== \n";
	std::cout << "\nPlease enter =>Input password<= or =>Change password<= to perform the desired operation\n";
	while (true)
	{
		if (!getline::Mygetline::M("command:", input))
		{
			std::cerr << "[ERR]Input error\n";
			continue;
		}
		if (input == one)
		{
			std::cout << "Please enter the password\n";
			if (in.fallout_password())
			{
				my_log::log();
				delay_time d(std::chrono::seconds(2));
				success = true;
				return;
			}
			std::cout << "Validation failed\n";
			continue;
		}
		else if (input == two)
		{
			std::cout << "Successfully changed password, automatically entering the system_\n";
			std::cout << "Please enter the original password:";
			if (in.Mypassword())
			{
				my_log::log();
				delay_time d(std::chrono::seconds(2));
				success = true;
				return;
			}
			std::cout << "Failed to change password\n";
			continue;
		}
		else
		{
			std::cerr << "[ERR]Please enter the correct command!!!\n";
			continue;
		}
	}
}
//Password verification