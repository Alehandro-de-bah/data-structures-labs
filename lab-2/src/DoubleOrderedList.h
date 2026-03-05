#ifndef	DOUBLE_ORDERED_LIST_H
#define DOUBLE_ORDERED_LIST_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include "exceptions.h"

template <typename T>
class DoubleOrderedList
{
public:
	// Конструкторы и деструктор
	DoubleOrderedList();
	DoubleOrderedList(const T& value);
	DoubleOrderedList(const DoubleOrderedList<T>& rhs);
	void swap(DoubleOrderedList<T>& rhs) noexcept;
	DoubleOrderedList(DoubleOrderedList<T>&& rhs) noexcept;
	~DoubleOrderedList();

	// Операторы присваивания
	DoubleOrderedList<T>& operator=(const DoubleOrderedList<T>& rhs);
	DoubleOrderedList<T>& operator=(DoubleOrderedList<T>&& rhs) noexcept;

	// Доступ к узлам
	T head() const;
	T tail() const;
	bool search(const T& key) const noexcept;

	// Вставка узлов
	template <typename V>
	void insert(V&& value);

	// Удаление узлов
	void removeHead();
	void clear() noexcept;

	// Информация о состоянии
	size_t size() const noexcept { return size_; }
	bool isEmpty() const noexcept { return size_ == 0; }
	void print() const noexcept;

	// Базовые требования к классу DoubleOrderedList<T>
	void removeKey(const T& keyBegin, const T& keyEnd);
	bool operator==(const DoubleOrderedList<T>& rhs) const noexcept;

	// Дополнение к базовой части
	void merge(DoubleOrderedList<T>& rhs);
	void remove(const DoubleOrderedList& rhs) noexcept;

	// Отсортирован ли список (и нет ли в нём дубликатов)
	bool isListSorted() const noexcept;
private:
	struct Node
	{
		T data_; // Значение узла
		Node* prev_; // Указатель на предыдущий узел
		Node* next_; // Указатель на следующий узел

		template <typename V>
		Node(V&& value, Node* prev = nullptr, Node* next = nullptr)
			: data_(std::forward<V>(value)), prev_(prev), next_(next) {} // Может быть исключение ... при копировании

		// Правило пяти
		Node(const Node& rhs) = delete;
		Node(Node&& rhs) = delete;
		Node& operator=(const Node& rhs) = delete;
		Node& operator=(Node&& rhs) = delete;
		~Node() = default;
	};

	Node* head_; // Указатель на голову списка (первый узел)
	Node* tail_; // Указатель на хвост списка (последний узел)
	size_t size_; // Размер списка

	void removeNode(Node* node) noexcept; // Удаление заданного узла (для внутренней логики)
};

template <typename T>
DoubleOrderedList<T>::DoubleOrderedList() : head_(nullptr), tail_(nullptr), size_(0) {} // Конструктор по умолчанию

template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(const T& value) : head_(nullptr), tail_(nullptr), size_(0) // Конструктор со значением
{
	try
	{
		head_ = new Node(value); // Может быть исключение bad alloc или ...
		tail_ = head_; // хвост указывает на тот же узел, что и голова (т.к. 1 узел)
		size_++; // Увеличиваем размер
	}
	catch (const std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(const DoubleOrderedList<T>& rhs) : head_(nullptr), tail_(nullptr), size_(0) // Конструктор копирования
{
	try
	{
		if (rhs.head_ != nullptr) // Если список rhs не пустой
		{
			head_ = new Node(rhs.head_->data_); // Может быть исключение bad alloc или ...
			size_++; // Увеличиваем размер (т.к. создали голову)
			Node* srcPtr = rhs.head_->next_; // Заводим указатель на следующий за головой узел
			Node* destPtr = head_; // Заводим указатель на голову списка
			while (srcPtr != nullptr) // Проходимся до конца списка rhs
			{
				destPtr->next_ = new Node(srcPtr->data_, destPtr, nullptr); // Может быть исключение bad alloc или ...
				destPtr = destPtr->next_; // Сдвигаем указатель
				srcPtr = srcPtr->next_; // Сдвигаем указатель
				size_++; // Увеличиваем размер
			}
			tail_ = destPtr; // После цикла хвост указывает на последний узел (т.е. destPtr)
		}
	}
	catch (const std::bad_alloc&)
	{
		clear();
		throw;
	}
	catch (...)
	{
		clear(); // Освобождаем память, иначе - утечка
		throw;
	}
}

template <typename T>
void DoubleOrderedList<T>::swap(DoubleOrderedList<T>& rhs) noexcept // Метод swap (для идиомы copy-and-swap)
{
	std::swap(head_, rhs.head_);
	std::swap(tail_, rhs.tail_);
	std::swap(size_, rhs.size_);
}

template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(DoubleOrderedList<T>&& rhs) noexcept : head_(nullptr), tail_(nullptr), size_(0) // Конструктор перемещения
{
	this->swap(rhs);
}

template <typename T>
DoubleOrderedList<T>::~DoubleOrderedList() // Деструктор
{
	clear();
}

template <typename T>
DoubleOrderedList<T>& DoubleOrderedList<T>::operator=(const DoubleOrderedList<T>& rhs) // Оператор копирующего присваивания
{
	try
	{
		if (this != &rhs)
		{
			DoubleOrderedList<T> temp(rhs); // Может быть исключение bad alloc или ...
			this->swap(temp);
		}
		return *this;
	}
	catch (const std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
DoubleOrderedList<T>& DoubleOrderedList<T>::operator=(DoubleOrderedList<T>&& rhs) noexcept // Оператор перемещающего присваивания
{
	if (this != &rhs)
	{
		this->swap(rhs);
	}
	return *this;
}

template <typename T>
T DoubleOrderedList<T>::head() const // Доступ к голове списка
{
	if (isEmpty())
	{
		throw std::out_of_range(ERROR_LIST_IS_EMPTY);
	}
	return head_->data_;
}

template <typename T>
T DoubleOrderedList<T>::tail() const // Доступ к хвосту списка
{
	if (isEmpty())
	{
		throw std::out_of_range(ERROR_LIST_IS_EMPTY);
	}
	return tail_->data_;
}

template <typename T>
void DoubleOrderedList<T>::removeHead() // Удаление головы списка
{
	if (isEmpty())
	{
		throw std::out_of_range(ERROR_LIST_IS_EMPTY);
	}
	removeNode(head_);
}

template <typename T>
void DoubleOrderedList<T>::clear() noexcept // Удаление всех элементов
{
	while (head_ != nullptr) // Проходимся по всему списку
	{
		Node* nodeToDelete = head_; // Запоминаем узел, который нужно удалить
		head_ = head_->next_; // Продвигаемся вперёд
		delete nodeToDelete; // Удаляем узел, который запоминали
	}
	tail_ = nullptr; // Хвост должен указывать на nullptr после очистки
	size_ = 0; // Список очищен => обнуляем размер
}

template <typename T>
void DoubleOrderedList<T>::print() const noexcept // Вывод значений всех узлов списка
{
	std::cout << "{ ";
	for (Node* ptr = head_; ptr != nullptr; ptr = ptr->next_)
	{
		std::cout << ptr->data_ << " ";
	}
	std::cout << "}" << std::endl;
}

template <typename T>
void DoubleOrderedList<T>::removeNode(Node* node) noexcept // Удаление заданного узла (для внутренней логики)
{
	if (node != nullptr) // Проверка на то, что узел node - это действительно узел
	{
		if (node->prev_ != nullptr) // Если node - это не голова
		{
			node->prev_->next_ = node->next_; // Корректируем указатели
		}
		else // Если node - это голова
		{
			head_ = node->next_; // Сдвигаем голову
			if (head_ != nullptr) // Если после node есть узел
			{
				head_->prev_ = nullptr; // Корректируем указатель (перед головой узлов нет)
			}
		}
		if (node->next_ != nullptr) // Если после node есть узел
		{
			node->next_->prev_ = node->prev_; // Корректируем указатель
		}
		else // Если после node нет узла (т.е. node - это хвост)
		{
			tail_ = node->prev_; // Теперь хвост - это узел перед node
			if (tail_ != nullptr) // Если node - это не голова
			{
				tail_->next_ = nullptr; // Корректируем указатель (после хвоста узлов нет)
			}
		}
		delete node; // После всех корректировок указателей удаляем node
		size_--; // Уменьшаем размер
	}
}

template <typename T>
template <typename V>
void DoubleOrderedList<T>::insert(V&& value)
{
	try
	{
		Node* newNode = nullptr; // создаём новый узел (изначально nullptr)
		Node* currentNode = head_; // для прохода по узлам
		while (currentNode != nullptr && currentNode->data_ < value) // проходим по списку, начиная с головы, пока не дойдём до конца
		{															 // или не встретим значение большее, чем текущее
			currentNode = currentNode->next_;
		}
		if (currentNode == nullptr) // если список пустой или нужно вставить новый узел в конец
		{
			newNode = new Node(std::forward<V>(value), tail_, nullptr); // создаём новый узел
			if (tail_ != nullptr) // если список не пустой
			{
				tail_->next_ = newNode; // next_ у хвоста будет указывать на новый узел
			}
			else // если список пустой
			{
				head_ = newNode; // голова будет указывать на новый узел
			}
			tail_ = newNode; // теперь хвост - это новый узел
			size_++; // вставили узел => увеличили размер списка
		}
		else if (currentNode->data_ != value) // если значения текущего и нового узлов не совпадают  
		{
			if (currentNode->prev_ == nullptr) // если текущий узел является головой (вставка в начало списка)
			{
				newNode = new Node(std::forward<V>(value), nullptr, head_); // создаём новый узел
				head_->prev_ = newNode; // prev_ у головы указывает на новый узел 
				head_ = newNode; // теперь голова - это новый узел
			}
			else // если текущий узел не является головой (вставка в середину)
			{
				newNode = new Node(std::forward<V>(value), currentNode->prev_, currentNode); // создаём новый узел
				currentNode->prev_->next_ = newNode; // связываем новый узел с узлами списка
				currentNode->prev_ = newNode;
			}
			size_++; // вставили узел => увеличили размер списка
		}
	}
	catch (const std::bad_alloc&)
	{
		throw;
	}
	catch (...)
	{
		throw;
	}
}

template <typename T>
bool DoubleOrderedList<T>::search(const T& key) const noexcept
{
	Node* currentNode = head_; // Заводим указатель на голову списка
	while (currentNode != nullptr && currentNode->data_ < key) // Проходимся по списку, пока не дойдём до конца или не встретим ключ key
	{
		currentNode = currentNode->next_; // Продвигаемся дальше
	}
	return (currentNode != nullptr && currentNode->data_ == key) ? true : false;
}

template <typename T>
void DoubleOrderedList<T>::removeKey(const T& keyBegin, const T& keyEnd) // Удаление всех узлов с ключами [keyBegin, keyEnd]
{
	if (keyBegin > keyEnd) // Если правая граница больше левой
	{
		throw std::out_of_range(ERROR_OUT_OF_RANGE_IN_REMOVE_KEYS); // Бросаем исключение
	}
	if (size_ != 0) // Если список не пустой
	{
		Node* currentNode = head_;
		while (currentNode != nullptr && currentNode->data_ < keyBegin) // Идём вперёд, пока не встретим узел, значение которого больше или равно keyBegin
		{
			currentNode = currentNode->next_; // Продвигаемся вперёд
		}
		while (currentNode != nullptr && currentNode->data_ <= keyEnd) // Проходимся по циклу, пока не встретим узел, значение которого больше keyEnd 
		{
			Node* nodeToDelete = currentNode; // Узел, который нужно удалить
			currentNode = currentNode->next_; // Продвигаемся вперёд
			removeNode(nodeToDelete); // Удаляем нужный узел
		}
	}
}

template <typename T>
bool DoubleOrderedList<T>::operator==(const DoubleOrderedList<T>& rhs) const noexcept // Оператор ==
{
	if (size_ != rhs.size_) // Если размеры списков разные
	{
		return false; // Сразу возвращаем false
	}
	Node* thisCurrentNode = head_; // Заводим указатель на голову у this
	Node* rhsCurrentNode = rhs.head_; // Заводим указатель на голову у rhs
	while (thisCurrentNode != nullptr && thisCurrentNode->data_ == rhsCurrentNode->data_) // Проходимся по спискам, пока не дойдём до конца
																						// или не встретим разные элементы
	{
		thisCurrentNode = thisCurrentNode->next_; // Продвигаемся дальше
		rhsCurrentNode = rhsCurrentNode->next_; // Продвигаемся дальше
	}
	return thisCurrentNode == nullptr; // Возвращаем true, если дошли до конца, иначе - false
}

template <typename T>
void DoubleOrderedList<T>::merge(DoubleOrderedList<T>& rhs) // Объединение (слияние) двух списков
{
	if (this->isEmpty()) // Если список this пустой
	{
		this->swap(rhs); // Просто обмениваемся списками
	}
	else if (this != &rhs && !rhs.isEmpty()) // Если списки разные и список rhs не пустой
	{
		Node* thisCurrentNode = head_; // Заводим указатель на голову this
		Node* rhsCurrentNode = rhs.head_; // Заводим указател на голову rhs
		Node* thisPrevNode = nullptr; // Заводим указатель на узел перед thisCurrentNode
		while (rhsCurrentNode != nullptr && thisCurrentNode != nullptr) // Проходимся по спискам, пока не дойдём до конца одного из них
		{
			if (thisCurrentNode->data_ < rhsCurrentNode->data_)
			{
				thisPrevNode = thisCurrentNode; // Продвигаемся дальше по списку this
				thisCurrentNode = thisCurrentNode->next_; // Продвигаемся дальше по списку this
			}
			else if (thisCurrentNode->data_ > rhsCurrentNode->data_)
			{
				// Нужно вставить rhsCurrentNode перед thisCurrentNode
				Node* rhsNextNode = rhsCurrentNode->next_; // Запоминаем узел, следующий за rhsCurrentNode
				rhsCurrentNode->next_ = thisCurrentNode; // Корректируем указатели
				rhsCurrentNode->prev_ = thisCurrentNode->prev_; 
				if (thisCurrentNode->prev_ != nullptr) // Если thisCurrentNode - это не голова списка this
				{
					thisCurrentNode->prev_->next_ = rhsCurrentNode; // Корректируем указатель
				}
				else // Если thisCurrentNode - это голова списка this
				{
					head_ = rhsCurrentNode; // Теперь голова - это rhsCurrentNode
				}
				thisCurrentNode->prev_ = rhsCurrentNode; // Корректируем указатель
				size_++; // Увеличиваем размер списка this (т.к. вставили узел)
				rhs.size_--; // Соответственно уменьшаем размер списка rhs
				rhsCurrentNode = rhsNextNode; // Продвигаемся дальше по списку rhs
			}
			else
			{
				Node* nodeToDelete = rhsCurrentNode;
				rhsCurrentNode = rhsCurrentNode->next_;
				delete nodeToDelete;
				rhs.size_--;
			}
		}
		if (rhsCurrentNode != nullptr && thisCurrentNode == nullptr) // Если дошли до конца списка this, но до rhs - ещё нет
		{
			if (thisPrevNode != nullptr) // Если есть предыдущий узел к у this
			{
				thisPrevNode->next_ = rhsCurrentNode; // Корректируем указатели
				rhsCurrentNode->prev_ = thisPrevNode;
				tail_ = rhs.tail_; // Теперь хвост у списка this - это хвост у списка rhs 
			}
			size_ += rhs.size_; // Добавили в список this оставшиеся узлы списка rhs => увеличили размер
		}
		rhs.head_ = nullptr; // "Обнуляем" список rhs (он должен быть пустым)
		rhs.tail_ = nullptr;
		rhs.size_ = 0;
	}
}

template <typename T>
void DoubleOrderedList<T>::remove(const DoubleOrderedList<T>& rhs) noexcept
{
	if (!this->isEmpty() && !rhs.isEmpty()) // Если списки не пустые
	{
		Node* thisCurrentNode = head_; // Заводим указатель на голову this
		Node* rhsCurrentNode = rhs.head_; // Заводим указатель на голову rhs
		while (thisCurrentNode != nullptr && rhsCurrentNode != nullptr) // Проходимся по двум спискам
		{
			if (thisCurrentNode->data_ < rhsCurrentNode->data_)
			{
				thisCurrentNode = thisCurrentNode->next_; // Продвигаемся по списку this
			}
			else if (thisCurrentNode->data_ > rhsCurrentNode->data_)
			{
				rhsCurrentNode = rhsCurrentNode->next_; // Продвигаемся по списку rhs
			}
			else // Элементы списков равны
			{
				Node* nodeToDelete = thisCurrentNode; // Запоминаем узел, который нужно удалить
				thisCurrentNode = thisCurrentNode->next_; // Продвигаемся дальше
				removeNode(nodeToDelete); // Удаляем нужный узел
				rhsCurrentNode = rhsCurrentNode->next_; // Продвигаемся дальше
			}
		}
	}
}

template <typename T>
bool DoubleOrderedList<T>::isListSorted() const noexcept // Отсортирован ли список (и одновременно нет ли дубликатов)
{
	Node* currentNode = head_; // Заводим указатель на голову
	Node* nextNode = (currentNode == nullptr ? nullptr : currentNode->next_); // Заводим указатель на узел, следующий за головой
	while (nextNode != nullptr) // Проходимся по списку
	{
		if (currentNode->data_ >= nextNode->data_) // Если текущий элемент больше или равен следующему
		{
			return false; // Возвращаем false (список не отсортирован или есть дубликаты)
		}
		currentNode = nextNode; // Продвигаемся дальше
		nextNode = nextNode->next_;
	}
	return true; // Возвращаем true (т.к. дошли до конца)
}

/*Сложность алгоритмов
DoubleOrderedList() - O(1)
DoubleOrderedList(const T& value) - O(1)
DoubleOrderedList(const DoubleOrderedList<T>& rhs) - O(n)
DoubleOrderedList(DoubleOrderedList<T>&& rhs) - O(1)
~DoubleOrderedList() - O(n)

swap(DoubleOrderedList<T>& rhs) - O(1)
operator=(const DoubleOrderedList<T>& rhs) - O(n)
operator=(DoubleOrderedList<T>&& rhs) - O(1)

head() - O(1)
tail() - O(1)
search(const T& key) - O(1) (в лучшем случае), O(n) (в худшем случае)

insert(V&& value) - O(1) (в лучшем случае), O(n) (в худшем случае)
removeHead() - O(1)
removeNode(Node* node) - O(1)
removeKey(const T& keyBegin, const T& keyEnd) - O(n)
clear() - O(n)

operator==(const DoubleOrderedList<T>& rhs) - O(1) (в лучшем случае), O(n) (в худшем случае)
merge(DoubleOrderedList<T>& rhs) - O(n + m)
remove(const DoubleOrderedList& rhs) - O(n + m)

isListSorted() - O(n)
*/

#endif