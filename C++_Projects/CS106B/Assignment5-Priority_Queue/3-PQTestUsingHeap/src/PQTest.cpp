/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
void list(const PriorityQueue &pq);

/* Main program */
/* main() manages the user interface;
 * instantiates priority queue object, then operates loop to read input 
 * from user and call the appropriate priority queue method
 */
int main() {
   PriorityQueue pq;
   TokenScanner scanner;
   while (true) {
      string line = getLine("> ");
      scanner.setInput(line);
      scanner.ignoreWhitespace();
      string cmd=scanner.nextToken();
      if (cmd == "help") {
         helpCommand();
      }      
      else if (cmd == "enqueue") {
	if(scanner.hasMoreTokens()){
	  string value=scanner.nextToken();
	  if(scanner.hasMoreTokens()){
	    scanner.scanNumbers();
	    string priorityStr=scanner.nextToken();
	    double priority=stringToDouble(priorityStr);	
	    pq.enqueue(value,priority);
	  }
	  else
	    pq.enqueue(value);
	}
      }    
      else if (cmd == "dequeue") {
	if(pq.isEmpty())
	  cout<<"The queue is empty"<<endl;
	else
	  cout<<pq.dequeue()<<endl;
      }
      else if (cmd == "peek") {
	if(pq.isEmpty())
	  cout<<"The queue is empty"<<endl;
	else
	  cout<<pq.peek()<<endl;
      }
      else if (cmd == "peekPriority"||cmd=="peekpriority") {
	if(pq.isEmpty())
	  cout<<"The queue is empty"<<endl;
	else
	  cout<<pq.peekPriority()<<endl;
      }
      else if (cmd == "clear") {
	pq.clear();
      }
      else if (cmd == "size") {
	cout<<pq.size()<<endl;
      }
      else if (cmd == "isEmpty"||cmd=="isempty") {
	if(pq.isEmpty())
	  cout<<"true";
	else
	  cout<<"false";
	cout<<endl;
      }
      else if(cmd=="list")
	list(pq);
      else {
         cout << "Undefined command: " << cmd << endl;
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}

/*
 * Function: list
 * Usage:  list(priorityQueue); 
 * -------------------------------
 * list will display the elements in the priority queueu without changing the order of those elements in the queue. 
 * Being a client function, list has no access to the internal data structure of the pqueue.h interface and
 * must use only the public methods of the priority queue class.
 * list will use the copy constructor to instantiate a replica of the original priority queue, which is 
 * passed by reference. It then dequeues and prints each element to terminal until the queue is empty.
 */
void list(const PriorityQueue &pq){
  PriorityQueue copy(pq);
  cout<<"Queueu: ";
  while(!copy.isEmpty())
    cout<<copy.dequeue()<<" ";
  cout<<endl;
}
