#include "NiceOut.h"

size_t _SIZE()
{
	size_t result = 100;

	#if defined(_WIN32) || defined(_WIN64)

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	result = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	result = w.ws_col;

	#else
	/**/
	#endif

	return result;
}


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
		int count = _SIZE() - 4 - str.size();
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
	for (size_t col = 1; col <= _SIZE(); col++)
	{
		if (col == 1)
		{
			cout << hlt;
		}
		else if (col == _SIZE())
		{
			cout << hrt;
		}
		else {
			cout << hhm;
		}
	}
	printM(str);
	for (size_t col = 1; col <= _SIZE(); col++)
	{
		if (col == 1)
		{
			cout << hhlhd;
		}
		else if (col == _SIZE())
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
		if (str.size() <= _SIZE() - 4)
		{
			cout << hvm << bgl;
			string begin = "";
			int count = _SIZE() - 4 - str.size();
			cout << str;
			for (int i = 0; i < count; i++)
			{
				cout << bgl;
			}
			cout << bgl << hvm;
		}
		else {
			print(str.substr(0, _SIZE() - 4));
			print(str.substr(_SIZE() - 4));
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
	for (size_t col = 1; col <= _SIZE(); col++)
	{
		if (col == 1)
		{
			cout << hhlhd;
		}
		else if (col == _SIZE())
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
	for (size_t col = 1; col <= _SIZE(); col++)
	{
		if (col == 1)
		{
			cout << hblhd;
		}
		else if (col == _SIZE())
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
	for (size_t col = 1; col <= _SIZE(); col++)
	{
		if (col == 1)
		{
			cout << hlb;
		}
		else if (col == _SIZE())
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
		int count = _SIZE() - 4 - str.size();
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
