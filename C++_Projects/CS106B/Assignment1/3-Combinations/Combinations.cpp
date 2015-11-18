/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
//#include "console.h"  //turn off console.h to avoid using stanford library and QtCreator; run in terminal instead
#include "simpio.h"
using namespace std;
int n_Choose_K(int n,int k);
void getInput(int &n, int &k);
void printPyramid();

int main() {
   // [TODO: fill in the code]
  cout<<"This program performs the combinations function C(n,k), also known as \"n choose k\". "<<endl;
  cout<<"The output of the function represents the number of possible ways that a subset of "<<endl;
  cout<<"k items can be chosen from a set of n items."<<endl;
  int n,k;
  getInput(n,k);
  cout<<"C("<<n<<","<<k<<")="<<n_Choose_K(n,k)<<endl<<endl;
  cout<<"Pascal's Triangle, first 10 rows: "<<endl<<endl;
  printPyramid();
  return 0;
}

/*function gets valid input from user to perform the n choose k function
 *precondition:  arguments are a reference to int n, the number of items in the set, and int k, the size of the subset
 *postcondition:  n and k have valid values to be used in the C(n,k) function
 */
void getInput(int &n, int &k){
  while(true){
     cout<<"Enter n, the number of items: ";
     cin>>n;
     if(n>=0){
       cout<<"Enter k, the number of items in the subset: ";
       cin>>k;
       if(k>=0&&k<=n)
	 break;  //valid input
       else
	 cout<<"k must be non-negative and not greater than n"<<endl;
     }
     else
       cout<<"n must be non-negative"<<endl;
  }
}
/*recursive implementation of n choose k function
 *precondition:  arguments n, k are both non-negative, with k<=n
 *postcondition:  result of n choose k calculation is returned to caller
 */
int n_Choose_K(int n, int k){
  if(n==k)
    return 1;
  else if (k==0)
    return 1;
  else
    return n_Choose_K(n-1,k-1)+n_Choose_K(n-1,k);	       
}


void printPyramid(){
  for(int n=0;n<=10;n++){
    for(int k=0;k<=n;k++)
      cout<<n_Choose_K(n,k)<<"  ";
    cout<<endl;
  }    
}
