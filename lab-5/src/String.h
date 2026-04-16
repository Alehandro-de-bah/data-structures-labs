#ifndef STRING_H
#define STRING_H

#include <iostream>

class String
{
public:
	// Конструкторы
	String(); // Конструктор по умолчанию
	String(const char* str); // Преобразующий конструктор
	String(const String& other); // Конструктор копирования
	String(String&& other) noexcept; // Конструктор перемещения

	~String() noexcept; // Деструктор

	// Методы доступа
	size_t getLength() const noexcept { return length_; }
	size_t getCapacity() const noexcept { return capacity_; }

	bool isEmpty() const noexcept { return length_ == 0; } // Метод, проверяющий пустая ли строка
	void swap(String& other) noexcept; // Метод обмена
	void resize(size_t newCapacity); // Метод перевыделения памяти

	// Операторы
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	String& operator=(const char* str);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	// Операции со строками
	String operator+(const String& other) const;
	String& operator+=(const String& other);
	String& operator+=(const char* str);
	void clear();

	// Сравнение
	bool operator==(const String& other) const noexcept;
	bool operator!=(const String& other) const noexcept;
	bool operator<(const String& other) const noexcept;
	bool operator>=(const String& other) const noexcept;
	bool operator>(const String& other) const noexcept;
	bool operator<=(const String& other) const noexcept;

	// Метод для задания A3 (вариант 9)
	bool areDublicatesInString() const noexcept;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
private:
	char* data_{ nullptr }; // Указатель на массив символов
	size_t length_{ 0 }; // Длина строки (без нуль-терминатора)
	size_t capacity_{ 0 }; // Ёмкость буфера

	static size_t countLength(const char* str);
	size_t countNewCapacity(size_t necessaryCapacity) const;
	void copyStr(const char* str);
};

// Расчёт длины строки
inline size_t String::countLength(const char* str)
{
	if (str == nullptr)
	{
		return 0;
	}
	size_t strLength = 0;
	while (str[strLength] != '\0')
	{
		strLength++;
	}
	return strLength;
}

// Расчёт новой ёмкости буфера
inline size_t String::countNewCapacity(size_t necessaryCapacity) const
{
	size_t newCapacity = capacity_ > 0 ? capacity_ : 16;
	while (newCapacity < necessaryCapacity)
	{
		newCapacity *= 2;
	}
	return newCapacity;
}

// Копирование строки
inline void String::copyStr(const char* str)
{
	size_t strLength = countLength(str);
	if (str != nullptr)
	{
		for (size_t i = 0; i < strLength; ++i)
		{
			data_[i] = str[i];
		}
	}
	data_[strLength] = '\0';
	length_ = strLength;
}

#endif