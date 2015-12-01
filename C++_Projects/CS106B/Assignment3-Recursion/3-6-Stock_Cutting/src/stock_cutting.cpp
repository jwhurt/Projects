/*  cs106b Assign 3, problem 6, Stock Cutting.
You are charged with buying the plumbing pipes for a construction project.  You are given
a list of the varying lengths of pipe needed.  Stock pipe is sold in one fixed length.  You
can divide each stock pipe in any way needed.  Your job is to figure out the minimum number of
stock pipes required to satisfy the list of requests in order to minimize waste and save money.
 */
#include "vector.h"
#include "console.h"
#include <iostream>

using namespace std;

void printVector(Vector<int> vec);
int CutStock(Vector<int> &requests, int stockLength);
void CutStockRec(Vector <int> req, int &stocklen, int left, int numPipes, int &minPipes);
void getNums(Vector <int> & list);

int main(){
  int stockLength;
  int minPipes;
  Vector<int> requests;  //vector will hold the list of requested pipe lengths to cut from the stock length
  cout<<"This program will determine the minimum number of fixed-length stock pipes needed to satisfy a list of cut pipe lengths.  "<<endl;
  cout<<"Enter the stock pipe length: ";
  cin>>stockLength;
  cout<<"Enter the required pipe lengths, one at a time.  Enter 0 when finished."<<endl;
  getNums(requests); //get list of requested pipe lengths
  cout<<"The set of lengths you entered is: "<<endl;
  printVector(requests);
  minPipes=CutStock(requests, stockLength);
  cout<<"Minimum number of pipes needed using stock length "<<stockLength<<":  "<<minPipes;  
  return 0;
}

/*wrapper function is given a vector of the lengths needed and the stock pipe length.  It returns the
  minimum number of stock pipes neeed to service all requests in the vector.  */
int CutStock(Vector<int> &requests, int stockLength){
  int minPipes=requests.size();  //init minPipes to number of requested lengths; this is the largest number of stock lengths possible
  int numPipes;
  if (minPipes==0)
    numPipes=0;
  else
    numPipes=1;
  int left=stockLength;
  CutStockRec(requests,stockLength,left,numPipes,minPipes); //call recursive function to try to improve upon minPipes
  return minPipes;
}

/* recursive function operates on shared variable minPipes, passes as reference */
void CutStockRec(Vector <int> req, int &stocklen, int left, int numPipes, int &minPipes){
  if (req.size()==0){
    //cout<<"arrived at base case"<<endl;
    if (numPipes<minPipes){
      minPipes=numPipes;
      //cout<<"new min pipes: "<<minPipes<<endl;
    }
    //cout<<"popping stack..."<<endl<<endl;
    return;
  }
  else{
    for (int i=0;i<req.size();i++){
      //cout<<"required: ";
      //printVector(req);     
      //cout<<", left: "<<left<<", numPipes: "<<numPipes;
      Vector<int> newReq=req;
      int cut=req[i];
      newReq.remove(i);
      int newLeft;
      if(cut>left){
	numPipes+=1;
	newLeft=stocklen-cut;
      }
      else{
	newLeft=left-cut;             
      }
      //cout<<", cut: "<<cut;
      if (numPipes<minPipes){	
	//cout<<endl<<"recur..."<<endl;
	CutStockRec(newReq,stocklen,newLeft,numPipes,minPipes);
      }
      /*else
	cout<<endl<<"backtracking; trying another option..."<<endl;
      */

    //cout<<"options complete for frame ";
      //printVector(req);
    //cout<<"popping stack..."<<endl;
    }
  } //end else
    return;
}
  

void printVector(Vector<int> vec){
  cout<<"{";
  for (int i=0;i<vec.size();i++){
    if(i==vec.size()-1)
      cout<<vec[i];
    else
      cout<<vec[i]<<", ";
  }
  cout<<"}"<<endl;
  return;
}

void getNums(Vector <int> & list){
  int n;
  while(true){
    cout<<"Enter a pipe length: ";
    cin>>n;
    if(n==0)
      break;
    list.add(n);
  }
return;
}
