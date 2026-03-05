#include "functions.h"
#include "A.h"

#include <cassert>
#include <ctime>

void testVector()
{
	std::cout << "===== Тестирование класса Vector =====" << std::endl;
	// 1. Создание векторов разными способами
	Vector<int> vIntegers1;
	Vector<double> vDouble(5);
	Vector<int> vIntegers2(4, 1);
	Vector<int> vIntegers3 = vIntegers1;

	// 2. Добавление элементов
	vIntegers1.push_back(10);
	vIntegers1.push_back(20);
	vIntegers1.push_back(30);
	vIntegers2.push_back(200);

	// 3. Доступ к элементам
	std::cout << "Первый элемент: " << vIntegers1[0] << std::endl;
	std::cout << "Последний элемент: " << vIntegers1.back() << std::endl;

	// 4. Безопасный доступ (с проверкой границ)
	try
	{
		std::cout << "Элемент по индексу 2: " << vIntegers1.at(2) << std::endl;
		// std::cout << vIntegers1.at(10) << std::endl; // выбросит исключение
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}

	// 5. Итерация по вектору
	std::cout << "\nВсе элементы: ";
	for (size_t i = 0; i < vIntegers1.size(); ++i) {
		std::cout << vIntegers1[i] << " ";
	}
	std::cout << std::endl;

	// 8. Размер и емкость
	std::cout << "\nРазмер: " << vIntegers1.size() << std::endl;
	std::cout << "Емкость: " << vIntegers1.capacity() << std::endl;
	std::cout << "Пуст ли?: " << (vIntegers1.empty() ? "Да" : "Нет") << std::endl;

	assert(vIntegers1.size() == 3);

	// 9. Удаление элементов
	vIntegers1.pop_back();  // удаляем последний
	std::cout << "\nРазмер после удаления: " << vIntegers1.size() << std::endl;

	// 10. Очистка
	vIntegers1.clear();
	std::cout << "\nПосле clear(): размер = " << vIntegers1.size() << std::endl << std::endl;
}

void testVectorWithClassA()
{
	std::cout << "===== Тестирование класса Vector с объектами класса A =====" << std::endl;
	// 1. Создание векторов
	Vector<A> v1;
	Vector<A> v2(5);
	A ob(7);
	Vector<A> v3(4, ob);
	Vector<A> v4(3, A(8));

	// 2. Операторы присваивания
	v1 = v2;
	v3 = Vector<A>(2);

	// 3. Доступ к элементам
	A firstInV1 = v1[0];
	A firstInV2 = v2.at(0);
	A firstInV3 = v3.front();
	A lastInV4 = v4.back();

	// 4. Вставка элементов
	v1.push_back(ob);
	v1.push_back(A(15));
	v2.insert(0, ob);
	v2.insert(1, A(20));

	// 5. Удаление элементов
	v3.pop_back();
	v3.clear();
	v1.erase(1);
	v2.erase(0, v2.size());

	// 6. Изменение размера
	v1.resize(8);
	v3.resize(10, ob);
	v2.reserve(12);
	v4.shrink_to_fit();

	// 7. Информация о состоянии
	size_t sizeOfV1 = v1.size();
	size_t capacityOfV1 = v1.capacity();
	bool isEmptyV2 = v2.empty();
}

void testSorting()
{
	std::cout << "===== Тестирование сортировки вставками =====" << std::endl;
	std::cout << "1) Сортировка для пустого вектора" << std::endl;
	Vector<int> v1;
	std::cout << "Вектор v1 до сортировки: v1 = " << (v1.empty() ? "{}" : "") << std::endl;
	std::cout << "Сортируем вектор v1..." << std::endl;
	insertionSort(v1);
	std::cout << "Вектор v1 после сортировки: v1 = " << (v1.empty() ? "{}" : "") << std::endl;
	std::cout << "Вектор v1 отсортирован? " << (isSorted(v1) ? "Да" : "Нет") << std::endl << std::endl;

	std::cout << "2) Сортировка для вектора, отсортированного в обратном порядке" << std::endl;
	Vector<int> v2;
	v2.push_back(20);
	v2.push_back(17);
	v2.push_back(12);
	v2.push_back(6);
	v2.push_back(1);
	std::cout << "Вектор v2 до сортировки: v2 = { ";
	for (size_t i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Сортируем вектор v2..." << std::endl;
	insertionSort(v2);
	std::cout << "Вектор v2 после сортировки: v2 = { ";
	for (size_t i = 0; i < v2.size(); i++)
	{
		std::cout << v2[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Вектор v2 отсортирован? " << (isSorted(v2) ? "Да" : "Нет") << std::endl << std::endl;

	std::cout << "3) Сортировка для уже отсортированного вектора" << std::endl;
	Vector<int> v3;
	v3.push_back(3);
	v3.push_back(9);
	v3.push_back(19);
	v3.push_back(27);
	v3.push_back(44);
	std::cout << "Вектор v3 до сортировки: v3 = { ";
	for (size_t i = 0; i < v3.size(); i++)
	{
		std::cout << v3[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Сортируем вектор v3..." << std::endl;
	insertionSort(v3);
	std::cout << "Вектор v3 после сортировки: v3 = { ";
	for (size_t i = 0; i < v3.size(); i++)
	{
		std::cout << v3[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Вектор v3 отсортирован? " << (isSorted(v3) ? "Да" : "Нет") << std::endl << std::endl;

	std::cout << "4) Сортировка вектора co случайными элементами" << std::endl;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Vector<int> v4(6);
	for (size_t i = 0; i < v4.size(); i++)
	{
		v4[i] = std::rand() % 50;
	}
	std::cout << "Вектор v4 до сортировки: v4 = { ";
	for (size_t i = 0; i < v4.size(); i++)
	{
		std::cout << v4[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Сортируем вектор v4..." << std::endl;
	insertionSort(v4);
	std::cout << "Вектор v4 после сортировки: v4 = { ";
	for (size_t i = 0; i < v4.size(); i++)
	{
		std::cout << v4[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Вектор v4 отсортирован? " << (isSorted(v4) ? "Да" : "Нет") << std::endl << std::endl;

	std::cout << "5) Сортировка вектора, состоящего из строк" << std::endl;
	Vector<std::string> v5;
	v5.push_back("hello");
	v5.push_back("abc");
	v5.push_back("c++");
	v5.push_back("world");
	v5.push_back("number");
	std::cout << "Вектор v5 до сортировки: v5 = { ";
	for (size_t i = 0; i < v5.size(); i++)
	{
		std::cout << v5[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Сортируем вектор v5..." << std::endl;
	insertionSort(v5);
	std::cout << "Вектор v5 после сортировки: v5 = { ";
	for (size_t i = 0; i < v5.size(); i++)
	{
		std::cout << v5[i] << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "Вектор v5 отсортирован? " << (isSorted(v5) ? "Да" : "Нет") << std::endl << std::endl;
}