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

TEST(BLTest, Events)
{
	User testUser("user1", "user1");
	vector<Event> eventsArr;
	istringstream input("title1\nshortPlot1\nplot1\n2\n1\nnewTitle1\nnewShortPlot1\nnewPlot1\n3\n1");

	ASSERT_EQ(testUser.getPosts().size(), 0);
	ASSERT_EQ(eventsArr.size(), 0);

	createEvent(testUser, testUser.getPosts(), eventsArr);

	ASSERT_EQ(testUser.getPosts()[0].getAuthor(), "user1");
	ASSERT_EQ(testUser.getPosts()[0].getPlot(), "plot1");
	ASSERT_EQ(testUser.getPosts()[0].getPopularity(), 0);
	ASSERT_EQ(testUser.getPosts()[0].getPriority(), medium);
	ASSERT_EQ(testUser.getPosts()[0].getShortPlot(), "shortPlot1");
	ASSERT_EQ(testUser.getPosts()[0].getTitle(), "title1");
	ASSERT_EQ(testUser.getPosts().size(), 1);

	ASSERT_EQ(eventsArr[0].getAuthor(), "user1");
	ASSERT_EQ(eventsArr[0].getPlot(), "plot1");
	ASSERT_EQ(eventsArr[0].getPopularity(), 0);
	ASSERT_EQ(eventsArr[0].getPriority(), medium);
	ASSERT_EQ(eventsArr[0].getShortPlot(), "shortPlot1");
	ASSERT_EQ(eventsArr[0].getTitle(), "title1");
	ASSERT_EQ(eventsArr.size(), 1);

	updateEvent(testUser, testUser.getPosts(), eventsArr);
	
	ASSERT_EQ(testUser.getPosts()[0].getAuthor(), "user1");
	ASSERT_EQ(testUser.getPosts()[0].getPlot(), "newPlot1");
	ASSERT_EQ(testUser.getPosts()[0].getPopularity(), 0);
	ASSERT_EQ(testUser.getPosts()[0].getPriority(), high);
	ASSERT_EQ(testUser.getPosts()[0].getShortPlot(), "newShortPlot1");
	ASSERT_EQ(testUser.getPosts()[0].getTitle(), "newTitle1");
	ASSERT_EQ(testUser.getPosts().size(), 1);

	ASSERT_EQ(eventsArr[0].getAuthor(), "user1");
	ASSERT_EQ(eventsArr[0].getPlot(), "newPlot1");
	ASSERT_EQ(eventsArr[0].getPopularity(), 0);
	ASSERT_EQ(eventsArr[0].getPriority(), high);
	ASSERT_EQ(eventsArr[0].getShortPlot(), "newShortPlot1");
	ASSERT_EQ(eventsArr[0].getTitle(), "newTitle1");
	ASSERT_EQ(eventsArr.size(), 1);

	removeEvent(testUser, testUser.getPosts(), eventsArr);

	ASSERT_EQ(testUser.getPosts().size(), 0);
	ASSERT_EQ(eventsArr.size(), 0);
}

TEST(BLTest, Comments)
{
	User testUser("user1", "user1");
	Event testEvent("title1", "plot1", "shortPlot1", getCurrentDate(), low, testUser.getUserName());
	vector<User> usersArr;
	vector<Event> eventsArr;
	usersArr.push_back(testUser);
	eventsArr.push_back(testEvent);

	ASSERT_EQ(testEvent.getComments().size(), 0);

	istringstream input("newUserComment\n1");
	cin.rdbuf(input.rdbuf());
	addComment(testUser, testEvent, testUser.getPosts(), eventsArr, usersArr);

	ASSERT_EQ(testEvent.getComments()[0].getAuthor(), "user1");
	ASSERT_EQ(testEvent.getComments()[0].getDate(), getCurrentDate());
	ASSERT_EQ(testEvent.getComments()[0].getPlotComment(), "newUserComment");
	ASSERT_EQ(testEvent.getComments().size(), 1);

	deleteComment(testUser, testEvent, testUser.getPosts());
	ASSERT_EQ(testEvent.getComments().size(), 0);
}
