#include "StackArray.h"
#include "QueueVector.h"
#include "StackExceptions.h"
#include "QueueExceptions.h"
#include "String.h"
#include "checkBalanceBrackets.h"
#include <gtest/gtest.h>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

TEST(StackArrayTest, StackArrayConstructorWithSize)
{
	StackArray<String> s(5);
	EXPECT_EQ(s.size(), 0);
	EXPECT_EQ(s.capacity(), 5);
	EXPECT_THROW(StackArray<String>(-10), WrongStackSize);
}

TEST(StackArrayTest, PushInStackArray)
{
	StackArray<String> s(3);
	s.push(String("home"));
	EXPECT_EQ(s.size(), 1);
	s.push(String("window"));
	EXPECT_EQ(s.size(), 2);
	s.push(String("chair"));
	EXPECT_EQ(s.size(), 3);
	EXPECT_EQ(s.capacity(), 3);
	EXPECT_THROW(s.push(String("smth")), StackOverflow);
}

TEST(StackArrayTest, PopFromStackArray)
{
	StackArray<String> s(3);
	String str1("palace");
	String str2("loop");
	String str3("title");
	s.push(str1);
	s.push(str2);
	s.push(str3);
	String first = s.pop();
	EXPECT_EQ(first, str3);
	EXPECT_EQ(s.size(), 2);
	first = s.pop();
	EXPECT_EQ(first, str2);
	EXPECT_EQ(s.size(), 1);
	first = s.pop();
	EXPECT_EQ(first, str1);
	EXPECT_EQ(s.size(), 0);
	EXPECT_TRUE(s.isEmpty());
	EXPECT_THROW(s.pop(), StackUnderflow);
}

TEST(QueueVectorTest, QueueVectorConstructorWithSize)
{
	QueueVector<String> q(5);
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.capacity(), 5);
	EXPECT_TRUE(q.isEmpty());
	EXPECT_FALSE(q.isFull());
	EXPECT_THROW(QueueVector<String>(-10), WrongQueueSize);
}

TEST(QueueVectorTest, EnQueueInQueueVector)
{
	QueueVector<String> q(3);
	String str1("floor");
	String str2("ceil");
	String str3("rabbit");
	String str4("gnome");
	q.enQueue(str1);
	EXPECT_EQ(q.size(), 1);
	EXPECT_EQ(q.capacity(), 3);
	q.enQueue(str2);
	EXPECT_EQ(q.size(), 2);
	EXPECT_EQ(q.capacity(), 3);
	q.enQueue(str3);
	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.capacity(), 3);
	EXPECT_TRUE(q.isFull());
	q.enQueue(str4);
	EXPECT_EQ(q.size(), 4);
	EXPECT_GT(q.capacity(), q.size());
}

TEST(QueueVectorTest, DeQueueFromQueueVector)
{
	QueueVector<String> q(2);
	String str1("plane");
	String str2("car");
	String str3("train");
	String str4("bus");
	q.enQueue(str1);
	q.enQueue(str2);
	q.enQueue(str3);
	q.enQueue(str4);
	String first = q.deQueue();
	EXPECT_EQ(first, str1);
	EXPECT_EQ(q.size(), 3);
	first = q.deQueue();
	EXPECT_EQ(first, str2);
	EXPECT_EQ(q.size(), 2);
	first = q.deQueue();
	EXPECT_EQ(first, str3);
	EXPECT_EQ(q.size(), 1);
	first = q.deQueue();
	EXPECT_EQ(first, str4);
	EXPECT_EQ(q.size(), 0);
	EXPECT_TRUE(q.isEmpty());
	EXPECT_THROW(q.deQueue(), QueueUnderflow);
}

TEST(CheckBalanceBracketsTest, EmptyText)
{
	EXPECT_FALSE(checkBalanceBrackets(""));
	EXPECT_FALSE(checkBalanceBrackets(nullptr));
}

TEST(CheckBalanceBracketsTest, IncorrectMaxDeep)
{
	EXPECT_FALSE(checkBalanceBrackets("()[{}]", -81));
}

TEST(CheckBalanceBracketsTest, TextWithoutBrackets)
{
	EXPECT_TRUE(checkBalanceBrackets("abcde", 7));
}

TEST(CheckBalanceBracketsTest, CorrectTextWithBrackets)
{
	EXPECT_TRUE(checkBalanceBrackets("()", 7));
	EXPECT_TRUE(checkBalanceBrackets("[]", 4));
	EXPECT_TRUE(checkBalanceBrackets("{}", 7));
	EXPECT_TRUE(checkBalanceBrackets("(([{}]))", 5));
	EXPECT_TRUE(checkBalanceBrackets("()[]{}{}()[]", 6));
	EXPECT_TRUE(checkBalanceBrackets("{[{}()[]]}", 4));
}

TEST(CheckBalanceBracketsTest, CorrectTextWithBracketsButTooDeep)
{
	EXPECT_FALSE(checkBalanceBrackets("([])", 1));
	EXPECT_FALSE(checkBalanceBrackets("({[{}]})", 3));
	EXPECT_FALSE(checkBalanceBrackets("[]({()()[]})", 2));
}

TEST(CheckBalanceBracketsTest, IncorrectTextWithBrackets)
{
	EXPECT_FALSE(checkBalanceBrackets("())", 7));
	EXPECT_FALSE(checkBalanceBrackets("[nj()", 4));
	EXPECT_FALSE(checkBalanceBrackets("nsdh}{}[", 4));
	EXPECT_FALSE(checkBalanceBrackets("(f)h{smt]"));
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RU");
	try
	{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	catch (const QueueUnderflow& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const WrongQueueSize& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const QueueBadAllocationInConstructor& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const QueueBadAllocationInResize& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const QueueErrorInCopying& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const StackOverflow& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const StackUnderflow& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const StackBadAllocationInConstructor& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const StackErrorInCopying& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const WrongStackSize& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}
	catch (const char* error)
	{
		std::cerr << error << std::endl;
		return 1;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}