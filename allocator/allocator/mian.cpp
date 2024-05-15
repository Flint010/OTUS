#include <iostream>
#include "allocator.h"
#include <map>
#include <string>


int main()
{

	{
		std::map<int,
			std::string,
			std::less<int>,
			my_allocator<std::pair<const int, std::string>, 10>
		> map;

		map.insert({ 1, "hi" });
		map.insert({ 2, "good" });
		map.insert({ 3, "world" });
		map.insert({ 4, "ok" });


		for (auto&& [key, value] : map) {
			std::cout << "key: " << key << " value: " << value << std::endl;
		}

		//map.get_allocator().my_deallocate();
	}


	std::cout << "Hello CMake." << std::endl;
	return 0;
}
