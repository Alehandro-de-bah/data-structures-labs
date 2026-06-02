#include "Dictionary.h"

// ======= Реализация private методов =======

// Разбор записи словаря
void Dictionary::parseLine(const std::string& line,
    std::string& outWord,
    RedBlackTree::List<std::string>& outTranslations,
    bool& isSuccess,
    size_t lineNumber) const
{
    isSuccess = false;
    size_t pos = 0;

    // Требование 2.1.1. Перед словом отсутствует открывающая квадратная скобка 
    if (pos >= line.size() || line[pos] != OPENING_SQUARE_BRACKET)
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_MISSING_OPEN_BRACKET_BEFORE_WORD << '\n';
        return;
    }
    ++pos;

    size_t wordEnd = line.find(CLOSING_SQUARE_BRACKET, pos);

    // Требование 2.1.3. После слова отсутствует закрывающая квадратная скобка 
    if (wordEnd == NOT_FOUND)
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD << '\n';
        return;
    }

    std::string word = line.substr(pos, wordEnd - pos);

    // Требование 2.1.3. После слова отсутствует закрывающая квадратная скобка 
    if (word.find(OPENING_SQUARE_BRACKET) != NOT_FOUND)
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD << '\n';
        return;
    }

    toLower(word);

    // Требование 2.1.2. В слове присутствуют некорректные символы
    if (!isValidEnglishWord(word))
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_INVALID_CHAR_IN_WORD << '\n';
        return;
    }

    outWord = word;
    pos = wordEnd + 1;

    // Требование 2.2.1. Перед переводом отсутствует открывающая квадратная скобка
    if (pos >= line.size() || line[pos] != OPENING_SQUARE_BRACKET)
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_MISSING_OPEN_BRACKET_BEFORE_TRANSLATION << '\n';
        return;
    }
    ++pos;

    size_t translationsEnd = line.find(CLOSING_SQUARE_BRACKET, pos);

    // Требование 2.2.3. После перевода отсутствует закрывающая квадратная скобка
    if (translationsEnd == NOT_FOUND)
    {
        std::cerr << MSG_LINE << lineNumber << MSG_POINT << ERROR_MISSING_CLOSE_BRACKET_AFTER_TRANSLATION << "\n";
        return;
    }

    std::string translationsStr = line.substr(pos, translationsEnd - pos);
    toLower(translationsStr);

    // Разбиваем на отдельные переводы
    size_t start = 0;
    while (start < translationsStr.size())
    {
        while (start < translationsStr.size() && translationsStr[start] == WHITESPACE)
        {
            ++start;
        }

        if (start >= translationsStr.size())
        {
            break;
        }

        size_t end = translationsStr.find(WHITESPACE, start);
        if (end == NOT_FOUND)
        {
            end = translationsStr.size();
        }

        std::string translation = translationsStr.substr(start, end - start);

        // Требование 2.2.2. В переводе присутствуют некорректные символы
        if (!isValidRussianTranslation(translation))
        {
            std::cerr << MSG_LINE << lineNumber << MSG_POINT << WARNING_INVALID_CHAR_IN_TRANSLATION << "\n";
        }
        else
        {
            outTranslations.insert(translation);
        }

        start = end + 1;
    }

    isSuccess = true;
}

// Обработка команды INSERT
void Dictionary::handleInsert(const std::string& args)
{
    // Формат: INSERT [слово][перевод1 перевод2 ...]

    // Требование 3.1.1. Слово не задано
    if (args.empty())
    {
        std::cerr << ERROR_WORD_NOT_SPECIFIED << '\n';
        return;
    }

    size_t pos = 0;

    // Пропускаем ведущие пробелы
    while (pos < args.size() && args[pos] == WHITESPACE)
    {
        ++pos;
    }

    // Требование 3.1.1. Слово не задано
    if (pos >= args.size())
    {
        std::cerr << ERROR_WORD_NOT_SPECIFIED << '\n';
        return;
    }

    // Требование 3.1.2. Перед словом отсутствует открывающая квадратная скобка
    if (args[pos] != OPENING_SQUARE_BRACKET)
    {
        std::cerr << ERROR_MISSING_OPEN_BRACKET_BEFORE_WORD_IN_INSERT << '\n';
        return;
    }
    ++pos;

    size_t wordEnd = args.find(CLOSING_SQUARE_BRACKET, pos);

    // Требование 3.1.4. После слова отсутствует закрывающая квадратная скобка
    if (wordEnd == NOT_FOUND)
    {
        std::cerr << ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD_IN_INSERT << '\n';
        return;
    }

    std::string word = args.substr(pos, wordEnd - pos);

    // Требование 3.1.4. После слова отсутствует закрывающая квадратная скобка
    if (word.find(OPENING_SQUARE_BRACKET) != NOT_FOUND)
    {
        std::cerr << ERROR_MISSING_CLOSE_BRACKET_AFTER_WORD_IN_INSERT << '\n';
        return;
    }

    // Требование 3.1.1. Слово не задано
    if (word.empty())
    {
        std::cerr << ERROR_WORD_NOT_SPECIFIED << '\n';
        return;
    }

    toLower(word);

    // Требование 3.1.3. Слово задано некорректно
    if (!isValidEnglishWord(word))
    {
        std::cerr << ERROR_INVALID_WORD_IN_COMMAND << '\n';
        return;
    }

    pos = wordEnd + 1;

    // Требование 3.1.5. Перед переводом отсутствует открывающая квадратная скобка
    if (pos >= args.size() || args[pos] != OPENING_SQUARE_BRACKET)
    {
        std::cerr << ERROR_MISSING_OPEN_BRACKET_BEFORE_TRANSLATION_IN_INSERT << '\n';
        return;
    }
    ++pos;

    size_t translationsEnd = args.find(CLOSING_SQUARE_BRACKET, pos);

    // Требование 3.1.7. После перевода отсутствует закрывающая квадратная скобка
    if (translationsEnd == NOT_FOUND)
    {
        std::cerr << ERROR_MISSING_CLOSE_BRACKET_AFTER_TRANSLATION_IN_INSERT << '\n';
        return;
    }

    std::string translationsStr = args.substr(pos, translationsEnd - pos);
    toLower(translationsStr);

    size_t start = 0;
    bool hasAnyTranslation = false;

    while (start < translationsStr.size())
    {
        while (start < translationsStr.size() && translationsStr[start] == WHITESPACE)
        {
            ++start;
        }

        if (start >= translationsStr.size())
        {
            break;
        }

        size_t end = translationsStr.find(WHITESPACE, start);
        if (end == NOT_FOUND)
        {
            end = translationsStr.size();
        }

        std::string translation = translationsStr.substr(start, end - start);

        // Требование 3.1.6. Перевод задан некорректно
        if (!isValidRussianTranslation(translation))
        {
            std::cerr << WARNING_INVALID_TRANSLATION_IN_COMMAND << '\n';
        }
        else
        {
            tree_.insert(word, translation);
            hasAnyTranslation = true;
        }

        start = end + 1;
    }

    if (!hasAnyTranslation)
    {
        RedBlackTree::List<std::string> emptyList;
        tree_.insert(word, std::move(emptyList));
    }

    // Требование 3.1.8. Слово задано корректно и запись соответствует шаблону
    std::cout << MSG_RECORD_WITH_WORD << word << MSG_SUCCESSFULLY_ADDED_TO_DICTIONARY << '\n';
}

// Обработка команды SEARCH
void Dictionary::handleSearch(const std::string& args) const
{
    std::string word = args;
    size_t first = word.find_first_not_of(WHITESPACE);
    size_t last = word.find_last_not_of(WHITESPACE);
    if (first != NOT_FOUND)
    {
        word = word.substr(first, last - first + 1);
    }
    else
    {
        // Требование 3.2.1. Слово не задано
        std::cerr << ERROR_WORD_NOT_SPECIFIED << '\n';
        return;
    }

    toLower(word);

    // Требование 3.2.2. Слово задано некорректно
    if (!isValidEnglishWord(word))
    {
        std::cerr << ERROR_INVALID_WORD_IN_COMMAND << '\n';
        return;
    }

    // Требование 3.2.3. Слово отсутствует в словаре
    if (!tree_.search(word))
    {
        std::cout << MSG_WORD_NOT_FOUND_PREFIX << " \"" << word << "\" " << MSG_WORD_NOT_FOUND_SUFFIX << "\n";
        return;
    }

    // Требование 3.2.4. Слово задано корректно и присутствует в словаре
    const auto& translations = tree_.getValue(word);
    std::cout << word << " - ";

    if (translations.isEmpty())
    {
        std::cout << MSG_NO_TRANSLATIONS;
    }
    else
    {
        translations.print(std::cout);
    }
    std::cout << '\n';
}

// Обработка команды REMOVE
void Dictionary::handleRemove(const std::string& args)
{
    std::string word = args;
    size_t first = word.find_first_not_of(WHITESPACE);
    size_t last = word.find_last_not_of(WHITESPACE);
    if (first != NOT_FOUND)
    {
        word = word.substr(first, last - first + 1);
    }
    else
    {
        // Требование 3.3.1. Слово не задано
        std::cerr << ERROR_WORD_NOT_SPECIFIED << '\n';
        return;
    }

    toLower(word);

    // Требование 3.3.2. Слово задано некорректно
    if (!isValidEnglishWord(word))
    {
        std::cerr << ERROR_INVALID_WORD_IN_COMMAND << '\n';
        return;
    }

    // Требование 3.3.3. Слово отсутствует в словаре
    if (!tree_.remove(word))
    {
        std::cout << MSG_WORD_NOT_FOUND_PREFIX << " \"" << word << "\" " << MSG_WORD_NOT_FOUND_SUFFIX << '\n';
        return;
    }

    // Требование 3.3.4. Слово задано корректно и присутствует в словаре
    std::cout << MSG_WORD_REMOVED_PREFIX << " \"" << word << "\" " << MSG_WORD_REMOVED_SUFFIX << '\n';
}

// Обработка команды PRINT
void Dictionary::handlePrint(const std::string& args) const
{
    std::istringstream checkArgs(args);
    std::string extra;
    
    // Требование 3.4.1. После названия команды присутствуют символы
    if (checkArgs >> extra)
    {
        std::cerr << ERROR_PRINT_TAKES_NO_ARGUMENTS << '\n';
    }
    else
    {
        printAll(std::cout);
    }
}

// Обработка команды EXIT
bool Dictionary::handleExit(const std::string& args) const
{
    std::istringstream exitArgs(args);
    std::string filename;
    exitArgs >> filename;

    // Требование 3.5.1. Выходной файл не задан
    if (filename.empty())
    {
        if (tree_.isEmpty())
        {
            std::cout << WARNING_DICTIONARY_IS_EMPTY << '\n';
        }
        filename = DEFAULT_OUTPUT_FILENAME;
        std::cout << MSG_OUTPUT_FILENAME_NOT_SPECIFIED << MSG_DICTIONARY_SAVED << filename << '\n';
        saveToFile(filename);
        return false;
    }

    // Требование 3.5.3. Выходной файл задан и открыт
    if (saveToFile(filename))
    {
        if (tree_.isEmpty())
        {
            std::cout << WARNING_DICTIONARY_IS_EMPTY << '\n';
        }
        std::cout << MSG_DICTIONARY_SAVED << filename << '\n';
    }
    else
    {
        printHelp();
        return true;
    }

    return false;
}

// Вывод списка допустимых команд
void Dictionary::printHelp() const
{
    std::cout << MSG_COMMAND_LIST_HEADER << "\n"
        << MSG_COMMAND_INSERT << "\n"
        << MSG_COMMAND_SEARCH << "\n"
        << MSG_COMMAND_REMOVE << "\n"
        << MSG_COMMAND_PRINT << "\n"
        << MSG_COMMAND_EXIT << "\n";
}

// ======= Реализация public методов =======

// Загрузка словаря из входного файла
bool Dictionary::loadFromFile(const std::string& filename)
{
    // Требование 1.1. Входной файл не задан
    if (filename.empty())
    {
        std::cout << INPUT_FILE_IS_NOT_SPECIFIED << '\n';
        printHelp();
        return false;
    }

    // Требование 1.2. Входной файл не найден/не открыт
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << ERROR_INPUT_FILE_NOT_FOUND << '\n';
        printHelp();
        return false;
    }

    // Требование 1.3. Входной файл задан и открыт
    std::cout << MSG_INPUT_FILE << filename << MSG_PROCESSING_DICTIONARY_RECORDS << '\n';

    std::string line;
    size_t lineNumber = 0;
    bool hasValidRecords = false;

    while (std::getline(file, line))
    {
        ++lineNumber;
        if (line.empty())
        {
            continue;
        }

        hasValidRecords = true;

        std::string word;
        RedBlackTree::List<std::string> translations;
        bool success = false;

        parseLine(line, word, translations, success, lineNumber);

        if (success)
        {
            tree_.insert(word, std::move(translations));
        }
    }

    file.close();

    if (!hasValidRecords)
    {
        std::cout << WARNING_INPUT_FILE_IS_EMPTY << '\n';
    }

    printHelp();
    return true;
}

// Сохранение текущего состояния словаря в выходной файл
bool Dictionary::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    // Требование 3.5.2. Выходной файл не открыт
    if (!file.is_open())
    {
        std::cerr << ERROR_OUTPUT_FILE_NOT_OPENED << "\n";
        return false;
    }

    printAll(file);
    file.close();
    return true;
}

// Обработка команды, вводимой пользователем
bool Dictionary::processCommand(const std::string& commandLine)
{
    std::istringstream iss(commandLine);
    std::string command;
    iss >> command;

    std::string args;
    std::getline(iss, args);

    if (command == CMD_INSERT)
    {
        handleInsert(args);
        printHelp();
    }
    else if (command == CMD_SEARCH)
    {
        handleSearch(args);
        printHelp();
    }
    else if (command == CMD_REMOVE)
    {
        handleRemove(args);
        printHelp();
    }
    else if (command == CMD_PRINT)
    {
        handlePrint(args);
        printHelp();
    }
    else if (command == CMD_EXIT)
    {
        return handleExit(args);
    }
    else if (!command.empty())
    {
        // Требование 3.0. Название команды должно быть задано корректно
        std::cerr << ERROR_INVALID_COMMAND_NAME << "\n";
        printHelp();
    }

    return true;
}

// Вывод свех записей словаря в поток
void Dictionary::printAll(std::ostream& out) const
{
    // Требование 3.4.2. Словарь является пустым
    if (tree_.isEmpty())
    {
        out << MSG_DICTIONARY_IS_EMPTY << "\n";
    }
    // Требование 3.4.3.Словарь не является пустым
    else
    {
        tree_.print(out);
    }
}

// Запуск интерактивного режима работы со словарём
void Dictionary::runInteractiveMode()
{
    std::string line;
    while (true)
    {
        std::cout << PROMPT_COMMAND;
        if (!std::getline(std::cin, line))
        {
            break;
        }

        if (!line.empty())
        {
            if (!processCommand(line))
            {
                break;
            }
        }
    }
}