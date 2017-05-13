#pragma once
#include "../Utils/Header.h"
#include "User.h"

using namespace std;


class Comment
{
private:
	string author;
	string plotComment;
	string date;
	int popularity;
	vector<string> popularityUsers;

public:
	Comment();

	Comment(string author, string plotComment, string date);

	// getters
	string getAuthor();

	string getPlotComment();

	string getDate();

	// setters
	void setAuthor(string author);

	void setPlotComment(string plotComment);

	void setDate(string date);

	void setPopularity(int popularity);

	vector<string> getPopularityUsers();

	int getPopularity();

	void addPopularityUsers(string currentUser);

	void addPopularityUsers(vector<string> users);

	// other
	friend istream& operator >> (istream& input, Comment& comment);

	friend ostream& operator << (ostream& output, Comment& comment);

	bool operator== (const Comment& rightVal);

	void operator=(const Comment& comment);
};
