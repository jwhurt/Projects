/**********************************************
COT3002 Assignment 1

Description:  This program simulates the flight of a balloon.  The program performs the following steps:
 1.  Prompt the user for desired altitude and a number of time steps.
 2.  Cause the balloon to ascend to one-third of the specified altitude, then cruise for one-quarter
         of the time steps.
 3.  Repeat step 2 twice more (ascend one-third, cruise one-quarter, ascend one-third, cruise
        one-quarter).
 4.  Descend halfway to the ground, cruise for the remaining time steps, and then descend
         back to the ground.
 5.  After the first ballon flight, your program should ask the user if he/she would like to continue.
*********************************************/
#include <iostream>
#include <string>
#include "balloon.h"
using namespace std;

void flightSim(Balloon &balloon,double height, double time);

int main(){
  double height;  //altitude for balloon
  double time;  //minutes of flight
  string flyAgain;
  string y1("yes");//quoted strings are c-strings, we want c++ string class
  string y2("Yes");
  Balloon balloon;  //instantiate balloon object
  //user input loop
  while(true){
    cout<<"How high (meters) do you want your flight to be? ";
    cin>>height;
    cout<<"How long(in minutes) would you like your flight to be? ";
    cin>>time;
    flightSim(balloon,height,time); //call function to run simulation of balloon flight
    cout<<"Would you like to continue (enter 'yes' or 'no')? ";
    cin>>flyAgain;    
    if(flyAgain!=y1&&flyAgain!=y2){
      cout<<"Thank you for your business!"<<endl;
      break;
    }
  } 
  return 0;
}

/*function will run balloon flight
 *arguments are reference to balloon object, altitude (alt) of flight, duration in minutes (dur) of flight  
 *simulation will ascend 1/3 of altitue, cruise for 1/4 of time steps
 *repeat above 2 more times(for a total of 3 ascension steps)
 *descend 1/2 to ground, cruise for the remaining 1/4 time steps
 *descend all the way to ground, ending flight.
 */
void flightSim(Balloon &balloon,double alt, double dur){
  int step=alt/3;
  
  /*ascension phase */
  for(int i=1;i<=3;i++){
    balloon.Ascend(step*i);
    balloon.Cruise(dur/4);//each ascension is followed by cruise for 1/4 of total time
  }

  /*descension phase*/
  balloon.Descend(alt/2);
  balloon.Cruise(dur/4);
  balloon.Descend(0);  
  return;
}
