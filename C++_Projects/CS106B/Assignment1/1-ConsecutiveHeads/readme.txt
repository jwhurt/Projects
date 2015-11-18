To run from command line, navigate to the directory containing the source code, then at the prompt type 'make' 
to run the makefile which creates the a.out executable file.
Then type './a.out' at the terminal prompt to run the program.

The commands should look like below:

bash-3.2$ make
g++ -c ConsecutiveHeads.cpp
g++ -c random.cpp
g++ ConsecutiveHeads.o random.o
bash-3.2$ ./a.out
