/*Tinv.cpp:  Implementation file for class TINV, tee shirt inventory system*/

/*Preprocessor directives*/
#include <iostream>	//std io library
#include <string>	//library for string manip
#include <fstream>	//library for file i/o
#include "Tinv.h"	//statement to include header file that contains these function definitions
#include "safeio.h"     //collection of fault-tolerant I/O functions to ease user and file I/O

using namespace std;

/*Function Definitions*/

/*constructor
 *precondition:  Tee_DB array is empty
 *postcondition:  The Tee_DB array is constructed with data from the external file "TeeShirt_Records.txt"
 */
TINV::TINV()
{
  int i=0;
  ifstream infile;	//declare input file stream
  infile.open("TeeShirt_Records.txt");	//open external file
  if(infile.fail()){
    cerr<< "Unable to open file.\n";
    exit(EXIT_FAILURE);
  }
  readFile(infile,Tee_DB);
  infile.close();	    //close input file
}

/*readFile: reads stream data into a data structure
 *parameters are pointer to input stream and pointer to array of records
 *function will read data from file into each element of list
 */
void TINV::readFile(istream &is,tee_record list[])
{  
  cout<<"Reading file 'TeeShirt_Records.txt'...\n";
  string line,name,priceStr,qtyStr; //declare 3 strings for the 3 data fields
  int i=0;  //index to iterate through array of records

  /*process data in file one line at a time;data in format Name<string> Price<double> Quantity<int>*/   
  while(getline(is,line)){
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
    /*assign data to record attributes at list[i], using functions in safeio.h to validate string data format */
    list[i].tee_name=name;  //name string is directly copied into tee_name
    list[i].price=stringToDouble(priceStr); //uses safeio.h function to convert string to double, if data corrupt error will be given
    list[i].quantity=stringToInteger(qtyStr); //convert quantity string to integer
    cout<<i+1<<". "<<list[i].tee_name<<" "<<list[i].price<<" "<<list[i].quantity<<endl;  //display each line read into record
    /*reset strings to empty, necessary to cause read to fail on empty line*/
    name="";
    priceStr="";
    qtyStr="";
    i++; //increment iterator
  }
  count=i;        //use count to track number of records	
}

/*menu(): function manages user interface;calls functions selected by user;continues until user quits*/
void TINV::menu()
{
  char menu_choice;      //variable for user input option
  cout << "\nWelcome to the Tee Shirts for Haiti Project!";
  cout << "\nYou are logged in to the Inventory Management System\n";
  string prompt="Enter selection>";
  /*Main loop to run menu; continues taking user input and calling database functions until user wants to quit session*/
  do
  {	
    /* display menu options */
    cout << "\nPlease select from the following menu:\n";
    cout << "\nA....Add a new item to inventory";
    cout << "\nE....Edit an item in inventory";
    cout << "\nD....Delete an item from inventory";
    cout << "\nS....Search for a record by name";
    cout << "\nP....Print a single record";
    cout << "\nI....Print all records in inventory";
    cout << "\nQ....Quit Session\n";
    menu_choice=getChar(prompt);	//get safe single char input representing menu choice
    menu_choice=tolower(menu_choice);
    switch(menu_choice)	//switch to control what function gets called based on user's menu choice
    {
    case 'a':	
      add_Record();		//function call to add record to inventory
      break;
    case 'e':	
      edit_Record();		//function call to edit record in inventory
      break;
    case 'd':	
      delete_Record();	//function call to Delete record in inventory
      break;
    case 's':
      searchName();  //search for a record by name
      break;
    case 'p':	
      print_Record();	//function call to print a single record in inventory to console
      break;
    case 'i':	
      print_All_Records();		//function call to print all records in inventory
      break;
    case 'q':	
      cout << "\nAn inventory report has been written to TeeShirt_Records_New.txt.\n";
      cout << "You are now logged out.\n";	//goodbye message after quitting
      output_Report();	//function call to write inventory report to external file
      break;
    default:	
      cout << "\nInvalid selection, please try again";	//error message if user selects incorrectly
      break;
    }
  }while(menu_choice!='q');	//continue to display menu until user quits	
}


/*Add_Record: adds new record to database (Tee_DB);gets user to enter information for new record
 *precondition:  array ready to accept new record, max size not yet exceeded
 *postcondition:  individual record has been added to database, count of records incremented
 */
void TINV::add_Record() 
{	
  string tee_name;
  if(count>=SIZE)		//will allow added record if number of records has not yet exceeded max capacity
      cout << "Sorry, current inventory at max capacity, please make another selection \n";
  else{        
    cout<<"Add new record"<<endl;
    Tee_DB[count].tee_name=getName();
    Tee_DB[count].price=getDouble("Enter unit price>");
    Tee_DB[count].quantity=getInteger("Enter inventory quantity>");
    cout << "\nNew record accepted\n";
    count++;
  }
}

/*wrapper function for search, gets user to input name to search for*/
void TINV::searchName()
{
  int index;
  if((index=search(getName()))==-1)
    cout<<"Name not in inventory.";
  else
    print(index);  
}

string TINV::getName()
{
  string name;
  cout<< "Please enter record name>";
  getline(cin,name);	
  return name;
}

/*Search: searches list of records by name, returns location in list to calling function */
int TINV::search(string name)
{
  for(int i=0;i<count;i++){
    if(Tee_DB[i].tee_name==name)
      return i;
  }
  return -1; //if not found
}

/*Print_All_Records-prints all records in database to console
 *precondition: the constructor function will have filled the tee shirt array
 *postcondition:  this function will print the array records to the screen 
 */
void TINV::print_All_Records(){		
  printHeader();
  for(int i=0;i<count;i++){	    
    print(i);
  }
  return;
}

void TINV::printHeader()
{
  cout<<"Tee Name  "<< "  Price  "<< "  Qty in Stock" << "\n";
}

/*prints record attributes on single line to terminal*/
void TINV::print(int i)
{
  cout<<Tee_DB[i].tee_name<<"        "<<Tee_DB[i].price<<"        "<<Tee_DB[i].quantity<<endl;
}


/*function that prints current inventory to external file
 *precondition: The user indicates they want to quit
 *postcondition: The data from the Tee_DB is printed to external file
 */
void TINV::output_Report()	
{	
	ofstream fout;		//declare output stream
	fout.open("TeeShirt_Records_New.txt");	//open output file, connect to output object
	if(fout.fail())
	{
	cout << "Output file open failed.\n";
	exit(1);
	}
	for(int i=0;i<count;i++){	//loop to print entire contents of array 
	  fout<<Tee_DB[i].tee_name<<" "<<Tee_DB[i].price<<" "<<Tee_DB[i].quantity<<endl;
	}
	fout.close();
	return;
}

/*function that allows user to edit a record
 *precondition:  A record exists for the user to change, user selects  menu correctly
 *postcondition:  The user has changed a record field
 */
void TINV::edit_Record()	
{	
  int fieldnum;	//variable to capture user selection for field to edit
  int index;
  if((index=search(getName()))==-1)  
    cout << "Invalid name.  Please try again.\n";
  else{
    printHeader();
    print(index);
    cout << "\nSelect record field you would like to change\n";	//asks user to select field
    cout << "1. Tee Name\n";
    cout << "2. Price\n";
    cout << "3. Quantity in Stock\n";
    fieldnum=getInteger("Enter field>");
    if(fieldnum>3||fieldnum<1)	//range check
      cout << "Invalid field number.";
    else if(fieldnum==1){		//allows user to change name
	cout << "Enter new Teeshirt name>";
	getline(cin,Tee_DB[index].tee_name);
    }
    else if(fieldnum==2)	//lets user change price      
      Tee_DB[index].price=getDouble("Enter new Teeshirt price>");
    else
      Tee_DB[index].quantity=getInteger("Enter new inventory quantity>");
     cout << "Record updated.\n";
  }
}

/* wrapper function to print record by first searching for name*/
void TINV::print_Record()  
{	
  int index;
  if((index=search(getName()))==-1)  
    cout << "Invalid name.  Please try again.\n";
  else{
    printHeader();
    print(index);
  }
}  

/*Delete_Record-deletes a single record by name
 *delete will copy the last record into the space deleted record formerly occupied
 *count of records is decremented by 1.  if no record by that name is found, nothing is deleted
 */
void TINV::delete_Record() 
{	
  int index;
  if((index=search(getName()))==-1)
    cout << "Invalid name.  Please try again.\n";
  else{
    Tee_DB[index].tee_name=Tee_DB[count-1].tee_name;
    Tee_DB[index].price=Tee_DB[count-1].price;
    Tee_DB[index].quantity=Tee_DB[count-1].quantity;
    count--;
    cout << "Record deleted. \n";
  }
}
