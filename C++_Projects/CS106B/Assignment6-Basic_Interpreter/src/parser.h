/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_h
#define _parser_h
#include <string>
#include "exp.h"
#include "tokenscanner.h"

/* the following interfaces were not part of the starter program*/
#include "statement.h"


/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses an expression by reading tokens from the scanner, which must
 * be provided by the client.  The scanner should be set to ignore
 * whitespace and to scan numbers.
 */

Expression *parseExp(TokenScanner & scanner);

/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Returns the next expression from the scanner involving only operators
 * whose precedence is at least prec.  The prec argument is optional and
 * defaults to 0, which means that the function reads the entire expression.
 */

Expression *readE(TokenScanner & scanner, int prec = 0);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Returns the next individual term, which is either a constant, an
 * identifier, or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If the token
 * is not an operator, precedence returns 0.
 */

int precedence(std::string token);


/*
 * Function: parseStatement
 * Usage: Statement *stmnt=parseStatement(scanner);
 * ------------------------------------
 * Parses a statement by reading tokens from the scanner, which must be provided by the client;
 * Function will read the first token on the line, if that token is the name of one of seven legal
 * statements, the constructor for that statement subclass is called.  
 * This function returns a pointer to a statement object constructed.
 * Note:  This function added to parser.h starter code, per the assignment 6 instructions on p.6 
 */

Statement *parseStatement(TokenScanner & scanner);
#endif
