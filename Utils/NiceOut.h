#pragma once
#include "Header.h"

using namespace std;

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

size_t _SIZE();
void printM(string str);
void printH(string str);
void print(string str);
void alert(string str);
void input(string prompt, string& input);
void printD();
void printDS();
void printE();
