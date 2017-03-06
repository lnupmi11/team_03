#include"Header.h"
#include "User.h"
#include"Comment.h"

using namespace std;


Comment::Comment(string author, string plotComment, string date)
{
	this->author = author;
	this->plotComment = plotComment;
	this->date = date;
};

string Comment::getAuthor() 
{
	return author;
}

string Comment::getPlotÑomment() 
{
	return plotComment;
}

string Comment::getDate() 
{
	return date;
}

void Comment::setAuthor(string author)
{
	this->author = author;
}

void Comment::setPlotÑomment(string plotComment)
{
	this->plotComment = plotComment;
}

void Comment::setDate(string date)
{
	this->date = date;
}

istream & operator >> (istream &input, Comment &comment)
{
	cout << "Comment: ";
	getline(input, comment.plotComment);
	cout << "Date: ";
	input >> comment.date;

	return input;
}

ostream & operator << (ostream &output, Comment &comment)
{
	output << comment.plotComment << endl;
	output << comment.date << comment.author << endl;
	
	return output;
}