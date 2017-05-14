#include "gtest/gtest.h"
#include "../BL/Functions.h"

TEST(BLTest, InputToInt)
{
	string input;
	input = "1";
	ASSERT_EQ(inputToInt(input), 1);
	input = "0";
	ASSERT_EQ(inputToInt(input), 0);
	input = "a";
	ASSERT_EQ(inputToInt(input), 0);
	input = "some invalid input";
	ASSERT_EQ(inputToInt(input), 0);
}

TEST(BLTest, LikeEvent)
{
	User testUser;
	Event testEvent;
	ASSERT_EQ(testEvent.getPopularity(), 0);
	like(testEvent, testUser);
	ASSERT_EQ(testEvent.getPopularity(), 1);
}

TEST(BLTest, DislikeEvent)
{
	User testUser;
	Event testEvent;
	vector<Event> testEventsArr;
	testEvent.setPopularity(1);
	testEventsArr.push_back(testEvent);
	ASSERT_EQ(testEvent.getPopularity(), 1);
	dislike(testEvent, testUser, testEventsArr, testUser.getPosts());
	ASSERT_EQ(testEvent.getPopularity(), 0);
}
