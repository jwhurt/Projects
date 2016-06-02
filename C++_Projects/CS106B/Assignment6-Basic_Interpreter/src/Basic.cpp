/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"

/*below interfaces not included in starter code*/
#include "statement.h"
using namespace std;

void processLine(string line, Program & program, EvalState & state);

int main() {
   EvalState state;
   Program program;
   cout << "Minimal BASIC --- Type HELP for help." << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   string token=scanner.nextToken();
   TokenType type=scanner.getTokenType(token);
   int lineNumb;
   int priorLineNumb;
   if(type==NUMBER){
     if(scanner.hasMoreTokens()){
       program.addSourceLine(stringToInteger(token),line);
       Statement *stmt=parseStatement(scanner); 
       program.setParsedStatement(stringToInteger(token),stmt);  //link statement to line number
     }
     else
       program.removeSourceLine(stringToInteger(token));
   }
   if(type==WORD){
     if(token=="LIST"){
       lineNumb=program.getFirstLineNumber();
       while(lineNumb!=-1){
	 cout<<program.getSourceLine(lineNumb)<<endl;
	 lineNumb=program.getNextLineNumber(lineNumb);
       }
     }
     else if(token=="RUN"){
       state.setCurrentLine(program.getFirstLineNumber());
       lineNumb=state.getCurrentLine();
       while(lineNumb!=-1){	 
	 if(program.hasLineNumber(lineNumb)==false)
	   error("Invalid line reference at program line "+integerToString(priorLineNumb));
	 Statement *stmt=program.getParsedStatement(lineNumb);
	 state.setCurrentLine(program.getNextLineNumber(lineNumb));
	 stmt->execute(state);
	 priorLineNumb=lineNumb;
	 lineNumb=state.getCurrentLine();
       }
     }
     else if(token=="CLEAR"){
       program.clear();
     }
     else if(token=="HELP"){
       cout<<"Minimal Basic Statements"<<endl; 
       cout<<"REM   This statement used for comments"<<endl;
       cout<<"LET   This statement is BASIC's assigment statement"<<endl;
       cout<<"PRINT In minimal BASIC, the PRINT statement has the form: "<<endl;
       cout<<"         PRINT exp"<<endl;
       cout<<"      where exp is an expression."<<endl;
       cout<<"INPUT In the minimal version of the BASIC interpreter, the INPUT statement has the form:"<<endl;
       cout<<"         INPUT var"<<endl;
       cout<<"      where var is a variable read in from the user"<<endl;
       cout<<"GOTO  This statement has the syntax"<<endl;
       cout<<"         GOTO n"<<endl;
       cout<<"      which forces the program to continue from line n instead of continuing with the next statement"<<endl;
       cout<<"IF    This statement provides conditional control. The syntax for this statement is: "<<endl;
       cout<<"      IF exp1 op exp2 THEN n"<<endl;
       cout<<"      where exp1 and exp2 are expressions and op is one of the conditional operators =, <, or >."<<endl;
       cout<<"END   This statment marks the end of the program."<<endl;
       cout<<"Commands to control the BASIC interpreter"<<endl;
       cout<<"RUN   This command starts program execution beginning at the lowest-numbered line. "<<endl;
       cout<<"LIST  This command lists the steps in the program in numerical sequence."<<endl;
       cout<<"CLEAR This command deletes the program so the user can start entering a new one."<<endl;
       cout<<"HELP  This command provides a simple help message describing the interpreter."<<endl;
       cout<<"QUIT  Typing QUIT exits from the BASIC interpreter by calling exit(0)."<<endl;	 
     }
     else if(token=="QUIT"){
       exit(0);
     }
     else
       cout<<"Invalid command"<<endl;     
   }
}
