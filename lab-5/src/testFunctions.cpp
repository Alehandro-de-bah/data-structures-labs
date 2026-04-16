#include "testFunctions.h"

void testHTDefaultConstructor()
{
	// Создаём таблицу без указания размера
	HT<String> ht1;
	size_t ht1Size = ht1.getTableSize();
	assert(ht1.getCollisionsNumber() == 0);
	assert(ht1.getElementsNumber() == 0);
	assert(ht1Size == 31);
	std::cout << "Constructor HashTable(): size of table = " << ht1Size << '\n';

	// Создаём таблицу с указанием размера (простое число)
	HT<String> ht2(7);
	size_t ht2Size = ht2.getTableSize();
	assert(ht2.getCollisionsNumber() == 0);
	assert(ht2.getElementsNumber() == 0);
	assert(ht2Size == 7);
	std::cout << "Constructor HashTable(7): size of table = " << ht2Size << '\n';

	// Создаём таблицу с указанием размера (составное число)
	HT<String> ht3(24);
	size_t ht3Size = ht3.getTableSize();
	assert(ht3.getCollisionsNumber() == 0);
	assert(ht3.getElementsNumber() == 0);
	assert(ht3Size == 29);
	std::cout << "Constructor HashTable(24): size of table = " << ht3Size << '\n';
}

void testHTInsert()
{
	HT<String> ht(7);
	assert(ht.getTableSize() == 7);

	// Добавляем запись с ещё не существующим в таблице ключом
	assert(ht.insert("Alex", String("12-345-67")) == true);
	std::cout << "Record {\"Alex\", \"12-345-67\"} was inserted\n";
	assert(ht.getElementsNumber() == 1);

	// Добавляем запись с ещё не существующим в таблице ключом
	assert(ht.insert("John", String("48-682-21")) == true);
	std::cout << "Record {\"John\", \"48-682-21\"} was inserted\n";
	assert(ht.getElementsNumber() == 2);

	// Пытаемся добавить запись с повторным ключом
	assert(ht.insert("Alex", String("52-987-22")) == false);
	std::cout << "Record {\"Alex\", \"52-987-22\"} was not inserted (key \"Alex\" is already in table)\n";
	assert(ht.getElementsNumber() == 2);

	// Добавляем запись с ещё не существующим в таблице ключом
	assert(ht.insert("David", String("33-926-55")) == true);
	std::cout << "Record {\"David\", \"33-926-55\"} was inserted\n";
	assert(ht.getElementsNumber() == 3);

	// Добавляем запись с ещё не существующим в таблице ключом
	assert(ht.insert("Oliver", String("49-105-26")) == true);
	std::cout << "Record {\"Oliver\", \"49-105-26\"} was inserted\n";
	assert(ht.getElementsNumber() == 4);

	// Пытаемся добавить запись с повторным ключом
	assert(ht.insert("Oliver", String("87-322-42")) == false);
	std::cout << "Record {\"Oliver\", \"87-322-42\"} was not inserted (key \"Oliver\" is already in table)\n";
	assert(ht.getElementsNumber() == 4);

	// Добавляем запись с ещё не существующим в таблице ключом
	assert(ht.insert("George", String("98-203-68")) == true);
	std::cout << "Record {\"George\", \"98-203-68\"} was inserted\n";
	assert(ht.getElementsNumber() == 5);

	// Пытаемся добавить записи в максимально заполненную таблицу
	assert(ht.insert("Thomas", String("19-560-34")) == false);
	std::cout << "Record {\"Thomas\", \"19-560-34\"} was not inserted (MAX_LOAD_FACTOR was exceeded)\n";
	assert(ht.getElementsNumber() == 5);
	assert(ht.insert("Mason", String("20-561-35")) == false);
	std::cout << "Record {\"Mason\", \"20-561-35\"} was not inserted (MAX_LOAD_FACTOR was exceeded)\n";
	assert(ht.getElementsNumber() == 5);
	assert(ht.insert("Matthew", String("21-562-36")) == false);
	std::cout << "Record {\"Matthew\", \"21-562-36\"} was not inserted (MAX_LOAD_FACTOR was exceeded)\n\n";
	assert(ht.getElementsNumber() == 5);

	std::cout << "Hash Table after all insertions (collisionsNumber = " << ht.getCollisionsNumber() << ")\n";
	ht.print();
}

void testHTSearch()
{
	HT<String> ht(7);
	assert(ht.search("Jacob") == false);
	std::cout << "Before insertion: search(\"Jacob\") = false\n";
	ht.insert("Jacob", String("45-298-90"));
	assert(ht.search("Jacob") == true);
	std::cout << "After insertion: search(\"Jacob\") = true\n\n";

	assert(ht.search("Henry") == false);
	std::cout << "Before insertion: search(\"Henry\") = false\n";
	ht.insert("Henry", String("22-720-44"));
	assert(ht.search("Henry") == true);
	std::cout << "After insertion: search(\"Henry\") = true\n\n";

	assert(ht.search("Lucas") == false);
	std::cout << "Before insertion: search(\"Lucas\") = false\n";
	ht.insert("Lucas", String("14-223-39"));
	assert(ht.search("Lucas") == true);
	std::cout << "After insertion: search(\"Lucas\") = true\n\n";

	assert(ht.search("Samuel") == false);
	std::cout << "Before insertion: search(\"Samuel\") = false\n";
	ht.insert("Samuel", String("97-734-75"));
	assert(ht.search("Samuel") == true);
	std::cout << "After insertion: search(\"Samuel\") = true\n\n";

	assert(ht.search("Daniel") == false);
	std::cout << "Before insertion: search(\"Daniel\") = false\n";
	ht.insert("Daniel", String("65-565-87"));
	assert(ht.search("Daniel") == true);
	std::cout << "After insertion: search(\"Daniel\") = true\n";

	// Пытаемся найти записи по ключам, которых нет в таблице
	assert(ht.search("Benjamin") == false);
	assert(ht.search("Sebastian") == false);
	assert(ht.search("Jackson") == false);
}

void testHTRemove()
{
	HT<String> ht(7);
	ht.insert("Harry", String("75-638-78"));
	ht.insert("Oscar", String("43-299-80"));
	ht.insert("Charlie", String("29-341-21"));
	ht.insert("Edward", String("55-142-56"));
	ht.insert("Luke", String("45-100-33"));

	// Удаление по ключам, которых нет в таблице
	assert(ht.remove("Anthony") == false);
	assert(ht.remove("Julian") == false);
	assert(ht.remove("Wyatt") == false);

	assert(ht.remove("Harry") == true); // Удаляем по ключу, который есть в таблице
	assert(ht.search("Harry") == false); // После удаления ключа его не должно быть в таблице
	assert(ht.getElementsNumber() == 4); // Количество элементов становится 4 (5 - 1)
	std::cout << "Hash Table after remove(\"Harry\"):" << '\n';
	ht.print();
	assert(ht.insert("Harry", String("75-638-78")) == true); // Добавление записи с ключом, который мы удалили, должно быть успешным
	assert(ht.remove("Harry") == true); // Снова удаляем запись с ранее добавленным ключом

	assert(ht.remove("Oscar") == true); // Удаляем по ключу, который есть в таблице
	assert(ht.search("Oscar") == false); // После удаления ключа его не должно быть в таблице
	assert(ht.getElementsNumber() == 3); // Количество элементов становится 3 (4 - 1)
	std::cout << "Hash Table after remove(\"Oscar\"):" << '\n';
	ht.print();
	assert(ht.insert("Oscar", String("43-299-80")) == true); // Добавление записи с ключом, который мы удалили, должно быть успешным
	assert(ht.remove("Oscar") == true); // Снова удаляем запись с ранее добавленным ключом

	assert(ht.remove("Charlie") == true); // Удаляем по ключу, который есть в таблице
	assert(ht.search("Charlie") == false); // После удаления ключа его не должно быть в таблице
	assert(ht.getElementsNumber() == 2); // Количество элементов становится 2 (3 - 1)
	std::cout << "Hash Table after remove(\"Charlie\"):" << '\n';
	ht.print();
	assert(ht.insert("Charlie", String("29-341-21")) == true); // Добавление записи с ключом, который мы удалили, должно быть успешным
	assert(ht.remove("Charlie") == true); // Снова удаляем запись с ранее добавленным ключом

	assert(ht.remove("Edward") == true); // Удаляем по ключу, который есть в таблице
	assert(ht.search("Edward") == false); // После удаления ключа его не должно быть в таблице
	assert(ht.getElementsNumber() == 1); // Количество элементов становится 1 (2 - 1)
	std::cout << "Hash Table after remove(\"Edward\"):" << '\n';
	ht.print();
	assert(ht.insert("Edward", String("55-142-56")) == true); // Добавление записи с ключом, который мы удалили, должно быть успешным
	assert(ht.remove("Edward") == true); // Снова удаляем запись с ранее добавленным ключом

	assert(ht.remove("Luke") == true); // Удаляем по ключу, который есть в таблице
	assert(ht.search("Luke") == false); // После удаления ключа его не должно быть в таблице
	assert(ht.getElementsNumber() == 0); // Количество элементов становится 0 (1 - 1)
	std::cout << "Hash Table after remove(\"Luke\"):" << '\n';
	ht.print();
	assert(ht.insert("Luke", String("45-100-33")) == true); // Добавление записи с ключом, который мы удалили, должно быть успешным
	assert(ht.remove("Luke") == true); // Снова удаляем запись с ранее добавленным ключом
}

void runAllHashTableTests()
{
	std::cout << "================= HashTable tests =================\n";

	std::cout << "1) testHTDefaultConstructor\n";
	testHTDefaultConstructor();
	std::cout << "testHTDefaultConstructor passed!\n\n";

	std::cout << "2) testHTInsert\n";
	testHTInsert();
	std::cout << "testHTInsert passed!\n\n";

	std::cout << "3) testHTSearch\n";
	testHTSearch();
	std::cout << "testHTSearch passed!\n\n";

	std::cout << "4) testHTRemove\n";
	testHTRemove();
	std::cout << "testHTRemove passed!\n\n";

	std::cout << "================ All tests passed! ================\n";
}