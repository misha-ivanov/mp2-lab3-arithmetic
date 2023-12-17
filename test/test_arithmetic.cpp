// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "stack.h"
#include "arithmetic.h"

TEST(Arithmetic, can_convert_true_expression)
{
	std::string S = "4+2*a";
	Arithmetic A;
	ASSERT_NO_THROW(A.Convert(S));
}

TEST(Arithmetic, cannot_convert_expression_with_unacceptable_symbol)
{
	std::string S = "4+#*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, cannot_convert_expression_with_several_points_in_one_number)
{
	std::string S = "4.1.3+2*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, cannot_convert_expression_with_close_brackets_error)
{
	std::string S = "(4+2*a))";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, cannot_convert_expression_with_open_brackets_error)
{
	std::string S = "(4+2*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, near_signs_error)
{
	std::string S = "4+-2*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, near_brackets_error)
{
	std::string S = "4+()2*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, next_to_open_brackets_error)
{
	std::string S = "4(+2*a";
	Arithmetic A;
	ASSERT_ANY_THROW(A.Convert(S));
}

TEST(Arithmetic, size_of_data_is_correct)
{
	std::string S = "4+2*a";
	Arithmetic A;
	A.Convert(S);

	EXPECT_EQ(A.GetLengthFromData(), 5);
}


// postfix

TEST(Arithmetic, size_of_postfix_is_correct)
{
	std::string S = "4+2*a";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();


	EXPECT_EQ(A.GetLengthFromPostfix(), 5);
}

TEST(Arithmetic, can_calculate_simple)
{
	std::string S = "4+2";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), 6.0);
}

TEST(Arithmetic, can_calculate_with_negative)
{
	std::string S = "-4+2";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -2.0);
}

TEST(Arithmetic, can_calculate_with_negative_in_brackets_1)
{
	std::string S = "4+2*(-4)";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -4.0);
}

TEST(Arithmetic, can_calculate_with_negative_in_brackets_2)
{
	std::string S = "4*2*(-4)";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -32.0);
}

TEST(Arithmetic, can_calculate_with_negative_and_brackets)
{
	std::string S = "(4+2)*(-4-2)";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -36.0);
}

TEST(Arithmetic, can_calculate_with_float_negative_and_brackets)
{
	std::string S = "(4.0+2.0)*(-4.0-2.0)";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -36.0);
}

TEST(Arithmetic, cannot_devide_by_real_zero)
{
	std::string S = "4/0";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	ASSERT_ANY_THROW(A.Calculate());
}

TEST(Arithmetic, cannot_devide_by_float_zero)
{
	std::string S = "4/0.0";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	ASSERT_ANY_THROW(A.Calculate());
}

TEST(Arithmetic, can_calculate_with_several_brackets)
{
	std::string S = "4-(2*(1+4))";
	Arithmetic A;
	A.Convert(S);
	A.CreatePostfix();

	EXPECT_EQ(A.Calculate(), -6.0);
}