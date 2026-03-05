#ifndef A_H
#define A_H

#include <iostream>

// Класс A - это простейший класс, где динамически выделяется память под поле value_
// Этот класс используется для тестирования класса Vector, чтобы убедиться в отсутствии утечек памяти
class A
{
public:
	A() : value_(new int(0))
	{
		count_++;
		std::cout << "A() " << count_ << std::endl;
	}
	A(int value) : value_(new int(value))
	{
		count_++;
		std::cout << "A(int value) " << count_ << std::endl;
	}
	A(const A& other) : value_(new int(*other.value_))
	{
		count_++;
		std::cout << "A(const A&) " << count_ << std::endl;
	}
	A(A&& other) noexcept : value_(nullptr)
	{
		std::swap(value_, other.value_);
		count_++;
		std::cout << "A(A&&) " << count_ << std::endl;
	}
	~A()
	{
		delete value_;
		count_--;
		std::cout << "~A() " << count_ << std::endl;
	}
	A& operator=(const A& other)
	{
		if (this != &other)
		{
			int* newValue = new int(*other.value_);
			delete value_;
			value_ = newValue;
		}
		std::cout << "operator=(const A&)" << std::endl;
		return *this;
	}
	A& operator=(A&& other) noexcept
	{
		std::swap(value_, other.value_);
		std::cout << "operator=(A&&)" << std::endl;
		return *this;
	}
	static int getCount() { return count_; }
private:
	int* value_;
	static int count_; // счётчик созданных объектов
};

#endif