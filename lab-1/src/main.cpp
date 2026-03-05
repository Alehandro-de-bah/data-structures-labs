#include "Vector.h"
#include "functions.h"
#include "A.h"
#include <vector>

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

int A::count_ = 0;

int main()
{
	setlocale(LC_ALL, "RU");
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try
	{
		testVector();
		testVectorWithClassA();
		testSorting();
		/*
		* Возможные утечки памяти можно обнаружить, использовав встроенные средства VS (как указано выше).
		* В ОС GNU\Linux можно использовать утилиту valgrind:
		* 1) Собираем проект (например, с помощью компилятора GCC)
		* g++ *.cpp *.h
		* 2) Запускаем исполняемую программу под valgrind'ом:
		* valgrind ./a.out
		* Получаем примерно такой вывод в консоли
		* HEAP SUMMARY:
		      in use at exit: 0 bytes in 0 blocks
		      total heap usage: 104 allocs, 104 frees, 85,682 bytes allocated
		      All heap blocks were freed -- no leaks are possible
		*/
	}
	catch (const std::bad_alloc& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << ERROR_SOMETHING_WENT_WRONG << std::endl;
		return 1;
	}
	return 0;
}