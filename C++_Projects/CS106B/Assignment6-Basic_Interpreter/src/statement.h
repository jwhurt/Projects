/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h
#include "evalstate.h"
#include "exp.h"

/*the following were not included in starter kit*/
#include "tokenscanner.h"
//#include "program.h"  //added to allow statement subclasses GotoStmt and IfStmt to be aware of program state

//Program program;  //experimental forward reference
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */


/*
 * Class: RemStmt
 * ----------------
 * The REM statement has the following syntax in BASIC:
 *     10 REM comment
 * where 10 is a hypothetical line number, and comment is the statement used to document the code/program.
 * This class is used to represent a remark (aka comment) statement in the program that
 * is only used to document and explain the code; 
 * the execute method of this class is empty, as there is nothing to execute; 
 * there is also no private data for this statement, so no destructor is needed
 */
class RemStmt: public Statement{
 public:
/*
 * Constructor
 * Usage:  Statement *stmt=new RemStmt(scanner);
 * ----------------
 * Creates a new RemStmt using the token scanner
 */
  RemStmt(TokenScanner & scanner);

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * Prototype for virtual method overridden by this class
 * This method has does nothing since a comment is ignored
 */
  virtual void execute(EvalState & state);
};


/*
 * Class: PrintStmt
 * ----------------
 * This Statement subclass represents a PRINT statement
 */
class PrintStmt: public Statement {
 public:
/*
 * Constructor
 * Usage:  Statement *stmt=new PrintStmt(scanner);
 * ----------------
 * The print statement has the form:
 *    20 PRINT exp
 * Where exp is a valid BASIC expression.  
 * The constructor will verify if the rest of the line after the PRINT keyword is a valid expression;
 * if so, it creates a new PrintStmt object that stores the parsed representation of exp in an instance variable.
 */
  PrintStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
  virtual ~PrintStmt();
  virtual void execute(EvalState & state);
 private:
  Expression *exp;  //pointer to the parsed representation of the expression 
};


/*
 * Class: LetStmt
 * ----------------
 * This subclass represents a LET statement, which has the following syntax in BASIC:
 *      10 LET varname = exp
 * where varname is a string, "=" the only allowed operator, and exp a valid BASIC expression, which
 * does not contain another "=" operator
 */
class LetStmt: public Statement{
 public:
/*
 * Constructor
 * Usage: Statement *stmt=new LetStmt(scanner);
 * ----------------
 * The constructor uses the scanner to stores the varname and parsed representation of the expression 
 * in the private instance variables varName and *rhs respectively
 */
  LetStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
  virtual ~LetStmt();
/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * The execute method will create an association in the state between 
 * the instance variable varName and the integer value of the expression pointed to by *rhs
 */
  virtual void execute(EvalState & state);
 private:
  std::string varName;  //string name on LHS of "=" statement
  Expression *rhs;   //pointer to expression on RHS of "=" statement
};


/*
 * Class: InputStmt
 * ----------------
 * This subclass represents an INPUT statement, which has the following syntax:
 *     10 INPUT varname
 * Upon execution this statement will print a prompt "?" and then assign the value
 * entered by user to the variable varname
 */
class InputStmt: public Statement{
 public:
/*
 * Constructor
 * Usage:  Statement *stmt=new InputStmt(scanner);
 * ----------------
 * Creates a new InputStmt; assigns the string varname to the lhs instance variable
 */
  InputStmt(TokenScanner & scanner);

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * The execute method will create an association in the state between 
 * the instance variable lhs and the value read in from user
 */
  virtual void execute(EvalState & state); 
 private:
  std::string lhs; 
};


/*
 * Class: GotoStmt
 * ----------------
 * This subclass represents an GOTO statement, which has the syntax
 *     60 GOTO n
 * where n is an existing line number in the program. This statement will
 * force an unconditional change in the control flow of the program so that
 * line number n will be executed next.
 */
class GotoStmt: public Statement{
 public:
/*
 * Constructor
 * Usage:  Statement *stmt=new GotoStmt(scanner);
 * ----------------
 * Creates a new GotoStmt; The scanner will read the remaining line after the string "GOTO",
 * and initialize the instance variable gotoLine to the value n
 */
  GotoStmt(TokenScanner & scanner);

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * The execute method will change the next line of the program to be executed in the EvalState to n
 */  
  virtual void execute(EvalState & state);

 private:
  int gotoLine;
};


/*
 * Class: IfStmt
 * ----------------
 * This subclass represents an IF statement, which has the following syntax:
 *     140 IF exp1 op exp2 THEN n
 * where exp1 is an expression, op is one of the  conditional operators
 * =, <, or >, and exp2 is an expression.  If the condition holds, the program
 * will continue from line number n; if not it will continue to the next line
 */
class IfStmt: public Statement{
 public:
/*
 * Constructor
 * Usage:  Statement *stmt=new GotoStmt(scanner);
 * ----------------
 * Creates a new GotoStmt; The constructor will use the scanner to parse the remaining expression after "IF" 
 * into 2 expressions and an operator, setting the instance variables representing the components of the IF statement
 */
  IfStmt(TokenScanner & scanner);

  virtual ~IfStmt();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * The execute method will evaluate the condition (exp1 op exp2); if true it will set the next line of the program to be executed
 * in the EvalState to n; if false does nothing
 */  
  virtual void execute(EvalState & state);
 private:
  Expression *exp1;
  Expression *exp2;
  std::string op;
  int goToLine;
};


/*
 * Class: EndStmt
 * ----------------
 * This subclass represents an END statement, which has the following syntax:
 *     70 END
 *  The END statement marks the end of the program
 */
class EndStmt: public Statement{
 public:
  EndStmt(TokenScanner & scanner);

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * The execute method will use the program state to halt the execution of the program
 */  
  virtual void execute(EvalState & state);
 private:
};

#endif
