#include <iostream>
#include "allocator.h"
#include <map>
#include <string>


int main()
{
	std::map<int, 
		std::string, 
		std::less<int>,
		my_allocator<std::pair<const int, std::string>>
	> map(my_allocator<std::pair<const int, std::string>>(10));

	map[1] = "hi";
	map[2] = "good";
	map[3] = "world";
	map[4] = "ok";


	for(auto [key, value] : map) {
		std::cout << "key: " << key << " value: " << value << std::endl;
	}
	


	std::cout << "Hello CMake." << std::endl;
	return 0;
}
