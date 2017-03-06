#include "Header.h"
#include "User.h"
#include "Event.h"
#include "Functions.h"

using namespace std;


void testing(vector<User> &users, vector<Event> &events)
{
	User user1("yura", "yura");
	User user2("dima", "dima");

	Event event1("Hello, world", "Yura Lisovskiy is studying in university!", "Studiyng", "05/03/2017", high, "yura");
	Event event2("Good bye, world", "Yura Lisovskiy said good bye", "Good luck", "04/03/2017", medium, "dima");
	Event event3("world", "Yura Lisovskiy", "luck", "01/03/2017", medium, "yura");

	users.push_back(user1);
	users.push_back(user2);

	events.push_back(event1);
	events.push_back(event2);
	events.push_back(event3);
}

int main()
{
	vector<User> users;
	vector<Event> events;

	//TODO push users data to vector<User> users
	//TODO push events data to vector<Event> events

	testing(users, events);

	for (int i = 0; i < users.size(); i++)
	{
		for (int j = 0; j < events.size(); j++)
		{
			if (users[i].getUserName() == events[j].getAuthor())
			{
				users[i].setPosts(events[j]);
			}
		}
	}

	int option;

	mainMenu();

	while (true)
	{
		cout << "Option > ";
		cin >> option;

		switch (option)
		{
		case 1:
			signIn(users, events);
			mainMenu();
			break;
		case 2:
			signUp(users);
			mainMenu();
			break;
		case 3:
			return 0;
			break;
		default:
			cout << "Incorrect option." << endl;
			break;
		}
	}
	return 0;
}