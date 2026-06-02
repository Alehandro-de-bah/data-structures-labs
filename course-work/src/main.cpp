#include "Dictionary.h"

int main()
{
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian_Russia.1251");

    Dictionary dict;

    std::cout << ENTER_THE_NAME_OF_THE_FILE;
    std::string filename;
    std::getline(std::cin, filename);

    dict.loadFromFile(filename);

    dict.runInteractiveMode();

    return 0;
}