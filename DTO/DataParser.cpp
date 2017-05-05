#include "DataParser.h"

vector<User> parseUsersToList(string data)
{
	vector<User> result;
	vector<string> splited = split("~~~User~~~", data);
	if (splited.size() >= 1 && splited[0].size() != 0)
	{
		for (auto&& part : splited)
		{
			result.push_back(parseUser(part));
		}
	}
	return result;
}

vector<Event> parseEventsToList(string data)
{
	vector<Event> result;
	vector<string> splited = split("~~~Event~~~", data);
	if (splited.size() >= 1 && splited[0].size() != 0)
	{
		for (auto part : splited)
		{
			result.push_back(parseEvent(part));
		}
	}
	return result;
}

User parseUser(string data)
{
	User result;
	vector<string> args = split("^^^field^^^", data);
	if (args.size() != 2)
		throw invalid_argument("Wrong data");
	result = User(args[0], args[1]);
	return result;
}

Event parseEvent(string data)
{
	Event result;
	vector<string> args = split("^^^field^^^", data);
	if (args.size() != 9)
		throw invalid_argument("Wrong data");
	size_t priorVal;
	try {
		priorVal = (size_t)stoi(args[4]);
	}
	catch (invalid_argument e)
	{
		priorVal = 0U;
	}
	priorVal = priorVal < 3 ? priorVal : 0;
	Priority prior = (Priority)priorVal;
	result = Event(args[0], args[1], args[2], args[3], prior, args[5]);
	int popul;
	try {
		popul = stoi(args[6]);
	}
	catch (invalid_argument e)
	{
		popul = 0;
	}
	result.setPopularity(popul);
	for (string part : split("|||subfield|||", args[7]))
	{
		result.addPopularityUsers(part);
	}
	/*
	for each (string part in split("%%%COMMENT%%%", args[8]))
	{
		result.addComment(parseComment(part));
	}
	*/
	return result;
}

Comment parseComment(string data)
{
	vector<string> fields = split("|||subfield|||", data);
	if (fields.size() != 3)
		throw invalid_argument("Wrong data");
	Comment result(fields[0], fields[1], fields[2]);
	return result;
}

string compose(User user)
{
	string result = "", delim = "^^^field^^^";
	result += user.getUserName();
	result += delim;
	result += user.getPassword();
	return result;
}

string compose(Event event)
{
	string result = "", delim = "^^^field^^^";

	result += event.getTitle();
	result += delim;
	result += event.getPlot();
	result += delim;
	result += event.getShortPlot();
	result += delim;
	result += event.getDate();
	result += delim;
	result += to_string((size_t)event.getPriority());
	result += delim;
	result += event.getAuthor();
	result += delim;
	result += to_string(event.getPopularity());
	result += delim;
	result += compose(event.getPopularityUsers());
	result += delim;
	result += composeFromList(event.getComments());

	return result;
}

string compose(Comment comment)
{
	string result = "", delim = "|||subfield|||";

	result += comment.getAuthor();
	result += delim;
	result += comment.getPlotComment();
	result += delim;
	result += comment.getDate();

	return result;
}

string compose(vector<string> items)
{
	string result = "";
	if (items.size() > 0)
	{
		string delim = "|||subfield|||";
		for (size_t i = 0; i < items.size() - 1; i++)
		{
			result += items[i] + delim;
		}
		result += items[items.size() - 1];
	}
	return result;
}

vector<string> split(const string& delim, const string& toSplit)
{
	vector<string> result = vector<string>();
	int start = 0, end = toSplit.find(delim, start);
	while (end != -1)
	{
		result.push_back(string(toSplit, start, end - start));
		start = end + delim.size();
		end = toSplit.find(delim, start);
	}
	result.push_back(string(toSplit, start, toSplit.size() - start));
	return result;
}

void addEventsRespectively(vector<User>& allUsers, vector<Event>& allEvents)
{
	for (size_t i = 0; i < allUsers.size(); i++)
	{
		for (size_t j = 0; j < allEvents.size(); j++)
		{
			if (allUsers[i].getUserName() == allEvents[j].getAuthor())
			{
				allUsers[i].setPosts(allEvents[j]);
			}
		}
	}
}
