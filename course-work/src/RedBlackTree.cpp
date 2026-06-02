#include "RedBlackTree.h"

// Конструктор узла с ключом и строкой
RedBlackTree::Node::Node(const std::string& key, const std::string& str, Node* nil)
    : key_(key),
      color_(Color::RED), // Новый узел всегда красный
      value_(str), // Создаём список с одной строкой
      left_(nil),
      right_(nil),
      p_(nil)
{}

// Конструктор по умолчанию
RedBlackTree::RedBlackTree() : root_(nullptr), size_(0)
{
    initNil(); // Может быть исключение BadAllocation
    root_ = nil_;
}

// Конструктор копирования
RedBlackTree::RedBlackTree(const RedBlackTree& rhs) : size_(0)
{
    initNil();
    try
    {
        root_ = copyTree(rhs.root_, rhs.nil_, nil_); // Может быть исключение
    }
    catch (...)
    {
        delete nil_;
        throw;
    }
    size_ = rhs.size_;
}

// Конструктор перемещения
RedBlackTree::RedBlackTree(RedBlackTree&& rhs) noexcept : root_(nullptr), nil_(nullptr), size_(0)
{
    this->swap(rhs);
}

// Оператор копирующего присваивания
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rhs)
{
    if (this != &rhs)
    {
        RedBlackTree temp(rhs);
        swap(temp);
    }
    return *this;
}

// Оператор перемещающего присваивания
RedBlackTree& RedBlackTree::operator=(RedBlackTree&& rhs) noexcept
{
    if (this != &rhs)
    {
        swap(rhs);
    }
    return *this;
}

// Деструктор
RedBlackTree::~RedBlackTree()
{
    destroyTree(root_); // Удаляем все узлы дерева
    delete nil_;        // Удаляем NIL
}

// ----- private методы -----

// Инициализация узла-ограничителя
void RedBlackTree::initNil()
{
    try
    {
        nil_ = new Node("", "", nullptr);
        nil_->color_ = Color::BLACK;
        nil_->left_ = nil_;
        nil_->right_ = nil_;
        nil_->p_ = nil_;
    }
    catch (const std::bad_alloc&)
    {
        throw RBT::BadAllocation();
    }
}

// Метод swap (для идиомы copy-and-swap)
void RedBlackTree::swap(RedBlackTree& rhs) noexcept
{
    std::swap(root_, rhs.root_);
    std::swap(nil_, rhs.nil_);
    std::swap(size_, rhs.size_);
}

// Рекурсивное копирование поддерева (для конструктора копирования)
RedBlackTree::Node* RedBlackTree::copyTree(Node* otherRoot, Node* otherNil, Node* parent)
{
    // Базовый случай: достигли NIL другого дерева
    if (otherRoot == otherNil)
    {
        return nil_;
    }

    Node* newNode = nullptr;
    try
    {
        newNode = new Node(otherRoot->key_, "", nil_); // Может быть исключение
        newNode->value_ = otherRoot->value_; // Может быть исключение
    }
    catch (const std::bad_alloc&)
    {
        throw RBT::BadAllocation();
    }
    catch (...)
    {
        delete newNode;
        throw RBT::ErrorInCopying();
    }

    newNode->p_ = parent;
    newNode->color_ = otherRoot->color_;
    newNode->left_ = nil_;
    newNode->right_ = nil_;
  
    // Рекурсивно копируем левое и правое поддеревья
    try
    {
        // Копируем левое плечо
        newNode->left_ = copyTree(otherRoot->left_, otherNil, newNode); // Может быть исключение
        // Копируем правое плечо
        newNode->right_ = copyTree(otherRoot->right_, otherNil, newNode); // Может быть исключение
    }
    catch (...)
    {
        destroyTree(newNode);
        throw;
    }

    return newNode;
}

// Рекурсивное удаление поддерева (кроме NIL)
void RedBlackTree::destroyTree(Node* node)
{
    if (node != nil_ && node != nullptr)
    {
        destroyTree(node->left_);
        destroyTree(node->right_);
        delete node;
    }
}

// Поиск узла по ключу
RedBlackTree::Node* RedBlackTree::findNode(const std::string& key) const
{
    Node* current = root_;
    while (current != nil_)
    {
        if (key < current->key_)
        {
            current = current->left_;
        }
        else if (key > current->key_)
        {
            current = current->right_;
        }
        else
        {
            return current;
        }
    }
    return nil_;
}

// Поиск узла с минимальным ключом в поддереве
RedBlackTree::Node* RedBlackTree::minimum(Node* node) const
{
    while (node->left_ != nil_)
    {
        node = node->left_;
    }
    return node;
}

// Левый поворот вокруг узла x
void RedBlackTree::leftRotate(Node* x)
{
    Node* y = x->right_;
    x->right_ = y->left_;

    if (y->left_ != nil_)
    {
        y->left_->p_ = x;
    }

    y->p_ = x->p_;

    if (x->p_ == nil_)
    {
        root_ = y; // y становится новым корнем
    }
    else if (x == x->p_->left_)
    {
        x->p_->left_ = y;
    }
    else
    {
        x->p_->right_ = y;
    }

    y->left_ = x;
    x->p_ = y;
}

// Правый поворот вокруг узла x
void RedBlackTree::rightRotate(Node* x)
{
    Node* y = x->left_;
    x->left_ = y->right_;

    if (y->right_ != nil_)
    {
        y->right_->p_ = x;
    }

    y->p_ = x->p_;

    if (x->p_ == nil_)
    {
        root_ = y;
    }
    else if (x == x->p_->right_)
    {
        x->p_->right_ = y;
    }
    else
    {
        x->p_->left_ = y;
    }

    y->right_ = x;
    x->p_ = y;
}

// Восстановление свойств КЧ-дерева после вставки (по Кормену, глава 13.3)
void RedBlackTree::insertFixup(Node* z)
{
    // Восстановление свойств после вставки
    while (z->p_->color_ == Color::RED)
    {
        if (z->p_ == z->p_->p_->left_)
        {
            Node* y = z->p_->p_->right_; // "дядя" узла z

            if (y->color_ == Color::RED)
            {
                // Случай 1: дядя красный — перекрашиваем отца, дядю и деда
                z->p_->color_ = Color::BLACK;
                y->color_ = Color::BLACK;
                z->p_->p_->color_ = Color::RED;
                z = z->p_->p_; // Поднимаем проблему выше
            }
            else
            {
                // Случай 2: z — правый потомок (треугольник)
                if (z == z->p_->right_)
                {
                    z = z->p_;
                    leftRotate(z); // Преобразуем в случай 3
                }
                // Случай 3: z — левый потомок (линия)
                z->p_->color_ = Color::BLACK;
                z->p_->p_->color_ = Color::RED;
                rightRotate(z->p_->p_);
            }
        }
        else
        {
            // Симметричная ситуация (правая сторона)
            Node* y = z->p_->p_->left_;

            if (y->color_ == Color::RED)
            {
                z->p_->color_ = Color::BLACK;
                y->color_ = Color::BLACK;
                z->p_->p_->color_ = Color::RED;
                z = z->p_->p_;
            }
            else
            {
                if (z == z->p_->left_)
                {
                    z = z->p_;
                    rightRotate(z);
                }
                z->p_->color_ = Color::BLACK;
                z->p_->p_->color_ = Color::RED;
                leftRotate(z->p_->p_);
            }
        }
    }
    root_->color_ = Color::BLACK; // Корень всегда чёрный
}

// Замена поддерева u поддеревом v (вспомогательная для удаления)
void RedBlackTree::transplant(Node* u, Node* v)
{
    if (u->p_ == nil_)
    {
        root_ = v;
    }
    else if (u == u->p_->left_)
    {
        u->p_->left_ = v;
    }
    else
    {
        u->p_->right_ = v;
    }
    v->p_ = u->p_;
}

// Восстановление свойств КЧ-дерева после удаления (по Кормену, глава 13.4) 
void RedBlackTree::deleteFixup(Node* x)
{
    while (x != root_ && x->color_ == Color::BLACK)
    {
        if (x == x->p_->left_)
        {
            Node* w = x->p_->right_; // "брат" узла x

            // Случай 1: брат красный
            if (w->color_ == Color::RED)
            {
                w->color_ = Color::BLACK;
                x->p_->color_ = Color::RED;
                leftRotate(x->p_);
                w = x->p_->right_;
            }

            // Случай 2: оба потомка брата чёрные
            if (w->left_->color_ == Color::BLACK && w->right_->color_ == Color::BLACK)
            {
                w->color_ = Color::RED;
                x = x->p_;
            }
            else
            {
                // Случай 3: правый потомок брата чёрный
                if (w->right_->color_ == Color::BLACK)
                {
                    w->left_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    rightRotate(w);
                    w = x->p_->right_;
                }
                // Случай 4: правый потомок брата красный
                w->color_ = x->p_->color_;
                x->p_->color_ = Color::BLACK;
                w->right_->color_ = Color::BLACK;
                leftRotate(x->p_);
                x = root_;
            }
        }
        else
        {
            // Симметричная ситуация (x — правый потомок)
            Node* w = x->p_->left_;

            if (w->color_ == Color::RED)
            {
                w->color_ = Color::BLACK;
                x->p_->color_ = Color::RED;
                rightRotate(x->p_);
                w = x->p_->left_;
            }

            if (w->right_->color_ == Color::BLACK && w->left_->color_ == Color::BLACK)
            {
                w->color_ = Color::RED;
                x = x->p_;
            }
            else
            {
                if (w->left_->color_ == Color::BLACK)
                {
                    w->right_->color_ = Color::BLACK;
                    w->color_ = Color::RED;
                    leftRotate(w);
                    w = x->p_->left_;
                }
                w->color_ = x->p_->color_;
                x->p_->color_ = Color::BLACK;
                w->left_->color_ = Color::BLACK;
                rightRotate(x->p_);
                x = root_;
            }
        }
    }
    x->color_ = Color::BLACK;
}

// Стандартная вставка в бинарное дерево поиска (без балансировки)
void RedBlackTree::bstInsert(Node* z)
{
    Node* y = nil_;
    Node* x = root_;

    while (x != nil_)
    {
        y = x;
        if (z->key_ < x->key_)
        {
            x = x->left_;
        }
        else
        {
            x = x->right_;
        }
    }

    z->p_ = y;
    if (y == nil_)
    {
        root_ = z; // Дерево было пустым
    }
    else if (z->key_ < y->key_)
    {
        y->left_ = z;
    }
    else
    {
        y->right_ = z;
    }
}

// Рекурсивный вывод поддерева в поток
void RedBlackTree::printNode(std::ostream& out, Node* node, size_t& index) const
{
    // Центрированный обход с нумерацией и выводом в формате спецификации
    if (node == nil_)
    {
        return;
    }

    printNode(out, node->left_, index);

    // Вывод: "<номер>. <слово> - <перевод1>, <перевод2>, ..."
    out << index << ". " << node->key_ << " - ";

    // Требование 3.4.3. Слово не содержит переводов
    if (node->value_.isEmpty())
    {
        out << MSG_NO_TRANSLATIONS;
    }
    else
    {
        node->value_.print(out);
    }

    out << '\n';
    ++index;

    printNode(out, node->right_, index);
}

// ========== Публичные методы ==========

// Вставка ключа с одной строкой
void RedBlackTree::insert(const std::string& key, const std::string& str)
{
    // Если ключ уже существует — добавляем перевод в существующий список
    Node* existing = findNode(key);
    if (existing != nil_)
    {
        existing->value_.insert(str);
        return;
    }

    // Создаём новый красный узел с одним переводом
    Node* z = nullptr;
    try
    {
        z = new Node(key, str, nil_);
    }
    catch (const std::bad_alloc&)
    {
        throw RBT::BadAllocation();
    }

    bstInsert(z);
    insertFixup(z);
    ++size_;
}

// Вставка ключа со списком строк
void RedBlackTree::insert(const std::string& key, List<std::string>&& list)
{
    // Если ключ существует — сливаем списки переводов
    Node* existing = findNode(key);
    if (existing != nil_)
    {
        existing->value_.merge(list);
        return;
    }

    // Создаём новый узел
    Node* z = nullptr;
    try
    {
        z = new Node("", "", nil_); // Временный, чтобы передать переводы
    }
    catch (const std::bad_alloc&)
    {
        throw RBT::BadAllocation();
    }

    z->key_ = key;
    z->value_ = std::move(list);

    bstInsert(z);
    insertFixup(z);
    ++size_;
}

// Поиск ключа в дереве
bool RedBlackTree::search(const std::string& key) const
{
    return findNode(key) != nil_;
}

// Получение списка строк по ключу
const RedBlackTree::List<std::string>& RedBlackTree::getValue(const std::string& key) const
{
    Node* node = findNode(key);
    if (node == nil_)
    {
        throw RBT::KeyNotFound();
    }
    return node->value_;
}

// Удаление ключа из дерева
bool RedBlackTree::remove(const std::string& key)
{
    Node* z = findNode(key);
    if (z == nil_)
    {
        return false; // Ключ не найден
    }

    Node* y = z;
    Node* x = nullptr;
    Color yOriginalColor = y->color_;

    if (z->left_ == nil_)
    {
        // Случай 1: нет левого потомка
        x = z->right_;
        transplant(z, z->right_);
    }
    else if (z->right_ == nil_)
    {
        // Случай 2: нет правого потомка
        x = z->left_;
        transplant(z, z->left_);
    }
    else
    {
        // Случай 3: оба потомка есть — ищем преемника
        y = minimum(z->right_);
        yOriginalColor = y->color_;
        x = y->right_;

        if (y->p_ == z)
        {
            x->p_ = y;
        }
        else
        {
            transplant(y, y->right_);
            y->right_ = z->right_;
            y->right_->p_ = y;
        }

        transplant(z, y);
        y->left_ = z->left_;
        y->left_->p_ = y;
        y->color_ = z->color_;
    }

    delete z;

    if (yOriginalColor == Color::BLACK)
    {
        deleteFixup(x); // Восстанавливаем свойства
    }

    --size_;
    return true;
}

// Удаление всех узлов дерева
void RedBlackTree::clear() noexcept
{
    // Удаляем все узлы, кроме NIL
    destroyTree(root_);
    root_ = nil_;
    size_ = 0;
}

// Вывод дерева в поток (в формате выходного файла словаря)
void RedBlackTree::print(std::ostream& out) const
{
    size_t index = 1;
    printNode(out, root_, index);
}