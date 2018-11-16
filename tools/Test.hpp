#ifndef TEST_H
#define TEST_H
#include <iostream>
typedef void(*StepFunc)();

class Test
{
	static void printMsg(const char* const msg, const char* const type);

public:
	template<class T>
	class CompareData
	{
		T mActual;
		T mExpected;
	public:
		CompareData(T actual, T expected) : mActual(actual), mExpected(expected)
		{			
		}
		bool check()
		{
			return mActual == mExpected;
		}
	};

	static void note(const char* const msg);
	static void step(const char* const msg, StepFunc f);

	template<class T>
	static void verify(const char* const msg, Test::CompareData<T> obj)
	{
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << "Verify\t|" << (obj.check() ? "PASSED" : "FAILED") << "\t|" << msg << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
	}
};
#endif