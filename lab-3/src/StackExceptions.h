#ifndef STACK_EXCEPTIONS_H
#define STACK_EXCEPTIONS_H

#include <exception>

class StackOverflow : public std::exception
{
public:
	const char* what() const noexcept override { return "Stack overflow!"; }
};

class StackUnderflow : public std::exception
{
public:
	const char* what() const noexcept override { return "Stack underflow!"; }
};

class WrongStackSize : public std::exception
{
public:
	const char* what() const noexcept override { return "Stack size must be positive!"; }
};

class StackBadAllocationInConstructor : public std::exception
{
public:
	const char* what() const noexcept override { return "Stack bad allocation in constructor!"; }
};

class StackErrorInCopying : public std::exception
{
public:
	const char* what() const noexcept override { return "Stack error in copying!"; }
};

#endif