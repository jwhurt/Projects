/***************************************
File:  Tinv.h 
This file defines the interface for the Tinv class, which implements the tee shirt inventory system.  
This file also defines the tee_record, which represents an individual tee shirt item in inventory.
The methods of TINV initialize and manipulate the data structure Tee_DB, which is a dynamic array of tee_records.
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
 *Constructor: TINV
 *Usage TINV tdb(size);
 *---------------------------
 *Creates a new inventory system with an initial capacity of size. Initializes the system with tee_records from external data file "TeeShirt_Records.txt"
 */
  TINV(int size);

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
 *If receiving object has elements p,q,r,s in its dynamic array, and passed object has x,y,z, then after the + operation
 *the receiving object will have p,q,r,s,x,y,z and the passed object x,y,z
 */
  void operator+(const TINV &b);

/*
 *Operator: *
 *Usage: Tinv a;
 *        a*n;
 *------------------------------
 *The overloaded * operator is defined as a method within the TINV class.   In this style of overloading a binary operator 
 *the left operand is the receiving object and the right operand is passed as a parameter.  
 *Precondition: n is an integer, and the operand a is an existing object of type TINV.
 *Postcondition: In the above example, the overloaded * operator will increase the dynamic array capacity of object a by factor of n.  
 */
  void operator*(int multiplier);

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
 *precondition:  count of records in array is less than SIZE; parameters name, price, qty are correct types passed by client program
 *postcondition: if count<SIZE,record at index of current count has fields assigned to name, price, qty; count incremented
 *   if count>=SIZE, insert does nothing
 */
  void insert(string name,double price, int qty);

/*
 *Method: update_Record
 *Usage: tdb.update_Record(newPrice, newQty, index);
 *------------------------------
 *method updates price and/or quantity fields for tee record at given index 
 *precondition:  the newPrice and newQty are of type double and int respectively, and the index is a non-negative integer less than current count
 *postcondition:  The price and/or qty of a tee_record at index in inventory is updated
 */
  void update_Record(double newPrice, double newQty, int index);	 

/*
 *Method: remove
 *Usage: tdb.remove(i);
 *------------------------------
 *Removes the element at index i from the inventory
 *precondition:  the argument index is a non-negative integer having a value less than current inventory count
 *postcondition: the record at index i is removed from inventory and count of records is decremented by 1.  
 */
  void remove(int index);	

/*
 *Method: search
 *Usage: tdb.search(name);
 *------------------------------
 *Searches inventory for record with tee_name
 *precondition:  function is passed a name of type string
 *postcondition: if found, search returns int corresponding to index where record is found; if not found, returns -1
 */
  int search(string name); //searches list of Tee_DB for record index by name

/*
 *Method: print_Record
 *Usage: tdb.print_Record(os,index);
 *------------------------------
 *inserts the record fields into stream os, where os is generally cout or file output stream
 *precondition:  if os is a file output stream, then os has already been connected to the output file; index is within bounds
 *postcondition: fields of record at index are inserted into stream os
 */
  void print_Record(ostream &os,int index);

/*
 *Method: is_Full()
 *Usage: tdb.is_Full();
 *------------------------------
 *returns true if inventory is full and false otherwise
 */
  bool is_Full();

/*
 *Method: is_Empty()
 *Usage: tdb.is_Empty();
 *------------------------------
 *returns true if inventory is empty and false otherwise
 */
  bool is_Empty();


/*
 *Method: get_Capacity()
 *Usage: tdb.get_Capacity();
 *------------------------------
 *returns maximum number of records that can be stored, which is not same as current count of records
 */
  int get_Capacity();


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
  static const int INITIAL_CAPACITY = 5;		//constant to define initial capacity of dynamic array
  tee_record *Tee_DB; //The array of tee_records is implemented as a dynamic array; *Tee_DB is pointer to initial element, of type tee_record
  int capacity;  //the maximum number of elements the array is capable of holding; this changes as the dynamic array expands as needed
  int count;  //variable to keep track of number of tee_records in the array; represents current inventory size
  void initializeInventory(string fileName); //helper method for constructor; copies data file into tee_record array
  void expandCapacity(int factor=2);  //expands array as more space is needed, default expansion factor = 2

/*
 *Method: deepCopy
 *this private method is necessary to override default shallow copy; creates independent copy of all data from source object to current object.
 *deepCopy is a helper method called by the copy constructor and the overridden assignment operator 
 */
  void deepCopy(const TINV &src);  
};

#endif
