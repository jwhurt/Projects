/*FAU COP 2220 Programming in C
 *Assignment 4:  Hangman
 */

/*Preprocessor Directives*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SZ 20  //max size of char array
#define Max_Num_Wrong 5  //number of wrong guesses allowed

/*Function Prototypes*/
void readInstructions(); //displays instructions
int getNextWord(FILE *fp, char wordToGuess[]); //function to read next word from file, returns 0 if EOF
void arrayPrep(char wordToGuess[],char wordInProg[],char guessedLetters[]); //prepare word arrays for gameplay
void showStatus(char word[], char guessedLetters[], int *numWrong); //show current status of game
void getGuess(char guessedLetters[],char *guess); //retrieve letter guessed from user
void checkGuess(char wordToGuess[],char guess,char wordInProg[],char guessedLetters[],int *numGuesses,int *numWrongGuesses); //check if guess correct
int findGuessLoc(char wordToGuess[],char *guess);//finds the position in mystery word that matches guessed letter
int wordsMatch(char str1[],char str2[]);  //checks if 2 words match
int getStrLen(char *strPtr);  //finds string length
void showGameResult(int numWrong,char wordToGuess[]);  //displays final result of game
void playAgain(int *sentinel, int *numWrongGuesses, int *numGuesses);  //asks user if they want to play again
void draw(int *numWrong);  //function to enhance gameplay by drawing hanging process (not required in original assignment)

int main()
{
  /*Variable Declarations*/
  char wordToGuess[SZ];  //char array to hold the word to find
  char wordInProg[SZ];  //char array to show word in process of being guessed
  char guessedLetters[SZ];  //array to hold the letters guessed
  char guess;  //individual letter guess
  int numGuesses=0;  //total number of guesses, this matches length of guessedLetters array
  int numWrongGuesses=0;  //number of incorrect guesses, where char not found in wordToGuess
  int playOn=1;  //sentinel to control main loop
  FILE *fp;   //declare file pointer

  fp=fopen("words.txt","r");  //open file containing game words
  readInstructions(); //read game instructions

  /*main loop for playing multiple games; will keep playing until player quits or all words read from file*/
  while(playOn && getNextWord(fp,wordToGuess)){     
    arrayPrep(wordToGuess,wordInProg,guessedLetters); //function prepares the arrays guessedLetters[] and wordInProgres[] for gameplay
    /*loop for playing an individual game*/
    while(numWrongGuesses<=Max_Num_Wrong && !wordsMatch(wordToGuess,wordInProg)){  //continue as long as more guesses allowed and word is not found
      showStatus(wordInProg,guessedLetters,&numWrongGuesses); //display the current status of the game
      getGuess(guessedLetters,&guess);  //get the next guess
      checkGuess(wordToGuess,guess,wordInProg,guessedLetters,&numGuesses,&numWrongGuesses); //evaluate latest guess
    }
    showGameResult(numWrongGuesses,wordToGuess);   //show end of game result
    playAgain(&playOn,&numWrongGuesses,&numGuesses);  //ask user if they wish to play again, reset game variables if so
  }
  printf("Goodbye!\n");
}

/*Function Definitions*/

/*checkGuess: check if guess is correct, gives feedback to user, updates display*/
void  checkGuess(char wordToGuess[],char guess,char wordInProg[],char guessedLetters[],int *numGuesses,int *numWrongGuesses)
{
  int indexFound;
  if((indexFound=findGuessLoc(wordToGuess,&guess))!=-1){  //look for location of letter in word
    printf("Correct!\n");  
    wordInProg[indexFound]=guess;
  }
  else{
    printf("Wrong!\n");
    (*numWrongGuesses)++;
    }
  //update number of guesses and guessedLetters on display
  (*numGuesses)++;
  guessedLetters[*numGuesses-1]=guess;  
}

/*getGuess: asks user for a new letter guess; continues looping until
 *user guesses with a char that is not in list of guess chars already used
 */
void getGuess(char guessedLetters[],char *guess)
{
  while(1){  //continue looping until user gives new guess
    printf("\nGuess a letter>");
    scanf(" %c",guess);
    *guess=tolower(*guess);
    if(findGuessLoc(guessedLetters,guess)==-1) //negative one is returned by findGuessLoc if letter not found
      break;
    printf("\nYou have already guessed %c!",*guess);
  }
}

/*findGuessLoc: attempts to find char guess in string,
 *returns the first index location where there is a match,
 *if no match found returns -1 
 */
int findGuessLoc(char word[], char *guess){
  int sz=getStrLen(word); 
  for(int i=0;i<sz;i++){
    if(*guess==word[i])
      return i;
  }
  return -1;
}

/*getNextWord: reads next word from file into wordToGuess, converts word to lowercase
 *function returns 1 if string is read from file,returns 0 if EOF
 */
int getNextWord(FILE *fp, char wordToGuess[])
{
  int sz,i;
  if(fscanf(fp,"%s",wordToGuess)==EOF){
    printf("End of mystery word file.\n");
    return 0;
  }    
  sz=strlen(wordToGuess);  //wordtoguess is converted to lower case      
  for(i=0;i<sz;i++)
    wordToGuess[i]=tolower(wordToGuess[i]);	
  return 1;
}

/*arrayPrep: prepares the arrays guesses[] and wordInProgres[] for gameplay
 *precondition is that wordToGuess has been read, since it is used to build array of *'s for word in progress
 */
void arrayPrep(char wordToGuess[],char wordInProg[],char guessedLetters[])
{ 
  int i;
  for(i=0;wordToGuess[i]!='\0';i++)  //fill the mystery word with correct number of "*" spaces
    wordInProg[i]='*';
  wordInProg[i]='\0';//enter string terminating character
  for(i=0;i<SZ;i++)  //fill the guessedLetters array with null char
    guessedLetters[i]='\0';
}

/*readInstructions: read game instructions*/
void readInstructions(){
    printf("WELCOME TO HANGMAN!\n\n");
    printf("You must guess the mystery word to avoid being hung!\n");
    printf("You will be asked to enter one letter at a time. \n");
    printf("If the letter you guess is part of the mystery word,\n");
    printf("it will appear in the correct location.\n");
    printf("If the letter you guess is not contained in the word,\n");
    printf("you will advance one step closer to being hung.\n");
    printf("You are allowed a maximum of 5 incorrect guesses.\n");
    printf("On your 6th incorrect guess you will be hung!\n");
    printf("Good Luck!\n\n");
}

/*showStatus: print the mystery word in progress, the array of letters guessed, and the number of wrong guesses*/
void showStatus(char word[], char guessedLetters[],int *numWrong){
  printf("Letters Guessed: %s\n",guessedLetters);
  printf("Word In Progress: %s\n",word);
  printf("Number of Wrong Guesses: %d\n",*numWrong);
  draw(numWrong);
}

/*showGameResult: print result at end of game*/
void showGameResult(int numWrong,char word[]){
  if(numWrong<=Max_Num_Wrong){
    printf("Congratulations, you escaped being hung!\n");
  }
  else{
    printf("You have been hung!\n");
  }
  draw(&numWrong);
  printf("The mystery word was %s.\n",word);
}

/*playAgain: ask user if they want to play again*/
void playAgain(int *sentinel, int *numWrongGuesses, int *numGuesses)
{
  char play;
  printf("Would you like to play again? (Enter y/n) >");
  scanf(" %c",&play);
  if(play=='y'||play=='Y'){
    *sentinel=1;  //continue gameplay
    *numWrongGuesses=0;
    *numGuesses=0;
  }    
  else
    *sentinel=0; //set sentinel to stop gameplay
}

/*wordsMatch: test if 2 strings match, return value is 1 if match and 0 if no match
 *uses strcmp function in <string.h> library which returns numerical result of str1-str2
 */
int wordsMatch(char str1[],char str2[]){
  return (strcmp(str1,str2)==0);  
}

/*getStrLen: my implementation of strlen() function in the <string.h> library
 *getStrLen() determines string length by incrementing character pointer 
 *until null character '\0' found, whereupon the index of the null character is returned.
 *For example, if '\0' found at index 9, then valid string characters occupy elements
 *0-8, representing string length of 9.
 */
int getStrLen(char *strPtr){
  int i;
  for(i=0; *strPtr!='\0'; i++){    
    strPtr++; //increment pointer
  }
  return i;    
}

/*draw: print image of the hanging progress (not part of original assignment, added for entertainment value)
 *draws additional limbs based on the number of wrong guesses
 *this feature would need to be modified if the number of wrong guesses allowed is changed.
 */
void draw(int *numWrong){
  switch(*numWrong){
     case 0:
       printf("---------------\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");    
       printf("|\n");    
       break;
     case 1: 
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");    
       printf("|\n");    
       break;
     case 2:
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|     ||\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");    
       break;
     case 3:       
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|     ||\\_\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");    
       break;
     case 4:
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|   _/||\\_\n");
       printf("|\n");
       printf("|\n");
       printf("|\n");    
       break;
     case 5:
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|   _/||\\_\n");
       printf("|     / \n");
       printf("|   _/  \n");    
       printf("|\n");    
       break;
     default:
       printf("----/-|--------\n");
       printf("|  /  | \n");
       printf("| /   | \n");
       printf("|/    ()\n");
       printf("|   _/||\\_\n");
       printf("|     /\\  \n");
       printf("|   _/  \\_\n");    
       printf("|\n");    
       break;
  }
}
