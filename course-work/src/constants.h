#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Константа для индекса элемента, отсутствующего в строке
constexpr std::string::size_type NOT_FOUND = std::string::npos;

// Символы, использующиеся в записи словаря и команде INSERT
const char WHITESPACE = ' ';
const char OPENING_SQUARE_BRACKET = '[';
const char CLOSING_SQUARE_BRACKET = ']';

// Приглашение ко вводу
const std::string ENTER_THE_NAME_OF_THE_FILE = "Введите имя файла словаря: ";
const std::string PROMPT_COMMAND = "Введите команду: ";

// Сообщения об ошибках (входной файл)
const std::string INPUT_FILE_IS_NOT_SPECIFIED = "Входной файл не задан. Работа продолжится с пустым словарём";
const std::string ERROR_INPUT_FILE_NOT_FOUND = "Ошибка: входной файл не найден/не открыт. Работа продолжится с пустым словарём";
const std::string ERROR_MISSING_OPEN_BRACKET_BEFORE_WORD = "Ошибка: отсутствует открывающая квадратная скобка перед словом, запись будет проигнорирована";
const std::string ERROR_INVALID_CHAR_IN_WORD = "Ошибка: в слове присутствуют некорректные символы, запись будет проигнорирована";
const std::string ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD = "Ошибка: после слова отсутствует закрывающая квадратная скобка, запись будет проигнорирована";
const std::string ERROR_MISSING_OPEN_BRACKET_BEFORE_TRANSLATION = "Ошибка: отсутствует открывающая квадратная скобка перед переводом, запись будет проигнорирована";
const std::string WARNING_INVALID_CHAR_IN_TRANSLATION = "Предупреждение: в переводе присутствуют некорректные символы, перевод будет проигнорирован";
const std::string ERROR_MISSING_CLOSE_BRACKET_AFTER_TRANSLATION = "Ошибка: после перевода отсутствует закрывающая квадратная скобка, запись будет проигнорирована";

// Сообщения об ошибках (команды)
const std::string ERROR_INVALID_COMMAND_NAME = "Ошибка: название команды задано некорректно";
const std::string ERROR_MISSING_OPEN_BRACKET_BEFORE_WORD_IN_INSERT = "Ошибка: отсутствует открывающая квадратная скобка перед словом";
const std::string ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD_IN_INSERT = "Ошибка: после слова отсутствует закрывающая квадратная скобка";
const std::string ERROR_INVALID_WORD_IN_COMMAND = "Ошибка: слово задано некорректно";
const std::string ERROR_MISSING_OPEN_BRACKET_BEFORE_TRANSLATION_IN_INSERT = "Ошибка: отсутствует открывающая квадратная скобка перед переводом";
const std::string ERROR_WORD_NOT_SPECIFIED = "Ошибка: слово не задано";
const std::string WARNING_INVALID_TRANSLATION_IN_COMMAND = "Предупреждение: перевод задан некорректно, он будет проигнорирован";
const std::string ERROR_MISSING_CLOSE_BRACKET_AFTER_TRANSLATION_IN_INSERT = "Ошибка: после перевода отсутствует закрывающая квадратная скобка";
const std::string ERROR_PRINT_TAKES_NO_ARGUMENTS = "Ошибка: команда PRINT не принимает аргументов";
const std::string ERROR_OUTPUT_FILE_NOT_OPENED = "Ошибка: выходной файл не открыт";

// Информационные сообщения
const std::string MSG_INPUT_FILE = "Входной файл ";
const std::string MSG_PROCESSING_DICTIONARY_RECORDS = " открыт. Начинается обработка записей словаря";
const std::string MSG_RECORD_WITH_WORD = "Запись со словом \"";
const std::string MSG_SUCCESSFULLY_ADDED_TO_DICTIONARY = "\" успешно добавлена в словарь";
const std::string MSG_DICTIONARY_IS_EMPTY = "Словарь пуст (не содержит ни одной записи)";
const std::string MSG_LINE = "Строка ";
const std::string MSG_POINT = ". ";
const std::string MSG_WORD_NOT_FOUND_PREFIX = "Слово";
const std::string MSG_WORD_NOT_FOUND_SUFFIX = "отсутствует в словаре";
const std::string MSG_WORD_REMOVED_PREFIX = "Слово";
const std::string MSG_WORD_REMOVED_SUFFIX = "удалено";
const std::string MSG_NO_TRANSLATIONS = "НЕТ ПЕРЕВОДОВ";
const std::string MSG_OUTPUT_FILENAME_NOT_SPECIFIED = "Имя выходного файла не задано. ";
const std::string MSG_DICTIONARY_SAVED = "Словарь сохранён в файл ";
const std::string DEFAULT_OUTPUT_FILENAME = "output_dictionary.txt";
const std::string WARNING_INPUT_FILE_IS_EMPTY = "Предупреждение: входной файл является пустым";
const std::string WARNING_DICTIONARY_IS_EMPTY = "Предупреждение: словарь является пустым";

// Список команд
const std::string MSG_COMMAND_LIST_HEADER = "Список команд:";
const std::string MSG_COMMAND_INSERT = "  INSERT [слово][перевод1 перевод2 ...]";
const std::string MSG_COMMAND_SEARCH = "  SEARCH <слово>";
const std::string MSG_COMMAND_REMOVE = "  REMOVE <слово>";
const std::string MSG_COMMAND_PRINT = "  PRINT";
const std::string MSG_COMMAND_EXIT = "  EXIT <выходной файл>";

// Названия команд
const std::string CMD_INSERT = "INSERT";
const std::string CMD_SEARCH = "SEARCH";
const std::string CMD_REMOVE = "REMOVE";
const std::string CMD_PRINT = "PRINT";
const std::string CMD_EXIT = "EXIT";

#endif