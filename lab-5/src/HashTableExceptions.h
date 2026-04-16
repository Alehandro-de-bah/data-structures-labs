#ifndef HASH_TABLE_EXCEPTIONS_H
#define HASH_TABLE_EXCEPTIONS_H

#include <exception>

class BadAllocation : public std::exception
{
public:
	const char* what() const noexcept override { return "Error: bad allocation!"; }
};

class ErrorInCopying : public std::exception
{
public:
	const char* what() const noexcept override { return "Error: something went wrong in copying!"; }
};

#endif