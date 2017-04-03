#include "DataParser.h"

vector<User> parseUsersToList(string data)
{
	vector<User> result;
	for each (auto part in split('^', data))
	{
		result.push_back(parseUser(part));
	}
	return result;
}

vector<Event> parseEventsToList(string data)
{
	vector<Event> result;
	for each (auto part in split('^', data))
	{
		result.push_back(parseEvent(part));
	}
	return result;
}

string composeUsersToList(vector<User> users)
{
	string result = "^";
	for each (auto part in users)
	{
		result += composeUser(part) + "^";
	}
	return result;
}

string composeEventsToList(vector<Event> events)
{
	string result = "^";
	for each (auto part in events)
	{
		result += composeEvent(part) + "^";
	}
	return result;
}


User parseUser(string data)
{
	User result;
	string args[2];
	size_t iter = 0;
	for each (string part in split('~', data))
	{
		args[iter] = part;
		iter++;
	}
	result = User(args[0], args[1]);
	return result;
}

Event parseEvent(string data)
{
	Event result;
	vector<string > args = split('~', data);
	size_t priorVal;
	try {
		priorVal = (size_t) stoi(args[4]);
	}
	catch(invalid_argument e)
	{
		priorVal = 0;
	}
	priorVal = priorVal < 3 ? priorVal : 0;
	Priorities prior = (Priorities) priorVal;
	result = Event(args[0], args[1], args[2], args[3], prior, args[5]);
	result.setDate(args[6]);
	int popul;
	try {
		popul = stoi(args[7]);
	}
	catch (invalid_argument e)
	{
		popul = 0;
	}
	result.setPopularity(popul);
	for each (string part in split('|', args[8]))
	{
		result.addPopularityUsers(part);//^event^
	}
	for each (string part in split('|', args[8]))
	{
		result.addComment(parseComment(part));
	}
	return result;
}

Comment parseComment(string data)
{
	Comment result;
	for each (string part in split('^', data))
	{
		//result.push_back(parseUser(part));
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

string composeComment(Comment event)
{
	string result = "";

	return result;
}

//this function is to be changed (deprecated)
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

/* this function is future solution
vector<string> split(string delim, string toSplit)
{
vector<string> result = vector<string>();
int start = delim.size(), end;
for (size_t i = start; i < toSplit.size(); i++) {
bool match = true;
while (i - start < delim.size()) {

}
end = i;
result.push_back(string(toSplit, start, end - start));
start = i + 1;
}
return result;
}
*/
/*
//kbjhbjbk//kjbhjhb//

*/
