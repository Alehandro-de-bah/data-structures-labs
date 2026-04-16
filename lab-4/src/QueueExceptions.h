#ifndef QUEUE_EXCEPTIONS_H
#define QUEUE_EXCEPTIONS_H

#include <exception>

class QueueUnderflow : public std::exception
{
public:
	const char* what() const noexcept override { return "Queue underflow!"; }
};

class WrongQueueSize : public std::exception
{
public:
	const char* what() const noexcept override { return "Queue size must be positive!"; }
};

class QueueBadAllocationInResize : public std::exception
{
public:
	const char* what() const noexcept override { return "Queue bad allocation in resize!"; }
};

class QueueErrorInCopying : public std::exception
{
public:
	const char* what() const noexcept override { return "Queue error in copying!"; }
};

class QueueBadAllocationInConstructor : public std::exception
{
public:
	const char* what() const noexcept override { return "Queue bad allocation in constructor!"; }
};

#endif