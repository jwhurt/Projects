/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

const string ALPHABET="abcdefghijklmnopqrstuvwxyz";  //letters in alphabet
void printQueue(Queue< Vector<string> > &queue);
void promptUserForInput(string &start,string &target);
void printLadder(Vector<string> ladder);
void generateNewLadders(Vector<string> ladder,Queue< Vector<string> > &queue, Lexicon &english,Lexicon &wordsUsed);

int main(){
	// [TODO: fill in the code]
  Lexicon english("EnglishWords.dat");   //declare & init english words lexicon
  Lexicon wordsUsed;//Lexicon to store words already used in some ladder
  string start="";
  string target="";
  Vector<string> initLadder;  //initial ladder with start string at index 0;
  Vector<string> solnLadder;  //initialize empty ladder for soln ladder, which is the shortest ladder-the one with fewest words
  Queue< Vector<string> > queue;  //declare queue to hold word ladders
  bool solved=false;  //loop sentinel that stores the solution status of word ladder
  while(true){    //main program loop
    promptUserForInput(start,target);
    if(start=="")
      break;
    initLadder.add(start);  
    wordsUsed.add(start);
    queue.enqueue(initLadder);  //place initial ladder in queue  
    while(!queue.isEmpty()&&!solved){    //loop to process queue
      solnLadder=queue.dequeue();  //dequeu ladder at head of queue
      if(solnLadder[(solnLadder.size()-1)]==target) //test if ladder is a soln
	solved=true;  //if ladder is a solution,set sentinel to true
      else
        generateNewLadders(solnLadder,queue,english,wordsUsed);
    }
    if(solved){
      cout<<"Found ladder: ";
      printLadder(solnLadder);
    }
    else
      cout<<"No ladder found."<<endl;

    //clear vectors and queues for next iteration
    solved=false;
    wordsUsed.clear();
    initLadder.clear();
    solnLadder.clear();
    queue.clear();
  }
  cout<<"Program end."<<endl;
  return 0;
}

/*function extends ladder by new word that is one letter removed from last word in ladder
 *precondition: ladder is a vector of words, queueu, a queue of ladders, lexicon english checks for 
 *valid words, and wordsUsed is a list of words used in previous ladders
 *postcondition: new ladders are created and queued for each word that is one letter different from last word in
 *ladder, words that were previously used are not used again
 */
void generateNewLadders(Vector<string> ladder,Queue< Vector<string> > &queue,Lexicon &english,Lexicon &wordsUsed){
  string headWord=ladder[ladder.size()-1];  //last word in ladder represents latest attempt to hit target
  for(int i=0;i<headWord.size();i++){
    for(int j=0;j<ALPHABET.size();j++){
      string newWord=headWord;  //make fresh copy of new word to be added
      newWord[i]=ALPHABET[j];  //change 1 letter in newWord
      if(english.contains(newWord)&& !wordsUsed.contains(newWord)){
	Vector<string> newLadder=ladder;  //make copy of previous ladder	
	newLadder.add(newWord);
	queue.enqueue(newLadder);
	wordsUsed.add(newWord);
      }
    }
  }  
}

/*loops until user enters valid start and target string 
 *precondition:  str1 and str2 declared, passed as reference
 *postcondition: str1 and str2 contain start and target string
 */
void promptUserForInput(string &str1,string &str2){
  cout<<"Enter start word (Return to quit): ";
  getline(cin,str1);
  str1=toLowerCase(str1);
  if(str1!=""){
    cout<<"Enter destination word: ";
    getline(cin,str2);  
    str2=toLowerCase(str2);
  }
}

//prints words in ladder
void printLadder(Vector<string> ladder){
  for(int i=0;i<ladder.size();i++){
    if(i<ladder.size()-1)
      cout<<ladder[i]<<" ";
    else
      cout<<ladder[i]<<endl;
  }
}

