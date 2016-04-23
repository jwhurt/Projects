/***************************************
File:  Tinv.h 
This file defines the interface for the Tinv class, which implements the tee shirt inventory system.  
This file also defines the tee_record, which represents an individual tee shirt item in inventory.
***************************************/

#include <string.h>
using namespace std;

#ifndef TINV_H
#define TINV_H

/*class definition for an individual teeshirt record*/
class tee_record			
{								
 public:
  string tee_name;	//record name
  double price;		//record price
  int quantity;		//record qty
  tee_record *next;     //pointer to next tee_record in singly-linked list
};


/*class definition for TINV, the teeshirt inventory system */
class TINV	
{
 public:

/*
 *Default Constructor: TINV
 *Usage TINV tdb;
 *---------------------------
 *Creates a new inventory system that can hold tee_records, initializes the system with tee_records from external data file "TeeShirt_Records.txt"
 */
  TINV();		       

/*
 *Copy Constructor: TINV
 *Usage: TINV tdb2(tdb);  
 *---------------------------
 *Creates a new object (tdb2) that is initialized using an existing object (tdb) of the same class; 
 *The copy constructor is used when an object (tdb2) is initialized for the first time
 */
  TINV(const TINV &src);

/*
 *Operator: =
 *Usage: dest=src;
 *---------------------------
 *Precondition:  dest and src are both existing TINV objects
 *Postcondition:  src data is copied to dest using deep Copy method so that the two TINV objects are independent copies
 */
  TINV & operator=(const TINV &src);  


/*
 *Operator: <<
 *Usage: cout<<tdb; 
 *         os<<tdb;  //where os is type ostream
 *---------------------------
 *Overloaded insertion operator copies inventory data into output stream
 *Precondition:  if os is a file output stream, then os has already been connected to the output file;
 *Postcondition:  inventory data from left operand object is inserted into right operand stream object
 */
  friend ostream& operator<<(ostream& os, const TINV& tdb);

/*
 *Operator: +
 *Usage: Tinv a,b;
 *        a+b;
 *---------------------------
 *Overloaded addition operator;  adds inventory of one TINV object to another.  
 *In the above code example, operand a is the receiving object while b is passed as a parameter.
 *Precondition:  The left and right operands must be 2 different existing TINV objects
 *Postcondition:  The inventory of object b will be added to the end of object a inventory.  Object b will remain unchanged.
 *If receiving object has elements p,q,r,s in its list, and passed object has x,y,z, then after the + operation
 *the receiving object will have p,q,r,s,x,y,z and the passed object x,y,z
 */
  void operator+(const TINV &b);

/*
 *Destructor
 *Usage:  Called automatically when object of class TINV disappears
 *---------------------------
 *Frees the heap memory created by the object of class TINV
 */
  ~TINV();

/*
 *Method: insert
 *Usage: tdb.insert(tee_name,price,quantity_in_stock);
 *------------------------------
 *precondition:  Parameters name, price, qty are correct types
 *postcondition: New record added to inventory with fields assigned to name, price, qty; the count of records is incremented
 */
  void insert(string name,double price, int qty);

/*
 *Method: update_Record
 *Usage: tdb.update_Record(newPrice, newQty, *tee_record);
 *------------------------------
 *method updates price and/or quantity fields for tee record pointed to
 *precondition:  the newPrice and newQty are of type double and int respectively
 *postcondition:  returns true if the price and/or qty of the tee_record pointed to is updated, false if pointer is null
 */
  bool update_Record(double newPrice, double newQty, tee_record *cellPtr);	 

/*
 *Method: remove
 *Usage: tdb.remove(name);
 *------------------------------
 *Removes the record with matching name
 *precondition:  the argument name is a string
 *postcondition: the record with matching name is removed from inventory and count of records is decremented by 1.  
 */
  bool remove(string name);	

/*
 *Method: search
 *Usage: tee_record *cellPtr=tdb.search(name);
 *------------------------------
 *Searches inventory for record with tee_name
 *precondition:  function is passed a name of type string
 *postcondition: if found, search returns a tee_record pointer which points to the tee_record whose tee_name matches the name parameter
 */
  tee_record* search(string name); //searches list of Tee_DB for record index by name

/*
 *Method: print_Record
 *Usage: tdb.print_Record(os,index);
 *------------------------------
 *inserts the record fields into stream os, where os is generally cout or file output stream
 *precondition:  if os is a file output stream, then os has already been connected to the output file; index is within bounds
 *postcondition: fields of record pointed to by pointer are inserted into stream os
 */
  void print_Record(ostream &os,tee_record *cellPtr);

/*
 *Method: is_Empty()
 *Usage: tdb.is_Empty();
 *------------------------------
 *returns true if inventory is empty and false otherwise
 */
  bool is_Empty();


/*
 *Method: get_Count()
 *Usage: tdb.get_Count();
 *------------------------------
 *returns current number of records in system
 */
  int get_Count();

/*
 *Method: close_DB
 *Usage: tdb.close_DB(tdb);
 *------------------------------
 *opens output file "TeeShirt_Records_New.txt", writes all records from TINV object tdb to that file
 *postcondition:  if output file already exists, will overwrite old data with new data.  If file does not exist
 *will create new file with inventory data
 */
  void close_DB(const TINV& tdb);
 
 private:
  tee_record *Tee_DB; //*Tee_DB is pointer to the head dummy cell of the linked list
  tee_record *tail;  //pointer to the tail cell in the list; 
  int count;  //variable to keep track of number of tee_records, representing current inventory size
  void initializeInventory(string fileName); //helper method for constructor; copies data file into tee_record list
  void deleteRestOfList(tee_record *tPtr);  //private helper method that deletes linked list from node pointed to by tPtr to end of list

/*
 *Method: deepCopy
 *this private method is necessary to override default shallow copy; creates independent copy of all data from source object to current object.
 *deepCopy is a helper method called by the copy constructor and the overridden assignment operator 
 */
  void deepCopy(const TINV &src);  
};

#endif
