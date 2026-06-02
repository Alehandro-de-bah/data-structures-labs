#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "DoubleOrderedList.h"
#include "RedBlackTreeExceptions.h"
#include "constants.h"

class RedBlackTree
{
public:
	template <typename T>
	using List = DoubleOrderedList<T>;

	// Конструктор по умолчанию
	RedBlackTree();

	// Конструктор копирования
	RedBlackTree(const RedBlackTree& rhs);

	// Конструктор перемещения
	RedBlackTree(RedBlackTree&& rhs) noexcept;

	// Оператор копирующего присваивания
	RedBlackTree& operator=(const RedBlackTree& rhs);

	// Оператор перемещающего присваивания
	RedBlackTree& operator=(RedBlackTree&& rhs) noexcept;

	// Деструктор
	~RedBlackTree();

	// Вставка ключа с одной строкой
	void insert(const std::string& key, const std::string& str);

	// Вставка ключа со списком строк
	void insert(const std::string& key, List<std::string>&& list);

	// Поиск ключа в дереве
	bool search(const std::string& key) const;

	// Получение списка строк по ключу
	const List<std::string>& getValue(const std::string& key) const;

	// Удаление ключа из дерева
	bool remove(const std::string& key);

	// Удаление всех узлов дерева
	void clear() noexcept;

	// Пусто ли дерево
	bool isEmpty() const noexcept { return size_ == 0; }

	// Количество узлов в дереве
	size_t size() const noexcept { return size_; }

	// Вывод дерева в поток (в формате выходного файла словаря)
	void print(std::ostream& out) const;
private:
	// Цвет узла
	enum class Color
	{
		RED = 0,
		BLACK = 1
	};

	// Узел красно-чёрного дерева
	struct Node
	{
		std::string key_;         // Английское слово (ключ)
		Color color_;             // Цвет (RED, BLACK)
		List<std::string> value_; // Список переводов (значение)
		Node* left_;              // Указатель на левого потомка
		Node* right_;             // Указатель на правого потомка
		Node* p_;                 // Указатель на родителя

		// Конструктор узла с ключом и строкой
		Node(const std::string& key, const std::string& str, Node* nil);
	};

	Node* root_;  // Корень дерева
	Node* nil_;   // Единственный узел ограничитель (чёрный NIL)
	size_t size_; // Количество узлов в дереве (не считая NIL)


	// Инициализация узла-ограничителя
	void initNil();

	// Метод swap (для идиомы copy-and-swap)
	void swap(RedBlackTree& rhs) noexcept;

	// Рекурсивное копирование поддерева (для конструктора копирования)
	Node* copyTree(Node* otherRoot, Node* otherNil, Node* parent);

	// Рекурсивное удаление поддерева (кроме NIL)
	void destroyTree(Node* node);

	// Поиск узла по ключу
	Node* findNode(const std::string& key) const;

	// Поиск узла с минимальным ключом в поддереве
	Node* minimum(Node* node) const;

	// Левый поворот вокруг узла x
	void leftRotate(Node* x);

	// Правый поворот вокруг узла x
	void rightRotate(Node* x);

	// Восстановление свойств КЧ-дерева после вставки
	void insertFixup(Node* z);

	// Замена поддерева u поддеревом v (вспомогательная для удаления)
	void transplant(Node* u, Node* v);

	// Восстановление свойств КЧ-дерева после удаления
	void deleteFixup(Node* x);

	// Стандартная вставка в бинарное дерево поиска (без балансировки)
	void bstInsert(Node* z);

	// Рекурсивный вывод поддерева в поток
	void printNode(std::ostream& out, Node* node, size_t& index) const;
};

#endif