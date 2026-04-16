#include "BinarySearchTree.h"
#include "BinarySearchTreeExceptions.h"
#include "testFunctions.h"

int main()
{
	try
	{
		runAllTests();
	}
	catch (const InvalidRange& error)
	{
		std::cerr << error.what() << '\n';
		return 1;
	}
	catch (const BadAllocationInInsert& error)
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