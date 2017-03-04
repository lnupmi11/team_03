#pragma once
#include "Header.h"

namespace niceOut {
	using namespace std;

	const size_t SIZE = 120;

	const char hlt = '+';	
	const char hrt = '+';
	const char hlb = '+';
	const char hrb =  '+';
	const char hvm =  '|';
	const char hhm =  '-';
	const char bhm =  '-';
	const char hhlhd =  '+';
	const char hhrhd =  '+';
	const char hblhd =  '+';
	const char hbrhd =  '+';
	const char bgl =  ' ';
	const char bgm =  '.';
	const char bgh =  '#';
	const string tabl =  "  ";
	const string tabm =  "  ";
	const string tabh =  "  ";
	const char bell =  (char)7;
	const char bkl =  '[';
	const char bks =  '/';
	const char bkr =  ']';
	const char crl =  ')';
	const char crr =  '(';

	//info:
	//	Prints information with average background
	//	in the middle of the line
	void printM(string str)
	{
		int pos = str.find('\n');
		if (pos == -1) {
			int pos2;
			while ((pos2 = str.find('\t')) != -1) {
				if (pos2 == 0)
				{
					str = tabm + str.substr(pos2 + 1);
				}
				else if (pos2 == str.size())
				{
					str = str.substr(0, str.size() - 1);
				}
				else
				{
					str = str.substr(0, pos2) + "  " + str.substr(pos2 + 1);
				}
			}
			while ((pos2 = str.find('\r')) != -1) {
				if (pos2 == 0)
				{
					str = str.substr(pos2 + 1);
				}
				else if (pos2 == str.size())
				{
					str = str.substr(0, str.size() - 1);
				}
				else
				{
					str = str.substr(0, pos2) + str.substr(pos2 + 1);
				}
			}
			cout << hvm << bgm;
			string begin = "";
			int count = SIZE - 4 - str.size();
			int cbgin = count / 2;
			int cend = count - cbgin;
			for (int i = 0; i < cbgin - 1; i++)
			{
				cout << bgm;
			}
			cout << " " + str + " ";
			for (int i = 0; i < cend - 1; i++)
			{
				cout << bgm;
			}
			cout << bgm << hvm;
		}
		else {
			printM(str.substr(0, pos));
			printM(str.substr(pos + 1));
		}
	}

	//info:
	//	Prints header with the subject of menu or submenu
	void printH(string str) {
		for (size_t col = 1; col <= SIZE; col++)
		{
			if (col == 1)
			{
				cout << hlt;
			}
			else if (col == SIZE)
			{
				cout << hrt;
			}
			else {
				cout << hhm;
			}
		}
		printM(str);
		for (size_t col = 1; col <= SIZE; col++)
		{
			if (col == 1)
			{
				cout << hhlhd;
			}
			else if (col == SIZE)
			{
				cout << hhrhd;
			}
			else {
				cout << hhm;
			}
		}

	}

	//info:
	//	Simply prints lines with text and low background
	void print(string str)
	{
		int pos = str.find('\n');
		if (pos == -1) {
			int pos2;
			if ((pos2 = str.find('\t')) != -1) {
				while ((pos2 = str.find('\t')) != -1) {
					if (pos2 == 0)
					{
						str = tabl + " " + str.substr(pos2 + 1);
					}
					else if (pos2 == str.size())
					{
						str = str.substr(0, str.size() - 1);
					}
					else
					{
						str = str.substr(0, pos2) + "  " + str.substr(pos2 + 1);
					}
				}
			}
			else {

				str = " " + str;
			}
			str += " ";

			while ((pos2 = str.find('\r')) != -1) {
				if (pos2 == 0)
				{
					str = str.substr(pos2 + 1);
				}
				else if (pos2 == str.size())
				{
					str = str.substr(0, str.size() - 1);
				}
				else
				{
					str = str.substr(0, pos2) + str.substr(pos2 + 1);
				}
			}
			if (str.size() <= SIZE - 4)
			{
				cout << hvm << bgl;
				string begin = "";
				int count = SIZE - 4 - str.size();
				cout << str;
				for (int i = 0; i < count; i++)
				{
					cout << bgl;
				}
				cout << bgl << hvm;
			}
			else {
				print(str.substr(0, SIZE - 4));
				print(str.substr(SIZE - 4));
			}

		}
		else {
			print(str.substr(0, pos));
			print(str.substr(pos + 1));
		}
	}

	//info:
	//	Gets user input
	void input(string prompt, string & input) {
		
				cout << hvm << "   ";
				string begin = "";
				cout << prompt;
				cin >> input;
	}

	//info:
	//	Prints double-lined horisontal delimiter
	void printD()
	{
		for (size_t col = 1; col <= SIZE; col++)
		{
			if (col == 1)
			{
				cout << hhlhd;
			}
			else if (col == SIZE)
			{
				cout << hhrhd;
			}
			else {
				cout << hhm;
			}
		}
	}

	//info:
	//	Prints single-lined horisontal delimiter
	void printDS()
	{
		for (size_t col = 1; col <= SIZE; col++)
		{
			if (col == 1)
			{
				cout << hblhd;
			}
			else if (col == SIZE)
			{
				cout << hbrhd;
			}
			else {
				cout << bhm;
			}
		}
	}

	//info:
	//	Prints double-lined ending border
	void printE()
	{
		for (size_t col = 1; col <= SIZE; col++)
		{
			if (col == 1)
			{
				cout << hlb;
			}
			else if (col == SIZE)
			{
				cout << hrb;
			}
			else {
				cout << hhm;
			}
		}
	}

	//info:
	//	Prints alert message with system bell
	void alert(string str) {
		cout << bell << endl;
		int pos = str.find('\n');
		if (pos == -1) {
			int pos2;
			while ((pos2 = str.find('\t')) != -1) {
				if (pos2 == 0)
				{
					str = tabm + str.substr(pos2 + 1);
				}
				else if (pos2 == str.size())
				{
					str = str.substr(0, str.size() - 1);
				}
				else
				{
					str = str.substr(0, pos2) + "  " + str.substr(pos2 + 1);
				}
			}
			while ((pos2 = str.find('\r')) != -1) {
				if (pos2 == 0)
				{
					str = str.substr(pos2 + 1);
				}
				else if (pos2 == str.size())
				{
					str = str.substr(0, str.size() - 1);
				}
				else
				{
					str = str.substr(0, pos2) + str.substr(pos2 + 1);
				}
			}
			cout << bks << bgh;
			string begin = "";
			int count = SIZE - 4 - str.size();
			int cbgin = count / 2;
			int cend = count - cbgin;
			for (int i = 0; i < cbgin - 1; i++)
			{
				cout << bgm;
			}
			cout << " " + str + " ";
			for (int i = 0; i < cend - 1; i++)
			{
				cout << bgm;
			}
			cout << bgh << bks << endl;
		}
		else {
			alert(str.substr(0, pos));
			alert(str.substr(pos + 1));
		}
	}
}
