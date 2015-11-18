/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
//#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);

int stringToInt(string str);

/* Main program */

int main() {
   // [TODO: fill in the code]
  const int arraySize=3;
  int nums[arraySize]={-237,0,9876};
  string strNums[arraySize]={"0","1357","-42"};
  cout<<"testing intToString function on integers: "<<endl;
  for(int i=0;i<arraySize;i++)
    cout<<nums[i]<<"-->"<<intToString(nums[i])<<endl;
  cout<<endl<<"testing stringToInt function on numerical strings "<<endl;
  for(int i=0;i<arraySize;i++)
    cout<<strNums[i]<<"-->"<<stringToInt(strNums[i])<<endl;
  cout<<endl<<"testing complete."<<endl;
  return 0;
}

	
/*function recursively constructs string from integer using /10 and %10 operators to break integer into 2 parts
 *precondition:  argument n is an integer
 *postcondition:  string representation of integer is returned
 */
string intToString(int n){
  if (n/10==0){
    if(n>=0)
      return string(1,char(48+n%10));  //<string> library convert single char to string
    else
      return "-"+string(1,char(48+(-n%10)));
  }
  else{
    if(n>=0)
      return intToString(n/10)+string(1,char(48+n%10));
    else
      return intToString(n/10)+string(1,char(48+(-n%10)));
  }
}

/*recursive function converts string to integer
 *precondition:  argument str is a string representing a numerical value, such as "101" or "-42"
 *postcondition:  type int value represented by str is returned
 */
int stringToInt(string str){
  //base case is a string of length 1, as in "9"
  if(str.length()==1){
    return int(str[0])-48;  //convert 0th element of string to int using typecast, 48 is ascii for 0
  }
  else{
    if(str[0]=='-')  //negative case
      return -1*stringToInt(str.substr(1));  //recur with '-' sign stripped
    return 10*stringToInt(str.substr(0,(str.length()-1)))+(int(str[str.length()-1]))-48; //recursive call with string less last char
  }
}
						       

		       
