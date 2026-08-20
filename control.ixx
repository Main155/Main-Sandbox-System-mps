module;
#include <iostream>
#include <chrono>

export module control;

import clear;
import delay;
import password;
import FS_OPS;
import std;
import STBN;

namespace control
{
	export void  RunSystem()
	{
		MY_STBN::Boot_up();
		std::cout << "A simple main OS practical real simulation operating system based on the Windows platform\n";
		bool a = false;
		MyFunc(a);
		if (!a)
		{
			std::cout << "[ERR]Validation error！！！\n";
			delay_time d(std::chrono::seconds(25));
			clear_max();
			return;
		}
		delay_time dc(std::chrono::seconds(2));
		clear_max();
		FS_OPS();
	}
}
//Central control