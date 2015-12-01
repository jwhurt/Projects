/*Assignment 3, problem 5:  A recursive puzzle.
 *You are given a puzzle consisting of a row of squares each containing an
 *integer.  The goal of the puzzle is to move the marker to the 0 at the far end
 *of the row. 
 *The project is to write a function bool Solvable(int start, Vector<int> & squares) 
 *that takes a starting position of the marker along with the vector of squares. 
 *The function should return true if it is possible to solve the puzzle from the starting configuration and false if it is impossible.
 */
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
using namespace std;

/*function prototypes*/
bool Solvable(int start, Vector<int> & squares);
bool SolvableRec(int start, Vector<int> & squares, Vector<int> & visited);
bool VectorContainsVal(int val, Vector<int> vec);

int main(){
  Vector<int> puzzle;
  int num;
  int start;
  cout<<"please enter the numbers for the row of squares puzzle"<<endl;
  bool sentinel=true;
  while(sentinel){
    cout<<"enter a positive number (0 for the last square): "<<endl;
    cin>>num;
    if(num==0)
      sentinel=false;
    puzzle.add(num);
  }
  while(true){
    cout<<"enter the start position index: ";
    cin>>start;
    if(start>=0 && start<=puzzle.size()-1)
      break;
    cout<<"please enter a valid index value";
  }    
  if(Solvable(start,puzzle) )
    cout<<"is solvable";
  else
    cout<<"not solvable";
  return 0;
}

/*Solvable takes a starting position of the marker along with the vector of squares. 
 *The function should return true if it is possible to solve the puzzle from the starting configuration and false if it is impossible.
 *this function is a wrapper function for the recursive function SolvableRec
 */
bool Solvable(int start, Vector<int> & squares){
  Vector<int> visited;
  visited.add(start);
  if(SolvableRec(start,squares,visited)   )
    return true;
  else
    return false;
}
/*recursive function that generates set of completions for given string input */
bool SolvableRec(int start, Vector<int> & squares, Vector<int> & visited){
  cout<<"start index: "<<start<<" ";
  /*base case */
  if(start==squares.size()-1)
    return true;
  /*try left path if possible*/  
  cout<<"from index "<<start<<"try left"<<endl;
  if( (start-squares[start]>=0)&&(!VectorContainsVal(start-squares[start],visited) ) ){
    cout<<"will move left"<<endl;
    visited.add(start-squares[start]);
    if( SolvableRec(start-squares[start],squares,visited))
      return true;
  }
  /*try right path */
  cout<<"from index "<<start<<" try right"<<endl;
  if( (start+squares[start]<squares.size() )&&(!VectorContainsVal(start+squares[start],visited) ) ){
    cout<<"will move right"<<endl;
    visited.add(start+squares[start]);
    if(SolvableRec(start+squares[start],squares,visited))
      return true;
  }
  cout<<"can't move, index "<<start<<" returning false"<<endl;
  return false;	       
}
bool VectorContainsVal(int val, Vector<int> vec){
  for(int i=0; i<vec.size();i++){
    if(val==vec[i])
      return true;
  }
  return false;
}
