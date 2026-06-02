#ifndef	DOUBLE_ORDERED_LIST_H
#define DOUBLE_ORDERED_LIST_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include <cassert>
#include <iterator>
#include "ListExceptions.h"

template <typename T>
class DoubleOrderedList
{
public:
	class Iterator;
	class ConstIterator;
	class ReverseIterator;
	class ConstReverseIterator;

	// Конструктор по умолчанию
	DoubleOrderedList();

	// Конструктор со значением
	DoubleOrderedList(const T& value);

	// Конструктор копирования
	DoubleOrderedList(const DoubleOrderedList<T>& rhs);

	// Метод swap (для идиомы copy-and-swap)
	void swap(DoubleOrderedList<T>& rhs) noexcept;

	// Конструктор перемещения
	DoubleOrderedList(DoubleOrderedList<T>&& rhs) noexcept;

	// Деструктор
	~DoubleOrderedList();

	// Оператор копирующего присваивания
	DoubleOrderedList<T>& operator=(const DoubleOrderedList<T>& rhs);

	// Оператор перемещающего присваивания
	DoubleOrderedList<T>& operator=(DoubleOrderedList<T>&& rhs) noexcept;

	// Доступ к головному элементу
	T head() const;

	// Доступ к хвостовому элементу
	T tail() const;

	// Поиск ключа
	bool search(const T& key) const noexcept;

	// Вставка узла
	template <typename V>
	void insert(V&& value);

	// Удаление головного элемента
	void removeHead();

	// Удаление всех элементов
	void clear() noexcept;

	// Размер списка
	size_t size() const noexcept { return size_; }

	// Пуст ли список
	bool isEmpty() const noexcept { return size_ == 0; }

	// Вывод значений всех элементов списка
	void print(std::ostream& out) const noexcept;

	// Удаление всех элементов с ключами [keyBegin, keyEnd]
	void removeKey(const T& keyBegin, const T& keyEnd);

	// Оператор равенства
	bool operator==(const DoubleOrderedList<T>& rhs) const noexcept;

	// Объединение (слияние) двух списков
	void merge(DoubleOrderedList<T>& rhs);

	// Удаление из первого списка элементов, встречающихся во втором
	void remove(const DoubleOrderedList& rhs) noexcept;

	// Отсортирован ли список (и нет ли в нём дубликатов)
	bool isListSorted() const noexcept;


	// ===== Методы для получения итераторов =====
	Iterator begin() { return Iterator(head_); }
	Iterator end() { return Iterator(); }

	ConstIterator begin() const { return ConstIterator(head_); }
	ConstIterator end() const { return ConstIterator(); }

	ConstIterator cbegin() const { return ConstIterator(head_); }
	ConstIterator cend() const { return ConstIterator(); }

	ReverseIterator rbegin() { return ReverseIterator(tail_); }
	ReverseIterator rend() { return ReverseIterator(); }

	ConstReverseIterator rbegin() const { return ConstReverseIterator(tail_); }
	ConstReverseIterator rend() const { return ConstReverseIterator(); }

	ConstReverseIterator crbegin() const { return ConstReverseIterator(tail_); }
	ConstReverseIterator crend() const { return ConstReverseIterator(); }
private:
	struct Node
	{
		T data_;     // Значение узла
		Node* prev_; // Указатель на предыдущий узел
		Node* next_; // Указатель на следующий узел

		template <typename V>
		Node(V&& value, Node* prev = nullptr, Node* next = nullptr)
			: data_(std::forward<V>(value)), prev_(prev), next_(next) {} // Может быть исключение ... при копировании
	};

	Node* head_; // Указатель на голову списка (первый узел)
	Node* tail_; // Указатель на хвост списка (последний узел)
	size_t size_; // Размер списка

	// Удаление узла
	void removeNode(Node* node) noexcept;

public:
	// ===== Прямой итератор =====
	class Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		using NodeType = typename DoubleOrderedList<T>::Node;
		using ThisType = Iterator;

		Iterator() : current_(nullptr) {}
		Iterator(NodeType* ptr) : current_(ptr) {}
		Iterator(const ThisType&) = default;
		ThisType& operator=(const ThisType&) = default;

		bool operator==(const ThisType& other) const { return current_ == other.current_; }
		bool operator!=(const ThisType& other) const { return !(*this == other); }

		T& operator*() const
		{
			assert(current_ != nullptr);
			return current_->data_;
		}
		T* operator->() const
		{
			assert(current_ != nullptr);
			return &(current_->data_);
		}

		ThisType& operator++()
		{
			assert(current_ != nullptr);
			current_ = current_->next_;
			return *this;
		}

		ThisType operator++(int)
		{
			ThisType temp(*this);
			operator++();
			return temp;
		}

		ThisType& operator--()
		{
			assert(current_ != nullptr);
			current_ = current_->prev_;
			return *this;
		}

		ThisType operator--(int)
		{
			ThisType temp(*this);
			operator--();
			return temp;
		}
	private:
		NodeType* current_;
	};

public:
	// ===== Константный итератор =====
	class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		using NodeType = const typename DoubleOrderedList<T>::Node;
		using ThisType = ConstIterator;

		ConstIterator() : current_(nullptr) {}
		ConstIterator(NodeType* ptr) : current_(ptr) {}
		ConstIterator(const ThisType&) = default;
		ThisType& operator=(const ThisType&) = default;

		bool operator==(const ThisType& other) const { return current_ == other.current_; }
		bool operator!=(const ThisType& other) const { return !(*this == other); }

		const T& operator*() const
		{
			assert(current_ != nullptr);
			return current_->data_;
		}
		const T* operator->() const
		{
			assert(current_ != nullptr);
			return &(current_->data_);
		}

		ThisType& operator++()
		{
			assert(current_ != nullptr);
			current_ = current_->next_;
			return *this;
		}

		ThisType operator++(int)
		{
			ThisType temp(*this);
			operator++();
			return temp;
		}

		ThisType& operator--()
		{
			assert(current_ != nullptr);
			current_ = current_->prev_;
			return *this;
		}

		ThisType operator--(int)
		{
			ThisType temp(*this);
			operator--();
			return temp;
		}
	private:
		NodeType* current_;
	};

public:
	// ===== Реверсивный итератор =====
	class ReverseIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		using NodeType = typename DoubleOrderedList<T>::Node;
		using ThisType = ReverseIterator;

		ReverseIterator() : current_(nullptr) {}
		ReverseIterator(NodeType* ptr) : current_(ptr) {}
		ReverseIterator(const ThisType&) = default;
		ThisType& operator=(const ThisType&) = default;

		bool operator==(const ThisType& other) const { return current_ == other.current_; }
		bool operator!=(const ThisType& other) const { return !(*this == other); }

		T& operator*() const
		{
			assert(current_ != nullptr);
			return current_->data_;
		}
		T* operator->() const
		{
			assert(current_ != nullptr);
			return &(current_->data_);
		}

		ThisType& operator++()
		{
			assert(current_ != nullptr);
			current_ = current_->prev_;
			return *this;
		}
		ThisType operator++(int)
		{
			ThisType temp(*this);
			operator++();
			return temp;
		}

		ThisType& operator--()
		{
			assert(current_ != nullptr);
			current_ = current_->next_;
			return *this;
		}

		ThisType operator--(int)
		{
			ThisType temp(*this);
			operator--();
			return temp;
		}
	private:
		NodeType* current_;
	};

public:
	// ===== Константный реверсивный итератор =====
	class ConstReverseIterator : public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		using NodeType = const typename DoubleOrderedList<T>::Node;
		using ThisType = ConstReverseIterator;

		ConstReverseIterator() : current_(nullptr) {}
		ConstReverseIterator(NodeType* ptr) : current_(ptr) {}
		ConstReverseIterator(const ThisType&) = default;
		ThisType& operator=(const ThisType&) = default;

		bool operator==(const ThisType& other) const { return current_ == other.current_; }
		bool operator!=(const ThisType& other) const { return !(*this == other); }

		const T& operator*() const
		{
			assert(current_ != nullptr);
			return current_->data_;
		}
		const T* operator->() const
		{
			assert(current_ != nullptr);
			return &(current_->data_);
		}

		ThisType& operator++()
		{
			assert(current_ != nullptr);
			current_ = current_->prev_;
			return *this;
		}
		ThisType operator++(int)
		{
			ThisType temp(*this);
			operator++();
			return temp;
		}
		ThisType& operator--()
		{
			assert(current_ != nullptr);
			current_ = current_->next_;
			return *this;
		}

		ThisType operator--(int)
		{
			ThisType temp(*this);
			operator--();
			return temp;
		}
	private:
		NodeType* current_;
	};
};

// Конструктор по умолчанию
template <typename T>
DoubleOrderedList<T>::DoubleOrderedList() : head_(nullptr), tail_(nullptr), size_(0) {}

// Конструктор со значением
template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(const T& value) : head_(nullptr), tail_(nullptr), size_(0)
{
	try
	{
		head_ = new Node(value); // Может быть исключение bad alloc или ...
		tail_ = head_; // хвост указывает на тот же узел, что и голова (т.к. 1 узел)
		size_++; // Увеличиваем размер
	}
	catch (const std::bad_alloc&)
	{
		throw List::BadAllocation();
	}
	catch (...)
	{
		throw List::ErrorInCopying();
	}
}

// Конструктор копирования
template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(const DoubleOrderedList<T>& rhs) : head_(nullptr), tail_(nullptr), size_(0)
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
		throw List::BadAllocation();
	}
	catch (...)
	{
		clear(); // Освобождаем память, иначе - утечка
		throw List::ErrorInCopying();
	}
}

// Метод swap (для идиомы copy-and-swap)
template <typename T>
void DoubleOrderedList<T>::swap(DoubleOrderedList<T>& rhs) noexcept
{
	std::swap(head_, rhs.head_);
	std::swap(tail_, rhs.tail_);
	std::swap(size_, rhs.size_);
}

// Конструктор перемещения
template <typename T>
DoubleOrderedList<T>::DoubleOrderedList(DoubleOrderedList<T>&& rhs) noexcept : head_(nullptr), tail_(nullptr), size_(0)
{
	this->swap(rhs);
}

// Деструктор
template <typename T>
DoubleOrderedList<T>::~DoubleOrderedList()
{
	clear();
}

// Оператор копирующего присваивания
template <typename T>
DoubleOrderedList<T>& DoubleOrderedList<T>::operator=(const DoubleOrderedList<T>& rhs)
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
		throw List::BadAllocation();
	}
	catch (...)
	{
		throw List::ErrorInCopying();
	}
}

// Оператор перемещающего присваивания
template <typename T>
DoubleOrderedList<T>& DoubleOrderedList<T>::operator=(DoubleOrderedList<T>&& rhs) noexcept
{
	if (this != &rhs)
	{
		this->swap(rhs);
	}
	return *this;
}

// Доступ к головному элементу
template <typename T>
T DoubleOrderedList<T>::head() const
{
	if (isEmpty())
	{
		throw List::EmptyList();
	}
	return head_->data_;
}

// Доступ к хвостовому элементу
template <typename T>
T DoubleOrderedList<T>::tail() const
{
	if (isEmpty())
	{
		throw List::EmptyList();
	}
	return tail_->data_;
}

// Удаление головного элемента
template <typename T>
void DoubleOrderedList<T>::removeHead()
{
	if (isEmpty())
	{
		throw List::EmptyList();
	}
	removeNode(head_);
}

// Удаление всех элементов
template <typename T>
void DoubleOrderedList<T>::clear() noexcept
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

// Вывод значений всех элементов списка
template <typename T>
void DoubleOrderedList<T>::print(std::ostream& out) const noexcept
{
	if (!isEmpty())
	{
		auto it = this->cbegin();
		out << *it++;
		for (; it != this->cend(); it++)
		{
			out << ", " << *it;
		}
	}
}

// Удаление узла
template <typename T>
void DoubleOrderedList<T>::removeNode(Node* node) noexcept
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

// Вставка узла
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
		throw List::BadAllocation();
	}
	catch (...)
	{
		throw List::ErrorInCopying();
	}
}

// Поиск ключа
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

// Удаление всех элементов с ключами [keyBegin, keyEnd]
template <typename T>
void DoubleOrderedList<T>::removeKey(const T& keyBegin, const T& keyEnd)
{
	if (keyBegin > keyEnd) // Если правая граница больше левой
	{
		throw List::InvalidKeyRange(); // Бросаем исключение
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

// Оператор равенства
template <typename T>
bool DoubleOrderedList<T>::operator==(const DoubleOrderedList<T>& rhs) const noexcept
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

// Объединение (слияние) двух списков
template <typename T>
void DoubleOrderedList<T>::merge(DoubleOrderedList<T>& rhs)
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

// Удаление из первого списка элементов, встречающихся во втором
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

// Отсортирован ли список (и нет ли в нём дубликатов)
template <typename T>
bool DoubleOrderedList<T>::isListSorted() const noexcept
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