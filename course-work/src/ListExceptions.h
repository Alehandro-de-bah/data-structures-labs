#ifndef LIST_EXCEPTIONS_H
#define LIST_EXCEPTIONS_H

#include <exception>

namespace List
{
	class BadAllocation : public std::exception
	{
	public:
		const char* what() const noexcept override { return "Error: bad allocation"; }
	};

	class ErrorInCopying : public std::exception
	{
	public:
		const char* what() const noexcept override { return "Error: something went wrong in copying!"; }
	};

	class EmptyList : public std::exception
	{
	public:
		const char* what() const noexcept override { return "Error: list is empty"; }
	};

	class InvalidKeyRange : public std::exception
	{
	public:
		const char* what() const noexcept override { return "Error: keyBegin is more than keyEnd"; }
	};
}

#endif