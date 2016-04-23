/*********************************************
 File: TeesForHaiti_linked_list.cpp
 Assignment 5: TeesForHaiti-Tee shirt inventory system, linked list version
 Description:  This program is the driver program that simulates a Tee shirt inventory system. The program performs the following steps:
 1.  Pulls data from an external file into the Tee shirt inventory management system.
 2.  Prompts the user to select an option from a menu.
 3.  Based on the user's selection, the program performs actions on the inventory.
 4.  Upon exiting the system, the program writes an updated inventory report to an external file.
*********************************************/

/*preprocessor directives; include libraries for i/o, strings, and file i/o */
#include <iostream>
#include <string>
#include <fstream>
#include "Tinv.h"	/*include header file containing class declarations*/
#include "safeio.h"    /*header file for more robust i/o */
using namespace std;

string getName();  //helper function for menu functions

int main()
{		
  TINV tdb;    //instantiate database object 
  char menu_choice;      //variable for user input option
  string name;     //represents tee_record attribute tee_name
  double price;    //represents tee_record attribute price
  int quantity;    //represents tee_record attribute quantity
  int indexFound;  //used to store index of record search
  int capacity;    //initial capacity value from user input; used in explicit value constructor
  int factor;      //multiplication factor used to expand inventory; factor=2 will double inventory
  string prompt="Enter selection>";
  cout << "\nWelcome to the Tee Shirts for Haiti Project!";
  cout << "\nYou are logged in to the Inventory Management System\n";
  do{	
    cout << "\nPlease select from the following menu:\n\n";
    cout << "A....Add a new item to inventory\n";
    cout << "U....Update an item in inventory\n";
    cout << "R....Remove an item from inventory\n";
    cout << "S....Search for a record by name\n";
    cout << "P....Print a single record\n";
    cout << "I....Print all records in inventory\n";
    cout << "N....Get the current number of records in the database\n";
    cout << "T....Test addition feature by adding a copy of this database to itself\n";
    cout << "Q....Quit Session\n";
    menu_choice=getChar(prompt);	//get safe single char input representing menu choice
    menu_choice=tolower(menu_choice);
    switch(menu_choice)	    //switch to control what function gets called based on user's menu choice
    {
    case 'a':	
      name=getName();
      price=getDouble("Enter unit price>");  //uses function from safeio
      quantity=getInteger("Enter inventory quantity>");  //uses function from safeio
      tdb.insert(name,price,quantity);
      cout<<"Record added";
      break;
    case 'u':	
      if(!tdb.is_Empty()){
	name=getName();
	price=getDouble("Enter new price>");  //uses function from safeio
	quantity=getInteger("Enter new quantity>");  //uses function from safeio
	if(tdb.update_Record(price,quantity,tdb.search(name)))
	  cout<<"Record updated";
	else
	  cout<<"Record not found";
      }
      else
	cout<<"Database empty, aborting update operation";
      break;
    case 'r':	
      if(!tdb.is_Empty()){
	if(tdb.remove(getName()))
	  cout<<"Record removed";
	else
	  cout<<"Record not found";
      }
      else
	cout<<"Database empty";      
      break;
    case 's':
      if(!tdb.is_Empty()){
      	if(tdb.search(getName())!=NULL)
	  cout<<"Record found";     //search for a record by name
      	else
	  cout<<"Record not found";
      }	  
      else
	cout<<"Database empty, aborting search";      
      break;
    case 'p':	
      if(!tdb.is_Empty())
	tdb.print_Record(cout,tdb.search(getName()));
      else
	cout<<"Database empty";
      break;
    case 'i':	
      if(!tdb.is_Empty())
	cout<<tdb;    //uses overloaded insertion operator
      else
	cout<<"Database empty, aborting print";      
      break;
    case 'n':	
      if(!tdb.is_Empty())
	cout<<tdb.get_Count();
      else
	cout<<"Database empty";      
      break;
    case 't':
      {
	TINV tdb2(tdb);  //instantiate new TINV object using existing object in copy constructor
	tdb+tdb2; 
      }
      break;
    case 'q':	
      tdb.close_DB(tdb);	//function call to write inventory report to external file
      cout << "\nAn inventory report has been written to TeeShirt_Records_New.txt.\n";
      cout << "You are now logged out.\n";	//goodbye message after quitting
      break;
    default:	
      cout << "\nInvalid selection, please try again";	//error message if user selects incorrectly
      break;      
    }
  }while(menu_choice!='q');	//continue to display menu until user quits	

  return 0;
}

/*
 *Method: getName
 *Usage: getName();
 *------------------------------
 *helper function prompts user to enter name for tee shirt record, uses getline() function in the <iostream> library to 
 *read console input into string name, returns string representing name
 */

string getName()
{
  string name;
  cout<< "Please enter record name>";
  getline(cin,name);	
  return name;
}
