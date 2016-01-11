/*********************************************
ClassID:  COT3002			
Instructor:  Dr. Bullard
Assignment 3: madlibs.cpp		

Description:  This program simulates a madlibs game. The program performs the following steps:
 1.  Asks the user to input the files used for the madlibs story, the madlibs dictionary, and the output file.  
 2.  Creates a dictionary used to validate and replace bracketed words in the madlibs story.  
 2.  Reads the words from the story and outputs them to the output file, replacing the validated bracketed words with the 
	 appropriate dictionary word.
*********************************************/

//Preprocessor Directives
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
#define MAXCHAR 60

void fileOpen(ifstream &infile_story,ifstream &infile_dictionary,ofstream &outfile_story); //function to open game files
void  initDictionary(ifstream &infile,vector<string>&dictionary);  //function to fill dictionary vector
string getWord(vector<string> &dictionary,int &position,string key);  
void writeNewStory(vector<string>&dictionary,int &dictIndex, ifstream &infile, ofstream &outfile);
void replaceBracketedWords(vector<string>&dictionary,int &dictIndex,string &line);
string getWord(vector<string> &dictionary,int &dictIndex,string key);
bool isDictionaryEntry(vector<string>&dictionary,string key);
void writeLine(ofstream &outfile,string &line,int &charCount);


int main()
{  
  ifstream infile_dictionary;  //declare file stream objects
  ifstream infile_story;       
  ofstream outfile_story;      
  vector<string> dictionary;  //vector of strings is used to hold dictionary key-value pairs
  int dictIndex=0;  //keeps track of position in dictionary, rules of game require one pass through dictionary
  fileOpen(infile_story,infile_dictionary,outfile_story);  //function to open game files
  initDictionary(infile_dictionary,dictionary);  //initialize the dictionary for game
  writeNewStory(dictionary,dictIndex,infile_story,outfile_story); //write new story given dictionary,story stream, and new story file
  infile_dictionary.close();  //close streams
  infile_story.close();
  outfile_story.close();
  cout<<endl<<"Program complete.  Open the output file to see the new story!"<<endl;
  return 0;
}


/*fileOpen:  opens the necessary files for playing the game.  
 *precondition: The files for the game have been created and are in the current directory; the files consist of an 
 *original story file and a dictionary file with key-value pairs. Stream objects for handling files have been constructed;
 *infile_story is the stream object that handles the original story file; infile_dictionary is stream assigned to the 
 *dictionary file that contains key:value pairs for word replacement;outfile_story is stream for writing the finished 
 *story to the output file. Filenames must be entered on one line with no commas, or the program will exit.
 *postcondition:  If user enters valid filenames, those files will be opened by the streams.  If an invalid filename
 *is given the program will exit; if the output file does not exist, it will be created.  
 */
void fileOpen(ifstream &infile_story,ifstream &infile_dictionary,ofstream &outfile_story)
{
  string sfile,dfile,ofile,line;
  cout << "Welcome to Computer Madlibs!"<<endl;
  cout << "Enter the game filenames: (e.g. madlib_story.txt madlib_dictionary.txt madlib_output.txt)"<<endl;
  getline(cin,line);
  istringstream stream(line);
  stream>>sfile>>dfile>>ofile;
  if(!stream.eof())  //allow trailing whitespace, but no other characters
    stream>>ws;
  if(stream.fail() || !stream.eof()){  //good data entry leaves stream with no fail flag at end of file 
    cout<<"Invalid input format."<<endl;
    exit(1);
  }  
  infile_story.open(sfile.c_str()); //open input file for story
  if(infile_story.fail()){
    cout << "Story file open failed.\n";
    exit(1);
  }
  infile_dictionary.open(dfile.c_str());	//open input file for dictionary				
  if(infile_dictionary.fail()){	
    cout << "Dictionary file open failed.\n";
    exit(1);
  }
  outfile_story.open(ofile.c_str());	//open output file
  if(outfile_story.fail()){
    cout << "Output file open failed.\n";
    exit(1);
  }
  return;
}


/*initDictionary: reads the dictionary file into a vector of strings which contains the key:value pairs.
 *precondition: an infile stream object has opened the dictionary file, and an empty dictionary vector has been declared.
 *The dictionary file has strict 2 column format, with first column representing key, second column value.  No other 
 *characters besides the key and value word are permitted on each line of the dictionary; otherwise a file error 
 *is thrown and the program will close.
 *postcondition:  the dictionary vector will be initialized with key:value pairs necessary for gameplay, and the 
 *original dictionary file will not modified.
 */
void  initDictionary(ifstream &infile,vector<string>&dictionary)
{
  string dataline,key,value;
  while(getline(infile,dataline)){ //getline reads line by line of file inserts ws at end of each line
    /*extract first 2 fields from line, if not at end of line, data file is corrupt*/
    istringstream stream(dataline);  //declare object of input string stream type;
    if((stream>>key>>value>>ws)&&(stream.eof()) ){
      dictionary.push_back(key);
      dictionary.push_back(value);
    }
    else{
      cout<<"Dictionary file error"<<endl;
      exit(1);
    }
  }
}


/*writeNewStory: driver function that calls helper functions to write new story.  Extracts one line at
 *a time from original story; calls function to replace the bracketed words in that line, then calls a
 *function to write that completed line to the output file.
 *precondition:  dictionary vector is initialized with key-value pairs, an integer to track the position in
 *the dictionary has been initialized to the starting position (0); the helper functions have been created.
 *postcondition:  upon return the output file pointed to by the outfile stream will contain the completed
 *madlibs story that has replacement words from dictionary
 */
void writeNewStory(vector<string>&dictionary,int &dictIndex, ifstream &infile, ofstream &outfile)
{
  string line;
  int charCount=0;  //keeps track of number of chars output per line
  while (getline(infile,line)){
    replaceBracketedWords(dictionary,dictIndex,line);  //call function to replace bracketed words in line
    writeLine(outfile,line,charCount);  //call function to write that line to output
  }
}


/*replaceBracketedWords: main workhorse function of the game; processes one line at a time from original story; 
 *reads each line char by char, looking to form a bracketed word.  The scanning process has 3 states, depending
 *on the type of char read.  State 1 is where no open bracket '[' has been read, and the function copies the current 
 *char to the new output line.  Upon reading the first '[', the scanning process enters state 2, where it starts writing 
 *the bracketed word to replace. Upon reading a ']' char in state 2, the function will then enter state 3, where it looks
 *to complete the bracketed word with any char besides a ']'.  This last step is necessary to handle the boundary 
 *condition where a bracketed word could look like this: [hello]]! and the extracted word to be replaced would be
 *[hello]].  Once the bracketed word has been formed, the function looks up the replacement word using the 
 *dictionary.  In the event the end of the line is reached before completing the bracketed word, progress on
 *the bracketed word is stopped and it will be written to the output line.
 *Upon reaching the end of string line, line is then assigned to the new output line value
 *precondition: dictionary vector has been initialized, the index position within the dictionary has the correct value,
 *and a line from the originial story has been passed to the function.
 *postcondition:  the line parameter points to the new line that has had its valid bracketed words replaced with
 *dictionary words, provided a replacement was possible.
 */
void replaceBracketedWords(vector<string>&dictionary,int &dictIndex,string &line)
{
  string newline,bracketedWord;
  istringstream stream(line);
  int state=1;  //state will control switch statement
  int c;
  while((c=stream.get())!=EOF){
    switch(state){
    case 1:  //in state 1 the stream adds the char read to the newline, unless a '[' is read, which moves the stream to state 2
      if(c!='[')
	newline+=c;
      else{
	bracketedWord+=c;
	state=2;
      }
      break;
    case 2:  //in state 2 the stream adds the chars read to the bracketed word which will be looked up, unless a ']' triggers state 3
      if(c==']'){
	state=3;
	bracketedWord+=c;	
      }
      else
	bracketedWord+=c;
      break;
    case 3:  //in state 3 the stream has read a pair of '[' and ']' and will complete the bracketed word, unless ']' is read
      if(c==']')
	bracketedWord+=c;      
      else if(c=='['){
	state=2;
	newline+=getWord(dictionary,dictIndex,bracketedWord);      //bracketed word complete,insert new word
	bracketedWord=c;
      }
      else{
	state=1;
	newline+=getWord(dictionary,dictIndex,bracketedWord);      //bracketed word complete,insert new word
	bracketedWord="";
	newline+=c;
      }
      break;
    default: break;      
    }
  }
  newline+=bracketedWord; //bracketed word may contain string in progress, need to add it back
  line=newline;
}


/*writeLine:  manages the process of writing completed lines to the output file so that each output file
 *line has the maximum number of chars while remaining under the char count limit constraint.
 *Writes to output file one word at a time, until character count limit is reached; at which point the 
 *function writes a newline character and sets the line char counter back to 0. The line length of the original 
 *story file is not maintained in the output file.
 *precondition: outfile is a stream object pointing to output file; line is reference to most recent line
 *that has completed the word replacement process, the charCount that references an integer that tracks the number
 *of characters on current line being written (whitespace included in count) is correct.
 *postcondition:  The line is written to the output file in a way that maximizes char count subject to the constraint;
 *outfile stream maintains position on last line of output file waiting for next character, and charCount is updated to 
 *represent count of this last line.
 */
void writeLine(ofstream &outfile,string &line,int &charCount)
{
  string nextWord;
  istringstream stream(line);  //stream object which allows string to be treated as stream
  while(stream>>nextWord){     //while there are words to extract, continue loop 
    if( (charCount+nextWord.length()+1)<=MAXCHAR ){  //check length of next word+space to verify they can be added to output line
      outfile<<nextWord+" ";
      charCount+=(nextWord.length()+1);  //update count
    }
    else if( (charCount+nextWord.length())<=MAXCHAR ){  //check if word alone can be added
      outfile<<nextWord;
      charCount+=nextWord.length();
    }
    else{  //start new line
      outfile<<"\n"<<nextWord<<" ";
      charCount=nextWord.length()+1;
    }
  }
}


/*getWord: searches dictionary for replacement word
 *precondition: dictionary is reference to the dictionary vector containing sequence of key-value pairs,
 *where the key index is an even number and the value index is odd; dictIndex is reference to index in dictionary;
 *bracketedKey is word taken from original story that starts with '[' and ends with ']'
 *postcondition: function will return the value corresponding to the key in the dictionary, or the original bracketed 
 *word if no key found; dictionary index is updated to point to next key position that has not been searched/consumed
 */
string getWord(vector<string> &dictionary,int &dictIndex,string bracketedKey)
{
  string key=bracketedKey.substr(1,bracketedKey.length()-2);
  if(isDictionaryEntry(dictionary,key)){  //first check if key is a valid entry, if not, no dictionary keys are used up
    while(dictIndex<dictionary.size()){  //search the dictionary
      if(dictionary[dictIndex]==key){
	dictIndex+=2;                    //advance the dictionary index for next word to search
	return dictionary[dictIndex-1];  //-1 because we advanced the index position past the index where we found a match
      }
      else
	dictIndex+=2;  //+2 because the keys are in every other index position
    }
  }
  return bracketedKey;
}

  
/*isDictionaryEntry: determines if a given key is valid.  In order to be valid the key must be contained in the 
 *list of keys in the dictionary.  
 *precondition:  dictionary has been initialized with keys, and a key to search for has been passed
 *postcondition:  If the key is found in the list of all the dictionary keys, the function returns true.
 *If the key is not found the function returns false.
 */
bool isDictionaryEntry(vector<string>&dictionary,string key)
{
  for(int i=0;i<dictionary.size();i+=2){  //increment by 2 because keys are stored at even index locations
    if(key==dictionary[i])
      return true;
  }
  return false;
}
