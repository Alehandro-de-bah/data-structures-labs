#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue
{
public:
	virtual ~Queue() {} // Деструктор
	virtual void enQueue(const T& e) = 0; // Добавление элемента  
	virtual T deQueue() = 0; // Удаление элемента
	virtual bool isEmpty() const noexcept = 0; // Проверка очереди на пустоту
};

#endif