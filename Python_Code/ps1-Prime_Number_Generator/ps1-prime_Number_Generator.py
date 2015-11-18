#This program finds prime numbers and identifies the nth prime.  
#This program evolved from problem set 1a, course 6.00, Fall 2008 MIT OCW.
#A number is prime if it is an integer only divisible by 1 and itself.  By definition, 1 is not a prime number. 2 is the smallest prime number.
#Originally the project assignment was to calculate the 1000th prime(7919).  It has since been modified to allow the user
#to enter n in order to calculate the nth prime number.  A further modification allows the user to print the list of primes 
#found while calculating the nth prime.  

#This function builds an array of prime numbers up to and including the nth prime, where n is passed as an argument by client
def buildPrimeArray(n,primeArray):
    """Precondition:  n is a positive integer, representing number of primes to find 
       Postcondition:  function returns the array of prime numbers it has built"""    
    if(n>=1):
        #local variable declarations
        oddIntCandidate=3  #odd integers are candidates for primes, since evens are divisible by 2. The first candidate is 3
        isPrime=True; #bool to represent if the candidate is a prime number
        primeArray.append(2) #array of primes which grows as new primes discovered.  It is initialized with first prime,2    

        #loop to build array of primes
        while(len(primeArray)<n):#stop looping when n primes have been placed in array, the nth prime is last element of the primeArray    
            #attempt to divide next odd integer candidate by each prime in the array        
            for prime in primeArray:        
                if(prime>oddIntCandidate/prime): #if the prime is greater than its possible cofactor, the cofactor would have been found already
                    break        
                if(oddIntCandidate%prime==0): #if a prime divides the candidate, the candidate is not prime
                    isPrime=False
                    break
            if(isPrime): #upon completion of division by prime array elements, test if the candidate was prime
                primeArray.append(oddIntCandidate) #add prime to array
            oddIntCandidate+=2  #increment to next candidate
            isPrime=True #reset prime test result variable    

#function for getting user to input value
#precondition:  arguments valType is the type of value expected, promptMesg is displayed on terminal to prompt user for input
# errMesg is the message to be displayed when ValueError exception is generated           
#postcondition: function returns value input by user; continues looping until user enters correct type
def getValue(valType,promptMesg,errMesg):
    while(True):
        val=raw_input(promptMesg)
        try:
            val=valType(val) #if string is not of type requested, a ValueError will be raised and program will skip to except block
            break
        except ValueError:  #this block will handle the exception gracefully
            print (val+errMesg)
    return val

#This function is driver program for the buildPrimeArray function.  It manages the user interface and calls on buildPrimeArray to 
#generate an array of primes, from which the user can select a given prime
def testBuildPrimeArray():
    arrayOfPrimes=[] #declare initial prime array
    print'This program calculates prime numbers.  You will be asked to enter a number representing how many prime numbers to calculate.'
    print'After the program has calculated the number of primes you selected, you can choose to pick an individual prime or print the entire list.\n'
    n=getValue(int,'Enter an integer for the number of primes to calculate: ',' is not an integer')
    print 'Calculating primes...',
    buildPrimeArray(n,arrayOfPrimes) #call function to build array of primes up to the nth prime
    print 'done'
    while(True):        
        print'\n..........Menu..........'
        print'\'n\'....select the nth prime of the list'
        print'\'p\'....print entire list of primes calculated'
        print'\'q\'....quit'        
        option=raw_input('enter option>')
        if(option=='n'):            
            n=getValue(int,'Enter an integer n to receive the nth prime in the sequence of primes: ',' is not an integer')
            if(n>len(arrayOfPrimes)):
                print 'Sorry, the prime corresponding to that value of n was not calculated.'
            elif(n>=1):
                if(n==1):
                    print 'The 1st prime is:',arrayOfPrimes[n-1]
                elif(n==2):
                    print 'The 2nd prime is:',arrayOfPrimes[n-1]
                elif(n==3):
                    print 'The 3rd prime is:',arrayOfPrimes[n-1]
                else:
                    print 'The '+str(n)+'th prime is:',arrayOfPrimes[n-1]
            else:
                print 'Invalid n'
        elif(option=='p'):
            print 'List of',n,'primes:'
            rowCounter=0 #sentinel to count number of primes to print in a row, we want 10
            for prime in arrayOfPrimes:
                #right justify the prime number for printout
                if len(str(prime))==1:
                    prime='   '+str(prime)  
                elif len(str(prime))==2:
                    prime='  '+str(prime)  
                elif len(str(prime))==3:
                    prime=' '+str(prime)
                else:
                    prime=str(prime)
                if rowCounter<10:
                    print prime,'  ', #print a prime on same line
                    rowCounter+=1
                else:
                    print '\n',       #print last space to
                    print prime,'  ',      #print on next line
                    rowCounter=1
        elif(option=='q'):
            break
        else:
            print 'Invalid option'

#run program
testBuildPrimeArray()



