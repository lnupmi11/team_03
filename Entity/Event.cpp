#include <string>
#include"Event.h"

Event::Event(string t, string p, string shP, int pop, Priorities prior)
{
	title = t;
	plot = p;
	shortPlot = shP;
	popularity = pop;
	priority = prior;
}

//get
string Event::getTitle()
{
	return title;
}

string Event::getPlot()
{
	return plot;
}

string  Event::getShortPlot()
{
	return shortPlot;
}

string Event::getDate()
{
	return date;
}

int Event::getPopularity()
{
	return popularity;
}

Priorities Event::getPriority()
{
	return priority;
}

// set
string Event::setTitle(string t)
{
	title = t;
}

string Event::setPlot(string p)
{
	plot = p;
}

string  Event::setShortPlot(string shP)
{
	shortPlot = shP;
}

string Event::setDate(string d)
{
	date = d;
}

int Event::setPopularity(int pop)
{
	popularity = pop;
}

Priorities Event::setPriority(Priorities prior)
{
	priority = prior;
}