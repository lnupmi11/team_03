#include "DataProcessor.h"

DataProcessor::DataProcessor(string name, bool encode)
{
	data = "";
	filename = name;
	this->encode = encode;
	readData(filename);
	if(encode) decodeData();
}

void DataProcessor::readData(string name)
{
	ifstream file(name);
	char c;
	while (file.get(c))
	{
		data += c;
	}
	file.close();
}

void DataProcessor::decodeData()
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

void DataProcessor::encodeData()
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

void DataProcessor::putData(string name)
{
	ofstream file;
	file.open(name, ios::out | ios::trunc);
	file << data;
	file.close();
}

DataProcessor::~DataProcessor()
{
	if(encode) encodeData();
	putData(filename);
}

string const DataProcessor::getData() const
{
	return data;
}

void DataProcessor::setData(string data)
{
	this->data = data;
}
