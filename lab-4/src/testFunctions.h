#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <cassert>
#include "BinarySearchTree.h"

template <typename T>
using BST = BinarySearchTree<T>;

void createBST(BST<int>& tree);

void testBSTDefaultConstructor();

void testBSTInsert();

void testBSTMoveConstructor();

void testBSTMovingAssignmentOperator();

void testBSTSearchIterative();

void testBSTRemove();

void testBSTOutput();

void testBSTWalkInOrder();

void testBSTWalkByLevels();

void testBSTCountKeysInRange();

void runAllTests();

#endif
