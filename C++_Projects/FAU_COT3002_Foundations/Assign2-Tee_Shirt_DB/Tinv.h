/*Tinv.h: Header file for Tinv.cpp */

#include <string.h>
using namespace std;

#ifndef TINV_H
#define TINV_H

const int SIZE = 30;		//constant to define max number of inventory records

/*class declaration for an individual teeshirt record*/
class tee_record			
{								
 public:
  string tee_name;	//record name
  double price;		//record price
  int quantity;		//record qty
};

/*class declaration for TINV, the teeshirt inventory system */
class TINV	
{
 public:
  TINV();		       //constructor function
  void menu();           //menu function handles all user interface tasks
  void add_Record();		//function to add additional teeshirt record
  void delete_Record();	//function to delete record
  void edit_Record();		//function to edit record
  void print_Record();	//function to display a single record
  void print_All_Records();	//function to print all inventory records to screen
  void output_Report();	//function to output record to external file
  void searchName();    //searches for record by name
 private:
  int search(string name); //searches list of Tee_DB for record index by name
  string getName();         //helper function to get name of record from user
  void print(int i);
  void printHeader();
  void readFile(istream &is,tee_record list[]);//helper function for constructor to read file data
  tee_record Tee_DB[SIZE]; //array for tee shirt records; represents the shirt inventory.  Private to prevent accidental changes
  int count;  //variable to keep track of records
};

#endif
