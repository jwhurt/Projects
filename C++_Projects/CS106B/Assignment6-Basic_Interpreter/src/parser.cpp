/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.  Copied from chap 19 of the text, only changes are 
 * modification of the function precedence() so that the "=" operator is disabled and 
 * adding the parseStatement() function
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"  //parser.h includes statement.h
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   if (scanner.hasMoreTokens()) {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD) return new IdentifierExp(token);
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (token != "(") error("Illegal term in expression");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 * the code to recognize the "=" operator was removed because basic doesn't recognize "=" in expressions,
 * per instructions p 6
 */
int precedence(string token) {
  //  if (token == "=") return 1; 
  if (token == "+" || token == "-") return 2;
  if (token == "*" || token == "/") return 3;
  return 0;
}

/*
 * Implementation notes: parseStatement
 * --------------------------------
 * This function calls the appropriate statement subclass constructor to implement the next token command 
 * in the scanner.  If the token is not one of the valid BASIC commands, the function will throw an error.
 */
Statement *parseStatement(TokenScanner & scanner){
  Statement *stmt=NULL;
  string token=scanner.nextToken();
  if(token=="REM")
    stmt=new RemStmt(scanner);
  else if(token=="LET")
    stmt=new LetStmt(scanner);
  else if(token=="PRINT")
    stmt=new PrintStmt(scanner);
  else if(token=="INPUT")
    stmt=new InputStmt(scanner);
  else if(token=="GOTO")
    stmt=new GotoStmt(scanner);
  else if(token=="IF")
    stmt=new IfStmt(scanner);
  else if(token=="END")
    stmt=new EndStmt(scanner);
  else
    error("Invalid token "+token);
  return stmt;
}
