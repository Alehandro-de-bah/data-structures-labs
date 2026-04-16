#include "testFunctions.h"

void createBST(BST<int>& tree)
{
	tree.insert(8);
	tree.insert(3);
	tree.insert(10);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	tree.insert(1);
	tree.insert(14);
	tree.insert(13);
}

void testBSTDefaultConstructor()
{
	BST<int> t;
	assert(t.getNumberOfNodes() == 0);
	assert(t.getHeight() == -1);
}

void testBSTInsert()
{
	BST<int> t;
	assert(t.insert(8) == true);
	assert(t.getNumberOfNodes() == 1);
	assert(t.getHeight() == 0);
	
	assert(t.insert(3) == true);
	assert(t.getNumberOfNodes() == 2);
	assert(t.getHeight() == 1);

	assert(t.insert(10) == true);
	assert(t.getNumberOfNodes() == 3);
	assert(t.getHeight() == 1);

	assert(t.insert(6) == true);
	assert(t.getNumberOfNodes() == 4);
	assert(t.getHeight() == 2);

	assert(t.insert(4) == true);
	assert(t.getNumberOfNodes() == 5);
	assert(t.getHeight() == 3);

	assert(t.insert(7) == true);
	assert(t.getNumberOfNodes() == 6);
	assert(t.getHeight() == 3);

	assert(t.insert(1) == true);
	assert(t.getNumberOfNodes() == 7);
	assert(t.getHeight() == 3);

	assert(t.insert(14) == true);
	assert(t.getNumberOfNodes() == 8);
	assert(t.getHeight() == 3);

	assert(t.insert(13) == true);
	assert(t.getNumberOfNodes() == 9);
	assert(t.getHeight() == 3);

	assert(t.insert(13) == false);
}

void testBSTOutput()
{
	BST<int> t;
	std::cout << "Output for empty tree: ";
	t.output(std::cout);
	std::cout << '\n';

	createBST(t);

	std::cout << "Output for non-empty tree: ";
	t.output(std::cout);
	std::cout << '\n';
}

void testBSTMoveConstructor()
{
	BST<int> t1;
	createBST(t1);
	BST<int> t2 = std::move(t1);
	std::cout << "Output for t2 after move constructor: ";
	t2.output(std::cout);
	std::cout << '\n';
	assert(t2.getNumberOfNodes() == 9);
	assert(t2.getHeight() == 3);
}

void testBSTMovingAssignmentOperator()
{
	BST<int> t;
	createBST(t);
	t = BST<int>();
	assert(t.getNumberOfNodes() == 0);
	assert(t.getHeight() == -1);
}

void testBSTSearchIterative()
{
	BST<int> tree;
	// ѕоиск в пустом дереве
	assert(tree.searchIterative(1) == false);
	assert(tree.searchIterative(4) == false);
	assert(tree.searchIterative(10) == false);

	createBST(tree);
	std::cout << "tree: ";
	tree.output(std::cout);
	std::cout << '\n';

	bool isFourInTree = tree.searchIterative(4);
	bool isSevenInTree = tree.searchIterative(7);
	bool isFourteenInTree = tree.searchIterative(14);
	
	bool isFiveInTree = tree.searchIterative(5);
	bool isNineInTree = tree.searchIterative(9);
	bool isTwelveInTree = tree.searchIterative(12);

	assert(isFourInTree == true);
	std::cout << "searchIterative(4) = " << std::boolalpha << isFourInTree << '\n';
	assert(isSevenInTree == true);
	std::cout << "searchIterative(7) = " << std::boolalpha << isSevenInTree << '\n';
	assert(isFourteenInTree == true);
	std::cout << "searchIterative(14) = " << std::boolalpha << isFourteenInTree << '\n';
	assert(isFiveInTree == false);
	std::cout << "searchIterative(5) = " << std::boolalpha << isFiveInTree << '\n';
	assert(isNineInTree == false);
	std::cout << "searchIterative(9) = " << std::boolalpha << isNineInTree << '\n';
	assert(isTwelveInTree == false);
	std::cout << "searchIterative(12) = " << std::boolalpha << isTwelveInTree << '\n';
}

void testBSTRemove()
{
	BST<int> t;
	// ”даление ключа в пустом дереве
	assert(t.remove(8) == false);
	assert(t.remove(3) == false);

	createBST(t);
	t.insert(5); // 5 - правый ребЄнок дл¤ 4

	std::cout << "Tree before remove: ";
	t.output(std::cout);
	std::cout << '\n';

	assert(t.remove(9) == false); // ”даление несуществующего ключа

	assert(t.remove(1) == true); // ”даление листа
	std::cout << "Tree after remove(1): ";
	t.output(std::cout);
	std::cout << '\n';
	assert(t.getNumberOfNodes() == 9);
	assert(t.getHeight() == 4);
	assert(t.searchIterative(1) == false);

	assert(t.remove(14) == true); // ”даление узла с одним потомком
	std::cout << "Tree after remove(14): ";
	t.output(std::cout);
	std::cout << '\n';
	assert(t.getNumberOfNodes() == 8);
	assert(t.getHeight() == 4);
	assert(t.searchIterative(14) == false);

	assert(t.remove(6) == true); // ”даление узла с двум¤ потомками
	std::cout << "Tree after remove(6): ";
	t.output(std::cout);
	std::cout << '\n';
	assert(t.getNumberOfNodes() == 7);
	assert(t.getHeight() == 4);
	assert(t.searchIterative(6) == false);
}

void testBSTWalkInOrder()
{
	BST<int> t;
	std::cout << "inorderWalk for empty tree:          ";
	t.inorderWalk();
	std::cout << "\ninorderWalkIterative for empty tree: ";
	t.inorderWalkIterative();

	createBST(t);

	std::cout << "\ninorderWalk for non-empty tree:          ";
	t.inorderWalk();
	std::cout << "\ninorderWalkIterative for non-empty tree: ";
	t.inorderWalkIterative();
	std::cout << '\n';
}

void testBSTWalkByLevels()
{
	BST<int> t;
	std::cout << "walkByLevels for empty tree: ";
	t.walkByLevels();
	
	createBST(t);

	std::cout << "\nwalkByLevels for non-empty tree: ";
	t.walkByLevels();
	std::cout << '\n';
}

void testBSTCountKeysInRange()
{
	BST<int> tree;
	createBST(tree);
	std::cout << "tree: ";
	tree.output(std::cout);
	std::cout << '\n';

	//std::cout << t.countKeysInRange(13, 10); // »сключение InvalidRange
	//std::cout << t.countKeysInRangeIterative(13, 10); // »сключение InvalidRange

	int amountOfNodes = tree.getNumberOfNodes();
	int amountOfKeysInOneToFive = tree.countKeysInRange(1, 5);
	int amountOfKeysInOneToFiveIterative = tree.countKeysInRangeIterative(1, 5);
	int amountOfKeysInElevenToTwelve = tree.countKeysInRange(11, 12);
	int amountOfKeysInElevenToTwelveIterative = tree.countKeysInRangeIterative(11, 12);
	int amountOfKeysInSevenToSeven = tree.countKeysInRange(7, 7);
	int amountOfKeysInSevenToSevenIterative = tree.countKeysInRangeIterative(7, 7);
	int amountOfKeysInOneToFourteen = tree.countKeysInRange(1, 14);
	int amountOfKeysInOneToFourteenIterative = tree.countKeysInRangeIterative(1, 14);

	assert(amountOfKeysInOneToFive == 3);
	std::cout << "countKeysInRange(1, 5) = " << amountOfKeysInOneToFive << '\n';
	assert(amountOfKeysInOneToFiveIterative == 3);
	std::cout << "countKeysInRangeIterative(1, 5) = " << amountOfKeysInOneToFiveIterative << '\n';
	assert(amountOfKeysInElevenToTwelve == 0);
	std::cout << "countKeysInRange(11, 12) = " << amountOfKeysInElevenToTwelve << '\n';
	assert(amountOfKeysInElevenToTwelveIterative == 0);
	std::cout << "countKeysInRangeIterative(11, 12) = " << amountOfKeysInElevenToTwelveIterative << '\n';
	assert(amountOfKeysInSevenToSeven == 1);
	std::cout << "countKeysInRange(7, 7) = " << amountOfKeysInSevenToSeven << '\n';
	assert(amountOfKeysInSevenToSevenIterative == 1);
	std::cout << "countKeysInRangeIterative(7, 7) = " << amountOfKeysInSevenToSevenIterative << '\n';
	assert(amountOfKeysInOneToFourteen == amountOfNodes);
	std::cout << "countKeysInRange(1, 14) = getNumberOfNodes() = " << amountOfKeysInOneToFourteen << '\n';
	assert(amountOfKeysInOneToFourteenIterative == amountOfNodes);
	std::cout << "countKeysInRangeIterative(1, 14) = getNumberOfNodes() = " << amountOfKeysInOneToFourteenIterative << '\n';
}

void runAllTests()
{
	std::cout << "===== BinarySearchTree tests =====\n\n";

	std::cout << "1) testBSTDefaultConstructor\n";
	testBSTDefaultConstructor();
	std::cout << "testBSTDefaultConstructor passed!\n\n";

	std::cout << "2) testBSTInsert\n";
	testBSTInsert();
	std::cout << "testBSTInsert passed!\n\n";

	std::cout << "3) testBSTOutput\n";
	testBSTOutput();
	std::cout << "testBSTOutput passed!\n\n";

	std::cout << "4) testBSTMoveConstructor\n";
	testBSTMoveConstructor();
	std::cout << "testBSTMoveConstructor passed!\n\n";

	std::cout << "5) testBSTMovingAssignmentOperator\n";
	testBSTMovingAssignmentOperator();
	std::cout << "testBSTMovingAssignmentOperator passed!\n\n";

	std::cout << "6) testBSTSearchIterative\n";
	testBSTSearchIterative();
	std::cout << "testBSTSearchIterative passed!\n\n";

	std::cout << "7) testBSTRemove\n";
	testBSTRemove();
	std::cout << "testBSTRemove passed!\n\n";

	std::cout << "8) testBSTWalkInOrder\n";
	testBSTWalkInOrder();
	std::cout << "testBSTWalkInOrder passed!\n\n";

	std::cout << "9) testBSTWalkByLevels\n";
	testBSTWalkByLevels();
	std::cout << "testBSTWalkByLevels passed!\n\n";

	std::cout << "10) testBSTCountKeysInRange\n";
	testBSTCountKeysInRange();
	std::cout << "testBSTCountKeysInRange passed!\n\n";

	std::cout << "===== All tests passed! =====" << '\n';
}