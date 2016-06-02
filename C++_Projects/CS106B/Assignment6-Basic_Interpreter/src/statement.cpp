/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
/*the following interfaces not part of starter code*/
#include "parser.h"
#include "simpio.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}


/* Implementation notes: RemStmt
 * --------------------------------
 * The constructor and execute methods are empty because this subclass has no instance variables and there is nothing to execute
 */
RemStmt::RemStmt(TokenScanner & scanner){
}

void RemStmt::execute(EvalState &state){
  //RemStmt is a comment statement and execution method does nothing
}

/* Implementation notes: PrintStmt
 * --------------------------------
 * The constructor parses the statement following "PRINT" into a single expression pointed to by *exp;
 * if there are remaining tokens in the string after the expression has been created then a syntax error
 * exists and an error is thrown.
 * The execute method prints the integer result of evaluating the expression 
 */
PrintStmt::PrintStmt(TokenScanner & scanner){
  exp=readE(scanner,0);
  if(scanner.hasMoreTokens())
    error("Extraneous token "+scanner.nextToken());
}

PrintStmt::~PrintStmt(){
  delete exp;
}

void PrintStmt::execute(EvalState &state){
  cout<<exp->eval(state)<<endl;
};


LetStmt::LetStmt(TokenScanner & scanner){
  varName=scanner.nextToken();
  if(scanner.nextToken()!="=")
    error("LetStmt syntax error, expecting \"=\" token");
  rhs=readE(scanner,0);
  if(scanner.hasMoreTokens())
    error("LetStmt extraneous token "+scanner.nextToken());
}


LetStmt::~LetStmt(){
  delete rhs;
}

void LetStmt::execute(EvalState &state){
  int value=rhs->eval(state); //will update state
  state.setValue(varName,value);  
}


InputStmt::InputStmt(TokenScanner & scanner){
  lhs=scanner.nextToken();
  if(scanner.hasMoreTokens())
    error("Extraneous token "+scanner.nextToken());
}

void InputStmt::execute(EvalState &state){  
  string inputExp=getLine("?");
  state.setValue(lhs,stringToInteger(inputExp));
  
}


/* Implementation notes: GotoStmt
 * --------------------------------
 * The execute method changes the state by setting the current line to that of
 * the instance variable
 */
GotoStmt::GotoStmt(TokenScanner & scanner){
  string token=scanner.nextToken();
  TokenType type=scanner.getTokenType(token);
  if(type!=NUMBER)
    error("Goto line number not valid");
  else
    gotoLine=stringToInteger(token);
  if(scanner.hasMoreTokens())
    error("Extraneous token "+scanner.nextToken());
}  

void GotoStmt::execute(EvalState & state){
  state.setCurrentLine(gotoLine);
}

/* Implementation notes: EndStmt
 * --------------------------------
 * The constructor is empty because there are no instance variables to initialize
 * The execute method changes the EvalState by setting the current line to -1, which
 * will end execution of the BASIC "RUN" command
 */
EndStmt::EndStmt(TokenScanner & scanner){
  //nothing to initialize
}

void EndStmt::execute(EvalState & state){
  state.setCurrentLine(-1);
}



/* Implementation notes: IfStmt
 * --------------------------------
 * The constructor will use the parser to read tokens from the scanner to build the 
 * expression exp1, then it will look for a comparison operator string, then it will
 * use the parser again to build exp2.  The scanner will then check if the THEN part 
 * of the statement has the correct syntax.
 * The execute method will call the eval method for both expressions, storing the
 * results in the integers lhs and rhs, then evaluate the condition by performing the 
 * comparison specified by the operator string op; if the condition is true the 
 * current line in the state will be set to the goToLine.
 */
IfStmt::IfStmt(TokenScanner & scanner){
  exp1=readE(scanner,0);
  op=scanner.nextToken();
  exp2=readE(scanner,0);
  if(scanner.nextToken()!="THEN")
    error("IfStmt error:  invalid syntax"); 
  goToLine=stringToInteger(scanner.nextToken());
  if(scanner.hasMoreTokens())
    error("IfStmt Extraneous token "+scanner.nextToken());
}

IfStmt::~IfStmt(){
  delete exp1;
  delete exp2;
}

void IfStmt::execute(EvalState & state){
  int lhs=exp1->eval(state);
  int rhs=exp2->eval(state);
  if((op=="="&&lhs==rhs)||(op=="<"&&lhs<rhs)||(op==">"&&lhs>rhs))
    state.setCurrentLine(goToLine);	
}
