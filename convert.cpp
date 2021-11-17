#include <iostream>
#include <string>
#include <unordered_map>

class NFA
{

	int n; 																											// Total number of states (0, 1, ..., n - 1)
	int a; 																											// Final Accept State
	std::unordered_map<std::pair<int, char>, int> transition; 	// Transition Function
public:
	NFA();
	~NFA();



};

void convert(string regex) {
}

int main(int argc, char const *argv[])
{
	std::cout << "Enter regex" << std::endl;

	std::string regex;
	std::cin >> regex;

	convert(regex);


	return 0;
}