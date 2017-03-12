#include "Header.h"
#include "User.h"

using namespace std;


User::User(string username, string password)
{
	this->username = username;
	this->password = password;
}

string User::getUserName()
{
	return this->username;
}

string User::getPassword()
{
	return this->password;
}

vector<Event> User::getPosts()
{
	return posts;
}

void User::setUserName(string username)
{
	this->username = username;
}

void User::setPassword(string password)
{
	this->password = password;
}

void User::setPosts(Event events)
{
	this->posts.push_back(events);
}

istream & operator >> (istream &input, User &user)
{
	cout << "Enter login > ";
	input >> user.username;
	cout << "Enter password > ";
	cin >> user.password;

	return input;
}

ostream & operator << (ostream &output, User &user)
{
	output << "Username -> ";
	output << user.username << endl;
	output << "Password -> ";
	output << user.password << endl;

	return output;
}