#pragma once
#include "Header.h"
#include "Event.h"

using namespace std;

class Event;

class User
{
private:
	string username;
	string password;
	vector<Event> posts;
	User();

public:
	User(string username, string password);

	~User();

	string getUserName();

	string getPassword();

	vector<Event> getPosts();

	void setUserName(string username);

	void setPassword(string password);

	void setPosts(Event events);

	friend istream & operator >> (istream &input, User &user);

	friend ostream & operator << (ostream &output, User &user);
};