from string import *

def countSubStringMatch(target,key):
    iter=0
    ctr=0
    while(iter<=(len(target)-len(key)) and iter >=0):
        iter=target.find(key,iter)
        #print iter
        if(iter >= 0):
            ctr+=1
            iter=iter+len(key)            
    return ctr


def countSubStringMatchRecursive(target,key):    
    cut=target.find(key)    #base case
    if(cut==-1):
        return 0
    else:
        target=target[(cut+len(key)):]
        #print 'cut target= ',target
        return (1 + countSubStringMatchRecursive(target,key))
    

#testing functions
print 'enter target string'
target=raw_input()
print 'enter key to search'
key=raw_input()

count = countSubStringMatch(target,key)    
print 'Using iterative function, number of matches found for key in target string: ', count
count = countSubStringMatchRecursive(target,key)    
print 'Using recursive function, number of matches found for key in target string: ', count



