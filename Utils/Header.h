#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <typeinfo>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define CLS do{system("cls");}while(0)
#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)
#include <sys/ioctl.h>
#define CLS do{system("clear");}while(0)
#else
#define CLS /**/
#endif
