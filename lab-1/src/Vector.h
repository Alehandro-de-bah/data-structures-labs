#ifndef VECTOR_H
#define VECTOR_H

#include "exceptions.h"
#include <stdexcept>

template<typename T>
class Vector
{
private:
	T* data_;
	size_t size_;
	size_t capacity_;

	size_t countNewCapacity(size_t size) const;
	void copyDataFrom(const Vector<T>& other);
	void copyDataTo(T* newData);
	void countNewCapacityAndReserve();
public:
	// 1. Конструкторы и деструктор
	Vector();
	Vector(size_t n);
	Vector(size_t n, const T& value);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	~Vector();

	// 2. Операторы присваивания
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other) noexcept;
	
	// 3. Доступ к элементам
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T& at(size_t index);
	const T& at(size_t index) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	// 4. Вставка элементов
	template <typename V>
	void push_back(V&& value);
	template <typename V>
	void insert(size_t index, V&& value);

	// 5. Удаление элементов
	void pop_back();
	void clear();
	void erase(size_t index);
	void erase(size_t first, size_t last);

	// 6. Изменение размера
	void resize(size_t newSize, const T& value);
	void resize(size_t newSize);
	void reserve(size_t newCapacity);
	void shrink_to_fit();

	// 7. Информация о состоянии
	size_t size() const noexcept;
	size_t capacity() const noexcept;
	bool empty() const noexcept;
	
	// 8. Дополнительно
	bool operator==(const Vector<T>& other) const;
	bool operator!=(const Vector<T>& other) const;
	bool operator<(const Vector<T>& other) const;
	bool operator>(const Vector<T>& other) const;
	bool operator<=(const Vector<T>& other) const;
	bool operator>=(const Vector<T>& other) const;
	void swap(Vector<T>& other) noexcept;
};

template <typename T>
size_t Vector<T>::countNewCapacity(size_t size) const
{
	size_t newCapacity = capacity_ > 0 ? capacity_ : 2; 
	while (newCapacity < size)
	{
		newCapacity *= 2; // стратегия увеличения capacity - x2
	}
	return newCapacity;
}

template <typename T>
void Vector<T>::copyDataFrom(const Vector<T>& other) // копирование данных в текущую data из другой data
{
	for (size_t i = 0; i < other.size_; i++)
	{
		data_[i] = other.data_[i];
	}
}

template <typename T>
void Vector<T>::copyDataTo(T* newData) // копирование данных из текущей data в newData
{
	for (size_t i = 0; i < size_; i++)
	{
		newData[i] = data_[i];
	}
}

template <typename T>
void Vector<T>::countNewCapacityAndReserve() // для push_back и insert
{
	size_t newCapacity = countNewCapacity(size_ + 1);
	this->reserve(newCapacity);
}
template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {} // Конструктор по умолчанию

template <typename T>
Vector<T>::Vector(size_t n) : data_(nullptr), size_(0), capacity_(0) // Конструктор с размером n
{
	try
	{
		if (n > 0)
		{
			data_ = new T[n]{};
			capacity_ = n;
			size_ = n;
		}
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
}

template <typename T>
Vector<T>::Vector(size_t n, const T& value) : data_(nullptr), size_(0), capacity_(0) // Конструктор с размером n и инициализирующим значением
{
	try
	{
		if (n > 0)
		{
			data_ = new T[n]; // Может быть исключение bad_alloc
			size_ = n;
			capacity_ = n;
			for (size_t i = 0; i < size_; i++)
			{
				data_[i] = value; // Может быть исключение ...
			}
		}
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		delete[] data_; // Обязательно освобождаем память при исключении
		throw;
	}
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : data_(nullptr), size_(0), capacity_(0) // Конструктор копирования
{
	try
	{
		if (other.size_ > 0)
		{
			data_ = new T[other.capacity_]; // Может быть исключение bad_alloc
			copyDataFrom(other); // Может быть исключение ...
			size_ = other.size_;
			capacity_ = other.capacity_;
		}
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		delete[] data_; // Обязательно освобождаем память при исключении
		throw;
	}
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : data_(nullptr), size_(0), capacity_(0) // Конструктор перемещения
{
	this->swap(other);
}

template <typename T>
Vector<T>::~Vector() // Деструктор
{
	delete[] data_; // оператор delete вызовет деструкторы ~T() для всех объектов внутри data_
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) // Оператор копирующего присваивания
{
	try
	{
		if (this != &other)
		{
			Vector<T> temp(other); // Может быть исключение ...
			this->swap(temp);
		}
		return *this;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept // Оператор перемещающего присваивания
{
	if (this != &other)
	{
		this->swap(other);
	}
	return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	return data_[index]; // Без проверки границ
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return data_[index]; // Без проверки границ
}

template <typename T>
T& Vector<T>::at(size_t index)
{
	if (index >= size_)
	{
		throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE); // С проверкой границ
	}
	return data_[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const
{
	if (index >= size_)
	{
		throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE); // С проверкой границ
	}
	return data_[index];
}

template <typename T>
T& Vector<T>::front()
{
	if (size_ == 0)
	{
		throw std::out_of_range(ERROR_EMPTY_VECTOR); // С проверкой границ
	}
	return data_[0];
}

template <typename T>
const T& Vector<T>::front() const
{
	if (size_ == 0)
	{
		throw std::out_of_range(ERROR_EMPTY_VECTOR); // С проверкой границ
	}
	return data_[0];
}

template <typename T>
T& Vector<T>::back()
{
	if (size_ == 0)
	{
		throw std::out_of_range(ERROR_EMPTY_VECTOR); // С проверкой границ
	}
	return data_[size_ - 1];
}

template <typename T>
const T& Vector<T>::back() const
{
	if (size_ == 0)
	{
		throw std::out_of_range(ERROR_EMPTY_VECTOR); // С проверкой границ
	}
	return data_[size_ - 1];
}

template <typename T>
template <typename V>
void Vector<T>::push_back(V&& value) // Добавление value в конец вектора
{
	try
	{
		if (capacity_ < size_ + 1)
		{
			countNewCapacityAndReserve(); // Может быть исключение bad_alloc или ...
		}
		data_[size_++] = std::forward<V>(value); // Может быть исключение, если value - lvalue
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
template <typename V>
void Vector<T>::insert(size_t index, V&& value) // Добавление value по индексу
{
	if (index > size_)
	{
		throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE);
	}
	try
	{
		if (capacity_ == size_)
		{
			countNewCapacityAndReserve(); // Может быть исключение bad_alloc или ...
		}
		for (size_t i = size_; i > index; i--)
		{
			data_[i] = std::move(data_[i - 1]); // Здесь более оптимально использовать оператор перемещающего присваивания, поэтому std::move
		}
		data_[index] = std::forward<T>(value); // Может быть исключение, если value - lvalue
		size_++;
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
void Vector<T>::pop_back()
{
	size_ -= (size_ > 0); // Не вызываем деструктор ~T() явно, иначе будет двойное освобождение памяти, что критично для объектов, владеющих ресурсами
}

template <typename T>
void Vector<T>::clear()
{
	size_ = 0; // Аналогично pop_back, деструкторы не вызываем
}

template <typename T>
void Vector<T>::erase(size_t index) // Удаление элемента по индексу
{
	if (index >= size_)
	{
		throw std::out_of_range(ERROR_INDEX_OUT_OF_RANGE);
	}
	for (size_t i = index; i < size_ - 1; i++)
	{
		data_[i] = std::move(data_[i + 1]); // Здесь более оптимально использовать оператор перемещающего присваивания, поэтому std::move
	}
	size_--;
}

template <typename T>
void Vector<T>::erase(size_t first, size_t last) // Удаление диапазона элементов
{
	if (first > last || last > size_)
	{
		throw std::out_of_range(ERROR_INVALID_RANGE);
	}
	size_t amountOfDeletedElements = last - first;
	if (first != last)
	{
		if (last < size_)
		{
			for (size_t i = last; i < size_; i++)
			{
				data_[i - amountOfDeletedElements] = std::move(data_[i]); // Здесь более оптимально использовать оператор перемещающего присваивания, поэтому std::move
			}
		}
	}
	size_ -= amountOfDeletedElements;
}

template <typename T>
void Vector<T>::resize(size_t newSize, const T& value) // Изменение размера вектора с инициализирующим значением
{
	try
	{
		if (newSize > size_)
		{
			if (capacity_ < newSize)
			{
				this->reserve(newSize); // Может быть исключение bad_alloc или ...
			}
			for (size_t i = size_; i < newSize; i++)
			{
				data_[i] = value; // Может быть исключение ...
			}
		}
		size_ = newSize;
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
void Vector<T>::resize(size_t newSize) // Изменение размера вектора
{
	resize(newSize, T()); // Просто используем уже ранее написанный метод со значением по умолчанию
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity) // Резервирование памяти
{
	T* newData = nullptr;
	try
	{
		if (newCapacity > capacity_)
		{
			newData = new T[newCapacity]; // Может быть исключение bad_alloc
			copyDataTo(newData); // Может быть исключение ...
			delete[] data_;
			data_ = newData;
			capacity_ = newCapacity;
		}
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		delete[] newData; // Обязательно освобождаем память при исключении
		throw;
	}
}

template <typename T>
void Vector<T>::shrink_to_fit() // Уменьшение capacity_ до size_
{
	T* newData = nullptr;
	try
	{
		if (capacity_ > size_)
		{
			if (size_ > 0)
			{
				newData = new T[size_]; // Может быть исключение bad_alloc
				copyDataTo(newData); // Может быть исключение ...
			}
			delete[] data_;
			data_ = newData;
			capacity_ = size_;
		}
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		delete[] newData; // Обязательно освобождаем память при исключении
		throw;
	}
}

template <typename T>
size_t Vector<T>::size() const noexcept // Информация о размере
{
	return size_;
}

template <typename T>
size_t Vector<T>::capacity() const noexcept // Информация о ёмкости
{
	return capacity_;
}

template <typename T>
bool Vector<T>::empty() const noexcept // Является ли вектор пустым
{
	return size_ == 0;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const
{
	if (size_ != other.size_)
	{
		return false;
	}
	size_t i = 0;
	for (i = 0; i < size_ && data_[i] == other.data_[i]; i++)
	{ }
	return i == size_;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const
{
	return !(*this == other);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& other) const
{
	size_t minSize = size_ < other.size_ ? size_ : other.size_;
	for (size_t i = 0; i < minSize; i++)
	{
		if (data_[i] != other.data_[i])
		{
			return data_[i] < other.data_[i];
		}
	}
	return size_ < other.size_;
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& other) const
{
	return other < *this;
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& other) const
{
	return !(other < *this);
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& other) const
{
	return !(*this < other);
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) noexcept // Метод swap для идиомы copy-and-swap (реализация такая же, как и в std::vector)
{
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
}

#endif