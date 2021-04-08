#include "../header/errorCodes.hpp"

#pragma once

extern const string E1 = "Input Syntax Error";
extern const string E2 = "Logical Input Error";
extern const string E3 = "No Suitable Route Found";

void logError(string e) {
	cout << "\nERROR: " << e << "\n\nPress Enter to Continue...";
	cin.ignore();
}