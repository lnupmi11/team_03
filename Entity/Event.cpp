#include "../Utils/Header.h"
#include "Event.h"

using namespace std;


Event::Event() {}

Event::Event(string title, string plot, string shortPlot, string date, Priorities priority, string author)
{
	this->title = title;
	this->plot = plot;
	this->shortPlot = shortPlot;
	this->date = date;
	this->priority = priority;
	this->author = author;
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

void Event::setPriority(Priorities priority)
{
	this->priority = priority;
}

void Event::setComment(Comment newComment)
{
	this->comments.push_back(newComment);
}

istream & operator >> (istream &input, Event &event)
{
	cin.ignore(1024, '\n');

	cout << "Title: ";
	getline(input, event.title);
	cout << "Short plot: ";
	getline(input, event.shortPlot);
	cout << "Plot: ";
	getline(input, event.plot);
	
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

	cout << "Date: ";
	getline(input, event.date);

	return input;
}

ostream & operator << (ostream &output, Event &event)
{
	output << "Title: " << event.getTitle() << endl;
	output << "Plot: " << event.getPlot() << endl;
	output << "Author: " << event.getAuthor() << "  Date: " << event.getDate() << endl;

	return output;
}

bool Event::operator== (const Event &rightVal)
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
