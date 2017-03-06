#pragma once
#include "Header.h"
#include "User.h"

using namespace std;


class Comment
{
private:
	string author;
	string plotComment;
	string date;
	Comment();

public:
	Comment(string author, string plotComment, string date);

	string getAuthor();

	string getPlotÑomment();

	string getDate();

	void setAuthor(string author);

	void setPlotÑomment(string plotComment);

	void setDate(string date);

	friend istream & operator >> (istream &input, Comment &comment);

	friend ostream & operator << (ostream &output, Comment &comment);
};