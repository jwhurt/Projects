/*Tinv.cpp:  Implementation file for class TINV, tee shirt inventory system*/

/*Preprocessor directives*/
#include <iostream>	//std io library
#include <string>	//library for string manip
#include <fstream>	//library for file i/o
#include "Tinv.h"	//statement to include header file that contains these function definitions
#include "safeio.h"     //collection of fault-tolerant I/O functions to ease user and file I/O

using namespace std;

/*Function Definitions*/

/*
 *Implementation notes: constructor
 *------------------------------
 *Per assignment instructions, constructor initializes the Tee_DB array of tee_records using data file "TeeShirt_Records.txt"
 *Opens file using input file stream and reads the tee_record parameters line by line, calling the insert method with those parameters 
 *after each line is read
 *Postcondition:  The Tee_DB array will have at most SIZE tee_records initialized to the values found in the file "TeeShirt_Records.txt"
 */

TINV::TINV()
{
  count=0;
  ifstream infile;	//declare input file stream
  string line,name,priceStr,qtyStr; //declare 3 strings for the 3 data fields
  infile.open("TeeShirt_Records.txt");	//open external file
  if(infile.fail()){
    cerr<< "Unable to open file.\n";
    exit(EXIT_FAILURE);
  }
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
    insert(name,stringToDouble(priceStr),stringToInteger(qtyStr)); //call insert with correct parameter types
  }
  infile.close();
}


/*
 *Implementation notes: insert
 *------------------------------
 *precondition:  array count<SIZE, name, price, qty are correct types passed by client program
 *postcondition: if count<SIZE,record at index of current count has fields assigned to name, price, qty; count incremented
 *   if count>=SIZE, insert does nothing
 */
void TINV::insert(string name,double price, int qty){
  if(!is_Full()){
    Tee_DB[count].tee_name=name;
    Tee_DB[count].price=price;
    Tee_DB[count].quantity=qty;    
    count++;
  }
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
 *Implementation notes: print_All_Records
 *------------------------------
 *This method iterates over the array of records, inserting fields of each record into stream os;
 *uses print_Record as helper method
 */
void TINV::print_All_Records(ostream &os){		
  for(int i=0;i<count;i++){	    
    print_Record(os,i);
  }
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
 *Implementation notes: close_DB
 *------------------------------
 *inserts all records in inventory into file "TeeShirt_Records_New.txt"
 *passes output file stream to method print_All_Records
 */
void TINV::close_DB()
{
  ofstream os;
  os.open("TeeShirt_Records_New.txt");
  if(os.fail()){
    cerr<< "Unable to open file.\n";
    exit(EXIT_FAILURE);
  }
  print_All_Records(os);
  os.close();
}


/*
 *Method: is_Full()
 *------------------------------
 *returns true if inventory is full and false otherwise
 */
bool TINV::is_Full(){
  return(count==SIZE);
}


/*
 *Method: is_Empty()
 *------------------------------
 *returns true if inventory is empty and false otherwise
 */
bool TINV::is_Empty(){
  return(count==0);
}
