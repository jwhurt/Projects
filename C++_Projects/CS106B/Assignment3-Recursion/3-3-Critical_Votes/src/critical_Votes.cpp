/* Problem 3:  Counting Voting Block Critical Votes. 
 * A critical vote is one that changes the election outcome.
 * For this problem, you will count the number of situations in which a block's vote is critical.
 * Methodology: The voting system has N blocks. Take the target block and set it aside. Now consider the 
 * possible election outcomes using the remaining N-1 blocks. There are 2N-1 different possibilities; 
 * In each of those 2N-1 situations, consider adding in the target block's vote— will its choice of 
 * candidate force the win for that candidate? If so, then it's a critical vote.
 */

#include <string>
#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

/*function declarations*/
int CountCriticalVotes(Vector<int> & blocks, int blockIndex); //wrapper function
int CountCritVoteRec(Vector<int> blocks, int target, int sumA, int blocksTotal); //recursive funct
int SumVect(Vector<int> vect); //function to sum int vector

int main(){
  Vector<int> blocks;
  int n;
  cout<<"This program will count the number of voting possibilities where a given block has a critical vote, which is a vote that could change the election. ";
  cout<<"You will be asked to enter a series of numbers (no commas) to represent the number of electoral votes in each block.  ";
  cout<<"The program will then calculate the number of possible critical votes for each block.  ";
  cout<<"For example, if you enter 4 2 7 4, block 0 and 3, with 4 electoral votes, each have 2 critical votes.  ";
  cout<<"Block 1, with 2 electoral votes, surprisingly has the same voting power with 2 critical votes.  ";
  cout<<"Let's begin.  Enter 0 when you are finished entering numbers."<<endl<<endl;
  while(true){
    cout<<"Enter the number of votes in a block: ";
    cin>>n;
    if(n==0)
      break;
    blocks.add(n);
  }
  cout<<endl<<"The set of voting blocks you entered is: "<<endl;
  cout<<"{";
  for(int i=0;i<blocks.size();i++){
    if(i==blocks.size()-1)
      cout<<blocks[i];
    else
      cout<<blocks[i]<<", ";
  }
  cout<<"}"<<endl<<endl;
  cout<<"The table below summarizes the critical votes for each block you entered: "<<endl;
  cout<<endl<<"Block Index   Electoral Votes   Critical Votes"<<endl;
  for(int i=0;i<blocks.size();i++){
    cout<<"     "<<i<<"                "<<blocks[i]<<"                "<<CountCriticalVotes(blocks,i)<<endl;
  }
  return 0;
}

/* wrapper function, used to match specification */
/*function takes a vector representing voting blocks and the target block index. The function will return the number
of times the target block vote is critical in determining the outcome of the election.  The recursive helper function
will do the work.
*/
int CountCriticalVotes(Vector<int> & blocks, int blockIndex){
  Vector<int> copyBlk=blocks; //make deep copy of voting block vector for manipulation in recursive function
  int target=blocks[blockIndex];
  copyBlk.remove(blockIndex);
  int blocksTotal=SumVect(copyBlk);
  return CountCritVoteRec(copyBlk,target,0,blocksTotal);
}

int CountCritVoteRec(Vector<int> blocks, int target, int sumA, int blocksTotal){
  /*base case*/
  if (blocks.size()==0){
    int sumB=blocksTotal-sumA; //sumB is votes that went for candidate B for this particular subset
    if((sumA<sumB)&&(sumA+target>sumB))  //check for critical vote; if target block changes outcome for candidate with fewer votes
      return 1; 
    else if((sumA>sumB)&&(sumB+target>sumA))
      return 1;
    else //target block is not critical
      return 0;
  }
  /*recursive case*/
  else{
    int next=blocks[0];
    blocks.remove(0);
  /*combine solutions to subproblems*/
    return CountCritVoteRec(blocks,target,sumA+next,blocksTotal)+CountCritVoteRec(blocks,target,sumA,blocksTotal);
  }
}

int SumVect(Vector<int> vect){
  int sum=0;
  for(int i=0;i<vect.size();i++)
    sum+=vect[i];
  return sum;
}
