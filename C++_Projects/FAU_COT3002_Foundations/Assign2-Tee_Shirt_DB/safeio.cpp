/*The purpose of this set of functions is to make formatted input, both from the console and from a file,
 *more robust.  Numerical console entry becomes more resistant to user input errors; instead of crashing, 
 *programs using these functions allow the user to recover and correct their data entry mistake.
 *File data read into the functions gives an error message when there is data corruption, instead of 
 *allowing the program to continue with corrupt data or crashing without feedback.
 */

#include "safeio.h"

using namespace std;
 /*this function converts a string to integer*/
int stringToInteger(string str)
{
  istringstream stream(str); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
  int value;
  stream >> value;
  if(!stream.eof()) 
    stream>>ws;  //this allows whitespace after integer 
  if (stream.fail() || !stream.eof()){
    cerr<<"stringToInteger: Illegal integer format"<<endl;
    exit(EXIT_FAILURE);
  }
  return value;
}

string lineToString(string &line)
{
  string subStr;
  istringstream stream(line); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
  stream >> subStr; //extract string that follows whitespace chars
  if(!stream.eof()) 
    stream>>ws;  //this allows whitespace after integer 
  if (stream.fail()){
    cerr<<"lineToString: Illegal string format"<<endl;
    exit(EXIT_FAILURE);
  }
  return subStr;
}

/*this function converts a string to a real, used with file input*/
double stringToDouble(string str)
{
  istringstream stream(str); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
  double value;
  stream >> value;
  if(!stream.eof()) 
    stream>>ws;  //this allows whitespace after value
  if (stream.fail() || !stream.eof()){
    cerr<<"stringToDouble: Illegal double format"<<endl;
    exit(EXIT_FAILURE);
  }
  return value;
}


/*prompts user for integer console input, continues looping until valid entry*/
int getInteger(string prompt)
{
  string str;
  int value;
  while(true){
    cout<<prompt;
    getline(cin,str);  
    istringstream stream(str); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
    stream >> value;
    if(!stream.eof()) 
      stream>>ws;  //this allows number to be followed by whitespace and still be valid entry
    if (!stream.fail() && stream.eof())  //good data entry leaves stream with no fail flag at end of file 
      break;
    cout<<"invalid entry, try again"<<endl;
  }
  return value;
}


/*prompts user for real console input, continues looping until valid entry*/
double getDouble(string prompt)
{
  string str;
  double value;
  while(true){
    cout<<prompt;
    getline(cin,str);  
    istringstream stream(str); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
    stream >> value;
    if(!stream.eof()) 
      stream>>ws;  //this allows number to be followed by whitespace and still be valid entry
    if (!stream.fail() && stream.eof())  //good data entry leaves stream with no fail flag at end of file 
      break;
    cout<<"invalid entry, try again"<<endl;
  }
  return value;
}


/*validates that user entered one char only at console; the char can be preceded by whitespace
 *characters and followed by ws chars, but any other combination is rejected, and the user
 *is asked to enter again
 */
char getChar(string prompt)
{
  string str;
  char value;
  while(true){
    cout<<prompt;
    getline(cin,str);  
    istringstream stream(str); //instantiate stream, an input stream object (in <sstream>) that reads data from the string variable str.
    stream >> value;
    if(!stream.eof()) 
      stream>>ws;  //this allows number to be followed by whitespace and still be valid entry
    if (!stream.fail() && stream.eof())  //good data entry leaves stream with no fail flag at end of file 
      break;
    cout<<"invalid entry, try again"<<endl;
  }
  return value;
}


/*prompts user for filename, attempts to open file using file stream parameter infile
 *will continue asking user for filename until file is successfully opened
 */
string promptUserForFile(ifstream &infile,string prompt)
{
  while(true){
    cout<<prompt;
    string filename;
    getline(cin,filename);
    infile.open(filename.c_str());
    if(!infile.fail())return filename;
    infile.clear();
    cout<<"Unable to open file.  Try again."<<endl;
    if(prompt=="")prompt="Input file: ";
  }
}


