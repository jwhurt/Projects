/*
 *File: Tinv.cpp
 *This file implements the TINV class, which represents the tee shirt inventory system
 *This implementation uses a dynamic array as the underlying representation for the inventory
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
 *default constructor initializes member variables count and capacity; create dynamic array with an INITIAL_CAPACITY number of tee_records;
 *calls private helper method initializeInventory to open and read data file into dynamic array
 */
TINV::TINV()
{
  Tee_DB=new tee_record[INITIAL_CAPACITY];  //point to array of tee_records; compiler will allocate space for INITIAL_CAPACITY number of tee_records in heap memory
  capacity=INITIAL_CAPACITY;
  count=0;
  initializeInventory("TeeShirt_Records.txt");
}

/*
 *Implementation notes: constructor
 *------------------------------
 *this version of the constructor creates the dynamic array using the parameter size passed by client
 */
TINV::TINV(int size){
  Tee_DB=new tee_record[size];  //point to array of tee_records; compiler will allocate space for an INITIAL_CAPACITY number of tee_records in heap memory
  capacity=size;
  count=0;
  initializeInventory("TeeShirt_Records.txt");
}

/*
 *Implementation notes: Copy Constructor
 *------------------------------
 *copy constructor, used when an object is initialized from an existing source object of the same class.
 *Implemented using deepCopy method which copies the member variables and dynamic array of the source object
 */
TINV::TINV(const TINV &src){
  deepCopy(src);
}

/*
 *Implementation notes: Destructor
 *------------------------------
 *destructor is called when function that created TINV object goes out of scope; heap memory used by the out of scope object is reclaimed using
 *the delete[] command for dynamic arrays
 */
TINV::~TINV(){
  delete[] Tee_DB;
}

/*
 *Implementation notes: operator=
 *------------------------------
 *overloaded assignment operator first checks if the pointers &src and this are equal(&src is a pointer); 
 *if so we don't want to delete the array of the destination object(object pointed to by this) before we call deepCopy.  The purpose of 
 *returning TINV & is that c++ is defined to return the lhs of the result of the assignment operation; in this case the lhs is an object, 
 *so we dereference the this pointer in order to return the original object
 */
TINV & TINV::operator=(const TINV &src){
  if(this!=&src){  //this is a pointer to current object, &src is address of object to be copied; need to make sure they're not same
    delete[] Tee_DB;
    deepCopy(src);
  }
  return *this; //the assignment operator returns the object on the LHS, since this is a pointer to current object, we dereference to get the object itself
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
  for(int i=0;i<tinv.count;i++)	//loop to print entire contents of array 
    os<<"  "<<tinv.Tee_DB[i].tee_name<<"        "<<tinv.Tee_DB[i].price<<"        "<<tinv.Tee_DB[i].quantity<<endl;
  return os;
}

/*
 *Implementation notes: Operator +
 *------------------------------
 *Usage: Tinv a,b;
 *        a+b;
 *The overloaded + operator is defined as a method within the TINV class.  In this style of overloading a binary operator 
 *the left operand is the receiving object and the right operand is passed as a parameter.
 *The function will iterate over the array of object b, copying the elements in order to the end of the object a array.
 *If object a has elements p,q,r,s in its dynamic array, and passed object b has x,y,z, then after the + operation
 *a will have p,q,r,s,x,y,z and b will still have x,y,z.
 *The expandCapacity function of object a will be called as needed to grow a's dynamic array.
 */
void TINV::operator+(const TINV &b){
  for(int i=0;i<b.count;i++){
    if(count>=capacity)
      expandCapacity();
    Tee_DB[count]=b.Tee_DB[i];  //perform shallow copy of tee_record at index i of object b in a+b
    count++;
  }    		  
}

/*
 *Implementation notes: operator *
 *------------------------------
 *The * operator is implemented as a simple wrapper function that calls expandCapacity() with the multiplication factor as the argument
 */
void TINV::operator*(int multiplier){  
  expandCapacity(multiplier);
}

/*
 *Implementation notes: deepCopy
 *------------------------------
 *Copies the member variables and dynamic array of the source object into the current object
 *new dynamic array created with capacity equal to the count of the source object, function iterates through source array
 *coping elements to Tee_DB in same order; sets count and capacity of current object equal to source object
 */
void TINV::deepCopy(const TINV &src){
  Tee_DB=new tee_record[src.count];  //we only allocate as much space as necessary for new array
  for(int i=0;i<src.count;i++)
    Tee_DB[i]=src.Tee_DB[i];
  count=src.count;
  capacity=src.count;
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
 *if the array is full, this function will call expandCapacity() function to increase the size of the dynamic array
 */
void TINV::insert(string name,double price, int qty){
  if(is_Full())
    expandCapacity();
  Tee_DB[count].tee_name=name;
  Tee_DB[count].price=price;
  Tee_DB[count].quantity=qty;    
  count++;
}

/*
 *Implementation notes: expandCapacity
 *------------------------------
 *dynamically allocates more space for array; the default increase in size is double the capacity of the old tee_record array;
 *this method will allocate space in the heap for a new array of tee_records that is factor times larger than the old array,
 *it copies each tee_record element of the old array to the new array, deletes old array in order to free heap memory no longer in use
 */
void TINV::expandCapacity(int factor){  
  tee_record *oldArray=Tee_DB;  
  capacity*=factor;
  Tee_DB=new tee_record[capacity];
  for(int i=0;i<count;i++)
    Tee_DB[i]=oldArray[i];
  delete[] oldArray;
  cout<<"array expanded by factor of "<<factor<<endl;
}

/*
 *Implementation notes: update_Record
 *check if index is valid, index is non-negative value less than current count, since count = last array element index+1
 *if so, method assigns the price and quantity fields of record at Tee_DB[index] to argument values
 */
void TINV::update_Record(double newPrice, double newQty, int index){	
  if(index>=0 && index<count){  
    Tee_DB[index].price=newPrice;
    Tee_DB[index].quantity=newQty;        
  }
}

/*
 *Implementation notes: remove
 *------------------------------
 *first checks if index is in bounds; index is non-negative value less than current count, since count = last array element index+1
 *if index valid, remove copies the last index element into the index of the removed element; 
 *the order of the array is therefore changed by this operation.  
 */
void TINV::remove(int index){
  if( (index>=0)&&(index<count)){  
    Tee_DB[index]=Tee_DB[count-1];
    count--;
  }
}

/*
 *Implementation notes: print_Record
 *------------------------------
 *This function takes a reference(because streams can't be copied) to ostream as an argument in order to use the same code to 
 *print to cout or to a file
 */
void TINV::print_Record(ostream &os,int index)  
{	
  if(index>=0 && index<count)
    os<<Tee_DB[index].tee_name<<"      "<<Tee_DB[index].price<<"      "<<Tee_DB[index].quantity<<endl;
}  

/*
 *Implementation notes: search
 *------------------------------
 *Iterates through Tee_DB array checking for record that has matching name; 
 *if found returns index of element with matching name, if not found returns  -1
 */
int TINV::search(string name)
{
  for(int i=0;i<count;i++){
    if(Tee_DB[i].tee_name==name)
      return i;
  }
  return -1;
}

/*
 *Method: is_Full()
 *------------------------------
 *returns true if inventory is full and false otherwise
 */
bool TINV::is_Full(){
  return(count==capacity);
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
 *simple getter method that returns the number of tee_records reserved in heap memory for the Tee_DB dynamic array
 */
int TINV::get_Capacity(){
  return capacity;
}

/*
 *Method: get_Capacity();
 *------------------------------
 *simple getter method that returns the current count of tee_records in the Tee_DB dynamic array
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
