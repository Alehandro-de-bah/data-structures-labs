#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include "Stack.h"
#include "StackExceptions.h"

template <typename T>
class StackArray : public Stack<T>
{
public:
	// Правило пяти
	StackArray(const StackArray<T>& other) = delete;
	StackArray(StackArray<T>&& other) noexcept = delete;
	StackArray<T>& operator=(const StackArray<T>& other) = delete;
	StackArray<T>& operator=(StackArray<T>&& other) noexcept = delete;
	~StackArray(); // Деструктор

	StackArray(int size); // Конструктор с размером
	void push(const T& e) override; // Вставка в стек
	T pop() override; // Возвращение элемента-вершины и его "удаление" из стека
	inline bool isEmpty() const noexcept override; // Проверка на пустоту
	inline int size() const noexcept; // Информация о размере
	inline int capacity() const noexcept; // Информация о ёмкости
private:
	T* arr_; // Массив в динамической памяти
	int size_; // Количество элементов в стеке
	int capacity_; // Ёмкость массива
	int topIndex_; // Индекс вершины стека
};

template <typename T>
StackArray<T>::StackArray(int size) // Конструктор с размером
{
	try
	{
		if (size <= 0)
		{
			throw WrongStackSize();
		}
		arr_ = new T[size]; // Может быть исключение bad_alloc
		capacity_ = size;
		size_ = 0;
		topIndex_ = -1;
	}
	catch (const std::bad_alloc&)
	{
		throw StackBadAllocationInConstructor();
	}
}

template <typename T>
void StackArray<T>::push(const T& e) // Вставка в стек
{
	if (topIndex_ >= capacity_ - 1)
	{
		throw StackOverflow();
	}
	try
	{
		arr_[++topIndex_] = e; // Может быть исключение ...
		size_++;
	}
	catch (...)
	{
		throw StackErrorInCopying();
	}
}

template <typename T>
T StackArray<T>::pop() // Возвращение элемента-вершины и его "удаление" из стека
{
	if (isEmpty())
	{
		throw StackUnderflow();
	}
	size_--;
	return arr_[topIndex_--];
}

template <typename T>
inline bool StackArray<T>::isEmpty() const noexcept // Проверка на пустоту
{
	return topIndex_ == -1;
}

template <typename T>
inline int StackArray<T>::size() const noexcept // Информация о размере
{
	return size_;
}

template <typename T>
inline int StackArray<T>::capacity() const noexcept // Информация о ёмкости
{
	return capacity_;
}

template <typename T>
StackArray<T>::~StackArray() // Деструктор
{
	delete[] arr_;
}

#endif