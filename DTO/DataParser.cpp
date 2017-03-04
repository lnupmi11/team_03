#include "DataParser.h"

DataParser::DataParser(string name)
{
	data = "";
	users = vector<User>();
	filename = name;
	readData(filename);
	decodeData();
	parseData();
}

User * DataParser::getUser(string login, string password)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i].getLogin()==login&&users[i].getPassword() == password) {
			return &users[i];
		}
	}
	return nullptr;
}

void DataParser::addUser(string email, string login, string password)
{
	User tmp = User(email, login, password);
	users.push_back(tmp);
}

bool DataParser::isInUsers(string email, string login)
{
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i].getEmail() == email || users[i].getLogin() == login) {
			return true;
		}
	}
	return false;
}

void DataParser::readData(string name)
{
	ifstream file(name);
	char c;
	while (file.get(c))
	{
		data += c;
	}
	file.close();
}

void DataParser::decodeData()
{

	for (size_t i = 0; i < data.size(); i++)
	{
		size_t size = 127 - 32;
		unsigned short pos = (unsigned short)(data[i]);
		pos -= 32;
		pos += 20 + size;
		pos %= size;
		pos += 32;
		data[i] = (char)pos;
	}

}

void DataParser::parseData()
{
	int start = 1, end;
	for (size_t i = 1; i < data.size(); i++) {
		if (data[i] == '^') {
			end = i;
			User temp = User(string(data, start, end - start));
			users.push_back(temp);
			start = i + 1;
		}
	}
}

void DataParser::prepareData()
{
	data = "^";
	for (size_t i = 0; i < users.size(); i++) {
		data += users[i].to_string() + "^";
	}
}

void DataParser::encodeData()
{

	for (size_t i = 0; i < data.size(); i++)
	{
		size_t size = 127 - 32;
		unsigned short pos = (unsigned short)(data[i]);
		pos -= 32;
		pos -= 20;
		pos += size;
		pos %= size;
		pos += 32;
		data[i] = (char)pos;
	}

}

void DataParser::putData(string name)
{
	ofstream file;
	file.open(name, ios::out | ios::trunc);
	file << data;
	file.close();
}

DataParser::~DataParser()
{
	prepareData();
	encodeData();
	putData(filename);
}
