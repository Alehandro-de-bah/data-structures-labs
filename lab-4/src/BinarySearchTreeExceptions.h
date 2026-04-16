#ifndef BINARY_SEARCH_TREE_EXCEPTIONS_H
#define BINARY_SEARCH_TREE_EXCEPTIONS_H

#include <exception>

class InvalidRange : public std::exception
{
public:
	const char* what() const noexcept override { return "Error: invalid range! (low is greater than high)"; }
};

class BadAllocationInInsert : public std::exception
{
public:
	const char* what() const noexcept override { return "Error: bad allocation in insert!"; }
};

class ErrorInCopying : public std::exception
{
public:
	const char* what() const noexcept override { return "Error: something went wrong in copying!"; }
};

#endif