/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: Joe Hurt 12/14/15
 * Section: [TODO: enter section leader here] 
 * This file is the starter project for the cell phone mind-reading problem
 * from Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
using namespace std;

const string ALPHA="abcdefghijklmnopqrstuvwxyz";

/* Function prototypes */
void listCompletions(string digits, Lexicon &lex);
string listCompletionsRec(string prefix,string digits, Lexicon &lex);
string getString(char digit);


/* Main program */

int main() {
   Lexicon english("EnglishWords.dat");
   cout << "Cell phone mind-reading problem" << endl;
   while (true) {
      cout << "Enter a set of digits: ";
      string digits = getLine();
      if (digits == "" || digits == "quit") break;
      cout << "The words beginning with those digits are:" << endl;
      listCompletions(digits, english);
   }
   return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lexicon);
 * ----------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon &lex){
  cout<<listCompletionsRec("",digits,lex);  
}
/*recursive function that does all the real work*/
string listCompletionsRec(string prefix,string digits, Lexicon &lex){
  string result="";
  if(digits!=""){  //this is part 1 of the recursion, where we reduce digit string to empty
    if(!lex.containsPrefix(prefix))  //base case 
      return result;  
    else{  //recursive decomp for part 1, we continue building prefix using digits from string
      string letters=getString(digits[0]);
      for(int i=0;i<letters.length();i++)
	result+=listCompletionsRec(prefix+letters[i],digits.substr(1),lex);
      return result;
    }
  }
  else{ //we now are in case where digits==""
    if(!lex.containsPrefix(prefix))
      return result;
    else{
      if(lex.contains(prefix))
	result+=prefix+"\n";//add word to result, but need to continue adding letters to get all words starting with this prefix
      for(int i=0;i<ALPHA.length();i++)  //go deeper down path of finding more words with this prefix
	result+=listCompletionsRec(prefix+ALPHA[i],digits,lex);
      return result;
    }
  } 
}

string getString(char digit){
  switch(digit){
  case '0':
    return "0";
  case '1':
    return "1";
  case '2':
    return "abc";
  case '3':
    return "def";
  case '4':
    return "ghi";
  case '5':
    return "jkl";
  case '6':
    return "mno";
  case '7':
    return "pqrs";
  case '8':
    return "tuv";
  case '9':
    return "wxyz";
  default:
   return "?"; 
  }
}
