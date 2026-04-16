#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "HashTable.h"
#include "String.h"
#include <cassert>

template <typename T>
using HT = HashTable<T>;

void testHTDefaultConstructor();

void testHTInsert();

void testHTSearch();

void testHTRemove();

void runAllHashTableTests();

#endif