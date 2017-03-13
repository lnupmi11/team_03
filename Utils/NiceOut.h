#pragma once
#include "Header.h"

namespace niceOut {
	using namespace std;

	const size_t SIZE = 120;

#if defined(_WIN32) || defined(_WIN64)
	const char hlt = (char)201;	//head left top
	const char hrt = (char)187;	//head right top
	const char hlb = (char)200;	//head left bot
	const char hrb = (char)188;	//head right bot
	const char hvm = (char)186;	//head vertical middle
	const char hhm = (char)205;	//head horisontal middle
	const char bhm = (char)196;	//body horisontal middle
	const char hhlhd = (char)204;	//head to head left horisontal delim
	const char hhrhd = (char)185;	//head to head right horisontal delim
	const char hblhd = (char)199;	//head to body left horisontal delim
	const char hbrhd = (char)182;	//head to body right horisontal delim
	const char bgl = (char)176;	//background low
	const char bgm = (char)177;	//background medium
	const char bgh = (char)178;	//background high
	const string tabl = { bgl, bgl }; //tab low
	const string tabm = { bgm, bgm }; //tab medium
	const string tabh = { bgh, bgh }; //tab high
	const char bell = (char)7; //system bell
	const char bkl = (char)221; //block left
	const char bks = (char)219; //block solid
	const char bkr = (char)222; //block right
	const char crl = (char)244; //curly left
	const char crr = (char)245; //curly right
#else
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
#endif

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
		cout << bell;
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
			cout << bgh << bks << endl << endl;
		}
		else {
			alert(str.substr(0, pos));
			alert(str.substr(pos + 1));
		}
	}
}
