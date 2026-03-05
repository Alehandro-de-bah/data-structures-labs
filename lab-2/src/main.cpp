#include "DoubleOrderedList.h"
#include "String.h"
#include "exceptions.h"
#include <gtest/gtest.h>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

template <typename T>
using List = DoubleOrderedList<T>; // Задаём шаблонный псевдоним (для более короткой записи)

TEST(DoubleOrderedListTest, CreateEmptyList)
{
	List<String> l1;
	EXPECT_EQ(l1.size(), 0);
}

TEST(DoubleOrderedListTest, CreateListWithValue)
{
	String str = "hello";
	List<String> l1(str);
	EXPECT_EQ(l1.size(), 1);
	EXPECT_EQ(l1.head(), str);
	EXPECT_EQ(l1.tail(), str);
}

TEST(DoubleOrderedListTest, CopyList)
{
	String str = "world";
	List<String> l1(str);
	List<String> l2(l1);
	EXPECT_EQ(l1.size(), l2.size());
	EXPECT_EQ(l1.head(), l2.head());
	EXPECT_EQ(l1.tail(), l2.tail());
}

TEST(DoubleOrderedListTest, MoveList)
{
	String str = "train";
	List<String> l1(str);
	List<String> l2(std::move(l1));
	EXPECT_EQ(l2.size(), 1);
	EXPECT_EQ(l2.head(), str);
}

TEST(DoubleOrderedListTest, CopyingAssignmentOperatorForList)
{
	String str1 = "c++";
	String str2 = "python";
	List<String> l1(str1);
	List<String> l2(str2);
	l2 = l1;
	EXPECT_EQ(l1, l2);
}

TEST(DoubleOrderedListTest, MovingAssignmentOperatorForList)
{
	String str1 = "java";
	String str2 = "rust";
	List<String> l1(str1);
	l1 = List<String>(str2);
	EXPECT_EQ(l1.size(), 1);
	EXPECT_EQ(l1.head(), str2);
}

TEST(DoubleOrderedListTest, AccessToHeadOfList)
{
	List<String> l1;
	EXPECT_THROW(l1.head(), std::out_of_range);

	String str = "key";
	List<String> l2(str);
	EXPECT_EQ(l2.head(), str);
}

TEST(DoubleOrderedListTest, AccessToTailOfList)
{
	List<String> l1;
	EXPECT_THROW(l1.tail(), std::out_of_range);

	String str = "tree";
	List<String> l2(str);
	EXPECT_EQ(l2.tail(), str);
}

TEST(DoubleOrderedListTest, SearchKeyInList)
{
	List<String> l1;
	String str = "job";
	EXPECT_FALSE(l1.search(str));
	List<String> l2(str);
	EXPECT_TRUE(l2.search(str));
}

TEST(DoubleOrderedListTest, InsertInList)
{
	List<String> l;
	l.insert(String("abc"));
	l.insert(String("abc"));
	l.insert(String("height"));
	l.insert(String("circle"));
	EXPECT_EQ(l.size(), 3);
	EXPECT_TRUE(l.isListSorted());
}

TEST(DoubleOrderedListTest, RemoveHeadFromList)
{
	List<String> l;
	EXPECT_THROW(l.removeHead(), std::out_of_range);
	String str1("window");
	String str2("house");
	l.insert(str1);
	l.insert(str2);
	l.removeHead();
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.head(), str1);
	EXPECT_EQ(l.head(), l.tail());
}

TEST(DoubleOrderedListTest, ClearList)
{
	List<String> l;
	l.insert(String("cat"));
	l.insert(String("dog"));
	l.insert(String("horse"));
	l.clear();
	EXPECT_EQ(l.size(), 0);
	EXPECT_THROW(l.head(), std::out_of_range);
	EXPECT_THROW(l.tail(), std::out_of_range);
}

TEST(DoubleOrderedListTest, RemoveKeysFromList)
{
	List<int> l;
	l.insert(3);
	l.insert(10);
	l.insert(5);
	l.insert(17);
	l.insert(8);
	l.insert(14);
	EXPECT_THROW(l.removeKey(10, 5), std::out_of_range);
	l.removeKey(20, 30);
	EXPECT_EQ(l.size(), 6);
	l.removeKey(7, 12);
	EXPECT_EQ(l.size(), 4);
	EXPECT_TRUE(l.isListSorted());
	l.removeKey(0, 20);
	EXPECT_TRUE(l.isEmpty());
}

TEST(DoubleOrderedListTest, EqualityOperatorForList)
{
	List<String> l1;
	l1.insert(String("road"));
	l1.insert(String("family"));
	l1.insert(String("animal"));
	l1.insert(String("human"));
	List<String> l2(l1);
	EXPECT_TRUE(l1 == l2);
	l1.removeHead();
	EXPECT_FALSE(l1 == l2);
}

TEST(DoubleOrderedListTest, MergeLists)
{
	List<String> l1;
	List<String> l2;
	l1.merge(l2);
	EXPECT_TRUE(l1.isEmpty());
	EXPECT_TRUE(l2.isEmpty());
	l2.insert(String("lake"));
	l2.insert(String("river"));
	l2.insert(String("sea"));
	l1.merge(l2);
	EXPECT_EQ(l1.size(), 3);
	EXPECT_TRUE(l1.isListSorted());
	EXPECT_TRUE(l2.isEmpty());
	l2.insert(String("queue"));
	l2.insert(String("stack"));
	l2.insert(String("lake"));
	l1.merge(l2);
	EXPECT_EQ(l1.size(), 5);
	EXPECT_TRUE(l1.isListSorted());
	EXPECT_TRUE(l2.isEmpty());
	l1.merge(l1);
	EXPECT_EQ(l1.size(), 5);
	EXPECT_TRUE(l1.isListSorted());
}

TEST(DoubleOrderedListTest, RemoveList)
{
	List<String> l1;
	l1.insert(String("php"));
	l1.insert(String("ruby"));
	List<String> l2(l1);
	l1.remove(l2);
	EXPECT_TRUE(l1.isEmpty());
	EXPECT_EQ(l2.size(), 2);
	EXPECT_TRUE(l2.isListSorted());
	l2.insert(String("git"));
	l2.insert(String("bash"));
	l1.insert(String("ruby"));
	l1.insert(String("bash"));
	l2.remove(l1);
	EXPECT_EQ(l2.size(), 2);
	EXPECT_TRUE(l2.isListSorted());
	EXPECT_EQ(l1.size(), 2);
	EXPECT_TRUE(l1.isListSorted());
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");
	try
	{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	catch (const std::bad_alloc& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const char* error)
	{
		std::cerr << error << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << ERROR_SOMETHING_WENT_WRONG << std::endl;
		return 1;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}