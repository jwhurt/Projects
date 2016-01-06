#include <iostream>
#include <string>
#include <fstream>
#include <sstream>     //used for safeIO.h
using namespace std;

#ifndef SAFEIO_H
#define SAFEIO_H

int stringToInteger(string str);
double stringToDouble(string str);
int getInteger(string prompt);  //get integer from console input
double getDouble(string prompt); //get double from console input
char getChar(string prompt);
string promptUserForFile(ifstream &infile,string prompt);  //get file to open from user
string lineToString(string &line);

#endif
