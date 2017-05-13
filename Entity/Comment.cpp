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
}

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

void Comment::setPopularity(int popularity)
{
	this->popularity = popularity;
}

vector<string> Comment::getPopularityUsers()
{
	return this->popularityUsers;
}

int Comment::getPopularity()
{
	return this->popularity;
}

void Comment::addPopularityUsers(string currentUser)
{
	this->popularityUsers.push_back(currentUser);
}

void Comment::addPopularityUsers(vector<string> users)
{
	this->popularityUsers = users;
}

bool Comment::operator==(const Comment & rightVal)
{

	if (this->author != rightVal.author)
	{
		return false;
	}
	if (this->date != rightVal.date)
	{
		return false;
	}
	if (this->plotComment != rightVal.plotComment)
	{
		return false;
	}
	return true;
}

void Comment::operator=(const Comment& comment)
{
	this->author = comment.author;
	this->plotComment = comment.plotComment;
	this->date = comment.date;
	this->popularity = comment.popularity;
	this->popularityUsers = comment.popularityUsers;
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
