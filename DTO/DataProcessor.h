#pragma once
#include <fstream>
#include <string>
using namespace std;

class DataProcessor
{
public:
	//info:
	//	Constructor to set filename and encoding (none or Caesar)
	DataProcessor(string name, bool encode);

	string const getData() const;
	void setData(string data);

	~DataProcessor();
	
private:
	//info:
	//	read data stored in file "name"
	void readData(string name);
	//info:
	//	decode data with simple Caesar algorithm
	void decodeData();
	//info:
	//	decode data with simple Caesar algorithm
	void encodeData();
	//info:
	//	store data in file "name"
	void putData(string name);

	DataProcessor();

	string filename;
	string data;
	bool encode;
};

