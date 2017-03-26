#include "DataParser.h"

vector<User> parseUsersToList(string data)
{
	vector<User> result;
	int start = 1, end;
	for (size_t i = 1; i < data.size(); i++) {
		if (data[i] == '^') {
			end = i;

			User created = parseUser(string(data, start, end - start));

			users.push_back(created);
			start = i + 1;
		}
	}

	return result;
}

vector<Event> parseEventsToList(string data);
{
	vector<Event> result;
	int start = 1, end;
	for (size_t i = 1; i < data.size(); i++) {
		if (data[i] == '^') {
			end = i;

			Event created = parseEvent(string(data, start, end - start));

			users.push_back(created);
			start = i + 1;
		}
	}
	return result;
}

string composeUsersToList(vector<User>) users;
{
	string result = "";
	return result;
}

string composeEventsToList(vector<Event> events);
{
	string result = "";

	return result;
}


User parseUser(string data)
{
	User result;
	string args[2];
	size_t iter = 0;
	int start = 1, end;
	for (size_t i = 1; i < data.size(); i++) {
		if (data[i] == '~') {
			end = i;
			args[iter] = string(data, start, end - start);
			iter++;
			start = i + 1;
		}
	}

	return result;
}

Event parseEvent(string data);
{
	Event result;
	string args[8];
	size_t iter = 0;
	int start = 1, end;
	for (size_t i = 1; i < data.size(); i++) {
		if (data[i] == '~') {
			end = i;
			args[iter] = string(data, start, end - start);
			iter++;
			start = i + 1;
		}
	}
	return result;
}

string composeUser(User user);
{
	string result = "";
	return result;
}

string composeEvent(Event event);
{
	string result = "";

	return result;
}
