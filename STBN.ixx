module;
#include <iostream>
#include <chrono>

export module STBN;
import delay;
import clear;
namespace MY_STBN
{
	export void my_STBN()
	{
		std::cout << "The system is shutting down....\n";
		delay_time d(std::chrono::seconds(3));
		clear_max();
		return;
	}
	export void Boot_up()
	{
		std::cout << "The system is booting up....\n";
		delay_time d(std::chrono::seconds(1));
		clear_max();
	}
}
//Power on and off