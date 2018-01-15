#pragma once
#include <iostream>
#include <string>
#include <ctime>

using System::String;

void throwErr(char* msg, bool pError = false);
void MarshalString ( String ^ s, std::string& os );
void getDate(char* buff);