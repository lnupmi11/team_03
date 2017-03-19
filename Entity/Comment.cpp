#include"../Utils/Header.h"
#include "User.h"
#include"Comment.h"
#include "../BL/Functions.h"

using namespace std;


Comment::Comment()
{
	this->plotComment = "";
	this->author = "";
	this->date = "";
}

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

string Comment::getPlotComment()
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

void Comment::setPlotComment(string plotComment)
{
	this->plotComment = plotComment;
}

void Comment::setDate(string date)
{
	this->date = date;
}

istream & operator >> (istream& input, Comment& comment)
{
	cout << "Comment: ";
	getline(input, comment.plotComment);

	return input;
}

ostream & operator << (ostream& output, Comment& comment)
{
	output << "  " << comment.plotComment << endl;
	output << "  " << comment.date << "   " << comment.author << endl;

	return output;
}
