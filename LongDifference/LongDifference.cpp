#include "BigInt.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Required one argument: <filename>" << std::endl;
		return 1;
	}

	std::string fileName(argv[1]);
	std::fstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Unable to open file" << std::endl;
		return 1;
	}

	std::string a, b;

	file >> a >> b;
	BigUInt intA(a);
	BigUInt intB(b);

	std::cout << intA - intB << std::endl;
}