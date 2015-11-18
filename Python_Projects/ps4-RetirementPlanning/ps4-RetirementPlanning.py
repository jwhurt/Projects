#
# Problem 1
#

def nestEggFixed(salary, save, growthRate, years):
    """
    - salary: the amount of money you make each year.
    - save: the percent of your salary to save in the investment account each
      year (an integer between 0 and 100).
    - growthRate: the annual percent increase in your investment account (an
      integer between 0 and 100).
    - years: the number of years to work.
    - return: a list whose values are the size of your retirement account at
      the end of each year.
    """
    # TODO: Your code here.
    if(years<1):
        return 'error, years must be at least 1'
    if(years==1):
        base=salary*save*0.01
        return [base]
    else:
        currentYrSavings=salary*(save*.01)
        valuesList=nestEggFixed(salary,save,growthRate,years-1)
        lastElement=valuesList[years-2]
        nextElement=lastElement*(1+growthRate*.01)+currentYrSavings
        return valuesList+[nextElement]

#recursive implementation of the function above
#postcondition:  function returns list F, representing retirement fund values at end of each year
def nestEggFixedRecursive(salary, save, growthRate, years):

    #recursive function that does actual work to fill out list values for each year
    def nestEggFixedRec(salary, save, growthRate, years, F):
        if(years==1):  #base case is 1 year; cannot have less than 1 yr
            F.append(salary*save*.01)
            return F[years-1]
        else:
            F.append(nestEggFixedRec(salary, save, growthRate, years-1,F)*(1+growthRate*.01)+(salary*save*.01))
            return F[years-1]
    
    F=[]#declare empty list F, representing Fund value at end of each yr; this will be passed (by reference) to the recursive function to do the work
    nestEggFixedRec(salary, save, growthRate, years, F)  #works on F, filling in the Fund values at year 1,2,...
    return F  

def testNestEggFixed():
    salary     = 10000
    save       = 10
    growthRate = 15
    years      = 5
    savingsRecord = nestEggFixed(salary, save, growthRate, years)
    
    print savingsRecord
    # Output should have values close to:
    # [1000.0, 2150.0, 3472.5, 4993.375, 6742.3812499999995]

    # TODO: Add more test cases here.

def testNestEggFixedRec():
    salary     = 10000
    save       = 10
    growthRate = 15
    years      = 5
    savingsRecord = nestEggFixedRecursive(salary, save, growthRate, years)
    
    print savingsRecord
    # Output should have values close to:
    # [1000.0, 2150.0, 3472.5, 4993.375, 6742.3812499999995]

    # TODO: Add more test cases here.

#
#  Problem 2
#

def nestEggVariable(salary, save, growthRates):
    """
    - salary: the amount of money you make each year.
    - save: the percent of your salary to save in the investment account each
      year (an integer between 0 and 100).
    - growthRate: the annual percent increase in your investment account (an
      integer between 0 and 100).
    - years: the number of years to work.
    - return: a list whose values are the size of your retirement account at
      the end of each year.
    """
    # TODO: Your code here.

    F=[] #declare list to store retirement fund values at end of each yr
    for yr in range(len(growthRates)):
        if yr==0:
            F.append(salary*save*.01)  #in yr 0 we only have contribution to fund; growth occurs in yr 1
        else:
            F.append(F[yr-1]*(1+growthRates[yr]*.01)+(salary*save*.01))
    return F
                     

def testNestEggVariable():
    salary      = 10000
    save        = 10
    growthRates = [3, 4, 5, 0, 3]

#    growthRates = [3,4,5]
    savingsRecord = nestEggVariable(salary, save, growthRates)
    print savingsRecord
    # Output should have values close to:
    # [1000.0, 2040.0, 3142.0, 4142.0, 5266.2600000000002]

    # TODO: Add more test cases here.


#
# Problem 3
#

def postRetirement(savings,growthRates,expenses):
    F=[]
    for yr in range(len(growthRates)):
        if yr==0:
            F.append(savings*(1+growthRates[yr]*.01)-expenses)
        else:
            F.append(F[yr-1]*(1+growthRates[yr]*.01)-expenses)
    return F
        

def testPostRetirement():
    savings     = 100000
    growthRates = [10, 5, 0, 5, 1]
#    growthRates = []
    expenses    = 30000
    savingsRecord = postRetirement(savings, growthRates, expenses)
    print savingsRecord
    # Output should have values close to:
    # [80000.000000000015, 54000.000000000015, 24000.000000000015,
    # -4799.9999999999854, -34847.999999999985]

    # TODO: Add more test cases here.



#
# Problem 4
#

#this function determines the maximum expenses per year that results in a final year fund value close to 0 (epsilon)
#bisection search is used to find the expense amount
def findMaxExpenses(salary,save,preRetireGrowthRates,postRetireGrowthRates,epsilon):
    """
    - salary: the amount of money you make each year.
    - save: the percent of your salary to save in the investment account each
      year (an integer between 0 and 100).
    - preRetireGrowthRates: a list of annual growth percentages on investments
      while you are still working.
    - postRetireGrowthRates: a list of annual growth percentages on investments
      while you are retired.
    - epsilon: an upper bound on the absolute value of the amount remaining in
      the investment fund at the end of retirement.
    """
    F=nestEggVariable(salary,save,preRetireGrowthRates)  #get F, list of fund values for work years using problem 1
    savings=F[-1]  #last value in list is nest egg we enter retirement years with
    min=0
    max=savings
    guess=(min+max)/2.0  #initial guess of expenses
    F=postRetirement(savings,postRetireGrowthRates,guess)   #now get F, list of fund values for retirement years using expenses guess
    while(abs(F[-1])>epsilon):
        if F[-1]> epsilon:
            min=guess
        else:
            max=guess
        guess=(min+max)/2.0
        F=postRetirement(savings,postRetireGrowthRates,guess)   
    return guess

#recursive version of the findMaxExpenses function; uses recursion instead of iteration 
#during binary search; generates same results as iterative version of function
def findMaxExpensesR(salary,save,preRetireGrowthRates,postRetireGrowthRates,epsilon):
    """
    - salary: the amount of money you make each year.
    - save: the percent of your salary to save in the investment account each
      year (an integer between 0 and 100).
    - preRetireGrowthRates: a list of annual growth percentages on investments
      while you are still working.
    - postRetireGrowthRates: a list of annual growth percentages on investments
      while you are retired.
    - epsilon: an upper bound on the absolute value of the amount remaining in
      the investment fund at the end of retirement.
    """
    assert len(preRetireGrowthRates)>0,'preRetireGrowthRates error'
    assert len(postRetireGrowthRates)>0,'postRetireGrowthRates error'
    fundValsPreRetirement=nestEggVariable(salary,save,preRetireGrowthRates)
    print 'pre-retirement fund values = ',fundValsPreRetirement
    savings=fundValsPreRetirement[len(fundValsPreRetirement)-1]
    low=0
    high=savings
    
    #definition of recursive function within the function findMaxExpensesR
    def expenseGuesser(low,high,savings,postRetireGrowthRates,epsilon):
        """
        -low:  the low value for the binary search range
        -high:  the high value for the binary search range
        -savings: the total nest egg value at last year of career, pre retirement
        - postRetireGrowthRates: a list of annual growth percentages on investments
          while you are retired.
        - epsilon: an upper bound on the absolute value of the amount remaining in
          the investment fund at the end of retirement.
        """
        guess=(low+high)/2.0
        fundVals=postRetirement(savings,postRetireGrowthRates,guess)
        endValue=fundVals[len(fundVals)-1]
        #base case
        if(abs(endValue)<=epsilon):
            return guess
        #reduction
        elif (endValue<0):
            high=guess
        else:
            low=guess
        return expenseGuesser(low,high,savings,postRetireGrowthRates,epsilon)    

        #guess annual expenses during retirement by calling recursive function
    return expenseGuesser(low,high,savings,postRetireGrowthRates,epsilon)



def testFindMaxExpenses():
    salary                = 10000
    save                  = 10
    preRetireGrowthRates  = [3, 4, 5, 0, 3]
    postRetireGrowthRates = [10, 5, 0, 5, 1]
    epsilon               = .01
    expenses = findMaxExpenses(salary, save, preRetireGrowthRates,
                               postRetireGrowthRates, epsilon)
    print expenses
    # Output should have a value close to:
    # 1229.95548986

    # TODO: Add more test cases here.
print 'testing problem 1, nest egg fixed (iterative implementation):'
testNestEggFixed()
print 'testing problem 1, nest egg fixed (recursive implementation):'
testNestEggFixedRec()
print 'testing problem 2, nest egg variable:'
testNestEggVariable()
print 'testing problem 3, post retirement:'
testPostRetirement()
print 'testing problem 4, find maximum expenses:'
testFindMaxExpenses()
