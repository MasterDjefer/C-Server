#include <iostream>
#include "Test.hpp"

int main()
{	
	Test::note("old time rock n roll");
	Test::step("simple number out", []()
	{
		int a = 5;
		char c = 8;
		std::cout << "a + c = " << a + c << std::endl;
	});
	const char *response = "Main page";
	Test::verify("check math question", Test::CompareData<const char*>(response, "Main page"));	
}