#include "gtest/gtest.h"
#include <sstream>
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

TEST(BLTest, SignUp)
{
	vector<User> usersArr;
	ASSERT_EQ(usersArr.size(), 0);
	istringstream input1("userLogin1\nuserPassword1\nuserLogin2\nuserPassword2\nuserLogin3\nuserPassword3\nuserLogin3\nuserPassword3");
	cin.rdbuf(input1.rdbuf());
	signUp(usersArr);
	ASSERT_EQ(usersArr.size(), 1);
	ASSERT_EQ(usersArr[0].getUserName(), "userLogin1");
	ASSERT_EQ(usersArr[0].getPassword(), "userPassword1");
	signUp(usersArr);
	ASSERT_EQ(usersArr.size(), 2);
	ASSERT_EQ(usersArr[1].getUserName(), "userLogin2");
	ASSERT_EQ(usersArr[1].getPassword(), "userPassword2");
	signUp(usersArr);
	ASSERT_EQ(usersArr.size(), 3);
	ASSERT_EQ(usersArr[2].getUserName(), "userLogin3");
	ASSERT_EQ(usersArr[2].getPassword(), "userPassword3");
	ASSERT_EQ(usersArr.size(), 3);
}
