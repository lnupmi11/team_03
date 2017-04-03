#include "Utils/Header.h"
#include "Entity/User.h"
#include "Entity/Event.h"
#include "BL/Functions.h"

using namespace std;


void testing(vector<User> &users, vector<Event> &allEvents)
{
	User user1("user1", "user1");
	User user2("user2", "user2");
	
	Event event1("User1: Event1: title", "User1: Event1: Plot", "User1: Event1: Short plot", getCurrentDate(), high, user1.getUserName());
	Event event2("User1: Event2: title", "User1: Event2: Plot", "User1: Event2: Short plot", getCurrentDate(), medium, user1.getUserName());
	Event event3("User1: Event3: title", "User1: Event3: Plot", "User1: Event3: Short plot", getCurrentDate(), low, user1.getUserName());
	Event event4("User1: Event4: title", "User1: Event4: Plot", "User1: Event4: Short plot", getCurrentDate(), high, user1.getUserName());
	Event event5("User1: Event5: title", "User1: Event5: Plot", "User1: Event5: Short plot", getCurrentDate(), medium, user1.getUserName());
	Event event6("User2: Event1: title", "User2: Event1: Plot", "User2: Event1: Short plot", getCurrentDate(), low, user2.getUserName());
	Event event7("User2: Event2: title", "User2: Event2: Plot", "User2: Event2: Short plot", getCurrentDate(), high, user2.getUserName());
	Event event8("User2: Event3: title", "User2: Event3: Plot", "User2: Event3: Short plot", getCurrentDate(), medium, user2.getUserName());
	Event event9("User2: Event4: title", "User2: Event4: Plot", "User2: Event4: Short plot", getCurrentDate(), low, user2.getUserName());
	Event event10("User2: Event5: title", "User2: Event5: Plot", "User2: Event5: Short plot", getCurrentDate(), high, user2.getUserName());
	
	users.push_back(user1);
	users.push_back(user2);
	
	allEvents.push_back(event1);
	allEvents.push_back(event2);
	allEvents.push_back(event3);
	allEvents.push_back(event4);
	allEvents.push_back(event5);
	allEvents.push_back(event6);
	allEvents.push_back(event7);
	allEvents.push_back(event8);
	allEvents.push_back(event9);
	allEvents.push_back(event10);
}

int main()
{
	vector<User> allUsers;
	vector<Event> allEvents;

	//TODO push users data to vector<User> users
	//TODO push events data to vector<Event> events

	testing(allUsers, allEvents);


	for (int i = 0; i < allUsers.size(); i++)
	{
		for (int j = 0; j < allEvents.size(); j++)
		{
			if (allUsers[i].getUserName() == allEvents[j].getAuthor())
			{
				allUsers[i].setPosts(allEvents[j]);
			}
		}
	}

	mainMenu(allUsers, allEvents);
	
	return 0;
}
