#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define CLS system("cls");
#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)
#include <sys/ioctl.h>
#define CLS system("clear");
#else
#define CLS /**/
#endif
