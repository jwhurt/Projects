/***************************************
File:  Tinv.h 
This file defines the interface for the Tinv class, which implements the tee shirt inventory system.  
This file also defines the tee_record, which represents an individual tee shirt item in inventory.
The methods of TINV initialize and manipulate the data structure Tee_DB, which is an array of tee_records.
*/

#include <string.h>
using namespace std;

#ifndef TINV_H
#define TINV_H

const int SIZE = 30;		//constant to define max number of inventory records

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
 *Constructor: TINV
 *Usage TINV tdb;
 *---------------------------
 *Creates a new inventory system that can hold tee_records, initializes the system with tee_records from external data file "TeeShirt_Records.txt"
 */
  TINV();		       


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
 *Method: print_All_Records
 *Usage: tdb.print_All_Records(os);
 *------------------------------
 *inserts all records in inventory into stream os
 *precondition:  if os is a file output stream, then os has already been connected to the output file
 *postcondition:  all records in the inventory system are inserted into stream os
 */
  void print_All_Records(ostream &os);


/*
 *Method: close_DB
 *Usage: tdb.close_DB();
 *------------------------------
 *opens output file "TeeShirt_Records_New.txt", writes all records in inventory to that file
 *postcondition:  if output file already exists, will overwrite old data with new data.  If file does not exist
 *will create new file with inventory data
 */
  void close_DB();


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


 private:
  tee_record Tee_DB[SIZE]; //array of type tee_record; represents the tee shirt inventory
  int count;  //variable to keep track of number of tee_records in the array; represents current inventory size
};

#endif
