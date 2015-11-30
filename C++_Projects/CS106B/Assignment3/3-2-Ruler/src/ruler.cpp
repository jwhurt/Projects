/* CS106B Assignment 3, problem 2:  Draw Ruler using recursion */

#include "gevents.h"
#include "gwindow.h"
#include <iostream>

using namespace std;

void DrawRuler(GWindow & gw,double x, double y, double w, double h);

int main(){
  GWindow gw;
  double width=gw.getWidth();
  double height=gw.getHeight();
  cout<<"window dimensions are height: "<<height<<" width: "<<width<<endl;
  double x1=width/4;
  double y1=height/2;
  DrawRuler(gw,x1,y1,width/2,height/8);  
  int exit;  //this is a hack to get the graphics window to stay open.  Ask for user input, close after any key hit followed by enter.
  cout<<"press any key to exit";
  cin>>exit;
  exitGraphics();
  return 0;
}

/*function draws ruler along bottom edge of rectangle with width w, height h,
starting at x,y, the coordinates for lower left corner 
*/
void DrawRuler(GWindow & gw,double x, double y, double w, double h){
  /*base case; stop drawing tick marks if height below some limit*/
  if(h<0.05)
    return;
  else{
    /*draw horizontal line along base of rectangle, and
      vertical line for center tick mark
    */
    gw.drawLine(x,y,x+w,y); //draw line along base of rectangle
    gw.drawLine(x+w/2,y,x+w/2,y-h); //draw center tick mark with same height as rectangle

    /*recursive decomposition; recur on left and right halves of ruler*/
    DrawRuler(gw,x,y,w/2,h/2);//left half
    DrawRuler(gw,x+w/2,y,w/2,h/2);//right half    
  }
}
