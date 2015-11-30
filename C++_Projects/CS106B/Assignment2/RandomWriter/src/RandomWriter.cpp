/*
RandomWriter.cpp  Random writing and Markov models of language.
Write program to read source text, build an order k Markov model for it, and generate
random output that follows the frequency patterns of the model.

Program prompt the user for the name of a file to read for the source text and re-prompt as needed until you get a valid name.
Then ask the user for what order of Markov model to use (a number from 1 to 10). This will control what seed length you are working with.

Data Structure:  Map and Vector interface from the Stanford library are used to store the model information. The keys into the map are the possible seeds (e.g. if order is 2,
each key is a 2-character sequence found in the source text). The associated value is a vector of all the characters that follow that seed
in the source text. That vector can, and likely will, contain a lot of duplicate entries. Duplicates represent higher probability transitions from this Markov state.

Build the model by reading seeds from the input file.  For reading a file one character at a time,use the get member function for ifstream. For example, if file input is
"The quick brown fox jumped over the lazy dog" and the seed length were 3
the reader would build the following key->value pairs into the map:
'the'->{' ',' '}
'he '->{'q','l'}
'e q'->{'u'}
etc...

In order to find the seed that occurs the most frequently, use the vector length corresponding to that seed value.  In the above example, there is a tie between 'the' and 'he '.
Pick either in this case.  The program would start with this most frequent seed as the key, get a character from the corresponding vector for this seed in the map(such as ' ' in the example above), add it to the string. The seed would
be updated with the added character ('he ' in example), and the program would repeat the above process until no key value is found or the desired string length has been generated.
*/

#include <fstream>
#include<iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

void BuildMap(ifstream &in,Map<string,Vector<char> > &map, int len);
char pickRandomElement(Vector<char> vec);
void GenerateRandom(Map<string, Vector<char> > &map, int numChars);
int getMarkovOrder(int low, int high,string mesg);
string promptUserForFile(ifstream &in,string mesg);

int main(){
  ifstream in;
  Map<string,Vector<char> > map;
  int seedLen;
  int numChars;
  promptUserForFile(in,"Enter file to build random text from: ");
  seedLen=getMarkovOrder(1,10,"Enter a number for Markov model order (1-10): ");
  numChars=getInteger("Enter a number of characters to output: ");
  BuildMap(in,map,seedLen);  //this function does work of building the data structure.
  GenerateRandom(map,numChars);
  cout<<endl<<"program complete"<<endl;
  return 0;
}

/*proper way to prompt user for filename to open
 *precondition: ifstream object declared and passed as reference
 *postconditon: upon valid filename entry, stream object has opened file and ready to read file contents, filename returned
 */
string promptUserForFile(ifstream &in,string mesg){
  string fname;
  while(true){
    cout<<mesg;
    getline(cin,fname);  
    in.open(fname.c_str());  //attempt to open file, remember to convert to c style string
    if(!in.fail())// check fail status of stream; if success, then return filename
      return fname;
    in.clear();  //clear fail flag
    cout<<"file not found"<<endl;    
  }
}

/*this function gets a number from user for the order of Markov model*/
int getMarkovOrder(int low, int high,string mesg){
  int n;
  while(true){
    n=getInteger(mesg);
    if (low<=n && n<=high)
      break;
    else
      cout<<"Out of range; enter integer between 1 and 10"<<endl;
  }
  return n;
}

/*BuildMap function builds map data structure from text that serves as source file.
 *arguments are an input file stream handle, a reference to a map object whose
 *key:value pairs are string(seed from text file):vector of characters, where each character follows the seed
 *and an int len that represents seed length.  Upon completion the program is 
 *ready to generate the random text.
 */
void BuildMap(ifstream &in,Map<string,Vector<char> > &map, int len){
  string seed;  
  for (int i=0;i<len;i++){
    in.seekg(i);
    seed=""; //init seed
    /*get characters from input file, build map */
    while(!in.eof()){  
      seed+=in.get();  //get returns next char in stream, represented as integer
      if(seed.length()==len){  //if seed has reached desired length
	if(map.containsKey(seed)){  //check if seed already in map; if so, add char following seed to vector<char>
	  char ch=char(in.get());//get() returns int, so need to cast as char
	  Vector<char> v=map[seed];  //pull vector for that seed
	  v.add(ch);  //add char to vector
	  map.put(seed,v);  //put updated key:value (seed:vector) pair back into map
	  in.unget();//move filestream pointer back by one char
	}
	//if map doesn't contain key, add the new seed and following char to map
	else{
	  Vector<char> v;
	  v.add(in.get());
	  map.put(seed,v);
	  in.unget(); //puts char back in stream
	}
        seed="";      //reset seed to empty
      }
    }//end while
    in.clear();  //need to clear stream pointer after each pass before you use seekg();
  } //end for loop
  return;
}

/*function generates random text using map built from source text
 *precondition:  map has been created with key:value pairs, where key is string seed and value is vector of chars following seed
 *postcondition:  string of randomly generated test has been generated and printed to terminal
 */
void GenerateRandom(Map<string,Vector<char> > &map, int numChars){
  string output="";  //string that will be printed to terminal
  string maxString="";
  char nextChar;
  int highestSeedCount=0; //variable to hold number of occurences of seed
  string mostFrequentSeed;  //seed that occurs most frequently in input text

  /*below code block iterates over the map in order to find the most frequent seed in the source text
   *the key having the longest vector value is the most frequent seed*/
  for (const string & key: map) {  //iterate thru collection
      if(map[key].size()>highestSeedCount){
          highestSeedCount=map[key].size();
          mostFrequentSeed=key;
      }
    }
  //start random generation with maxString
  cout<<endl<<"Now generating random text, starting with initial seed \""<<mostFrequentSeed<<"\""<<endl;
  string seed=mostFrequentSeed; //initialize seed;
  output+=seed; //init output
  while(true){      //loop to generate the random text
    nextChar=pickRandomElement(map[seed]);  //get random char from vector of chars following seed
    if(nextChar==EOF || output.length()>=numChars)
      break;
    output+=nextChar; //concatenate output string with randomly selected char
    seed=seed.substr(1)+nextChar;  //advance seed so that it ends with random char that was just added
  }
  cout<<endl<<output<<endl;
  return;
}

/*this function returns a randomly picked character from a vector of characters.
 *precondition: argument vec is the value vector from the map corresponding to a key value (seed)
 *postcondition:  one of the chars in the vector is randomly chosen and returned
 */
char pickRandomElement(Vector<char> vec){
  int index= randomInteger(0,vec.size()-1);
  return vec[index];
}
