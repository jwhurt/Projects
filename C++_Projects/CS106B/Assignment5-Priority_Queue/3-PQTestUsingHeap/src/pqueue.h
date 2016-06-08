/*
 * File: pqueue.h (heap version)
 * ------------------------------
 * This file exports the PriorityQueue class, a collection in which
 * values are processed in priority order.  The public section of the
 * class is common to all implementations of the queue, but the private
 * section is tailored to the heap-based implementation.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "error.h"

/*
 * Class: PriorityQueue
 * -----------------------
 * This class models a structure called a priority queue in which
 * values are processed in order of priority.  As in conventional
 * English usage, lower priority numbers correspond to higher effective
 * priorities, so that a priority 1 item takes precedence over a
 * priority 2 item.
 */

class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue pq;
 * ---------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any array storage associated with this priority queue.
 */

   ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size();

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

   bool isEmpty();

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  Lower priority
 * numbers correspond to higher priorities, which means that all
 * priority 1 elements are dequeued before any priority 2 elements.
 * If not specified, the priority is set to 1.
 */

   void enqueue(std::string value, double priority = 1);

/*
 * Method: dequeue
 * Usage: std::string first = pq.dequeue();
 * ------------------------------
 * Removes and returns the highest priority value.  If multiple
 * entries in the queue have the same priority, those values are
 * dequeued in the same order in which they were enqueued.
 */

   std::string dequeue();

/*
 * Method: peek
 * Usage: std::string first = pq.peek();
 * ---------------------------
 * Returns the value of highest priority in the queue, without
 * removing it.
 */

   std::string peek();

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, without
 * removing it.
 */

   double peekPriority();

/*
 * Method: copy constructor
 * ------------------------
 * The copy constructor makes it possible to pass a PriorityQueue by value.
 * Its signature follows a standard pattern for all copy constructors.
 */

   PriorityQueue(const PriorityQueue & src);

/*
 * Method: assignment operator
 * ---------------------------
 * The assignment operator makes it possible to assign a PriorityQueue.
 * Its signature follows a standard pattern for all assignment operators.
 */

   PriorityQueue & operator=(const PriorityQueue & src);

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

/* Type used for each heap entry, stores the value as a string and priority as double */
   struct ValuePriorityPair {
      std::string value;
      double priority;
   };

/* Constants */

   static const int INITIAL_CAPACITY = 10;

/* Instance variables */
/* The priority queue in this program is implemented using an array based structure 
 * called a heap, which simulates the operation of a partially ordered tree 
 */
   ValuePriorityPair *array;
   int count;
   int capacity;

/* Private methods */
   void insertAtLowestLevel(std::string value, double priority); //helper function to enqueue that fills bottom level first in left to right order
   void orderUpward(int nodeIdx); //function to maintain ordering property that each node has key less than or equal the key in its children
   void orderDownward(int nodeIdx); //function to maintain ordering property that smallest key in the tree is always root
   void swapNodes(int parentIdx, int childIdx);  //helper function to swap nodes into correct order
   void expandCapacity() { //dynamically allocates new array with twice the capacity as the prior array
      ValuePriorityPair *oldArray = array;
      capacity *= 2;
      array = new ValuePriorityPair[capacity];
      for (int i = 0; i < count; i++) {
         array[i] = oldArray[i];
      }
      delete[] oldArray;
   }

/*deepCopy is helper function to copy constructor and overloaded assignment operator;
 *allocates new data structure in dynamic memory for the current object and copies source object's data
 */
   void deepCopy(const PriorityQueue & src) {
      count = capacity = src.count;
      if (capacity < INITIAL_CAPACITY) capacity = INITIAL_CAPACITY;
      array = new ValuePriorityPair[capacity];
      for (int i = 0; i < count; i++) {
         array[i] = src.array[i];
      }
   }

};

#endif
