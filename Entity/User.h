#pragma once
#include "../Utils/Header.h"
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

	// getters
	string getUserName();

	string getPassword();

	vector<Event>& getPosts();

	// setters
	void setUserName(string username);

	void setPassword(string password);

	void setPosts(Event events);

	// other
	friend istream & operator >> (istream &input, User &user);

	friend ostream & operator << (ostream &output, User &user);
};
