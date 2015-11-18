/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Obenglobish problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

string Obenglobish(string word);
Vector<int> getVowelPositions(string word);
void insertSubstr(string &word, Vector<int> positions, string subStr="ob");
Vector<int> getInsertPositions(string word);
bool isVowel(char ch);

/* Main program */
int main() {
   // [TODO: fill in the code]
  string word;
  //loop until blank space entered
  cout<<"This program translates an English word into an Obenglobish word."<<endl;
  cout<<"When you are done entering words, hit enter to exit the program."<<endl;
  while(true){
    word=toLowerCase(getLine("Enter a word: "));
    if(word==""){//if no word entered, quit
      cout<<"Goodbye."<<endl;
      break;
    }
    cout<<word<<" ---> "<<Obenglobish(word)<<endl;
  }
  return 0;
}

/*function translates an English word into Obenglobish (see handout for rules description)
 *precondition:  function is passed string as argument
 *postcondition: Obenglobish word is returned
 */
string Obenglobish(string word){
  insertSubstr(word,getInsertPositions(word));  //function translates word
  return word;  
}


/*function takes string to convert as argument, then calls helper function getVowelPositions to get the vowel position vector;
 *then tests each vowel position to determine that it conforms to the rules of Obenglobish; those positions that don't are removed
 *precondition:  argument is a string value representing a single word
 *postcondition:  vector of positions to insert the substring is returned to caller
 */
Vector<int> getInsertPositions(string word){
  Vector<int> vowelPos=getVowelPositions(word);  //call helper function to first get vowel positions in word  
  for(int i=vowelPos.size()-1;i>=0;i--){  //iterate backward from last position to first, removing those positions that don't conform to rules   
    if((vowelPos[i]==word.length()-1)&&(word[vowelPos[i]]=='e')) //if last vowel is 'e', remove from insert position vector
      vowelPos.remove(i);
    else if((i>=1)&&(vowelPos[i]==(vowelPos[i-1]+1))) //if the vowel is consecutive(immediately follows another vowel), remove
      vowelPos.remove(i);
    else{
    }   
  }
  return vowelPos;
}


/*helper function to getInsertPositions; searches string and returns vector of all the vowel positions
 *postcondition:  function returns vector of vowel positions found in string argument
 */
Vector<int> getVowelPositions(string word){
  Vector<int> vowelPositions; //declare empty vector
  for(int i=0;i<word.length();i++){
    if(isVowel(word[i]))
      vowelPositions.add(i);  //add index where vowel is found in word
  }
  return vowelPositions;
}

/*function inserts substring ("ob" by default) at the positions specified by positions vector
 */
void insertSubstr(string &word, Vector<int> positions, string subStr){
  for(int i=positions.size()-1;i>=0;i--)
    word.insert(positions[i],subStr);
}

//function returns true if char is a vowel
bool isVowel(char ch){
  return (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u');
}
