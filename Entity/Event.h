#pragma once
#include"User.h"

using namespace std;

enum Priorities { low, medium, high };

class Event
{
private:
	string title;
	string date;
	string plot;
	string shortPlot;
	User *author;
	vector<Comment> *comments;
	int popularity;
	Priorities priority;

	Event();

public:
	Event(string t, string p, string shP, int pop, Priorities prior);
	
	//get
	string getTitle();

	string getPlot();

	string  getShortPlot();

	string getDate();

	int getPopularity();

	Priorities getPriority();

	// set
	string setTitle(string t);

	string setPlot(string p);

	string  setShortPlot(string shP);

	string setDate(string d);

	int setPopularity(int pop);

	Priorities setPriority(Priorities prior);
};
