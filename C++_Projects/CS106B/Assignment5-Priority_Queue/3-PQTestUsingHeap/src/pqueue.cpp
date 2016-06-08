/*
 * File: pqueue.cpp (heap version)
 * --------------------------------
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
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

PriorityQueue::~PriorityQueue() {
  delete[] array;
}

int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
   return count==0;
}

void PriorityQueue::clear() {
  count=0;
}
/*
 * Implementation notes: enqueue
 * -------------------------------
 * Function enqueue will add a new ValuePriorityPair to the dynamic array using the basic properties
 * of a partially ordered tree as explained in text on page 719.  The properties used by this function are
 * property 2), the bottom level is filled left-right order and property 3), each node has a key that is
 * less than or equal to the key of its children.  The function asses the value and priority parameters to 
 * the helper function insertAtLowestLevel, which adds a ValuePriorityPair to the end of the array, which
 * follows property 2.  The helper function orderUpward is then called to maintain property 3.
 */
void PriorityQueue::enqueue(std::string value, double priority){
  insertAtLowestLevel(value, priority);
  orderUpward(count-1); //order the node just added
}

/*
 * Implementation notes: insertAtLowestLevel
 * -------------------------------
 * This function maintains the second priority of the partially ordered tree, which is
 * that the number of nodes along any path can never differ by more than one.  To achieve this,
 * the bottom level of the "tree" is strictly filled in left to right order.
 */
void PriorityQueue::insertAtLowestLevel(std::string value, double priority){
  if(count==capacity){
    expandCapacity();
  }
  array[count].value=value;
  array[count].priority=priority;
  count++;
}

/*
 * Implementation notes: orderUpward
 * -------------------------------
 * This function maintains property 3 of partially orderted tree, that is, each node contains a key less than or equal the key in its children
 * The function takes an index of a node and compares its key with that of its parent node using the formula: parent index=(n-1)/2, where n is the node index.
 * If the key/priority is less than the parent, the nodes will be swapped using the function swapNodes. The function uses recursion to continue the ordering
 * process up the levels of the tree until the base case is reached where the new node has key greater than its parent
 */

void PriorityQueue::orderUpward(int nodeIdx){
  if (nodeIdx > 0){  
    int parentIdx=(nodeIdx-1)/2;
    if(array[nodeIdx].priority<array[parentIdx].priority){ //if parent value > node added, swap
      swapNodes(parentIdx,nodeIdx);
      orderUpward(parentIdx);  //recursive decomposition
    }
  }
}


/*
 * Implementation notes: swapNodes
 * -------------------------------
 * This function takes the array index of the parent and child to be swapped and uses a temp ValuePriorityPair to implement the swap
 */
void PriorityQueue::swapNodes(int parentIdx, int childIdx){
  ValuePriorityPair temp=array[childIdx];//temp node used to swap node at root with bottom rightmost node
  array[childIdx]=array[parentIdx];  //root node moved to bottom rightmost position
  array[parentIdx]=temp;  //bottom rightmost node moved into root position
}


/*
 * Implementation notes: dequeue
 * -------------------------------
 * This function will return the value in the queue with the lowest numerical priority, which represents the highest priority.  
 * This function simulates the removal of the root node of the tree as described in text on p720; Root node is swapped with the rightmost
 * node at the bottom of tree, then the tree is re-ordered from the top down to maintain the ordering property that parent nodes have lower
 * keys than children, then the rightmost bottom node is "pruned" from tree by reducing the array count
 * The helper functions swapNodes and orderDownward are used to implement the necessary swapping and re-ordering.
 */
string PriorityQueue::dequeue() {
  if(count==0)
    error("dequeue: queue is empty");    
  swapNodes(0,count-1);
  string value=array[count-1].value;  //get value of last element
  count--;
  orderDownward(0);  //root node now moves down subtree into correct position
  return value;  
}

/*
 * Implementation notes: orderDownward
 * -------------------------------
 * This recursive function maintains the ordering property of the partially ordered tree after a dequeue operation;
 * The base case occurs when the given node has no children, in which case no re-ordering occurs and the function returns.
 * The recursive decomposition involves 2 cases depending on whether there is one or two children: if there are 2 children
 * and the right child is smaller than the left and smaller than the parent, then swap and recur on the right child;
 * if there are 2 children and the left is the smaller, then the case is the handled the same as the 1 child case, since the left child is
 * the only child node.  If there is 1 child (the left child) whose key is less than parent, then swap and recur on the left child index
 */
void PriorityQueue::orderDownward(int nodeIdx){
  int lChildIdx=2*nodeIdx+1;
  int rChildIdx=2*nodeIdx+2;
  if(lChildIdx>count-1)  //base case, node has no children(won't have right child due to bottom level left-right fill order)
    return;
  if((lChildIdx<=count-1)&&(rChildIdx<=count-1)){ //case of node having 2 children
      if(array[rChildIdx].priority<=array[lChildIdx].priority){ //if right child smallest
	if(array[rChildIdx].priority<=array[nodeIdx].priority){ //if smaller than parent
	  swapNodes(nodeIdx,rChildIdx);
	  orderDownward(rChildIdx);//recursive decomp
	}
      }
  }
  if(array[lChildIdx].priority<=array[nodeIdx].priority){ //check if left child in bounds and smaller than parent
    swapNodes(nodeIdx,lChildIdx); //swap	  
    orderDownward(lChildIdx);//recursive decomp
  }
}


string PriorityQueue::peek() {  
  if(count==0)
    error("peek: queue is empty");    
  return array[0].value;  
}

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
