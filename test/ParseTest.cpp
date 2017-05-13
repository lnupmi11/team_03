#include "gtest/gtest.h"
#include "../DTO/DataParser.h"

TEST(ParseTest, composeUser)
{
	User test("user1", "user1");
	ASSERT_EQ("user1^^^field^^^user1", compose(test));
}

TEST(ParseTest, composeComment)
{
	Comment test("user1", "plot", "now");
	ASSERT_EQ("user1|||subfield|||plot|||subfield|||now", compose(test));
}

TEST(ParseTest, composeEvent)
{
	Event test("title", "Complete Plot", "Short plot", "now", 
		high, "user1");
	
	ASSERT_EQ("title^^^field^^^Complete Plot^^^field^^^Short plot^^^field^^^now^^^field^^^2^^^field^^^user1^^^field^^^0^^^field^^^^^^field^^^", compose(test));

	test.setPriority(Priority::low);

	ASSERT_EQ("title^^^field^^^Complete Plot^^^field^^^Short plot^^^field^^^now^^^field^^^0^^^field^^^user1^^^field^^^0^^^field^^^^^^field^^^", compose(test));
}
