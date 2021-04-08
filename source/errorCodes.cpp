#include "../header/errorCodes.hpp"

#pragma once

extern const string E1 = "Input Syntax Error";
extern const string E2 = "Logical Input Error";
extern const string E3 = "No Suitable Route Found";

void logError(string e) {
	cout << "\033[91m\nERROR:\033[0m " << e << "\n\nPress Enter to Continue...";
	cin.ignore();
}