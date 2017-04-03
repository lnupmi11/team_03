#include "DataParser.h"

vector<User> parseUsersToList(string data)
{
	vector<User> result;
	for each (string part in split('^', data))
	{
		result.push_back(parseUser(part));
	}
	return result;
}

vector<Event> parseEventsToList(string data)
{
	vector<Event> result;
	for each (string part in split('^', data))
	{
		result.push_back(parseEvent(part));
	}
	return result;
}

string composeUsersToList(vector<User> users)
{
	string result = "";
	return result;
}

string composeEventsToList(vector<Event> events)
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

Event parseEvent(string data)
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

string composeUser(User user)
{
	string result = "";
	return result;
}

string composeEvent(Event event)
{
	string result = "";

	return result;
}

vector<string> split(char delim, string toSplit)
{
	vector<string> result = vector<string>();
	int start = 1, end;
	for (size_t i = 1; i < toSplit.size(); i++) {
		if (toSplit[i] == delim) {
			end = i;
			result.push_back(string(toSplit, start, end - start));
			start = i + 1;
		}
	}
	return result;
}
