/* Assignment 3, Problem 1:  Stair problem.  Write a recursive function Countways that takes a positive int for number of
stairs and returns the number of different ways to climb it using strides of 1 or 2 stairs at a time
 */
#include <string>
#include <iostream>

using namespace std;

int CountWays(int numStairs);

int main(){
  int numStairs;
  cout<<"This program will calculate the number of different ways to climb a flight of stairs of length n, ";
  cout<<"using strides of either 1 or 2 stairs at a time."<<endl;
  cout<<"For example, a flight of 3 stairs could be climbed 3 ways: One way using only single-stair strides, ";
  cout<<"another way taking a single stair followed by a double"<<endl;
  cout<<"step, and the third way taking a double step followed by a single step."<<endl;
  cout<<"Enter the number of steps in the stairway: ";
  cin>>numStairs;
  cout<<endl<<"The number of ways to climb a stairway of "<<numStairs<<" steps is "<<CountWays(numStairs)<<endl;  
  return 0;
}

int CountWays(int numStairs){
  if (numStairs==0)
    return 1;
  else if (numStairs==1)
    return 1;
  else //if number stairs is 2 or greater
      return (CountWays(numStairs-1))+(CountWays(numStairs-2));
}
