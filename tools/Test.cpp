#include "Test.hpp"

void Test::printMsg(const char* const msg, const char* const type)
{
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << type << "\t|" << msg << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
}
void Test::note(const char* const msg)
{		
	printMsg(msg, "Note");
}
void Test::step(const char* const msg, StepFunc f)
{		
	printMsg(msg, "Step");
	f();
}