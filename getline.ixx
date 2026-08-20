module;
#include <iostream>
#include <string>
#include <limits>

export module getline;

namespace getline
{
	export class Mygetline
	{
	public:
		static bool M(const std::string& out, std::string& gl)
		{
			std::cout << out;
			if (!std::getline(std::cin, gl))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			return true;
		}
	};
}
namespace clear_getline
{
	export class input_clear {
	public:
		input_clear() noexcept
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		~input_clear() noexcept = default;
		input_clear(const input_clear&) = delete;
		input_clear& operator=(const input_clear&) = delete;
	};
}
namespace getline_math
{
	export bool A(const std::string& out_input, auto& num)
	{
		std::cout << out_input;
		if (!(std::cin >> num))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		std::cin.ignore();
		return true;
	}
}
//Processing input