#pragma once
#include <string>
#include "../Entity/User.h"
#include "../Entity/Event.h"
using namespace std;

vector<User> parseUsersToList(string data);

vector<Event> parseEventsToList(string data);

template <typename T>
string composeFromList(vector<T> items)
{
	string result = "";
	if (items.size() > 0)
	{
		string delim = ("~~~" + split(" ", typeid(T()).name())[1] + "~~~");
		for (size_t i = 0; i < items.size() - 1; i++)
		{
			result += compose(items[i]) + delim;
		}
		result += compose(items[items.size() - 1]);
	}
	return result;
}

string compose(vector<string> items);

User parseUser(string data);

Event parseEvent(string data);

Comment parseComment(string data);

string compose(User user);

string compose(Event event);

string compose(Comment comment);

vector<string> split(const string& delim, const string& toSplit);


void addEventsRespectively(vector<User>& allUsers, vector<Event>& allEvents);