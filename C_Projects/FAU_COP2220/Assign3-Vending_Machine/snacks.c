/*FAU COP2220 Programming in C
 *Assigment 3:  Vending Machine Simulation
 */

//Preprocessor directive
#include <stdio.h>  

//Function Prototypes
//prototype for function sets snack selection; reads snack menu and gets user input
void menu(char *selection);
//function that sets the item cost based on snack selected
void getCost(char selection,double *item_cost);
//function that increments payment until payment sufficient to cover item cost;
void getMoney(double *payment,double item_cost,char selection);
//function that prints payment menu and increments payment value; helper to getMoney
void coinMenu(double *payment);
//function compares payment balance with item cost; helper to getMoney
int checkMoney(double *payment,double item_cost);
//function that calculates change to be returned; sets change
void getChange(double *payment, double item_cost,double *change);
//function asks the user if they would like another snack or not
void quit(char *repeatOption);

int main(){
  //Variable declarations
  char selection; //variable for the snack selected
  char another; //variable to determine if another snack is wanted
  double payment,item_cost,change;  //variables to handle money amounts

  printf("Welcome to Vend-O-Matic\n");
  do{          //main do loop, will continue as long as user wants another snack.
    payment=0; //reset payment balance to 0    
    do{        //continue presenting menu until user enters valid selection
      menu(&selection); //call Menu function, passing address of selection variable
      getCost(selection, &item_cost); //call GetCost function, passing copy of selection and address to item cost
    }while(item_cost==0);//continue loop if item cost of 0 returned by GetCost.
    getMoney(&payment,item_cost,selection); //increment payment until sufficient
    printf("Dispensing selection \n");
    getChange(&payment, item_cost, &change);
    printf("Dispensing change $%3.2f \n",change);
    quit(&another);  //call quit function to determine if user wants another snack
  }while((another=='Y')||(another=='y'));
  printf("Thank you and enjoy!\n");
  return 0;
}

/*function checks if user wants another snack, parameter repeatOption is pointer to variable representing continuation*/
void quit(char *repeatOption){
    printf("Would you care to make another purchase(Y/N)?: ");
    scanf(" %c",repeatOption);
}

/*menu function displays snack menu and reads user input from terminal into selection variable
 *selection variable is passed by pointer
 */
void menu(char *selection){
  printf("Snacks Available\n");
  printf("P - Potato Chips\t$1.25\n");
  printf("S - Snickers Bar\t$1.35\n");
  printf("T - Pop Tart\t\t$0.95\n");
  printf("C - Cookies\t\t$1.50\n");
  printf("B - Brownie\t\t$1.75\n");
  printf("N - Nuts\t\t$1.40\n");
  printf("Please enter your snack selection: ");
  scanf(" %c",selection);  
}

/*function sets the item cost using the snack selection char
 *formal parameters are char representing menu selection and pointer to item cost variable
 *if selection argument not valid, item cost is set to 0
 */
void getCost(char selection,double *item_cost){
	if(selection=='P'||selection=='p')//if else-if conditions to determine snack cost
	  *item_cost=1.25;			//cost assigned using pointer to item_cost variable
	else if(selection=='S'||selection=='s')
	  *item_cost=1.35;
	else if(selection=='T'||selection=='t')
	  *item_cost=0.95;
	else if(selection=='C'||selection=='c')
	  *item_cost=1.50;
	else if(selection=='B'||selection=='b')
	  *item_cost=1.75;
	else if(selection=='N'||selection=='n')
	  *item_cost=1.40;
	else{
	  *item_cost=0;	//if an invalid selection made, item cost will be assigned 0, which will repeat Menu function call
	  printf("\nInvalid selection, please try again.\n\n");
	}
}

/*function increments payment until payment sufficient to cover item cost;
 *function uses helper function coinMenu to display payment options and get paymet from user,
 *and helper function checkMoney to compare payment balance with item cost
 */
void getMoney(double *payment,double item_cost,char selection){
  do{
    coinMenu(payment);
    printf("Price of item %c: $%3.2f \n",selection,item_cost);
    printf("Current balance: $%3.2f \n",*payment);
  }while(!checkMoney(payment,item_cost));
}

//function compares payment balance with item cost, returns 1 if sufficient payment made, 0 otherwise
int checkMoney(double *payment,double item_cost){
  return(*payment>=item_cost);
}

/*function sets the change amount. The payment has already been verified to be sufficient.
 *all that is needed is to set the change amount by performing a subtraction operation
 */
void getChange(double *payment, double item_cost,double *change){
  *change=*payment-item_cost;
}

/*function displays the payment amount options to user, gets user selection and increments payment balance
 *an invalid character entry results in a payment of 0
 */
void coinMenu(double *payment){
  char deposit;
  printf("Please deposit your money by selection: \n");
  printf("   1 - $5.00\n");
  printf("   2 - $1.00\n");
  printf("   3 - $0.25\n");
  printf("   4 - $0.10\n");
  printf("   5 - $0.05\n");
  printf("Deposit amount: ");
  scanf(" %c",&deposit);
  if(deposit=='1')
    *payment+=5.00;
  else if(deposit=='2')
    *payment+=1.00;
  else if(deposit=='3')
    *payment+=0.25;
  else if(deposit=='4')
    *payment+=0.10;
  else if(deposit=='5')
    *payment+=0.05;
  else
    *payment+=0;
}
