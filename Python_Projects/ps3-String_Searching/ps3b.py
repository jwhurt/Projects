from string import *
#Problem 2, pset3, MIT6.00 f2008

#  target strings
target1 = 'atgacatgcacaagtatgcat'
target2 = 'atgaatgcatggatgtaaatgcag'
target3 = 'abba'

# key strings
key10 = 'a'
key11 = 'atg'
key12 = 'atgc'
key13 = 'atgca'
key14 = 'ab'


#precondition:  target string and key to search are passed as arguments
#postcondition: function returns a tuple of the starting index positions where key is found
def subStringMatchExact(target,key):
    iter=0
    matches=[]
    while(iter<=(len(target)-len(key)) and iter >=0):
        iter=target.find(key,iter)
        if(iter >= 0):
            matches.append(iter)        
            iter=iter+len(key)            
    return tuple(matches)

#as an optional project I developed a recursive version of the above
#The recursive version needs a third parameter to track distance from original 0 index,
#and a list needs to be used instead of a tuple, because the list needs to be changed
def subStringMatchExactRec(target,key,dist):    
    matches=[]
    pos=target.find(key)    #base case
    if(pos==-1):
        return matches
    else:
        matches.append(pos+dist)
        cut=pos+len(key)
        target=target[cut:]
        dist=dist+cut
        matches=matches+(subStringMatchExactRec(target,key,dist))
        return matches


target=target2
key=key11
print 'Target string:',target,', key:',key
print 'Starting index positions using iterative method:',subStringMatchExact(target,key)    
print 'Starting index positions using recursive method:',subStringMatchExactRec(target,key,0)
