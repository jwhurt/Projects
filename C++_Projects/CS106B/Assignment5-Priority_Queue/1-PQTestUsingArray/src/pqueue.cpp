/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

/*Implementation notes: PriorityQueue constructor
 *The constructor allocates dynamic array storage for the queue
 *and initializes the instance variables
 */
PriorityQueue::PriorityQueue() {
  capacity=INITIAL_CAPACITY;
  count=0;
  array=new ValuePriorityPair[capacity];
}

/*Implementation notes: PriorityQueue destructor
 *The constructor frees any heap memory allocated by the class,
 *which is a dynamic array of elements
 */
PriorityQueue::~PriorityQueue() {
  delete[] array;
}

/*size returns the instance variable count, which represents
 *the number of objects in the queue
 */
int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
   return count==0;
}

void PriorityQueue::clear() {
  count=0;
}

/*Implementation notes: enqueue
 *The function takes a pair of arguments representing value and priority for the
 *ValuePriorityPair object, and inserts the object in priority order(lower numerical priority=
 *higher importance) into the queue using helper functions bisectSearch and insert.
 */
void PriorityQueue::enqueue(std::string value, double priority){
  int insertAtIndex;
  if(isEmpty())
    insertAtIndex=0;
  else
    insertAtIndex=bisectSearch(priority,0,count-1);          
  insert(value,priority,insertAtIndex);
}

/*Implementation notes: insert: 
 *insert is helper function for enqueue()
 *value is the element id, priority is the priority of the element, and index is the position in the 
 *array for the new element. Insert function will shift all array elements equal to or greater than the 
 *insert index up by one index value and assigns the value and priority parameters to the element in the 
 *array whose position is equal to index. 
 */
void PriorityQueue::insert(string value, double priority,int index){
  if(count==capacity){
    expandCapacity();
  }
  for(int i=count;i>index;i--)
    array[i]=array[i-1];
  array[index].value=value;
  array[index].priority=priority;
  count++;
}

/*Implementation notes: bisectSearch
 *function recursively finds index where new element is to be placed in array
 *using bisection search. A lower numeric value represents a higher priority,
 *so the priorities will be inserted in increasing numeric order, with array[0] 
 *corresponding to the highest priority element and array[count-1] the lowest.
 */
int PriorityQueue::bisectSearch(double priority,int lh, int rh){
  //handle invalid index parameters
  if(lh<0||rh<0||lh>count-1||rh>count-1||lh>rh)
        error("bisectSearch: invalid array index parameter");
  if(lh==rh){ //base case
    if(priority<array[lh].priority)
      return lh;
    else
      return lh+1;
  }
  else{  //recursive decomp, cutting problem in half with each call
    if(priority<array[(lh+rh)/2].priority){
      if((lh+rh)/2-1<lh) //prevent rh from going before lh
	rh=lh;
      else
	rh=(lh+rh)/2-1;
    }
    else
      lh=(lh+rh)/2+1; //lh cannot go beyond last element in array due to integer division
    return bisectSearch(priority,lh,rh);
  }
}

/*Implementation notes: dequeue
 *function first checks if count = 0, which causes error.  
 *The value of the object in array index 0 is returned, as this represents the 
 *highest priority.  All the subsequent elements are then copied to the prior position in 
 *the array so the the value at index i = i+1.  The count value is then decremented.
 */
string PriorityQueue::dequeue() {
  if(count==0)
    error("dequeue: queue is empty");    
  string front=array[0].value;
  for(int i=0;i<count-1;i++)
    array[i]=array[i+1];
  count--;
  return front; 
}

/*Implementation notes: peek
 *function makes a copy of the value of the object at index 0 and returns that value.
 *if array is empty the error function is called
 */
string PriorityQueue::peek() {  
  if(count==0)
    error("peek: queue is empty");    
  return array[0].value;
}

/*implemented in the same way as peek(), but returns the priority*/
double PriorityQueue::peekPriority() {  
  if(count==0)
    error("priorityQueue: queue is empty");      
  return array[0].priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */
PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
