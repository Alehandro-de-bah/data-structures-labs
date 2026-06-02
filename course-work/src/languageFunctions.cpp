#include "languageFunctions.h"

// Приведение к нижнему регистру + замена 'ёЁ' на 'е'
void toLower(std::string& str)
{
    for (char& c : str)
    {
        // CP1251: 'Ё' = 0xA8, 'ё' = 0xB8
        unsigned char uc = static_cast<unsigned char>(c);

        if (uc == 0xA8 || uc == 0xB8) // 'Ё' (oxA8), 'ё' (0xB8)
        {
            c = static_cast<char>(0xE5); // 'е' (0xE5)
        }
        else if ((c >= 'А' && c <= 'Я') || (c >= 'A' && c <= 'Z'))
        {
            c = static_cast<char>(c + 32);
        }
    }
}

// Проверка: является ли символ допустимым для английского слова
bool isEnglishChar(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '\'' || c == '-';
}

// Проверка: является ли символ допустимым для русского перевода
bool isRussianChar(char c)
{
    unsigned char uc = static_cast<unsigned char>(c);
    // CP1251: 'А'..'Я' = 0xC0..0xDF, 'а'..'я' = 0xE0..0xFF, 'Ё' = 0xA8, 'ё' = 0xB8
    return (uc >= 0xC0 ||  // 'А'..'Я', 'а'..'я'
            uc == 0xA8 ||  // 'Ё'
            uc == 0xB8 ||  // 'ё'
            c == '\'' ||
            c == '-');
}

// Проверка: слово содержит только латинские буквы, дефис, апостроф
bool isValidEnglishWord(const std::string& word)
{
    if (word.empty())
    {
        return false;
    }
    for (char c : word)
    {
        if (!isEnglishChar(c))
        {
            return false;
        }
    }
    return true;
}

// Проверка: перевод содержит только кириллицу, дефис, апостроф
bool isValidRussianTranslation(const std::string& translation)
{
    if (translation.empty())
    {
        return false;
    }
    for (char c : translation)
    {
        if (!isRussianChar(c))
        {
            return false;
        }
    }
    return true;
}