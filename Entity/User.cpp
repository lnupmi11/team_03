#include <iostream>
#include "User.h"

using namespace std;

User::User(string userN, string p)
{
	userName = userN;
	password = p;
}

string User::getUserName()
{
	return userName;
}
string User::getPassword()
{
	return password;
}
string User::setUserName(string userN)
{
	userName = userN;
}
string User::setPassword(string passw)
{
	password = passw;
}