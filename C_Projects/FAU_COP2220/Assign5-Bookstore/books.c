/*COP 2220 Programming in C
 *Assignment 5:  Bookstore Inventory Management System
 */

//Preprocessor Directives
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STRLEN 50    //constant for max length of string
#define MAXINVEN 20  //constant declaration for inventory array size

//Structure Definition-Book
typedef struct book{  
  char title[STRLEN];	//book title is string of max length 50
  char author[STRLEN];	//book author is string of max 50
  int date;		//date of publication
  int pages;		//number of pages in book
  double price;		//book price
  double rating;	//avg reader rating of book
}book;

//Function Prototypes
void Fillit(book L[]);			//function to fill first 5 array elements representing books
void Menu(char *menu_choice);		//function that displays inventory program menu
void DispArr(book List[],int inven);	//function for displaying contents of book array
void AddItem(book L[],int *inven);	//function letting user add to inventory
void OutputReport(book L[],int inven);	//function writing inventory report to .txt file
void ValueReport(book L[],int inven);	//function that calculates inventory value
void GetInfo(char title_to_change[],int *date_to_change);	//function that gets user to input book title and date
int  GetLoc(book L[],int inven,int date_to_change, char title_to_change[]);	//function that finds element location of user input
void Delete(book L[],int *inven,int loc);	//function to delete book from inventory 
void Edit(book L[],int loc);			//edit function allowing user to modify book components
void Clear(int *inven);				//function to remove entire book inventory
int getLine(char s[], int lim);                //reads entire input line from stdin, stopping at newline

int main()
{
  //Variable Declarations
  int inven=5;		        //number of books initially in inventory
  int date_to_change;		//variable used to capture user input to find book date of publication
  int loc;			//array index for matched element found by GetLoc function
  book List[MAXINVEN];          //structure array variable List representing the books in inventory
  char title_to_change[STRLEN]; //title of book in record to edit
  char menu_choice=' ';	        //variable capturing user selection from menu
  Fillit(List);			//function call to initiate 5 books in inventory
  printf("Welcome to Joe's University Bookstore!");
  printf("\nYou are logged in to the Inventory Management System\n");

  //Main loop to repeat until user wants to quit session
  do{	
    Menu(&menu_choice);	  //call menu function to display menu and get user's menu choice
    switch(menu_choice){  //switch to control what function gets called based on user's menu choice    
      case 'A': case 'a':	
        AddItem(List,&inven);  //call function to add book to inventory
        break;
      case 'C': case 'c':	
        Clear(&inven);	       //call function to clear inventory
        break;
      case 'D': case 'd':	
        GetInfo(title_to_change,&date_to_change);    //call to get title and date of book user wants to delete
        loc=GetLoc(List,inven,date_to_change,title_to_change);	//call to find index location of book user wants to delete
        if(loc!=-1)
  	  Delete(List,&inven,loc);  //call to delete book whose location was found by GetLoc
        break;
      case 'E': case 'e':	
        GetInfo(title_to_change,&date_to_change);	//call to get title and date of book user wants to edit
        loc=GetLoc(List,inven,date_to_change,title_to_change);	//call to function that finds index location of book user wants to edit
        if(loc!=-1)
  	  Edit(List,loc);    //call to Edit function
        break;
      case 'P': case 'p':	
        DispArr(List,inven);	//function call to display entire inventory
        break;
      case 'Q': case 'q':	
        printf("\nGoodbye!  You are now logged out.\n");  //goodbye message after quitting
        break;
      case 'S': case 's':	
        OutputReport(List,inven);	//call to save inventory report to text file
        printf("\nCurrent Inventory Report saved to report.txt");	
        break;
      case 'V': case 'v':	
        ValueReport(List,inven);  //call to function that calculates inventory value
        break;
      default:	
        printf("\ninvalid selection, please try again");  //error message if user selects incorrectly
        break;
    }
  }while(menu_choice!='q'&&menu_choice!='Q');  //continue to display menu until user quits
  return 0;
}

//Menu function that displays options for book inventory management system
void Menu (char *menu_choice)	//function uses pointer to modify menu_choice variable based on user selection
{
  printf("\n\nPlease select from the following menu:\n");
  printf("\nA....Add a new item to inventory");
  printf("\nD....Delete an item from inventory");
  printf("\nE....Edit an item in inventory");
  printf("\nP....Display all inventory records"); 
  printf("\nS....Create a current inventory report(saved to file)");
  printf("\nV....Calculate current inventory value");		
  printf("\nC....Clear all records");
  printf("\nQ....Quit\n");
  scanf(" %c",menu_choice);	//scan user input into menu_choice variable;
  getchar();	//remove that pesky carriage return to allow getLine to work properly
}

//Function Definitions
//Fillit:  fills structure array with initial 5 books in inventory
void Fillit(book L[])	//function takes book structure array as argument	
{	
  book a={"Calculus","George Simmons",1996,887,129.99,4.4};
  book b={"Problem Solving and Program Design in C","Hanley",2008,1130,89.99,3.1};
  book c={"Corporate Finance","Brealey Myers",2006,1028,145.95,4.2};
  book d={"Marketing Management","Philip Kotler",2000,718,120.99,3.8};
  book e={"Accounting","Libby",2001,875,115.49,4.1};
  L[0]=a;	//initialize array elements using overload method
  L[1]=b;
  L[2]=c;
  L[3]=d;
  L[4]=e;
}

//DispArr: display entire inventory of books on screen
void DispArr(book List[],int inven)	//takes book array and number of books in array as arguments
{	  
  int i=0;  //counter
  printf("\nCurrent Book Inventory:");
  if (inven==0)	
    printf("\nThere are currently no items in inventory.");
  for(i=0;i<inven;i++){  //loop for displaying book components until last element in array
    printf("\n\nTitle %d: %s",i+1,List[i].title);
    printf("\nAuthor: %s",List[i].author);
    printf("\nDate of Publication: %d",List[i].date);
    printf("\nNumber of Pages: %d",List[i].pages);
    printf("\nPrice: $%.2f",List[i].price);
    printf("\nAverage Reader Rating(0.0-5.0): %.1f",List[i].rating);
  }
}

//AddItem: prompts user to add new book to inventory
void AddItem(book L[],int *inven)  //takes book array and pointer to inventory size as arguments
{	
  printf("\nAdd new title: ");
  getLine(L[*inven].title,STRLEN);
  printf("Add new author: ");
  getLine(L[*inven].author,STRLEN);
  printf("Add new publication date: ");
  scanf("%d",&L[*inven].date);
  printf("Add new number of pages: ");
  scanf("%d",&L[*inven].pages);	
  printf("Add new item price: ");
  scanf("%lf",&L[*inven].price);
  printf("Enter average book rating (0.0-5.0): ");
  scanf("%lf",&L[*inven].rating);
  (*inven)++;	//increases number of books in inventory
  printf("\nNew item accepted");
  printf("\nCurrent items in inventory: %d",*inven);
}
//OutputReport: saves book inventory report to external text file
void OutputReport(book L[],int inven)	//takes structure array (book inventory) and inventory size
{
  int i=0;
  FILE *outptr;
  outptr=fopen("report.txt","w");  //tie to external file, write operation
  fprintf(outptr,"Joe's University Bookstore Inventory Report\n");
  for(i=0;i<inven;i++){	//loop that prints book components to .txt file
    fprintf(outptr,"\nTitle %d: %s",i+1,L[i].title);
    fprintf(outptr,"\nAuthor: %s",L[i].author);	
    fprintf(outptr,"\nDate of Publication: %d",L[i].date);
    fprintf(outptr,"\nPages: %d",L[i].pages);
    fprintf(outptr,"\nPrice: $%.2f",L[i].price);
    fprintf(outptr,"\nAverage Rating: %.1f\n",L[i].rating);
  }
  fclose(outptr);
}

//ValueReport: adds the prices of books in inventory, calculates average price/book
void ValueReport(book L[],int inven)
{	  
  int i;
  double inven_val=0;
  for(i=0;i<inven;i++)
    inven_val=inven_val+L[i].price;
  printf("\nInventory Value Report");
  printf("\n\nTotal Inventory Value:  $%.2lf",inven_val);
  printf("\nTotal Units in Inventory:  %d",inven);
  printf("\nAverage Unit Value ($/Book):  $%.2lf",inven_val/(double)inven);
}

//GetInfo:  get user to input the book title and date of publication for the book to be changed
void GetInfo(char title_to_change[],int *date_to_change)
{
  printf("\nPlease select the item from inventory");
  printf("\nEnter title (exact match!): ");
  getLine(title_to_change,STRLEN);
  printf("Enter date of publication: ");
  scanf("%d", date_to_change);
}

//GetLoc: tries to find match in inventory for book title and date input by user
int GetLoc(book L[],int inven,int date_to_change, char title_to_change[])
{
  int i=0;
  for(i=0;i<inven;i++){	
    if(L[i].date==date_to_change&&(strcmp(L[i].title,title_to_change))==0) 
      return i;
  }
  printf("\nMatch not found.  Please try again");
  return -1;
}

//Edit:  Function allowing user to edit components of an individual book in inventory
void Edit(book L[],int loc)
{	
  int editnum=0;
  printf("\nMatch found\n");
  do{	//loop that repeats edit menu until user exits    
    printf("\nSelect the parameter you would like to change[1-6]");  //function asks user which component they want to change
    printf("\n1.....Title: %s",L[loc].title);
    printf("\n2.....Author: %s",L[loc].author);	
    printf("\n3.....Date of Publication: %d",L[loc].date);
    printf("\n4.....Pages: %d",L[loc].pages);
    printf("\n5.....Price: %.2f",L[loc].price);
    printf("\n6.....Average Rating: %.1f",L[loc].rating);
    printf("\n7.....Return to main menu\n");
    scanf(" %d",&editnum);
    getchar();
    if(editnum==1){	//edit title
      printf("\nenter new title: ");
      getLine(L[loc].title,STRLEN);		
    }
    else if(editnum==2){	//edit author
      printf("\nenter new author: ");
      getLine(L[loc].author,STRLEN);
    }
    else if(editnum==3){	//edit date
      printf("\nenter new date of publication: ");
      scanf(" %d",&L[loc].date);
    }
    else if(editnum==4){	//edit number of pages
      printf("\nenter new number of pages: ");
      scanf(" %d",&L[loc].pages);
    }
    else if(editnum==5){	//edit book price
      printf("\nenter new price: ");
      scanf(" %lf",&L[loc].price);
    }
    else if(editnum==6){	//edit book rating
      printf("\nenter new rating: ");
      scanf(" %lf",&L[loc].rating);
    }
    else if(editnum>=1&&editnum<=6){
      printf("\nrecord modified\n");
    }
    else if(editnum==7){
    }
    else
      printf("invalid option");
  }while(editnum>=1&&editnum<=6);	//repeat until user enters number out of range
}

//Delete: deletes a book from inventory
void Delete(book L[],int *inven,int loc)
{	
  printf("\nmatch found, item deleted");
  (*inven)--;  //decreases inventory size by 1
  L[loc]=L[*inven];  //overwrites the location of the element to be deleted with the last element
}

//Clear: clear entire book inventory
void Clear(int *inven)
{	
  char clearsafety=' ';	 //safety function to verify
  printf("\nAre you sure you want to clear all records (y/n)?");
  scanf(" %c",&clearsafety);
  if(clearsafety=='Y'||clearsafety=='y'){    
      *inven=0;
      printf("\nRecords Cleared");
  }
  else
    printf("\nNo Records Cleared");
}	

/*getLine: reads an entire line up to and including '\n'
 *inserts all chars from line into string s, excluding '\n'.
 *inserts terminating char '\0' at end, returns line length
 */
int getLine(char s[], int lim)
{
  int c,i; 
  for (i=0;i<lim-1 &&(c=getchar())!=EOF && c!='\n';i++)
    s[i]=c;
  s[i]='\0';
  return i;
}
