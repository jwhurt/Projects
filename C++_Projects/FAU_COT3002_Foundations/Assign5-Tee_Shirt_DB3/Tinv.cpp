/*
 *File: Tinv.cpp
 *This file implements the TINV class, which represents the tee shirt inventory system
 *This implementation uses a linked list as the underlying representation for the inventory
 */

/*Preprocessor directives*/
#include <iostream>	//std io library
#include <string>	//library for string manip
#include <fstream>	//library for file i/o
#include "Tinv.h"	//statement to include header file that contains these function definitions
#include "safeio.h"     //collection of fault-tolerant I/O functions to ease user and file I/O

using namespace std;

/*Function Definitions*/

/*
 *Implementation notes: default constructor
 *------------------------------
 *The linked list is implemented with a head dummy cell and a pointer to the last record.
 *The constructor sets pointers Tee_DB to an empty tee_record which acts as head dummy cell, and the pointer tail
 *will initially point to this cell as well. New records are added to the end of the list and the tail pointer is updated.  
 *After the constructor initializes the pointers, (and the member variables count and capacity) it calls
 *private helper method initializeInventory to use data from file to create the initial linked list.
 */
TINV::TINV()
{
  Tee_DB=new tee_record; 
  Tee_DB->next=NULL;
  tail=Tee_DB;
  count=0;
  initializeInventory("TeeShirt_Records.txt");
}

/*
 *Implementation notes: Copy Constructor
 *------------------------------
 *copy constructor, used when an object is initialized from an existing source object of the same class.
 *Implemented using deepCopy method which copies the member variables and list of records of the source object
 */
TINV::TINV(const TINV &src){
  deepCopy(src);
}

/*
 *Implementation notes: Destructor
 *------------------------------
 *destructor is called when function that created TINV object goes out of scope; heap memory used by the out of scope object is reclaimed
 */
TINV::~TINV(){
  deleteRestOfList(Tee_DB);
}

/*
 *Implementation notes: operator=
 *------------------------------
 *overloaded assignment operator first checks if the pointers &src and this are equal(&src is a pointer); 
 *if so we don't want to delete the list of the destination object(object pointed to by this) before we call deepCopy.  The purpose of 
 *returning TINV & is that c++ is defined to return the lhs of the result of the assignment operation; in this case the lhs is an object, 
 *so we dereference the this pointer in order to return the original object
 */
TINV & TINV::operator=(const TINV &src){
  if(this!=&src){  //this is a pointer to current object, &src is address of object to be copied; need to make sure they're not same
    deleteRestOfList(Tee_DB);
    deepCopy(src);
  }
  return *this; //the assignment operator returns the object on the LHS, since this is a pointer to current object, we dereference to get the object itself
}

/*
 *Implementation notes: deleteRestOfList
 *------------------------------
 *Recursive private helper method that deletes linked list from node pointed to by tPtr to end of list; used by destructor and 
 *overloaded assignment operator
 */
void TINV::deleteRestOfList(tee_record *tPtr){
  if(tPtr!=NULL){
    deleteRestOfList(tPtr->next);
    delete tPtr;
  }
}

/*
 *Implementation notes: operator<<
 *------------------------------
 *overloaded insertion operator is a friend function and does not use the scope resolution operator syntax.  
 *the << operator is a binary operator; with a friend function both operands are passed as arguments
 *e.g.  cout<<tdb; cout is the ostream object and tdb is the TINV object.  C++ defines the result of an << expression
 *to be the stream, and since a stream cannot be copied the overloaded function must return a reference to the stream.
 *Important to declare this function as a friend in the class definition in TINV.h in order to have access to private member count
 */
ostream& operator<<(ostream& os, const TINV& tinv){  
  os<<"Tee Name  "<<"    Price  "<<"  Qty in Stock\n";
  tee_record *cellPtr=tinv.Tee_DB->next;  //declare temporary pointer to iterate over records of object to be printed
  while(cellPtr!=NULL){
    os<<"  "<<cellPtr->tee_name<<"        "<<cellPtr->price<<"        "<<cellPtr->quantity<<endl;
    cellPtr=cellPtr->next;
  }
  return os;
}

/*
 *Implementation notes: Operator +
 *------------------------------
 *Usage: Tinv a,b;
 *        a+b;
 *The overloaded + operator is defined as a method within the TINV class.  In this style of overloading a binary operator 
 *the left operand is the receiving object and the right operand is passed as a parameter.
 *The function will iterate over the list of object b, copying the elements in order to the end of object a's list.
 *If object a has elements p,q,r,s in its list, and passed object b has x,y,z, then after the + operation
 *a will have p,q,r,s,x,y,z and b will still have x,y,z.
 */

void TINV::operator+(const TINV &b){
  tee_record *srcPtr=b.Tee_DB->next;
  while(srcPtr!=NULL){
    tail->next=new tee_record;
    tail=tail->next;    
    *tail=*srcPtr;
    tail->next=NULL;
    count++;
    srcPtr=srcPtr->next;
  }    		  
}

/*
 *Implementation notes: deepCopy
 *------------------------------
 *Copies the member variables and linked list of the source object into the current object; helper method to overloaded= and 
 *copy constructor.  The current object will have an empty list when this method called, because if called by copy constructor, the current
 *object is being instantiated for first time; if  called by overloaded assignment operator, the current object list is first deleted by that 
 *method, so there is no need to free up heap memory of current object.
 *Precondition:  The src object will have at least the head dummy cell, since TINV object is constructed with dummy cell and there should be no way 
 *client can delete head dummy cell.
 */
void TINV::deepCopy(const TINV &src){    
  Tee_DB=new tee_record;  //initialize current object list
  tail=Tee_DB;
  tee_record *cpyPtr=src.Tee_DB;  //cpyPtr iterates over the linked list in the src object
  *tail=*cpyPtr;
  while(cpyPtr->next!=NULL){    
    cpyPtr=cpyPtr->next;  //advance the copy pointer in the src object linked list
    tail->next=new tee_record;  //create new node, link the last node's pointer to this new node
    tail=tail->next;  //advance to next node
    *tail=*cpyPtr;
  }
  count=src.count;
}

/*
 *Implementation notes: initializeInventory
 *------------------------------
 *helper method for constructor; opens file "TeeShirt_Records_New.txt" using input file stream and reads the tee_record parameters line by line
 */
void TINV::initializeInventory(string fileName){
  ifstream infile;	//declare input file stream
  string line; //string to process line-by-line file input
  string name,priceStr,qtyStr; //declare 3 strings for the 3 data fields
  infile.open(fileName);	//open external file
  if(infile.fail()){
    cerr<< "Unable to open file.\n";
    exit(EXIT_FAILURE);
  }
  /*process data in file one line at a time;data in format Name<string> Price<double> Quantity<int>*/   
  while(getline(infile,line)){
    istringstream stream(line);  //declare stream object that can use >> operator on line
    stream>>name>>priceStr>>qtyStr;  //read first 3 fields into strings
    //then read past trailing whitespace, if any, which allows for spaces at end of each data line
    if(!stream.eof())
      stream>>ws;
    /* if the stream is not at end of line after reading 3 fields and trailing whitespace(if any) there is data format error, end program*/
    if(!stream.eof()){
      cerr<<"Illegal file format"<<endl;
      exit(EXIT_FAILURE);
    }
    insert(name,stringToDouble(priceStr),stringToInteger(qtyStr));
  }
  infile.close();  
}

/*
 *Implementation notes: insert
 *------------------------------
 *Insert function inserts a new tee_record at the end of the linked list whose first node is a dummy cell pointed to by Tee_DB.
 *Precondition: tail is pointing to a tee_record, since if tail=NULL, the tail->next command will crash program. 
 *Uses new operator to create new tee_record on heap, sets the pointer of the last tee_record in linked list Tee_DB to the newly created node;
 *sets the attributes of the new tee_record to the passed arguments.  
 */
void TINV::insert(string name,double price, int qty){
  tail->next=new tee_record;
  tail->next->tee_name=name;
  tail->next->price=price;
  tail->next->quantity=qty;      
  tail=tail->next;  //advance tail to next node
  tail->next=NULL;  //set the last node's ptr to null
  count++;
}

/*
 *Implementation notes: update_Record
 *method assigns the arguments price and quantity to the fields of tee_record pointed to and returns true;
 *if pointer is null does nothing and returns false
 */
bool TINV::update_Record(double newPrice, double newQty, tee_record *cellPtr){	
  if(cellPtr!=NULL){  
    cellPtr->price=newPrice;
    cellPtr->quantity=newQty;        
    return true;
  }
  else 
    return false;
}

/*
 *Implementation notes: remove
 *------------------------------
 *since this implementation uses a singly linked list, the remove method cannot use the results of the search method because search returns 
 *a pointer to the actual record with matching name; what is needed is a pointer to the previous record of the matching record so that the next 
 *pointer of that previous record can be pointed to the record after the one to be removed
 *If the last record is to be removed, the method will first move the tail pointer to the previous record; this is necessary to maintain a tail
 *which is necessary to add a record to the end of the list
 */
bool TINV::remove(string name){
  tee_record *cellPtr=Tee_DB;
  while(cellPtr->next!=NULL){
    if(cellPtr->next->tee_name==name){
      tee_record *killPtr=cellPtr->next;
      cellPtr->next=cellPtr->next->next;
      if(killPtr==tail)
	tail=cellPtr;
      delete killPtr;
      count--;
      return true;
    }
    cellPtr=cellPtr->next;
  }
  return false;
}

/*
 *Implementation notes: print_Record
 *------------------------------
 *Method will print the attributes of tee_record pointed to by pointer; if pointer is null does nothing.
 *This function takes a reference(because streams can't be copied) to ostream as an argument in order to use the same code to 
 *print to cout or to a file.  
 */
void TINV::print_Record(ostream &os,tee_record *cellPtr){	
  if(cellPtr!=NULL)
    os<<"  "<<cellPtr->tee_name<<"      "<<cellPtr->price<<"      "<<cellPtr->quantity<<endl;
}  

/*
 *Implementation notes: search
 *------------------------------
 *Iterates through Tee_DB linked list checking for record that has matching name; 
 *if found returns pointer to element with matching name, if not found returns point to null
 */
tee_record* TINV::search(string name){
  tee_record *cellPtr=Tee_DB;  
  while(cellPtr!=NULL && cellPtr->tee_name!=name){
    cellPtr=cellPtr->next;
  }
  return cellPtr;
}

/*
 *Method: is_Empty()
 *------------------------------
 *returns true if inventory is empty and false otherwise
 */
bool TINV::is_Empty(){
  return(count==0);
}

/*
 *Method: get_Capacity();
 *------------------------------
 *simple getter method that returns the current count of tee_records in the Tee_DB list
 */
int TINV::get_Count(){
  return count;
}

/*
 *Implementation notes: close_DB
 *------------------------------
 *inserts all records in inventory into file "TeeShirt_Records_New.txt"
 *passes output file stream to method print_All_Records
 */
void TINV::close_DB(const TINV& tinv)
{
  ofstream os;
  os.open("TeeShirt_Records_New.txt");
  if(os.fail()){
    cerr<< "Unable to open file.\n";
    exit(EXIT_FAILURE);
  }
  os<<tinv;  //overloaded insertion operator replaces print_All_Records(os);  
  os.close();
}
