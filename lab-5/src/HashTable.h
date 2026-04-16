#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Вариант 5 - метод открытой адресации, квадратичное пробирование, определить число коллизий

#include <iostream>
#include <cmath>
#include <iomanip>
#include "HashTableExceptions.h"

template <typename T>
class HashTable
{
public:
	// Конструктор по умолчанию
	HashTable(size_t size = 31);

	// Деструктор
	~HashTable();

	// Конструктор копирования (запрещён)
	HashTable(const HashTable<T>&) = delete;

	// Конструктор перемещения (запрещён)
	HashTable(HashTable<T>&&) noexcept = delete;

	// Оператор копирующего присваивания (запрещён)
	HashTable<T>& operator=(const HashTable<T>&) = delete;

	// Оператор перемещающего присваивания (запрещён)
	HashTable<T>& operator=(HashTable<T>&&) noexcept = delete;

	// Вставка элемента в таблицу
	template <typename V>
	bool insert(const char* key, V&& value);

	// Поиск элемента в таблице по ключу
	bool search(const char* key) const;

	// Удаление элемента из таблицы по ключу
	bool remove(const char* key);

	// Вывод всех элементов таблицы
	void print() const;

	// Получение числа коллизий
	size_t getCollisionsNumber() const { return collisionsNumber_; }

	// Получение количества элементов таблицы
	size_t getElementsNumber() const { return number_; }

	// Получение размера таблицы
	size_t getTableSize() const { return size_; }
private:
	// Статус строки таблицы
	enum class Status
	{
		EMPTY = 0,    // Пустая ячейка
		OCCUPIED = 1, // Занятая ячейка
		DELETED = 2   // Удалённая ячейка
	};

	struct Record
	{
		char* key_; // Ключ (строка в стиле C)
		T value_; // Информационная часть
		Status status_; // Статус строки

		// Конструктор по умолчанию
		Record();
		// Конструктор с параметрами
		template <typename V>
		Record(const char* key, V&& value, Status status);
		// Деструктор
		~Record();
		// Метод swap (для идиомы copy-and-swap)
		void swap(Record& other) noexcept;
		// Конструктор копирования
		Record(const Record& other);
		// Конструктор перемещения
		Record(Record&& other) noexcept;
		// Оператор копирующего присваивания
		Record& operator=(const Record& other);
		// Оператор перемещающего присваивания
		Record& operator=(Record&& other) noexcept;

		// Длина строки str
		static size_t strLength(const char* str);
		// Копирование строки src в строку dest
		static void strCopy(char* dest, const char* src);
		// Равны ли строки str1 и str2
		static bool areStringsEqual(const char* str1, const char* str2);
	};

	Record* table_; // Адрес таблицы
	size_t size_; // Размер таблицы
	size_t number_; // Количество занесённых элементов
	size_t collisionsNumber_; // Количество коллизий
	static const double MAX_LOAD_FACTOR; // Максимальный коэффициент заполнения
	static const int P; // Простое число для хэш-функции

	// Хэш-функция (полиномиальный хэш)
	size_t hashFunction(const char* key) const;

	// Квадратичное пробирование (index = (h(k) + c1*i + c2*i^2) mod m) [Метод средних квадратов]
	size_t quadraticProbe(size_t hash, size_t step) const { return (hash + step * step) % size_; }

	// Является ли число number простым
	static bool isPrime(size_t number);

	// Получение простого числа, большего или равного number
	static size_t getNextPrime(size_t number);
};

template <typename T>
const double HashTable<T>::MAX_LOAD_FACTOR = 0.7;

template <typename T>
const int HashTable<T>::P = 31;

// ---------- Реализация методов структуры Record ----------

// Длина строки str
template <typename T>
size_t HashTable<T>::Record::strLength(const char* str)
{
	size_t i = 0;
	for (; str[i] != '\0'; i++)
	{}
	return i;
}

// Копирование строки src в строку dest
template <typename T>
void HashTable<T>::Record::strCopy(char* dest, const char* src)
{
	size_t i = 0;
	for (; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

// Равны ли строки str1 и str2
template <typename T>
bool HashTable<T>::Record::areStringsEqual(const char* str1, const char* str2)
{
	size_t i = 0;
	for (; str1[i] != '\0' && str1[i] == str2[i]; i++)
	{}
	return str1[i] == '\0' && str2[i] == '\0';
}

// Конструктор по умолчанию
template <typename T>
HashTable<T>::Record::Record() : key_(nullptr), value_(T()), status_(Status::EMPTY) {}

// Конструктор с параметрами
template <typename T>
template <typename V>
HashTable<T>::Record::Record(const char* key, V&& value, Status status)
{
	try
	{
		key_ = new char[strLength(key) + 1]; // Может быть исключение std::bad_alloc
		value_ = std::forward<V>(value); // Может быть исключение при копировании
	}
	catch (const std::bad_alloc&)
	{
		throw BadAllocation();
	}
	catch (...)
	{
		delete[] key_;
		throw ErrorInCopying();
	}
	strCopy(key_, key);
	status_ = status;
}

// Метод swap (для идиомы copy-and-swap)
template <typename T>
void HashTable<T>::Record::swap(Record& other) noexcept
{
	std::swap(key_, other.key_);
	std::swap(value_, other.value_);
	std::swap(status_, other.status_);
}

// Конструктор копирования
template <typename T>
HashTable<T>::Record::Record(const Record& other) : key_(nullptr), value_(T()), status_(Status::EMPTY)
{
	char* newKey = nullptr;
	try
	{
		newKey = new char[strLength(other.key_) + 1];
		value_ = other.value_;
	}
	catch (const std::bad_alloc&)
	{
		throw BadAllocation();
	}
	catch (...)
	{
		delete[] newKey;
		throw ErrorInCopying();
	}
	strCopy(newKey, other.key_);
	key_ = newKey;
	status_ = other.status_;
}

// Конструктор перемещения
template <typename T>
HashTable<T>::Record::Record(Record&& other) noexcept : key_(nullptr), value_(T()), status_(Status::EMPTY)
{
	this->swap(other);
}

// Оператор копирующего присваивания
template <typename T>
typename HashTable<T>::Record& HashTable<T>::Record::operator=(const Record& other)
{
	if (this != &other)
	{
		Record temp(other); // Может быть исключение BadAllocation или ErrorInCopying (поймаем в main)
		this->swap(temp);
	}
	return *this;
}

// Оператор перемещающего присваивания
template <typename T>
typename HashTable<T>::Record& HashTable<T>::Record::operator=(Record&& other) noexcept
{
	if (this != &other)
	{
		this->swap(other);
	}
	return *this;
}

// Деструктор
template <typename T>
HashTable<T>::Record::~Record()
{
	delete[] key_;
}

// ------------- Реализация методов класса HashTable -------------

// Хэш-функция (полиномиальный хэш)
template <typename T>
size_t HashTable<T>::hashFunction(const char* key) const
{
	size_t hash = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{
		hash = (hash * P + static_cast<size_t>(key[i])) % size_;
	}
	return hash;
}

// Является ли число number простым
template <typename T>
bool HashTable<T>::isPrime(size_t number)
{
	if (number == 2)
	{
		return true;
	}
	else if (number < 2 || number % 2 == 0)
	{
		return false;
	}
	for (size_t i = 3; i <= static_cast<int>(sqrt(number)); i += 2)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

// Получение простого числа, большего или равного number
template <typename T>
size_t HashTable<T>::getNextPrime(size_t number)
{
	if (!isPrime(number))
	{
		number += (number % 2 == 0) ? 1 : 0;
		while (!isPrime(number))
		{
			number += 2;
		}
	}
	return number;
}

// Конструктор по умолчанию
template <typename T>
HashTable<T>::HashTable(size_t size) : number_(0), collisionsNumber_(0)
{
	size_ = getNextPrime(size);
	try
	{
		table_ = new Record[size_];
	}
	catch (const std::bad_alloc&)
	{
		throw BadAllocation();
	}
}

// Деструктор
template <typename T>
HashTable<T>::~HashTable()
{
	delete[] table_;
}

// Вставка элемента в таблицу
template <typename T>
template <typename V>
bool HashTable<T>::insert(const char* key, V&& value)
{
	double loadFactor = static_cast<double>(number_) / size_;
	if (loadFactor >= MAX_LOAD_FACTOR)
	{
		return false;
	}
	size_t hash = hashFunction(key);
	size_t step = 0;
	size_t index = 0;

	while (step < size_)
	{
		index = quadraticProbe(hash, step);
		if (table_[index].status_ == Status::EMPTY || table_[index].status_ == Status::DELETED)
		{
			table_[index] = Record(key, std::forward<V>(value), Status::OCCUPIED); // Может быть исключение BadAllocation или ErrorInCopying (поймаем в main)
			number_++;
			return true;
		}
		else if (Record::areStringsEqual(table_[index].key_, key))
		{
			return false;
		}

		collisionsNumber_++;
		step++;
	}
	return false;
}

// Поиск элемента в таблице по ключу
template <typename T>
bool HashTable<T>::search(const char* key) const
{
	size_t hash = hashFunction(key);
	size_t step = 0;
	size_t index = 0;

	while (step < size_)
	{
		index = quadraticProbe(hash, step);
		if (table_[index].status_ == Status::EMPTY)
		{
			return false;
		}
		else if (table_[index].status_ == Status::OCCUPIED && Record::areStringsEqual(table_[index].key_, key))
		{
			return true;
		}
		step++;
	}
	return false;
}

// Удаление элемента из таблицы по ключу
template <typename T>
bool HashTable<T>::remove(const char* key)
{
	size_t hash = hashFunction(key);
	size_t step = 0;
	size_t index = 0;

	while (step < size_)
	{
		index = quadraticProbe(hash, step);
		if (table_[index].status_ == Status::EMPTY)
		{
			return false;
		}
		else if (table_[index].status_ == Status::OCCUPIED && Record::areStringsEqual(table_[index].key_, key))
		{
			table_[index].status_ = Status::DELETED;
			number_--;
			return true;
		}
		step++;
	}
	return false;
}

// Вывод всех элементов таблицы
template <typename T>
void HashTable<T>::print() const
{
	for (size_t i = 0; i < size_; i++)
	{
		std::cout << "[Index: " << i;
		switch (table_[i].status_)
		{
		case Status::EMPTY:
			std::cout << ", Key: -, Value: -, Status: [EMPTY]";
			break;
		case Status::OCCUPIED:
			std::cout << ", Key: " << table_[i].key_ << ", Value: " << table_[i].value_ << ", Status: [OCCUPIED]";
			break;
		case Status::DELETED:
			std::cout << ", Key: " << table_[i].key_ << ", Value: " << table_[i].value_ << ", Status: [DELETED]";
			break;
		}
		std::cout << "]\n";
	}
	std::cout << '\n';
}

#endif