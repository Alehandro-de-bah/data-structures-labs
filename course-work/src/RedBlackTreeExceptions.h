#ifndef RED_BLACK_TREE_EXCEPTIONS_H
#define RED_BLACK_TREE_EXCEPTIONS_H

#include <exception>

namespace RBT
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

    class KeyNotFound : public std::exception
    {
    public:
        const char* what() const noexcept override { return "Error: key is not found"; }
    };
}


#endif