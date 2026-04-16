#include "String.h"
#include <iostream>
#include "StringExceptions.h"

// Конструктор по умолчанию
String::String() : data_(nullptr), length_(0), capacity_(0)
{
	this->resize(16);
	data_[0] = '\0';
}

// Преобразующий конструктор
String::String(const char* str) : data_(nullptr), length_(0), capacity_(0)
{
	size_t strLength = countLength(str);
	if (strLength > 0)
	{
		size_t newCapacity = this->countNewCapacity(strLength + 1);
		try
		{
			this->resize(newCapacity);
		}
		catch (std::bad_alloc&)
		{
			std::cerr << ERROR_BAD_ALLOC_IN_STRING_CONST_CHAR << std::endl;
			throw;
		}

		this->copyStr(str);
	}
	else
	{
		this->resize(16);
		data_[0] = '\0';
	}
}

// Конструктор копирования
String::String(const String& other) : data_(nullptr), length_(0), capacity_(0)
{
	if (other.length_ > 0)
	{
		size_t newCapacity = this->countNewCapacity(other.length_ + 1);
		try
		{
			this->resize(newCapacity);
		}
		catch (std::bad_alloc&)
		{
			std::cerr << ERROR_BAD_ALLOC_IN_STRING_CONST_STRING << std::endl;
			throw;
		}

		this->copyStr(other.data_);
	}
	else
	{
		if (other.capacity_ > 16)
		{
			this->resize(other.capacity_);
		}
		else
		{
			this->resize(16);
		}
		data_[0] = '\0';
	}
}

// Конструктор перемещения
String::String(String&& other) noexcept : data_(nullptr), length_(0), capacity_(0)
{
	this->swap(other);
}

// Деструктор
String::~String() noexcept
{
	delete[] data_;
}

// Метод перевыделения памяти
void String::resize(size_t newCapacity)
{
	if (newCapacity > capacity_)
	{
		try
		{
			char* newData = new char[newCapacity];
			if (data_ != nullptr)
			{
				for (size_t i = 0; i < length_; ++i)
				{
					newData[i] = data_[i];
				}
				delete[] data_;
			}

			data_ = newData;
			capacity_ = newCapacity;
		}
		catch (std::bad_alloc&)
		{
			std::cerr << ERROR_BAD_ALLOC_IN_RESIZE << std::endl;
			throw;
		}
	}
}

// Метод обмена
void String::swap(String& other) noexcept
{
	std::swap(data_, other.data_);
	std::swap(length_, other.length_);
	std::swap(capacity_, other.capacity_);
}

// Оператор копирующего присваивания
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		String temp(other);
		this->swap(temp);
	}
	return *this;
}

// Оператор перемещающего присваивания
String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		this->swap(other);
	}
	return *this;
}

// Оператор присваивания
String& String::operator=(const char* str)
{
	if (str != nullptr)
	{
		size_t strLength = countLength(str);
		if (capacity_ < strLength + 1)
		{
			size_t newCapacity = countNewCapacity(strLength + 1);
			try
			{
				this->resize(newCapacity);
			}
			catch (std::bad_alloc&)
			{
				std::cerr << ERROR_BAD_ALLOC_IN_ASSIGNMENT_OPERATOR_CONST_CHAR << std::endl;
				throw;
			}
		}
		this->copyStr(str);
	}
	else
	{
		this->clear();
	}
	return *this;
}

// Оператор взятия индекса
char& String::operator[](size_t index)
{
	if (index >= length_)
	{
		throw std::out_of_range(ERROR_OUT_OF_RANGE);
	}
	return data_[index];
}

// Оператор взятия индекса
const char& String::operator[](size_t index) const
{
	if (index >= length_)
	{
		throw std::out_of_range(ERROR_OUT_OF_RANGE);
	}
	return data_[index];
}

// String + String
String String::operator+(const String& other) const
{
	String result(*this);
	result += other;
	return result;
}

// String += String
String& String::operator+=(const String& other)
{
	if (other.length_ > 0)
	{
		if (capacity_ < length_ + other.length_ + 1)
		{
			size_t newCapacity = this->countNewCapacity(length_ + other.length_ + 1);
			try
			{
				this->resize(newCapacity);
			}
			catch (std::bad_alloc&)
			{
				std::cerr << ERROR_BAD_ALLOC_IN_ADDITION_ASSIGNMENT_CONST_STRING << std::endl;
				throw;
			}
		}

		for (size_t i = 0; i < other.length_; ++i)
		{
			data_[length_++] = other.data_[i];
		}
		data_[length_] = '\0';
	}
	return *this;
}

// String += str
String& String::operator+=(const char* str)
{
	*this += String(str);
	return *this;
}

// Метод clear()
void String::clear()
{
	if (data_ != nullptr)
	{
		data_[0] = '\0';
	}
	length_ = 0;
}

// Оператор ==
bool String::operator==(const String& other) const noexcept
{
	if (length_ != other.length_)
	{
		return false;
	}

	for (size_t i = 0; i < length_; ++i)
	{
		if (data_[i] != other.data_[i])
		{
			return false;
		}
	}

	return true;
}

// Оператор !=
bool String::operator!=(const String& other) const noexcept
{
	return !(*this == other);
}

// Оператор <
bool String::operator<(const String& other) const noexcept
{
	size_t minLength = (length_ < other.length_ ? length_ : other.length_);

	for (size_t i = 0; i < minLength; ++i)
	{
		if (data_[i] != other.data_[i])
		{
			return data_[i] < other.data_[i];
		}
	}

	return length_ < other.length_;
}

bool String::operator>=(const String& other) const noexcept
{
	return !(*this < other);
}

// Оператор >
bool String::operator>(const String& other) const noexcept
{
	return other < *this;
}

bool String::operator<=(const String& other) const noexcept
{
	return !(*this > other);
}

// Метод для задания A3
bool String::areDublicatesInString() const noexcept
{
	if (length_ < 2)
	{
		return false;
	}

	for (size_t i = 0; i < length_ - 1; ++i)
	{
		if (data_[i] == data_[i + 1])
		{
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	for (size_t i = 0; i < str.length_; i++)
	{
		os << str[i];
	}
	return os;
}