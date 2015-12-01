/*Assignment 3, problem 4:  Cell phone mind reading.
 *Write the function ListCompletions that prints all words from the lexicon that can be formed
 *by extending the given digit sequence.
 */

#include <cctype>
#include <iostream>
#include <string>
using namespace std;

#include "simpio.h"
#include "gwindow.h"
#include "lexicon.h"  //used to verify words

void ListCompletions(string digits,Lexicon &lex);
void ListCompRec(string prefix,string digits,Lexicon &lex);
string DigitLetters(char ch);

int main(){
  Lexicon lex("EnglishWords.dat"); //initialize english lexicon object, which validates words
  string digits;
  cout<<"This program will take a digit sequence input and generate a list of possible valid word completions by mapping the digits to a valid word prefix. "<<endl;
  cout<<"Enter digits (no spaces) to see the list of valid words formed by that digit prefix: ";
  cin>>digits;
  ListCompletions(digits, lex);
  return 0;
}
/*wrapper function */
void ListCompletions(string digits,Lexicon &lex){
  ListCompRec("",digits,lex);
  return;
}

/*recursive function that generates set of completions for given string input */
void ListCompRec(string prefix,string digits,Lexicon &lex){
  /*base case*/
  if (digits.length()==0){
    if (lex.contains(prefix))
      cout<<prefix<<" ";
    else{
      string alpha="abcdefghijklmnopqrstuvwxyz";
      for (int i=0;i<int(alpha.length());i++){  //build larger prefix out of alphabet
	if(lex.containsPrefix(prefix+alpha[i]) )  
	  ListCompRec(prefix+alpha[i],digits,lex);
      }
    }
  }
  /*digits remain to be processes */
  else {
    string letters=DigitLetters(digits[0]);
    for (int i =0;i<int(letters.length());i++){
      if(lex.containsPrefix(prefix+letters[i]))
	 ListCompRec(prefix+letters[i],digits.substr(1),lex);
    }
  }
  
}

string DigitLetters(char ch){
  switch(ch){
  case '0': return ("0");
  case '1': return ("1");
  case '2': return ("abc");
  case '3': return ("def");
  case '4': return("ghi");
  case '5': return("jkl");
  case '6': return("mno");
  case '7': return ("pqrs");
  case '8': return ("tuv");
  case '9': return ("wxyz");
  default: return("");
  }
}
