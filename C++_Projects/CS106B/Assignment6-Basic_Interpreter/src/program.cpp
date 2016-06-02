/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"  //included in original starter code
using namespace std;

/*
 * Implementation notes: constructor
 * ---------------------------------------
 * The constructor creates a doubly linked list with head and tail sentinel nodes;
 * the linked list is initialized with the head pointer pointing to the head sentinel, 
 * the tail pointer pointing to the tail sentinel, the the sentinel nodes pointing to each other
 * The sentinel nodes will not contain data, so their line contains the empty string and their 
 * statement pointer points to null 
 */
Program::Program() {
   // Replace this stub with your own code
  head=new Cell;
  tail=new Cell;
  head->next=tail;
  head->prev=NULL;
  tail->prev=head;
  tail->next=NULL;
  head->lineNumber=0;
  head->line="";
  head->stm=NULL;
  tail->lineNumber=0;
  tail->line="";
  tail->stm=NULL;
}

/*
 * Implementation notes: destructor
 * ---------------------------------------
 * The destructor frees all memory that was dynamically allocated in order to create the linked list.
 * The destructor uses the clear() function to remove all the data nodes of the linked list,
 * then it deletes the head and tail sentinels
 */
Program::~Program() {
   // Replace this stub with your own code
  clear();
  delete head;
  delete tail;
}

/*
 * Implementation notes: clear
 * ---------------------------------------
 * The clear function uses 2 pointers to iterate through the linked list deleting all the cells
 * except the head and tail sentinels
 */
void Program::clear() {
   // Replace this stub with your own code
  Cell *killPtr;
  Cell *cellPtr;
  cellPtr=head->next;
  while(cellPtr!=tail){
    killPtr=cellPtr;
    cellPtr=cellPtr->next;
    delete killPtr->stm;  //delete the statement object
    delete killPtr;
  }
  head->next=tail;
  tail->prev=head;  //re-connect head and tail
  lineMap.clear();
}

/*
 * Implementation notes: addSourceLine
 * ---------------------------------------
 * The addSourceLine function first checks if the line number argument is already in the map;
 * If so, it replaces the string of that Cell and deletes the old parsed statement without creating and inserting
 * a new cell into the linked list.
 * If not, it creates a new cell and searches the linked list to find the insertion point, where the pointers are 
 * then re-wired as necessary to insert the new cell.
 */
void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
  if(lineMap.containsKey(lineNumber)){
    Cell *cPtr=lineMap.get(lineNumber);
    cPtr->line=line; //replace old string statement with new
    delete cPtr->stm;
    cPtr->stm=NULL; //program crashes at runtime without this line
  }
  else{
    Cell *newCell=new Cell;
    newCell->lineNumber=lineNumber;
    newCell->line=line;
    newCell->stm=NULL;
    if(head->next==tail){  //if linked list empty
      newCell->next=tail;    
      newCell->prev=head;
      head->next=newCell;
      tail->prev=newCell;
    }
    else{  //linked list not empty
      Cell *cPtr=tail->prev;//start looking for insert position at end of list
      while(cPtr->lineNumber>lineNumber &&cPtr!=head)
        cPtr=cPtr->prev;   //advance insert pointer to cell where new cell is to be inserted next
        newCell->prev=cPtr;
        newCell->next=cPtr->next;
        cPtr->next->prev=newCell;
        cPtr->next=newCell;
    }
    lineMap.add(lineNumber,newCell);  
  }
}

/*
 * Implementation notes: removeSourceLine
 * ---------------------------------------
 * This function first checks if the line number argument is already in the map;
 * if so it gets the pointer to the cell and first rewires the pointers of the list
 * around the cell to be removed, deletes the parsed statement pointed to by that cell, 
 * deletes the cell, and finally removes the line from the map.
 * If the line number is not found in the map, the function does nothing.
 */
void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
  if(lineMap.containsKey(lineNumber)){
    Cell *cellPtr=lineMap.get(lineNumber);
    cellPtr->next->prev=cellPtr->prev;
    cellPtr->prev->next=cellPtr->next;
    if(cellPtr->stm!=NULL)
      delete cellPtr->stm;
    delete cellPtr;
    lineMap.remove(lineNumber);
  }
}

/*
 * Implementation notes: removeSourceLine
 * ---------------------------------------
 * This function first checks if the line number argument is in the map;
 * if so it gets the pointer to the cell representing that line number
 * from the map and returns a copy of the string contained in that cell;
 * if not it returns the empty string
 */
string Program::getSourceLine(int lineNumber) {
  string result="";
  if(lineMap.containsKey(lineNumber))
    result=(lineMap.get(lineNumber))->line;
  return result;    // Replace this stub with your own code
}


/*
 * Implementation notes: setParsedStatement
 * ---------------------------------------
 * This function first checks if the line number argument is in the map;
 * if so, it sets the associated cell's statement pointer to the statement pointer argument;
 * if the cell's statement pointer is already pointing to a parsed statement, that statement
 * will first be deleted.  
 * if line number argument is not in map, the function will throw an error.
 */
void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
  if(lineMap.containsKey(lineNumber)){
    Cell *cellPtr=lineMap.get(lineNumber);
    if(cellPtr->stm!=NULL) //if there is a previous statement for that line number, delete and replace
      delete cellPtr->stm;
    cellPtr->stm=stmt;
  }
  else
    throw ErrorException("Invalid line number");

}

/*
 * Implementation notes: getParsedStatement
 * ---------------------------------------
 * This function first determines if line number is in the map; if so it returns the statement pointer of that cell,
 * if not it returns null
 */
Statement *Program::getParsedStatement(int lineNumber) {
// Replace this stub with your own code
  if(lineMap.containsKey(lineNumber))
    return lineMap.get(lineNumber)->stm;  //return statement pointer
  else
    return NULL;  
}

/*
 * Implementation notes: getFirstLineNumber
 * ---------------------------------------
 * This function first determines if linked list is empty by checking if the head sentinel points to tail:  if so, returns -1;
 * if not returns the line number of the next cell in the linked list after head
 */
int Program::getFirstLineNumber() {
  if(head->next==tail)
    return -1;
  else
    return head->next->lineNumber; // Replace this stub with your own code
   
}

/*
 * Implementation notes: getNextLineNumber
 * ---------------------------------------
 * This function first determines if map contains the lineNumber argument;
 * if so it then checks if that line number is the last line number by checking
 * if the next pointer of that cell points to tail; if so function returns -1, if not 
 * the function returns the number of the cell pointed to by the next pointer
 * if the map doesn't contain the line number, function returns -1
 */
int Program::getNextLineNumber(int lineNumber) {
  if(lineMap.containsKey(lineNumber)){
    Cell *cellPtr=lineMap.get(lineNumber);
    if(cellPtr->next==tail)  
      return -1;  //if there is no next line number
    else
      return cellPtr->next->lineNumber;
  }
  else  //line number not in map
   return -1;     // Replace this stub with your own code
}


/*
 * Implementation notes: hasLineNumber
 * ---------------------------------------
 * This function determines if map contains the lineNumber argument
 */
bool Program::hasLineNumber(int lineNumber) {
  return lineMap.containsKey(lineNumber);
}
