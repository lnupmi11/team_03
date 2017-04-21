#include "../Utils/Header.h"
#include "Event.h"

using namespace std;


Event::Event() : popularity(0) {}

Event::Event(string title, string plot, string shortPlot, string date, Priorities priority, string author)
{
	this->title = title;
	this->plot = plot;
	this->shortPlot = shortPlot;
	this->date = date;
	this->priority = priority;
	this->author = author;
	this->popularity = 0;
}

string Event::getAuthor()
{
	return this->author;
}

string Event::getTitle()
{
	return this->title;
}

string Event::getPlot()
{
	return this->plot;
}

string  Event::getShortPlot()
{
	return this->shortPlot;
}

string Event::getDate()
{
	return this->date;
}

int Event::getPopularity()
{
	return this->popularity;
}

vector<string> Event::getPopularityUsers()
{
	return this->popularityUsers;
}

Priorities Event::getPriority()
{
	return this->priority;
}

vector<Comment> Event::getComments()
{
	return comments;
}

void Event::setTitle(string title)
{
	this->title = title;
}

void Event::setPlot(string plot)
{
	this->plot = plot;
}

void  Event::setShortPlot(string shortPlot)
{
	this->shortPlot = shortPlot;
}

void Event::setDate(string date)
{
	this->date = date;
}

void Event::setPopularity(int popularity)
{
	this->popularity = popularity;
}

void Event::addPopularityUsers(string currentUser)
{
	this->popularityUsers.push_back(currentUser);
}

void Event::addPopularityUsers(vector<string> users)
{
	this->popularityUsers = users;
}

void Event::setPriority(Priorities priority)
{
	this->priority = priority;
}

void Event::addComment(Comment newComment)
{
	this->comments.push_back(newComment);
}

void Event::setComment(Comment newComment)
{
	for (int i = 0; i < comments.size(); i++)
	{
		if (comments[i] == newComment);
		{
			comments[i] = newComment;
			break;
		}
	}
}

void Event::setComments(vector<Comment> comments)
{
	this->comments = comments;
}

void Event::removeComment(int number)
{
	comments.erase(comments.begin() + number);
}

istream& operator >> (istream& input, Event& event)
{
	cin.ignore(1024, '\n');

	cout << "Title: ";
	getline(input, event.title);
	cout << "Plot: ";
	getline(input, event.plot);
	unsigned int plotSize;
	if (event.plot.size() < 135)
	{
		plotSize = event.plot.size() - 35;
	}
	else
	{
		plotSize = 100;
	}
	string tempShortPlot(event.plot, 0, plotSize);

	for (int i = plotSize; i < plotSize + 36; i++)
	{
		tempShortPlot += event.plot[i];
		if (event.plot[i] == '.')
		{
			break;
		}
		if (i >= plotSize + 25 && event.plot[i] == ' ')
		{
			tempShortPlot += "...";
		}
	}
	event.shortPlot = tempShortPlot;

	int choosePrior = 0;

	while (choosePrior != 1 || choosePrior != 2 || choosePrior != 3)
	{
		cout << " Priority (1 - low, 2 - medium, 3 - high): ";
		cin >> choosePrior;

		cin.ignore(1024, '\n');

		switch (choosePrior)
		{
		case 1:
			event.priority = low;
			break;
		case 2:
			event.priority = medium;
			break;
		case 3:
			event.priority = high;
			break;
		default:
			cout << "Error. Wrong priority." << endl;
			break;
		}
	}


	time_t currentTime = time(0);
	event.date = ctime(&currentTime);

	return input;
}

ostream& operator << (ostream& output, Event& event)
{
	output << "Title: " << event.getTitle() << endl;
	output << "Plot: " << event.getPlot() << endl;
	output << "Author: " << event.getAuthor() << endl;
	output << "Date: " << event.getDate() << endl;
	output << "Populariry: " << event.getPopularity() << endl;

	return output;
}

bool Event::operator== (const Event& rightVal)
{
	if (this->title != rightVal.title)
	{
		return false;
	}
	if (this->date != rightVal.date)
	{
		return false;
	}
	if (this->plot != rightVal.plot)
	{
		return false;
	}
	if (this->shortPlot != rightVal.shortPlot)
	{
		return false;
	}
	if (this->author != rightVal.author)
	{
		return false;
	}
	if (this->popularity != rightVal.popularity)
	{
		return false;
	}
	if (this->priority != rightVal.priority)
	{
		return false;
	}

	return true;
}
