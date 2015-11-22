/**
 * File: boggle.cpp
 * 2015 version
 * Implements the game of Boggle.
 */
 
#include <cctype>
#include <iostream>
using namespace std;

#include "simpio.h"
#include "gwindow.h"
#include "gboggle.h"
/* additional interfaces */
#include "grid.h"  //for data structure
#include "strlib.h"  //for string library such as toUpperCase function
#include "lexicon.h"  //used to verify words

const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;

const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

static void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*the following is from my previously working 2008 version*/
/*used to enumerate possible adjoining cubes*/
enum Direction {
  N=0,NE,E,SE,S,SW,W,NW
};

/*represents game cube, consisting of string of possible letters, and the active face up letter*/
struct cube {
  string letters;
  char face;
};

/*struct to encapsulate grid coordinate in terms of row,col*/
struct point {
  int row;
  int col;
};

/*function prototypes*/
Grid<cube> InitBoard(int row, int col);
void Shake(Grid<cube> &board);
void SwapCubes(Grid<cube> &board);
void FlipCubes(Grid<cube> &board);
int GetUserOption();
void EnterCustomCubes(Grid<cube> &board);
void HumanTurn(Grid<cube> &board, Lexicon &lex, Set<string> &enteredSoFar);
point GetAdjoiningPoint(int dir,point pt);
bool InPath(Vector<point> &path,point pt);
bool FindWord(Grid<cube> &board,Vector<point> &path,string word);
bool RecFindWord(Grid<cube> &board,Vector<point> &path,point pt,string word,int index);
bool InBounds(Grid<cube> &board,point pt);
void HighlightPath(Vector<point> path);
void MachineTurn(Grid<cube> &board, Lexicon &lex, Set<string> &setOfWords);
void RecMachineTurn(Grid<cube> &board, Lexicon &lex, Vector<point> path, Set<string> &setOfWords);
string MakeWord(Grid<cube> &board,Vector<point> path);
void PrintCubes(Grid<cube> &board);
void PrintPoint(point pt);
void PrintPoints(Vector<point> pts);


int main() {
  Grid<cube> board; //grid will be underlying data structure to represent board, elements at each grid coordinate are cube structs
  Lexicon lex("EnglishWords.dat"); //initialize english lexicon object, which validates words
  Set<string> wordsFound;  //this is set passed to word search functions to avoid duplicates 
  bool playOn=true;  //variable to continue main game play loop
  bool isFirstGame=true; //used to deliver appropriate messages
  int option; //value user inputs from option menu
   //double width=GetFullScreenWidth();  //used to set graphics window width
   //double height=GetFullScreenHeight();
   //SetWindowSize(width/2,height/2);   //set graphics window size

   
  GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);    
  /*big loop to play game and take user menu option */
  while(playOn){    
    initGBoggle(gw);  //InitGraphics();   
    if(isFirstGame){  //give instructions if it's the first game
      welcome();
      if (getYesOrNo("Do you need instructions?")) {
	giveInstructions();
      }
    }
    option=GetUserOption();  //call function to read menu and take user input
    switch (option){
    case 1:{
      board=InitBoard(4,4);
      drawBoard(board.numRows(),board.numCols());      
      Shake(board);
      break;
      }
    case 2:{
      board=InitBoard(4,4);
      drawBoard(board.numRows(),board.numCols());      
      EnterCustomCubes(board);
      break;
    }
    case 3:{
      board=InitBoard(5,5);
      drawBoard(board.numRows(),board.numCols());      
      Shake(board);
      break;
    }
    case 4:{
      board=InitBoard(5,5);
      drawBoard(board.numRows(),board.numCols());      
      EnterCustomCubes(board);
      break;
    }
    case 5:{
      playOn=false;
      cout<<endl<<"Goodbye.  ";
      if(!isFirstGame)
      	cout<<"Try to improve your vocabulary!";
      break;
    }
    default:
      cout<<"that is not a valid option";
      break;
    }

    /*if quit has not been selected, play game, human player goes first*/
    if(playOn){       
      HumanTurn(board,lex,wordsFound); //call function to manage Human turn at game
      cout<<endl<<"Hit enter when you are ready to watch my turn.";
      getLine();
      MachineTurn(board,lex,wordsFound); //call function to perform machine word search
      isFirstGame=false;
      cout<<endl<<"Hit enter to reset.";
      getLine();
    }

  } //end while loop for repeating game
   return 0;
} //end main


/*create board data structure, represented as grid of cubes.  Each cube object has
string of characters it can display on its face attribute*/
Grid<cube> InitBoard(int row, int col){
  Grid<cube> board(row,col);
  for(int r=0; r<board.numRows();r++){
    for(int c=0;c<board.numCols();c++){
      cube newCube; //create new cube struct
      if(row*col==16)
	newCube.letters=kStandardCubes[r*c];
      if(row*col==25)
	newCube.letters=kBigBoggleCubes[r*c];
      board.set(r,c,newCube);
    }
  }
  return board;
}



/*shaking the cubes consists of two separate operations:
1) randomly swapping cube positions on on the board, and 
2) flipping each individual cube.  These operations are implemented
by helper functions SwapCubes and FlipCubes
*/
void Shake(Grid<cube> &board){
  SwapCubes(board);
  FlipCubes(board);
}


/*function that randomly swaps cube positions.  Takes a board and for each 
coordinate, swaps the cube at that coordinate with a randomly chosen cube
at a greater coordinate*/
void SwapCubes(Grid<cube> &board){
  for(int r=0; r<board.numRows();r++){
    for(int c=0;c<board.numCols();c++){
      int randomRow=randomInteger(r,board.numRows()-1);
      int randomCol=randomInteger(r,board.numRows()-1);
      cube temp=board.get(r,c);  //temp holds the cube you are swapping out
      board.set(r,c,board.get(randomRow,randomCol));  //get random cube from greater position on board, place it in swap position
      board.set(randomRow,randomCol,temp);  //place cube removed from swap position into greater position
    }
  }
  return;
}

/*completes the shaking process, used in conjunction with SwapCubes */
void FlipCubes(Grid<cube> &board){
  for(int r=0; r<board.numRows();r++){
    for(int c=0;c<board.numCols();c++){
      cube cu=board.get(r,c);
      cu.face=cu.letters[randomInteger(0,5)];
      board.set(r,c,cu);
	//board(r,c).face=board(r,c).letters[RandomInteger(0,5)];  //assign face value of cube randomly
      labelCube(r,c,board.get(r,c).face);
    }
  }
  return;
}

  
/*function that displays menu and gets user's input; returns int*/
int GetUserOption(){
  int option;
  cout<<endl<<"Menu Options:"<<endl;
  cout<<"   1) Play the standard 4x4 board game (random cube values)"<<endl;
  cout<<"   2) Play 4x4 board with custom cube values"<<endl;
  cout<<"   3) Play with 5x5 board (random cube values)"<<endl;
  cout<<"   4) Play with 5x5 board with custom cube values"<<endl;
  cout<<"   5) Quit"<<endl;  
  while(true){
    cout<<endl<<"Please enter a game option (enter a number): ";
    option=getInteger();
    if( (option==1)||(option==2)||(option==3)||(option==4)||(option==5) )
      break;
  }
  return option;    
}


/*function is passed a board of cubes, then lets the user assign the cube face values
by typing in a string of the appropriate length; either 16 or 25 chars
*/
void EnterCustomCubes(Grid<cube> &board){
  string userString;
  while(true){
    cout<<"Enter a consecutive string of "<<board.numRows()*board.numCols()<< " characters representing the board configuration:  ";
    userString=toUpperCase(getLine());      	
    if(int(userString.length())==board.numRows()*board.numCols())
      break;
    else
      cout<<"Incorrect string length."<<endl;
  }      	
  for(int r=0; r<board.numRows();r++){
    for(int c=0;c<board.numCols();c++){
      cube userCube;
      userCube.face=userString[r*board.numCols()+c];
      board.set(r,c,userCube);
      labelCube(r,c,board.get(r,c).face);
    }
  }    
  return;
}


/*This function cycles through a loop asking the human player to enter a word.  It tests the word
to determine if it meets the folowing criteria:  1) the word must be long enough (>=4 chars)
2) The word must be a real word in the lexicon, and 3) the word is hasn't been used yet.
If the word is accepted, the word is passed to a display function (RecordWordForPlayer) in the 
gboggle.h graphics library which displays the word on the human's side of the window
*/

void HumanTurn(Grid<cube> &board, Lexicon &lex,Set<string> &enteredSoFar){
  string word;
  Vector<point> path; //path used to track points used to form word
  while(true){
    cout<<"Enter a word (or hit Enter to quit).  ";
    word=toUpperCase(getLine());
    if(word=="")
      break;
    /*perform initial screening of word before searching board*/
    if(word.length()>=4){ //initial test of word; is it long enough(>3 chars)
      if(lex.contains(word)){  //test if it is a word that exists in lexicon object
	if(!enteredSoFar.contains(word)){ //verify the word hasn't been entered yet
	  if(FindWord(board,path,word)){ //word meets basic criteria, now call function to search board for word	  
	    HighlightPath(path);
	    recordWordForPlayer(word,HUMAN);
	    enteredSoFar.add(word);
	  }
	  else  //word can't be found on the board using search 
	    cout<<"That word can't be formed on this board!"<<endl;
	}
	else  // word has been used before
	  cout<<"Duplicate word!  Try again!"<<endl;
      }
      else //word not valid
	cout<<"That is not a word! Try again!"<<endl;
    }
    else //word not long enough
      cout<<"Word is too short; must be at least 4 characters.  Try again!"<<endl;
  }//end while loop getting human word input
  return;
}



/*wrapper function for recursive function RecFindWord; iterates through all possible
start points on the board, passing each one to the recursive function to search for the word
*/
bool FindWord(Grid<cube> &board,Vector<point> &path,string word){
    point startPt;    
    bool found=false;
    for(int r=0;r<board.numRows();r++){      
      for(int c=0;c<board.numRows();c++){       
	path.clear();
	startPt.row=r;
	startPt.col=c;
	int index=0;
	if(RecFindWord(board,path,startPt,word,index)){	
	  found=true;
	  break;
	}
      }//end col looping
      if(found)
	break;
    }//end for loop
    return found;
}

/*function searches for word on the board using recursive backtracking technique*/
bool RecFindWord(Grid<cube> &board,Vector<point> &path,point pt,string word,int index){
  /*base case*/
  if(index==int(word.length()))
    return true;
  else if(board.get(pt.row,pt.col).face!=word[index]){
    return false;
  }
  /*recursive case*/
  else{
    path.add(pt);  //path tracks coordinates used for word formation
    index++;
    for(int i=0;i<=NW;i++){ //Recur on all valid adjacent points
      point nextPt=GetAdjoiningPoint((Direction)i,pt);
      if(InBounds(board,nextPt)){
	if(!InPath(path,nextPt)){
	  if(RecFindWord(board,path,nextPt,word,index) )
	    return(true);
	}
      }
    }        
    /*if no adjacent point leads to solution, backtrack*/
    path.remove(path.size()-1); //go back to previous point on board
    index--;  //go back to previous letter in word
    return false;
  } 
}

/* function checks if point is on board */
bool InBounds(Grid<cube> &board,point pt){
  return ((pt.row>=0)&&(pt.row<board.numRows())&&(pt.col>=0)&&(pt.col<board.numCols()));
}

/* function checks if point has already been visited in word formation */
bool InPath(Vector<point> &path,point pt){
  for(int i=0;i<path.size();i++){
    point used=path[i];
    if((pt.row==used.row)&&(pt.col==used.col)){
      return true;
    }
  }
  return false;
}

point GetAdjoiningPoint(int dir,point pt){
  switch (dir)
  {
  case 0:
    pt.row=pt.row-1;
    break;
  case 1://NE 
    pt.col=pt.col+1;
    pt.row=pt.row-1;
    break;
  case 2://E
    pt.col=pt.col+1;
    break;
  case 3: //SE
    pt.col=pt.col+1;
    pt.row=pt.row+1;
    break;
  case 4: //S
    pt.row=pt.row+1;
    break;
  case 5: //SW
    pt.col=pt.col-1;
    pt.row=pt.row+1;
    break;
  case 6://W
    pt.col=pt.col-1;
    break;
  case 7://NW
    pt.row=pt.row-1;
    pt.col=pt.col-1;
    break;
  default:
    cout<<"invalid direction";
  }
  return pt;
}


/*function uses the coordinates (points) contained in the path vector to highlight the
word corresponding to the points on the board
*/
void HighlightPath(Vector<point> path){
  for(int i=0;i<path.size();i++){
    highlightCube(path.get(i).row,path.get(i).col,true);
  }
  int count=0;
  while(true){ //delay loop; visual aid for the highlighting
    if(count>100000000)
      break;
    else
      count++;
  } 
  for(int i=0;i<path.size();i++)
    highlightCube(path.get(i).row,path.get(i).col,false);  
}

void MachineTurn(Grid<cube> &board, Lexicon &lex,Set<string> &setOfWords){
  Vector<point> path;
  point startPt;
  for(int r=0;r<board.numRows();r++){      
    for(int c=0;c<board.numRows();c++){       
      startPt.row=r;
      startPt.col=c;
      path.add(startPt);  //start with new startpoint
      RecMachineTurn(board,lex,path,setOfWords);
      path.clear();//remove prior startpoint path
    }
  } 

  setOfWords.clear(); //clear scoreboard
  return;
}

void RecMachineTurn(Grid<cube> &board, Lexicon &lex, Vector<point> path, Set<string> &setOfWords){
  string pathWord=MakeWord(board,path);
  if (!lex.containsPrefix(pathWord)){
    return;
  }
  else{
    if( (pathWord.length()>=4)&& (lex.contains(pathWord))&&(!setOfWords.contains(pathWord)) ){
      setOfWords.add(pathWord);
      HighlightPath(path);
      recordWordForPlayer(pathWord,COMPUTER);      
    }
    for(int i=0;i<=NW;i++){ //Recur on all valid adjacent points
      point nextPt=GetAdjoiningPoint((Direction)i,path.get(path.size()-1));
      if(InBounds(board,nextPt)){
	if(!InPath(path,nextPt)){
	  path.add(nextPt);
	  RecMachineTurn(board,lex,path,setOfWords);
	  path.remove(path.size()-1); //backtrack; recur on next adjoining point
	}
      }     
    }
  return;
  }
}

/*takes path and board as arguments, and returns the word that is formed from the 
  cube letters using the point sequence in the path vector*/
string MakeWord(Grid<cube> &board,Vector<point> path){
  string word="";
  for(int i=0;i<path.size();i++){
    point pt=path.get(i);    
    word=word+(board.get(pt.row,pt.col)).face;
  }
  return word;
}

/*Function used for debugging */
void PrintPoints(Vector<point> pts){
  if(pts.size()==0)
    cout<<"there are no points in the vector"<<endl;
  else{
  for(int i=0;i<pts.size();i++)
    PrintPoint(pts.get(i));
  }
}

/*Function used for debugging; used in combination with PrintPoints */
void PrintPoint(point pt){
  cout<<"("<<pt.row<<","<<pt.col<<")"<<endl;     
}
