/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC program.
 * It contains the functions and data structure necessary to allow the BASIC interpreter to run quickly
 */

#ifndef _program_h
#define _program_h
#include <string>
#include "statement.h" 

/*the following interface was not included in the starter kit*/
#include "map.h" 

using namespace std;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */
class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */
   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */
   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */
   void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */
   void addSourceLine(int lineNumber, std::string line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */
   void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */
   std::string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 */
   void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */
   Statement *getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */
   int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */
   int getNextLineNumber(int lineNumber);

/*
 * Method: hasLineNumbe
 * Usage: if(program.hasLineNumber(n));
 * ------------------------------------------------------------
 * Returns true if line number exists in program and false otherwise;
 */
   bool hasLineNumber(int lineNumber);

private:
/*
 * Instance variable: Cell
 * The Cell struct is used to build a doubly linked list of Cells, where each Cell represents a line of 
 * basic code and contains pointers to the previous and next Cells.  The integer lineNumber contains
 * the line number in the basic program, the string line contains the basic statement string, and
 * the pointer *stm is a pointer to the parsed representation of the statement
 */
   struct Cell{
     int lineNumber;
     std::string line;
     Cell *next;
     Cell *prev;
     Statement *stm; 
   };

/* 
 * Instance variables: *head, *tail
 * The head and tail are pointers to the sentinel nodes at the head and tail of the linked list
 */
   Cell *head;  
   Cell *tail;  

/* Instance variable: lineMap
 * lineMap is a mapping of line numbers to pointers to cells in the linked list
 * This map data structure was necessary in order to meet the instruction requirements that
 * getNextLineNumber() run in constant time.  Without the map, the linked list would need
 * to be searched sequentially from head to tail to find a given line number, which would 
 * run in linear time
 */
   Map<int, Cell*> lineMap;
};

#endif
