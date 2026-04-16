#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include "StackArray.h"
#include "QueueVector.h"
#include "BinarySearchTreeExceptions.h"

template <typename T>
class BinarySearchTree
{
public:
	// Конструктор по умолчанию
	BinarySearchTree();

	// Конструктор копирования (запрещён)
	BinarySearchTree(const BinarySearchTree<T>&) = delete;

	// Конструктор перемещения
	BinarySearchTree(BinarySearchTree<T>&& rhs) noexcept;

	// Оператор копирующего присваивания (запрещён)
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>&) = delete;

	// Оператор перемещающего присваивания
	BinarySearchTree<T>& operator=(BinarySearchTree<T>&& rhs) noexcept;

	// Деструктор
	virtual ~BinarySearchTree();

	// Поиск по ключу (итеративный)
	bool searchIterative(const T& key) const;

	// Вставка элемента по ключу
	bool insert(const T& key);

	// Удаление элемента по ключу
	bool remove(const T& key); 

	// Вывод дерева с использованием скобок
	void output(std::ostream& out) const;

	// Определение количества узлов дерева
	int getNumberOfNodes() const;

	// Определение высоты дерева
	int getHeight() const;

	// Инфиксный обход дерева (итеративный)
	void inorderWalkIterative() const;

	// Инфиксный обход дерева (рекурсивный)
	void inorderWalk() const;

	// Обход двоичного дерева по уровням (в ширину)
	void walkByLevels() const;

	// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (рекурсивно)
	int countKeysInRange(const T& low, const T& high) const;

	// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (итеративно)
	int countKeysInRangeIterative(const T& low, const T& high) const;
private:
	struct Node
	{
		T key_; // Значение ключа, содержащееся в узле
		Node* left_; // Указатель на левое поддерево
		Node* right_; // Указатель на правое поддерево
		Node* p_; // Указатель на родителя !!! не используется

		Node(const T& key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) // Конструктор узла
			: key_(key), left_(left), right_(right), p_(p) {} // Может быть исключение ... при копировании
	};

	Node* root_; // Указатель на корневой узел

	// Удаление узлов дерева
	void clear(Node* node);

	// Метод swap для идиомы copy-and-swap
	void swap(BinarySearchTree<T>& rhs) noexcept;

	// Поиск по ключу (итеративный)
	Node* findIterative(const T& key) const;

	// Вывод дерева с использованием скобок
	void output(std::ostream& out, Node* node) const;

	// Определение количества узлов дерева
	int getNumberOfNodes(const Node* node) const;

	// Определение высоты дерева
	int getHeight(const Node* node) const;

	// Инфиксный обход дерева (рекурсивный)
	void inorderWalk(Node* node) const;

	// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (рекурсивно)
	int countNodesInRange(Node* node, const T& low, const T& high) const;

	// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (итеративно)
	int countNodesInRangeIterative(Node* node, const T& low, const T& high) const;
};

// ===== Реализация private методов =====

// Удаление узлов дерева
template <typename T>
void BinarySearchTree<T>::clear(Node* node)
{
	if (node != nullptr)
	{
		clear(node->left_);
		clear(node->right_);
		delete node;
	}
}
// Порядок, в котором будут удаляться ключи: 1 4 7 6 3 13 14 10 8

// Метод swap для идиомы copy-and-swap
template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& rhs) noexcept
{
	std::swap(root_, rhs.root_);
}

// Поиск по ключу (итеративный)
template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findIterative(const T& key) const
{
	Node* currentNode = root_; // Заводим указатель на корень узла
	while (currentNode != nullptr && currentNode->key_ != key) // Пока не дошли до конца дерева или не нашли искомый ключ
	{
		if (key < currentNode->key_) // Если ключ, к-ый мы ищем, меньше текущего
		{
			currentNode = currentNode->left_; // Идём влево
		}
		else // Если ключ, к-ый мы ищем, больше текущего
		{
			currentNode = currentNode->right_; // Идём вправо
		}
	}
	return currentNode; // Если не нашли ключ key, вернётся nullptr
}

// Вывод дерева с использованием скобок
template <typename T>
void BinarySearchTree<T>::output(std::ostream& out, Node* node) const
{
	if (node == nullptr) // Если узел "нулевой"
	{
		out << "()"; // Выводим пустые скобки
	}
	else
	{
		out << "("; // Выводим открывающую скобку
		out << node->key_; // Выводим ключ узла
		if (node->left_ != nullptr) // Если у node есть левый ребёнок
		{
			out << " "; // Выводим пробел
			output(out, node->left_); // Выводим левое поддерево
		}
		else // Если у node нет левого ребёнока
		{
			out << " ()"; // Выводим пустые скобки
		}
		if (node->right_ != nullptr) // Если у node есть правый ребёнок
		{
			out << " "; // Выводим пробел
			output(out, node->right_); // Выводим правое поддерево
		}
		else // Если у node нет правого ребёнока
		{
			out << " ()"; // Выводим пустые скобки
		}
		out << ")"; // Выводим закрывающую скобку
	}
}

// Определение количества узлов дерева
template <typename T>
int BinarySearchTree<T>::getNumberOfNodes(const Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return (1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_));
}

// Определение высоты дерева
template <typename T>
int BinarySearchTree<T>::getHeight(const Node* node) const
{
	if (node != nullptr)
	{
		int leftTreeHeight = getHeight(node->left_); // Высота левого поддерева
		int rightTreeHeight = getHeight(node->right_); // Высота правого поддерева
		int maxHeight = (leftTreeHeight > rightTreeHeight) ? leftTreeHeight : rightTreeHeight;
		return 1 + maxHeight;
	}
	else
	{
		return -1; // Считаем, что высота пустого дерева равна -1 (высота дерева, состоящего только из корня, равна 0)
	}
}

// Инфиксный обход дерева (рекурсивный)
template <typename T>
void BinarySearchTree<T>::inorderWalk(Node* node) const
{
	if (node != nullptr)
	{
		inorderWalk(node->left_);
		std::cout << node->key_ << " ";
		inorderWalk(node->right_);
	}
}

// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (рекурсивно)
template <typename T>
int BinarySearchTree<T>::countNodesInRange(Node* node, const T& low, const T& high) const
{
	if (low > high) // Если некорректно заданы границы диапазона
	{
		throw InvalidRange(); // Выбрасываем исключение
	}
	if (node == nullptr)
	{
		return 0;
	}
	int amountOfNodes = 0;
	if (node->key_ == low) // Если ключ node равен левой границе
	{
		amountOfNodes = 1 + countNodesInRange(node->right_, low, high); // Идём только в правое поддерево
	}
	else if (node->key_ == high) // Если ключ node равен правой границе
	{
		amountOfNodes = 1 + countNodesInRange(node->left_, low, high); // Идём только в левое поддерево
	}
	else if (node->key_ > low && node->key_ < high) // Если ключ node находится в диапазоне [low, high]
	{
		amountOfNodes = 1 + countNodesInRange(node->left_, low, high) + countNodesInRange(node->right_, low, high);
	}
	else if (node->key_ < low) // Если ключ node меньше левой границы
	{
		amountOfNodes = countNodesInRange(node->right_, low, high); // Пытаемся найти подходящие узлы с в правом поддереве
	}
	else // Если ключ node больше правой границы
	{
		amountOfNodes = countNodesInRange(node->left_, low, high); // Пытаемся найти подходящие узлы в левом поддереве
	}
	return amountOfNodes;
}

// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (итеративно)
template <typename T>
int BinarySearchTree<T>::countNodesInRangeIterative(Node* node, const T& low, const T& high) const
{
	if (low > high) // Если некорректно заданы границы диапазона
	{
		throw InvalidRange(); // Выбрасываем исключение
	}
	int amountOfNodes = 0; // Заводим счётчик узлов в заданном диапазоне
	StackArray<Node*> s(getHeight(node)); // Заводим стек из указателей на узлы
	if (node != nullptr)
	{
		s.push(node);
	}
	while (!s.isEmpty()) // Пока стек не пуст
	{
		Node* currentNode = s.pop(); // Снимаем вершину стека
		amountOfNodes += (currentNode->key_ >= low && currentNode->key_ <= high) ? 1 : 0; // Увеличиваем счётчик, если ключ в диапазоне
		if (currentNode->left_ != nullptr && currentNode->key_ >= low) // Если у currentNode есть левый ребёнок и его ключ не меньше левой границы
		{
			s.push(currentNode->left_); // Заносим в стек левого ребёнка (идём в левое поддерево)
		}
		if (currentNode->right_ != nullptr && currentNode->key_ <= high) // Если у currentNode есть правый ребёнок и его ключ не больше правой границы
		{
			s.push(currentNode->right_); // Заносим в стек правого ребёнка (идём в правое поддерево)
		}
	}
	return amountOfNodes;
}

// ===== Реализация public методов =====

// Конструктор по умолчанию
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

// Конструктор перемещения
template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& rhs) noexcept : root_(nullptr)
{
	this->swap(rhs);
}

// Оператор перемещающего присваивания
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& rhs) noexcept
{
	if (this != &rhs)
	{
		this->swap(rhs);
	}
	return *this;
}

// Деструктор
template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	clear(root_);
}

// Поиск по ключу (итеративный)
template <typename T>
bool BinarySearchTree<T>::searchIterative(const T& key) const
{
	return findIterative(key) != nullptr;
}

// Вставка элемента по ключу
template <typename T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node* parent = nullptr; // Указатель на родителя currentNode
	Node* currentNode = root_; // Указатель на текущий узел

	while (currentNode != nullptr) // В цикле ищем место для вставки узла
	{
		parent = currentNode; // Обновляем указатель на родителя
		if (key < currentNode->key_)
		{
			currentNode = currentNode->left_; // Идём влево
		}
		else if (key > currentNode->key_)
		{
			currentNode = currentNode->right_; // Идём вправо
		}
		else
		{
			return false; // Ключи равны!
		}
	}
	
	Node* newNode = nullptr;
	try // Создаём новый узел
	{
		newNode = new Node(key); // Может быть исключение std::bad_alloc или ... при копировании
	}
	catch (const std::bad_alloc&)
	{
		throw BadAllocationInInsert();
	}
	catch (...)
	{
		throw ErrorInCopying();
	}

	newNode->p_ = parent; // Устанавливаем связь родителя с newNode
	if (parent == nullptr) // Вставка узла в пустое дерево
	{
		root_ = newNode; // newNode - корень дерева
	}
	else if (key < parent->key_)
	{
		parent->left_ = newNode; // newNode - левый ребёнок у parent
	}
	else
	{
		parent->right_ = newNode; // newNode - правый ребёнок у parent
	}
	return true;
}

// Удаление элемента по ключу
template <typename T>
bool BinarySearchTree<T>::remove(const T& key)
{
	Node* currentNodeParent = nullptr; // Указатель на родителя currentNode
	Node* currentNode = root_; // Указатель на текущий узел
	while (currentNode != nullptr && currentNode->key_ != key) // В цикле ищем узел, который нужно удалить
	{
		currentNodeParent = currentNode; // Обновляем указатель на родителя
		if (key < currentNode->key_)
		{
			currentNode = currentNode->left_; // Идём влево
		}
		else
		{
			currentNode = currentNode->right_; // Идём вправо
		}
	}
	if (currentNode == nullptr) // Если не нашли узла с заданным ключом
	{
		return false;
	}
	// Случай 1 - currentNode имеет 0 или 1 ребёнка
	if (currentNode->left_ == nullptr || currentNode->right_ == nullptr)
	{
		Node* tempNode = (currentNode->left_ != nullptr) ? currentNode->left_ : currentNode->right_; // Заводим временный указатель
		if (currentNodeParent == nullptr) // Если удаляем корень дерева
		{
			root_ = tempNode; // tempNode - новый корень дерева
		}
		else if (currentNodeParent->left_ == currentNode) // Если currentNode - левый ребёнок у parent
		{
			currentNodeParent->left_ = tempNode; // Левый ребёнок у parent - это ребёнок у currentNode (или nullptr)
		}
		else // Если currentNode - правый ребёнок у parent
		{
			currentNodeParent->right_ = tempNode; // Правый ребёнок у parent - это ребёнок у currentNode (или nullptr)
		}

		if (tempNode != nullptr)
		{
			tempNode->p_ = currentNodeParent; // Устанавливаем связь tempNode с родителем
		}
		delete currentNode; // Удаляем узел
	}
	// Случай 2 - currentNode имеет 2 детей
	else
	{
		Node* successor = currentNode->right_;
		while (successor->left_ != nullptr) // Ищем самого левого преемника в правом поддереве
		{
			successor = successor->left_; // Идём влево
		}

		if (successor != currentNode->right_) // Если successor - это НЕ правый ребёнок currentNode
		{
			successor->p_->left_ = successor->right_; // Меняем левый указатель у родителя successor
			if (successor->right_ != nullptr) // Если у successor есть правый ребёнок
			{
				successor->right_->p_ = successor->p_; // Меняем у этого ребёнка родителя
			}
			successor->right_ = currentNode->right_; // Меняем правого ребёнка у successor
			successor->right_->p_ = successor; // Меняем родителя для правого ребёнка у successor
		}

		successor->left_ = currentNode->left_; // Меняем левого ребёнка у successor
		successor->left_->p_ = successor; // Меняем родителя для левого ребёнка у successor
		successor->p_ = currentNodeParent; // Меняем родителя для successor
		if (currentNodeParent == nullptr) // Если удаляем корень
		{
			root_ = successor; // Теперь корень - это successor
		}
		else if (currentNode == currentNodeParent->left_) // Если currentNode - это левый ребёнок
		{
			currentNodeParent->left_ = successor; // Левый ребёнок у currentNodeParent - это successor
		}
		else // Если currentNode - это правый ребёнок
		{
			currentNodeParent->right_ = successor; // Правый ребёнок у currentNodeParent - это successor
		}
		delete currentNode; // Удаляем currentNode
	}
	return true;
}

// Вывод дерева с использованием скобок
template <typename T>
void BinarySearchTree<T>::output(std::ostream& out) const
{
	output(out, root_);
}

// Определение количества узлов дерева
template <typename T>
int BinarySearchTree<T>::getNumberOfNodes() const
{
	return getNumberOfNodes(root_);
}

// Определение высоты дерева
template <typename T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeight(root_);
}

// Инфиксный обход дерева (итеративный)
template <typename T>
void BinarySearchTree<T>::inorderWalkIterative() const
{
	if (root_ == nullptr)
	{
		std::cout << "Empty tree";
	}
	else
	{
		StackArray<Node*> s(getHeight()); // Создаём стек из указателей на узлы
		Node* currentNode = root_; // Заводим указатель на корень дерева
		while (currentNode != nullptr || !s.isEmpty()) // Во внешнем цикле идём, пока currentNode - это реальный узел или стек не пустой
		{
			while (currentNode != nullptr) // Во внутреннем цикле идём влево, пока не дойдём до листа
			{
				s.push(currentNode); // Заносим currentNode в стек
				currentNode = currentNode->left_; // Идём влево
			}
			currentNode = s.pop(); // Запоминаем вершину стека и удаляем её
			std::cout << currentNode->key_ << " "; // Выводим ключ узла, находящегося на вершине
			currentNode = currentNode->right_; // Идём вправо
		}
	}
}
// []->[8]->[8, 3]->[8, 3, 1]->[8, 3]->[8]->[8, 6]->[8, 6, 4]->[8, 6]->[8]->[8, 7]->
// ->[8]->[]->[10]->[]->[14]->[14, 13]->[14]->[]

// Инфиксный обход дерева (рекурсивный)
template <typename T>
void BinarySearchTree<T>::inorderWalk() const
{
	if (root_ != nullptr)
	{
		inorderWalk(root_);
	}
	else
	{
		std::cout << "Empty tree";
	}
}

// Обход двоичного дерева по уровням (в ширину)
template <typename T>
void BinarySearchTree<T>::walkByLevels() const
{
	if (root_ == nullptr)
	{
		std::cout << "Empty tree";
	}
	else
	{
		QueueVector<Node*> q(getNumberOfNodes()); // Создаём очередь из указателей на узлы
		q.enQueue(root_); // Заносим в очередь корень дерева
		while (!q.isEmpty()) // В цикле пока очередь не пустая
		{
			Node* currentNode = q.deQueue(); // Запоминаем голову очереди и удаляем её
			std::cout << currentNode->key_ << " "; // Выводим на экран ключ головного узла
			if (currentNode->left_ != nullptr) // Если у currentNode есть левый ребёнок
			{
				q.enQueue(currentNode->left_); // Заносим этого ребёнка в очередь
			}
			if (currentNode->right_ != nullptr) // Если у currentNode есть правый ребёнок
			{
				q.enQueue(currentNode->right_); // Заносим этого ребёнка в очередь
			}
		}
	}
}
// []->[8]->[]->[3]->[10, 3]->[10]->[1, 10]->[6, 1, 10]->[6, 1]->[14, 6, 1]->
// ->[14, 6]->[14]->[4, 14]->[7, 4, 14]->[7, 4]->[13, 7, 4]->[13, 7]->[13]->[]

// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (рекурсивно)
template <typename T>
int BinarySearchTree<T>::countKeysInRange(const T& low, const T& high) const
{
	return countNodesInRange(root_, low, high);
}

// Вариант 6 - подсчёт количества узлов, значения к-ых лежат в заданном диапазоне (итеративно)
template <typename T>
int BinarySearchTree<T>::countKeysInRangeIterative(const T& low, const T& high) const
{
	return countNodesInRangeIterative(root_, low, high);
}

#endif