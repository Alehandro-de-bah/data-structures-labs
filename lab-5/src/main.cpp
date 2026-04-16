#include "testFunctions.h"

int main()
{
	try
	{
		runAllHashTableTests();
	}
	catch (const BadAllocation& error)
	{
		std::cerr << error.what() << '\n';
		return 1;
	}
	catch (const ErrorInCopying& error)
	{
		std::cerr << error.what() << '\n';
		return 1;
	}
	return 0;
}