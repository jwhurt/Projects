#MIT 6.00 2008 OCW
#Problem Set 2
#ps2a.py

#This program calculates the largest number of chicken McNuggets that cannot be purchased 
#by using combinations of 6, 9, and 20 packs of McNuggets

#Function tests if there exists non-negative integers a,b,c such that 6a+9b+20c=n
#precondition: n is a non-negative integer that we are solving for in the above equation, representing number of chicken McNuggets
#postcondition:  function returns boolean of true if the 6a+9b+20c=n is solved, and false if not
def test(n):
    found=False #found is loop sentinel to indicate whether 6a+9b+20c=n has been solved
    for c in range(n/20+1): #iterate thru possible range of values for largest pack size        
        if found:
            break
        for b in range(n/9+1): #iterate thru range of possible medium box sizes
            if found:
                break
            for a in range(n/6+1): #iterate thru range of possible small box sizes
                if(n==(6*a)+(9*b)+(20*c)):
                    found=True
                    break
    return(found)

#function reads menu/background
def readBackGround():    
    print 'This problem set examines Diophantine equations.\n'
    print 'A Diophantine equation is a polynomial equation where the variables can only take on integer values.'
    print 'For example, x^n + y^n = z^n is a famous Diophantine equation. For n=2, there are infinitely many solutions'
    print 'called the Pythagorean triples, e.g. 3^2 + 4^2 = 5^2 \n'
    print 'This program looks at the Diophantine equation 6a + 9b + 20c = n'
    print 'which models the way different combinations of small, medium, and large boxes of chicken McNuggets'
    print 'can be purchased to arrive at a total of n chicken McNuggets. \n'
    print 'This program calculates the largest number of chicken McNuggets that cannot be purchased'
    print 'by using combinations of 6, 9, and 20 packs of McNuggets.\n'

#Variable declarations
n=1           #n is number to be purchased using integer combinations of 6, 9, and 20 packs
count=0       #count of consecutive n values that pass test; when 6 reached, we know by theorem that any larger number n can be bought
largest=0     #largest number of McNuggets that fail test

readBackGround() #read problem set background info

#driver program for test
while (count<6):
   if test(n):     #For each instance of n, perform test.  If pass, increment counter
      count=count+1
   else:             #If test fails, new largest value is n, reset counter to 0
      count=0
      largest=n  
   n=n+1

#print final output message
print 'The largest number of McNuggets that cannot be bought in exact quantity: ',largest

