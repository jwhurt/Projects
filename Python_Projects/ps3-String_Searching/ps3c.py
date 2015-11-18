from string import *
#Problem 3, pset3, MIT 6.00 f2008

#  target strings
target1 = 'atgacatgcacaagtatgcat'
target2 = 'atgaatgcatggatgtaaatgcag'
target3 = 'abracadabra'

# key strings
key10 = 'a'
key11 = 'atg'
key12 = 'atgc'
key13 = 'atgca'
key14 = 'abba'

#this is the same function we wrote in problem 2
def subStringMatchExact(target,key):
    iter=0
    matches=[]
    if(len(key)==0):
        for iter in range(len(target)-len(key)):
            matches.append(target.find(key,iter))
        return tuple(matches)
    else:
        while(iter<=(len(target)-len(key)) and iter >=0):
            iter=target.find(key,iter)
            if(iter >= 0):
                matches.append(iter)        
                iter=iter+len(key)            
        return tuple(matches)

#precondition: firstMatch is a tuple representing starting points for the first substring
# secondMatch is tuple representing starting points of second substring, 
# length is the length of the first substring
#postcondition: function returns a tuple of all members(n) of the first tuple for which
#  there is an element(k) in the second tuple such that n+m+1=k
def constrainedMatchPair(firstMatch,secondMatch,length):    
    n=[]
    for itr2 in secondMatch:
      #  print 'itr1=',itr2
        for itr1 in firstMatch:
            if(itr1+length+1==itr2):
                n.append(itr1)
    return tuple(n)



### the following procedure you will use in Problem 3
#this function tests the constrainedMatchPair function
def subStringMatchOneSub(key,target):
    """search for all locations of key in target, with one substitution"""
    allAnswers = ()
    for miss in range(0,len(key)):
        # miss picks location for missing element
        # key1 and key2 are substrings to match
        key1 = key[:miss]
        key2 = key[miss+1:]
        print 'breaking key',key,'into',key1,key2
        # match1 and match2 are tuples of locations of start of matches
        # for each substring in target
        match1 = subStringMatchExact(target,key1)
        match2 = subStringMatchExact(target,key2)
        # when we get here, we have two tuples of start points
        # need to filter pairs to decide which are correct
        filtered = constrainedMatchPair(match1,match2,len(key1))
        allAnswers = allAnswers + filtered
        print 'match1',match1
        print 'match2',match2
        print 'possible matches for',key1,key2,'start at',filtered
    return allAnswers


#testing       
key=key13
target=target2

print 'target, key: ',target,key
print subStringMatchOneSub(key,target)
