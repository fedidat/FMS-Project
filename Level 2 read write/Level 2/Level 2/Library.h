#define _CRT_SECURE_NO_WARNINGS	//prevents strcpy warnings
#pragma once
#include <iostream>

void throwErr(char* msg, bool pError = false);
enum HashFuncIDcode;
std::ostream& operator<<(std::ostream& out, const HashFuncIDcode func);