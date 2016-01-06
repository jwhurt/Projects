/*********************************************
Name:  Joe Hurt					UserID:  jhurt1
ClassID:  COT3002				Instructor:  Dr. Bullard
Assignment 2: TeesForHaiti.cpp	Classtime:  3:30 T/R
Due Date:  3/17/10 at 10:30pm	Today's Date:  3/17/10

Description:  This program simulates a Tee shirt inventory system. The program performs the following steps:
 1.  Pulls data from an external file into the Tee shirt inventory management system.
 2.  Prompts the user to select an option from a menu.
 3.  Based on the user's selection, the program performs actions on the inventory.
 4.  Upon exiting the system, the program writes an updated inventory report to an external file.
*********************************************/

//preprocessor directives; include libraries for i/o, strings, and file i/o
#include <iostream>
#include <string>
#include <fstream>
#include "Tinv.h"	//include header file containing class declarations
#include "safeio.h"
using namespace std;

/*main() calls constructor to instantiate teeshirt database object of class TINV, a class declared in Tinv.h and defined in Tinv.cpp
 *will pull data from external file into working database, all database functionality and user interface contained in
 *tdb
 */
int main()
{		
  TINV tdb;    //instantiate database object 
  tdb.menu();  //run menu function until user quits
  return 0;
}
