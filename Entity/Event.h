#pragma once
#include"Header.h"
#include"Comment.h"

using namespace std;


enum Priorities { low, medium, high };


class Event
{
private:
	string title;
	string date;
	string plot;
	string shortPlot;
	string author;
	vector<Comment> comments;
	int popularity;
	Priorities priority;
	Event();

public:
	Event(string title, string plot, string shortPlot, string date, Priorities priority, string author);

	//getters
	string getTitle();

	string getPlot();

	string  getShortPlot();

	string getDate();

	int getPopularity();

	Priorities getPriority();

	string getAuthor();

	// setters
	void setTitle(string title);

	void setPlot(string plot);

	void  setShortPlot(string shortPlot);

	void setDate(string date);

	void setPopularity(int popularity);

	void setPriority(Priorities priority);

	friend istream & operator >> (istream &input, Event &event);

	friend ostream & operator << (ostream &output, Event &event);
};
