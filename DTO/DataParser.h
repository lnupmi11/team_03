#pragma once
#include "User.h"
#include <fstream>
using namespace std;

class DataParser
{
public:
	//info:
	//	Constructor that takes filename
	DataParser(string name);
	//info:
	//	get the address of user with this login and password
	User * getUser(string login, string password);
	//info:
	//	Add new user with this data
	void addUser(string email, string login, string password);
	//info:
	//	return true if User with this email exists
	bool isInUsers(string email, string login);
	~DataParser();

private:
	//info:
	//	read data stored in file "name"
	void readData(string name);
	//info:
	//	decode data with simple char shift algorithm
	void decodeData();
	//info:
	//	parse data of special format: ^user1^user2^...^usern^
	void parseData();
	//info:
	//	form data to special format (^~||~^)
	void prepareData();
	//info:
	//	decode data with simple char shift algorithm
	void encodeData();
	//info:
	//	store data in file "name"
	void putData(string name);
	string filename;
	string data;
	vector<User> users;
};

