#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "RedBlackTree.h"
#include "languageFunctions.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Dictionary
{
public:
    // Загрузка словаря из входного файла
    bool loadFromFile(const std::string& filename);

    // Сохранение текущего словаря в выходной файл
    bool saveToFile(const std::string& filename) const;

    // Обработка команды, вводимой пользователем
    bool processCommand(const std::string& commandLine);

    // Вывод свех записей словаря в поток
    void printAll(std::ostream& out) const;

    // Запуск интерактивного режима работы со словарём
    void runInteractiveMode();
private:
    RedBlackTree tree_;

    // Разбор записи словаря
    void parseLine(const std::string& line,
                   std::string& outWord,
                   RedBlackTree::List<std::string>& outTranslations,
                   bool& isSuccess,
                   size_t lineNumber) const;

    // Обработка команды INSERT
    void handleInsert(const std::string& args);

    // Обработка команды SEARCH
    void handleSearch(const std::string& args) const;

    // Обработка команды REMOVE
    void handleRemove(const std::string& args);

    // Обработка команды PRINT
    void handlePrint(const std::string& args) const;

    // Обработка команды EXIT
    bool handleExit(const std::string& args) const;

    // Вывод списка допустимых команд
    void printHelp() const;
};

#endif