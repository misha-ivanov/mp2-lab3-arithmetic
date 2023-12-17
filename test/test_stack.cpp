// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create)
{
	ASSERT_NO_THROW(Stack<int> s());
}

TEST(Stack, can_create_with_positive_size)
{
	ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(Stack, cannot_create_with_zero_size)
{
	ASSERT_ANY_THROW(Stack<int> s(0));
}

TEST(Stack, cannot_create_with_negative_size)
{
	ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, can_copy)
{
	Stack<int> S1(2);
	S1.push(1);
	S1.push(2);
	Stack<int> S2(S1);

	EXPECT_EQ(S1.Top(), S2.Top());
}

TEST(Stack, can_push)
{
	Stack<int> S;
	S.push(5);

	EXPECT_EQ(S.Top(), 5);
}

TEST(Stack, can_push_and_increase_size)
{
	Stack<int> S;
	S.push(1);
	S.push(2);

	EXPECT_EQ(S.SizeData(), 2);
}

TEST(Stack, can_pop)
{
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.pop();

	EXPECT_EQ(S.Top(), 1);
}

TEST(Stack, cannot_pop_when_empty)
{
	Stack<int> S;
	S.push(1);
	S.pop();

	ASSERT_ANY_THROW(S.pop());
}

TEST(Stack, can_clear)
{
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.Clear();

	EXPECT_EQ(S.SizeData(), 1);
}

TEST(Stack, can_clear_correctly)
{
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.Clear();
	S.push(1);
	S.push(2);

	EXPECT_EQ(S.Top(), 2);
}

TEST(Stack, can_return_top)
{
	Stack<int> S;
	S.push(1);

	EXPECT_EQ(S.Top(), 1);
}

TEST(Stack, can_identify_empty)
{
	Stack<int> S1;
	S1.push(1);
	S1.pop();

	Stack<int> S2;
	S2.push(1);

	EXPECT_EQ(S1.IsEmpty() && !S2.IsEmpty(), 1);
}