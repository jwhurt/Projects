#MIT 6.00 2008 OCW
#Problem Set 2
#ps2b.py

#This program is a continuation of the Diophantine equation problem of ps2a.py.
#The program calculates the largest number of chicken McNuggets that cannot be purchased 
#by using combinations of small, medium, and large packs of McNuggets, where the pack sizes are input by user.


#this function tries to solve the equation xa+yb+zc=n, where x, y, and z are small, medium, and large boxes of chicken McNuggets
#precondition: n is a non-negative integer in the above equation, sizes is a tuple; sizes=(x,y,z), where x, y, and z are small
#     medium, and large sizes.  We assume the sizes are 3 different non-negative integers, with small<medium<large
#postcondition: function returns true if solution found and false otherwise.
def testVarSizes(n, sizes):
    found=False #found is loop sentinel to indicate whether 6a+9b+20c=n has been solved
    for c in range(n/sizes[2]+1): #iterate thru possible range of values for largest pack size        
        if found:
            break
        for b in range(n/sizes[1]+1): #iterate thru range of possible medium box sizes
            if found:
                break
            for a in range(n/sizes[0]+1): #iterate thru range of possible small box sizes
                if(n==(sizes[0]*a)+(sizes[1]*b)+(sizes[2]*c)):
                    found=True
                    break
    return(found)


#function reads menu/background
def readBackGround():    
    print 'This problem set examines Diophantine equations.\n'
    print 'A Diophantine equation is a polynomial equation where the variables can only take on integer values.'
    print 'For example, x^n + y^n = z^n is a famous Diophantine equation. For n=2, there are infinitely many solutions'
    print 'called the Pythagorean triples, e.g. 3^2 + 4^2 = 5^2 \n'
    print 'This program looks at the Diophantine equation xa + yb + zc = n'
    print 'which models the way different combinations of small, medium, and large boxes of chicken McNuggets'
    print 'can be purchased to arrive at a total of n chicken McNuggets. \n'
    print 'This program will calculate the largest number of chicken McNuggets that cannot be purchased'
    print 'by using combinations of small, medium, and large packs of McNuggets'


#gets input from the user for the number of McNuggets in the small, medium, and large packs
#precondition:  none
#postcondition:  returns tuple (x,y,z); x<y<z, x,y,z integers
def getInput():
    while(True):
        sml=int(raw_input("Enter the number of McNuggets in the small pack:")) #declare empty tuple which will hold the different McNugget package sizes
        med=int(raw_input("Enter the number of McNuggets in the medium pack:"))
        lrg=int(raw_input("Enter the number of McNuggets in the large pack:"))
        if(0<sml<med<lrg):
            break
        else:
            print 'Invalid pack sizes.',
            if(sml<=0)or(med<=0)or(lrg<=0):
                print 'Sizes must greater than 0.'
            else:
                print'Please enter 3 different sizes, where small<medium<large.'
    return (sml,med,lrg)


readBackGround()   #read problem set background info

option='y'  #loop sentinel 

while(option=='y'):
    #Variable declarations
    n=1           #n is number to be purchased using integer combinations of small, med, and large packs
    count=0       #count of consecutive n values that we can solve; when count=size of small pack, we know by theorem that any larger n can be solved
    bestSoFar=0     #largest number of McNuggets that cannot be solved for
    packages=getInput() #get user input for pack sizes
    
   #driver program for test
    for n in range(1,200): #only search for solutions up to size 200
       if testVarSizes(n,packages):     #For each instance of n, perform test.  If pass, increment counter
          count=count+1
          if(count==packages[0]):
              break
       else:             #If test fails, new largest value is n, reset counter to 0
          count=0
          bestSoFar=n  

    #print final output message
    print 'Given package sizes',packages[0],',',packages[1],', and',packages[2],', the largest number of McNuggets that cannot be bought in exact quantity is:',bestSoFar
    option=raw_input('Would you like to continue (y/n)?')
