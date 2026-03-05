#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// Исключения для класса String
constexpr const char* ERROR_BAD_ALLOC_IN_STRING_CONST_CHAR = "ERROR: bad alloc in String(const char*)";
constexpr const char* ERROR_BAD_ALLOC_IN_STRING_CONST_STRING = "ERROR: bad alloc in String(const String&)";
constexpr const char* ERROR_BAD_ALLOC_IN_RESIZE = "ERROR: bad allocation in resize()";
constexpr const char* ERROR_BAD_ALLOC_IN_ASSIGNMENT_OPERATOR_CONST_CHAR = "ERROR: bad alloc in operator=(const char*)";
constexpr const char* ERROR_OUT_OF_RANGE = "ERROR: index is out of range";
constexpr const char* ERROR_BAD_ALLOC_IN_ADDITION_ASSIGNMENT_CONST_STRING = "ERROR: bad alloc in operator+=(const String&)";
constexpr const char* ERROR_BAD_ALLOCATION_IN_MAIN = "ERROR: bad allocation in main()";

// Исключения для класса DoubleOrderedList<T>
constexpr const char* ERROR_LIST_IS_EMPTY = "Error: list is empty";
constexpr const char* ERROR_OUT_OF_RANGE_IN_REMOVE_KEYS = "Error: keyBegin is more than keyEnd";
constexpr const char* ERROR_SOMETHING_WENT_WRONG = "Something went wrong";

#endif