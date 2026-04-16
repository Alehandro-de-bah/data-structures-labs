#ifndef QUEUE_VECTOR_H
#define QUEUE_VECTOR_H

#include "Queue.h"
#include "QueueExceptions.h"

template <typename T>
class QueueVector : public Queue<T>
{
public:
	// Правило пяти
	QueueVector(const QueueVector<T>& other) = delete;
	QueueVector(QueueVector<T>&& other) noexcept = delete;
	QueueVector<T>& operator=(const QueueVector<T>& other) = delete;
	QueueVector<T>& operator=(QueueVector<T>&& other) noexcept = delete;
	~QueueVector(); // Деструктор

	QueueVector(int size); // Конструктор с размером
	void enQueue(const T& e) override; // Вставка в очередь
	T deQueue() override; // Возвращение головного элемента и его "удаление" из очереди
	inline bool isFull() const noexcept; // Проверка на заполненность
	inline bool isEmpty() const noexcept override; // Проверка на пустоту
	inline int size() const noexcept; // Информация о количестве элементов
	inline int capacity() const noexcept; // Информация о ёмкости
private:
	T* data_; // Массив элементов в динамической памяти 
	int headIndex_; // Индекс головного элемента
	int tailIndex_; // Индекс, СЛЕДУЮЩИЙ после головного элемента
	int size_; // Количество элементов в массиве
	int capacity_; // Ёмкость массива

	int countNewCapacity() const noexcept; // Подсчёт новой ёмкости (стратегия - x2)
	void copyDataTo(T* newData); // Копирование элементов из data_ в newData
	void resize(); // Расширение массива
};

template <typename T>
int QueueVector<T>::countNewCapacity() const noexcept // Подсчёт новой ёмкости (стратегия - x2)
{
	int newCapacity = capacity_;
	while (newCapacity <= capacity_)
	{
		newCapacity *= 2;
	}
	return newCapacity;
}

template <typename T>
void QueueVector<T>::copyDataTo(T* newData) // Копирование элементов из data_ в newData
{
	if (headIndex_ < tailIndex_)
	{
		for (int i = 0; i < size_; i++)
		{
			newData[i] = data_[headIndex_ + i];
		}
	}
	else
	{
		int firstPart = capacity_ - headIndex_;
		for (int i = 0; i < firstPart; i++)
		{
			newData[i] = data_[headIndex_ + i];
		}
		for (int i = 0; i < tailIndex_; i++)
		{
			newData[firstPart + i] = data_[i];
		}
	}
}

template <typename T>
void QueueVector<T>::resize() // Расширение массива
{
	T* newData = nullptr;
	try
	{
		int newCapacity = countNewCapacity();
		newData = new T[newCapacity]; // Может быть исключение bad_alloc
		copyDataTo(newData); // Может быть исключение ...
		delete[] data_;
		data_ = newData;
		headIndex_ = 0;
		tailIndex_ = size_;
		capacity_ = newCapacity;
	}
	catch (const std::bad_alloc&)
	{
		throw QueueBadAllocationInResize();
	}
	catch (...)
	{
		delete[] newData;
		throw QueueErrorInCopying();
	}
}

template <typename T>
QueueVector<T>::QueueVector(int size) // Конструктор с размером
{
	try
	{
		if (size <= 0)
		{
			throw WrongQueueSize();
		}
		data_ = new T[size]; // Может быть исключение bad_alloc
		capacity_ = size;
		headIndex_ = 0;
		tailIndex_ = 0;
		size_ = 0;
	}
	catch (const std::bad_alloc&)
	{
		throw QueueBadAllocationInConstructor();
	}
}

template <typename T>
void QueueVector<T>::enQueue(const T& e) // Вставка в очередь
{
	if (isFull())
	{
		resize(); // Могут быть исключения QueueBadAllocationInResize и QueueErrorInCopying (поймаем в main)
	}
	try
	{
		data_[tailIndex_] = e; // Может быть исключение ...
		tailIndex_ = (tailIndex_ + 1) % capacity_;
		size_++;
	}
	catch (...)
	{
		throw QueueErrorInCopying();
	}
}

template <typename T>
T QueueVector<T>::deQueue() // Возвращение головного элемента и его "удаление" из очереди
{
	if (isEmpty())
	{
		throw QueueUnderflow();
	}
	try
	{
		T value = data_[headIndex_]; // Может быть исключение ...
		headIndex_ = (headIndex_ + 1) % capacity_;
		size_--;
		return value;
	}
	catch (...)
	{
		throw QueueErrorInCopying();
	}
}

template <typename T>
QueueVector<T>::~QueueVector() // Деструктор
{
	delete[] data_;
}

template <typename T>
inline bool QueueVector<T>::isFull() const noexcept // Проверка на заполненность
{
	return size_ == capacity_;
}

template <typename T>
inline bool QueueVector<T>::isEmpty() const noexcept // Проверка на пустоту
{
	return size_ == 0;
}

template <typename T>
inline int QueueVector<T>::size() const noexcept // Информация о количестве элементов
{
	return size_;
}

template <typename T>
inline int QueueVector<T>::capacity() const noexcept // Информация о ёмкости
{
	return capacity_;
}

#endif