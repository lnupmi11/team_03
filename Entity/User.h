#pragma once
#include "Event.h"

using namespace std;

class User
{
private:
	string userName;
	string password;
	vector<Event> *posts;
	User();

public:
	User(string userN, string p);

	string getUserName();

	string getPassword();

	void setUserName(string userN);

	void setPassword(string passw);
};
