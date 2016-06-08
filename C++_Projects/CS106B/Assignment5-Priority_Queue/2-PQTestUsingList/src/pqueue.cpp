/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;


/*
 * Implementation notes: constructor
 * --------------------------------------------------------------
 * The constructor initializes head to point to a dummy cell at the head of the linked list;
 * the count is initialized to 0
 */
PriorityQueue::PriorityQueue() {
  head=new Cell;  //head points to dummy cell
  head->next=NULL;
  count=0;  
}

/*
 * Implementation notes: destructor
 * --------------------------------------------------------------
 * The destructor uses *cp as an iterator to move along the linked list, starting at the first cell
 * after head, while the prior cell is deleted
 */
PriorityQueue::~PriorityQueue() {
  while(head!=NULL){
    Cell *cp=head->next;
    delete head;
    head=cp;
  }
}

int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
   return count==0;
}

void PriorityQueue::clear() {
  while(count>0)
    dequeue();
}


/*
 * Implementation notes: enqueue
 * --------------------------------------------------------------
 * The enqueue method creates a new cell having value and priority attributes and inserts it into the correct priority order
 * using the insert and findPosition helper methods.  
 */

void PriorityQueue::enqueue(std::string value, double priority){
  Cell *cp=new Cell;
  cp->value=value;
  cp->priority=priority;
  insert(cp,findPosition(head,priority));//find cell where new value will be inserted after  
  count++;
}

/*
 * Implementation notes: dequeue
 * --------------------------------------------------------------
 * The dequeue method gets the value attribute from the first non-dummy cell in the linked list, 
 * then deletes that cell and sets the dummy cell pointer to the next cell;
 * count is decremented
 */

string PriorityQueue::dequeue() {
  if(count==0)
    error("dequeue: queue is empty");    
  Cell *killPtr=head->next;
  string value=head->next->value;
  head->next=head->next->next;
  delete killPtr;    
  count--;
  return value; 
}

/*
 * Implementation notes: insert
 * --------------------------------------------------------------
 * The insert method takes a new cell and a pointer to the position in the linked list
 * where that new cell will be inserted after
 */
void PriorityQueue::insert(Cell *newCell,Cell *pos){
  newCell->next=pos->next;
  pos->next=newCell;
}


/*
 * Implementation notes: findPosition
 * --------------------------------------------------------------
 * The findPosition method takes a cell pointer and priority number and recursively searches the linked list
 * to find the last cell whose priority value is less than the argument priority(remember, lower number is higher priority);
 * a pointer to that cell is returned to be used by caller to insert the new cell
 *remember to use scope resolution operator on return value, since it was defined in private section of PriorityQueue!
 */
PriorityQueue::Cell* PriorityQueue::findPosition(Cell *start,double priority){ 
  if(start->next==NULL)  //base case, end of linked list 
    return start;
  if(start->next->priority > priority) //base case, next cell is lower in priority
    return start;
  else
    return findPosition(start->next,priority);  //recursive decomp, call findPosition passing pointer to next cell in linked list
}


string PriorityQueue::peek() {  
  if(count==0)
    error("peek: queue is empty");    
  return head->next->value;
}

double PriorityQueue::peekPriority() {  
  if(count==0)
    error("priorityQueue: queue is empty");      
  return head->next->priority;
}


/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook p. 548
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}
