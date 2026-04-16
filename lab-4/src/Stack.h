#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
public:
	virtual ~Stack() {} // Деструктор
	virtual void push(const T& e) = 0; // Добавление элемента
	virtual T pop() = 0; // Удаление элемента
	virtual bool isEmpty() const noexcept = 0; // Проверка на пустоту
};

#endif