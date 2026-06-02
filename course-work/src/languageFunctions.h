#ifndef LANGUAGE_FUNCTIONS_H
#define LANGUAGE_FUNCTIONS_H

#include <string>

// Приведение к нижнему регистру + замена 'ёЁ' на 'е'
void toLower(std::string& str);

// Проверка: слово содержит только латинские буквы, дефис, апостроф
bool isValidEnglishWord(const std::string& word);

// Проверка: перевод содержит только кириллицу, дефис, апостроф
bool isValidRussianTranslation(const std::string& translation);

// Проверка: является ли символ допустимым для английского слова
bool isEnglishChar(char c);

// Проверка: является ли символ допустимым для русского перевода
bool isRussianChar(char c);

#endif