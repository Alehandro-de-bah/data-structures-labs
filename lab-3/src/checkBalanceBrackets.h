#ifndef CHECK_BALANCE_BRACKETS_H
#define CHECK_BALANCE_BRACKETS_H

#include <iostream>

const int DEFAULT_DEPTH = 10;
constexpr const char* TEXT_IS_EMPTY = "The text is empty! (Note: text must contain at least one character)";
constexpr const char* INCORRECT_MAX_DEEP = "Incorrect maxDeep! (Note: maxDeep must be a positive number)";
constexpr const char* MAXIMUM_DEPTH_OF_BRACKETS = "The maximum depth of brackets has been achieved!";
constexpr const char* UNNECESSARY_CLOSING_BRACKET = "The unnecessary closing bracket was noticed!";
constexpr const char* DIFFERENT_TYPES_OF_BRACKETS = "Types of brackets are defferent!";
constexpr const char* CLOSING_BRACKET_WAS_MISSED = "The closing bracket was missed!";

bool checkBalanceBrackets(const char* text, const int maxDeep = DEFAULT_DEPTH);

#endif
