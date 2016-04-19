Assignment1 Instructions

For this assignment, you will write a program in order to become more comfortable with the basic structure of C++ programs and the compilation process.  This program involves output (via cout statements), input (via cin statements), and the use of a previously define class.

Consider a class called Balloon.  Write a program called fly.cpp that uses a variable of type Ballon and performs the following sequence of actions:

    1.  Prompt the user for desired altitude and a number of time steps.
    2.  Cause the balloon to ascend to one-third of the specified altitude, then cruise for one-quarter
         of the time steps.
    3.  Repeat step 2 twice more (ascend one-third, cruise one-quarter, ascend one-third, cruise
        one-quarter).
    4.  Descend halfway to the ground, cruise for the remaining time steps, and then descend
         back to the ground.
    5.  After the first ballon flight, your program should ask the user if he/she would like to continue. 

Sample Output:
Welcome to Balloons-R-Us
How high (in meters) do you want to go today? 30
How long (in minutes) do you want your flight to be? 12
***** (Height = 0) Ascending to 10 meters *****

0 meters  Burn! ...

***** Cruising at 10 meters  with margin +/- 5 for 3 time-steps *****

10 meters (time step 0)
10 meters (time step 1)
10 meters (time step 2)

***** (Height = 10) Ascending to 20 meters *****

10 meters  Burn! ...

***** Cruising at 20 meters  with margin +/- 5 for 3 time-steps *****

20 meters (time step 0)
20 meters (time step 1)         wind-shear bump up 1 meters
21 meters (time step 2)         wind-shear drop 3 meters

***** (Height = 18) Ascending to 30 meters *****

18 meters  Burn! ...
28 meters  Burn! ...

***** Cruising at 38 meters  with margin +/- 5 for 3 time-steps *****

38 meters (time step 0)         wind-shear bump up 5 meters
43 meters (time step 1)
43 meters (time step 2)

***** (Height = 43) Descending to 15 meters *****

35 meters  Woooosh!
25 meters  Woooosh!

***** Cruising at 15 meters  with margin +/- 5 for 3 time-steps *****

15 meters (time step 0)
17 meters (time step 1)         wind-shear drop 2 meters
17 meters (time step 2)         wind-shear drop 4 meters too low!  Burn! ...
***** (Height = 47) Descending to 0 meters *****

20 meters  Woooosh!
10 meters  Woooosh!

Would you like to continue, enter yes or no?

Files needed
fly.cpp.....driver program containing main, runs UI
balloon.h....header file for the balloon class
balloon.cpp....implementation file for balloon class
randgen.h......header file for random generation library file
randgen.cpp....implementation of random functions
README.TXT....assignment instructions and instructions on running program
makefile.....build automation file

Compiling the program
Download the above file into the same directory 
Open terminal window
Change directory to the directory containing the above files.
     $ cd directoryName
Type "make" at terminal prompt       
     $ make
Run the executable file
     $ ./a.out


