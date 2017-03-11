#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#if defined(_WIN32) || defined(_WIN64)
#define CLS system("cls");
#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)
#define CLS system("clear");
#else
#define CLS /**/
#endif