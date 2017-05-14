#pragma once
#include "../Utils/Header.h"
#include "Comment.h"

using namespace std;


enum Priority { low, medium, high };

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
	vector<string> popularityUsers;
	Priority priority;
public:
	Event();

	Event(string title, string plot, string shortPlot, string date, Priority priority, string author);

	//getters
	string getTitle();

	string getPlot();

	string  getShortPlot();

	string getDate();

	int getPopularity();

	vector<string> getPopularityUsers();

	Priority getPriority();

	string getAuthor();

	vector<Comment> getComments();

	// setters
	void setTitle(string title);

	void setPlot(string plot);

	void setShortPlot(string shortPlot);

	void setDate(string date);

	void setPopularity(int popularity);

	void addPopularityUsers(string currentUser);

	void addPopularityUsers(vector<string> users);

	void setPriority(Priority priority);

	void addComment(Comment newComment);

	void setComment(Comment newComment);

	void setComments(vector<Comment> comments);

	// other
	void removeComment(int number);

	friend istream& operator >> (istream& input, Event& event);

	friend ostream& operator << (ostream& output, Event& event);

	bool operator== (const Event& rightVal);
};