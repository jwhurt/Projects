/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
//#include "console.h"
#include "random.h"
using namespace std;

//function prototype for function that flips coin
void flipConsecutive(int &flipCount, int &numConsecRemaining);

int main() {
   // [TODO: fill in the code]
  cout<<"This program simulates flipping a fair coin until 3 consecutive heads. Begin!"<<endl<<endl;

  int flipCount=0;  //variable to count the number of flips, will be incremented with each flip
  int numConsecHeads=3; //variable to keep track of the number of heads in a row
  flipConsecutive(flipCount,numConsecHeads);  //call function
  cout<<endl<<"It took "<<flipCount<<" flips to get 3 consecutive heads."<<endl;
  return 0;
}

/*function to perform coin flipping trial
 *precondition: arguments are references to an integer to count coin flips (flipcount) and an integer to
 *countdown the number of consecutive head flips remaining.  
 *postcondition:  function ends when 0 headflips remain, the flipcount variable in main will have the total 
 *number of flips it took to achieve 3 consecutive heads
 */
void flipConsecutive(int &flipCount, int &numConsecRemaining){
  while(numConsecRemaining>0){  //loop to count down number of consecutive head flips remaining until goal achieved
    if(randomChance(0.50)){//uses randomChance function from Stanford Library; returns true 50%
      cout<<"heads"<<endl;
      numConsecRemaining--;  //decrement number of flips remaining
    }
    else{
      cout<<"tails"<<endl;  
      numConsecRemaining=3;  //if tail flipped, need to start count over at original value
    }
    flipCount++;  //increment count of the number of flips
  }
}
