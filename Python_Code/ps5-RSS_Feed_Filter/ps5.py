# 6.00 Problem Set 5
# RSS Feed Filter

import feedparser
import string
import time
from project_util import translate_html
from news_gui import Popup

#-----------------------------------------------------------------------
#
# Problem Set 5

#======================
# Code for retrieving and parsing
# Google and Yahoo News feeds
# Do not change this code
#======================

def process(url):
    """
    Fetches news items from the rss url and parses them.
    Returns a list of NewsStory-s.
    """
    feed = feedparser.parse(url)
    entries = feed.entries
    ret = []
    for entry in entries:
        guid = entry.guid
        title = translate_html(entry.title)
        link = entry.link
        summary = translate_html(entry.summary)
        try:
            subject = translate_html(entry.tags[0]['term'])
        except AttributeError:
            subject = ""
        newsStory = NewsStory(guid, title, subject, summary, link)
        ret.append(newsStory)
    return ret

#======================
# Part 1
# Data structure design
#======================

# Problem 1
#Class represents a parsed news story; data stream is turned into a structured format that is easier to work with
#Code that retrieves and parses Google and Yahoo news feeds has been provided; this code instantiates newsStory object with following arguments:
#GUID-globally unique identifier, a unique name for parsed story entry
#title-string for story title
#subject,summary,link all self explanatory
#This creates a story object that gets passed around to the rest of the program.
class NewsStory(object):
    def __init__(self,guid,title,subject,summary,link):
        self.guid=guid
        self.title=title
        self.subject=subject
        self.summary=summary
        self.link=link
   
    def get_guid(self):
        return self.guid

    def get_title(self):
        return self.title
    
    def get_subject(self):
        return self.subject

    def get_summary(self):
        return self.summary

    def get_link(self):
        return self.link
    



#======================
# Part 2
# Triggers
#======================
#Triggers evaluate stories, generate alert when story meets trigger criteria. 
#Trigger is an interface that defines which methods must be present  subclass.  Subclasses of Trigger must implement the evaluate method. 
#Evaluate can be implemented in different ways by trigger subclasses-example of polymorphism
class Trigger(object):
    def evaluate(self, story):
        """
        Returns True if an alert should be generated
        for the given news item, or False otherwise.
        story=NewsStory object
        """
        raise NotImplementedError

# Whole Word Triggers
# Problems 2-5

# TODO: WordTrigger
#WordTrigger is abstract class, meaning we won't directly instantiate a WordTrigger object
#Subclasses of WordTrigger will inherit the is_word_in method; they will use this method to determine if word is found in an attribute of the newsStory
#Examples of newsStory attribute text that will be passed to is_word_in for evaluation include title, subject, and summary.
#is_word_in returns boolean; True if word present in text, false otherwise
#is_word_in takes text as argument, removes punctuation, converts to lowercase, then splits into word list

 
class WordTrigger(Trigger):
    def __init__(self,word):
        """
        word to search for is incoming argument
        """
        self.word=word.lower()  #convert incoming word to lower case

    def is_word_in(self,text):
        """
        Returns True if whole word is present in text and False otherwise
        """
        def removePunct(text):
            for i in text:
                if i in string.punctuation:
                    text=text.replace(i,' ')
            return text
        textWords=(removePunct(text).lower()).split()
        return (self.word in textWords)

#TitleTrigger inherits from WordTrigger; is a WordTrigger
#evaluate method uses inherited superclass method is_word_in to determine if word in story title    
class TitleTrigger(WordTrigger):    
    def evaluate(self, story):
        """
        searches for word in title 
        returns True if word found, False otherwise
        """

        return(self.is_word_in(story.get_title()))
            

# TODO: SubjectTrigger
#evaluate method looks for word in story subject; example of polymorphism
class SubjectTrigger(WordTrigger):
    def evaluate(self, story):
        """
        searches for word in title 
        returns True if word found, False otherwise
        """
        return(self.is_word_in(story.get_subject()))
    


# TODO: SummaryTrigger
#evaluate method looks for word in story summary; example of polymorphism
class SummaryTrigger(WordTrigger):
    def evaluate(self, story):
        """
        searches for word in title 
        returns True if word found, False otherwise
        """
        return(self.is_word_in(story.get_summary()))


# Composite Triggers
# Problems 6-8

# TODO: NotTrigger
class NotTrigger(Trigger):

#constructor takes trigger as argument, which becomes instance variable
    def __init__(self,trigger):
        self.trigger=trigger
#evaluate method has same specification as Trigger superclass in order to maintain polymorphism
#story passed as argument will be evaluated by the trigger instance variable's evaluate() method, resulting evaluation inverted and returned
    def evaluate(self,story):
        #returns the opposite of trigger.evaluate(NewsStoryObj)
        return not (self.trigger.evaluate(story))

# TODO: AndTrigger
class AndTrigger(Trigger):
#class creates object which takes two triggers as arguments and returns the logical AND of their evaluate methods
#constructor takes two triggers as arguments that are assigned to object instance variables
    def __init__(self,trigger1, trigger2):
        self.trigger1=trigger1
        self.trigger2=trigger2
    
    def evaluate(self,story):
#retuns the logical and of the trigger's evaluate methods
        return  (self.trigger1.evaluate(story) and self.trigger2.evaluate(story))

# TODO: OrTrigger
class OrTrigger(Trigger):
#class creates object which takes two triggers as arguments and returns the logical OR of their evaluate methods
    def __init__(self,trigger1, trigger2):
        self.trigger1=trigger1
        self.trigger2=trigger2
    
    def evaluate(self,story):
        #returns the opposite of trigger.evaluate(NewsStoryObj)
        return  (self.trigger1.evaluate(story) or self.trigger2.evaluate(story))

# Phrase Trigger
# Question 9

# TODO: PhraseTrigger
class PhraseTrigger(Trigger):
#constructor takes incoming phrase as attribute
    def __init__(self,phrase):
        self.phrase=phrase
#evaluate method returns true if phrase in any part of newsfeed title,subject or summary; returns false otherwise
    def evaluate(self,story):
        return self.phrase in story.get_title()+story.get_subject()+story.get_summary()

    
    
#======================
# Part 3
# Filtering
#======================

def filter_stories(stories, triggerlist):
    """
    Takes in a list of NewsStory-s.
    Returns only those stories for whom
    a trigger in triggerlist fires.
    
    argument1:  stories, a list comprised of newsStory objects
    argument2:  triggerlist:  a list comprised of trigger objects
    """
    # TODO: Problem 10

    filtered_stories=[]  #new story list will contain filted stories
    for s in stories:
        for t in triggerlist:
            if (t.evaluate(s)):
                filtered_stories.append(s)
                break
#this block necessary to print filtered feed in emacs editor.  pop up not working in emacs
    for s in filtered_stories:
            print 'title= ',s.get_title()
            print s.get_link()
    return filtered_stories

#======================
# Part 4
# User-Specified Triggers
#======================
def readTriggerConfig(filename):
    """
    Returns a list of trigger objects
    that correspond to the rules set
    in the file filename
    """
    # Here's some code that we give you
    # to read in the file and eliminate
    # blank lines and comments
    triggerfile = open(filename, "r")
    all = [ line.rstrip() for line in triggerfile.readlines() ]
    lines = []
    for line in all:
        if len(line) == 0 or line[0] == '#':
            continue
        lines.append(line)

    # TODO: Problem 11
    # 'lines' has a list of lines you need to parse
    # Build a set of triggers from it and
    # return the appropriate ones
    
    def BuildTriggers(lines):
        triggerSpecs=[] #list to contain trigger specs from config file lines
        triggers=[]  #list of trigger objects; these triggers will be used to build final list
        triggerlistNames=[]  #list of trigger names to be included in final triggerlist        
        triggerlist=[]  #list of final triggers to return
        triggerDict={}  #trigger dictionary containing trigger name and object

        for line in lines:
            triggerSpecs.append(line.split())        #place trigger parameters in list        
        
        for s in triggerSpecs:
            name=s[0]
            type=s[1]

            if name !='ADD':
                if type =='TITLE':
                    triggerDict[name]=TitleTrigger(s[2])
                elif type == 'SUBJECT':
                    triggerDict[name]=SubjectTrigger(s[2])
                elif type=='SUMMARY':
                    triggerDict[name]=SummaryTrigger(s[2])
                elif type=='PHRASE':
                    phrase=''
                    for p in s[2:len(s)-1]:
                        phrase+= p+' '
                    phrase+=s[len(s)-1]
                    triggerDict[name]=PhraseTrigger(phrase)
                elif type =='AND':
                    trigger1=triggerDict[s[2]]
                    trigger2=triggerDict[s[3]]
                    triggerDict[name]=AndTrigger(trigger1, trigger2)
                elif type =='OR':
                    trigger1=triggerDict[s[2]]
                    trigger2=triggerDict[s[3]]
                    triggerDict[name]=OrTrigger(trigger1, trigger2)
                else:# type =='NOT':
                    trigger1=triggerDict[s[2]]
                    triggerDict[name]=NotTrigger(trigger1)
#add triggers to triggerlist to be returned
            else: 
                for name in s[1:]:
                    triggerlistNames.append(name)
            
            for name in triggerlistNames:
                if name in triggerDict:
                    triggerlist.append(triggerDict[name])

#testing block
#        for key in triggerDict:
#           print 'key, value: ',key, ' ',triggerDict[key]
#        for name in triggerlistNames:
#            print 'trigger name in final list =',name
#        for trigger in triggerlist:
#            print 'trigger in final list =',trigger
#end testing block

        return triggerlist
        
    return (BuildTriggers(lines))
#end function


import thread

def main_thread(p):
    # A sample trigger list - you'll replace
    # this with something more configurable in Problem 11
#    t1 = SubjectTrigger("Obama")
#    t2 = SummaryTrigger("MIT")
#    t3 = PhraseTrigger("Supreme Court")
#    t4 = OrTrigger(t2, t3)
#    triggerlist = [t1, t4]
    
    # TODO: Problem 11
    # After implementing readTriggerConfig, uncomment this line 
    triggerlist = readTriggerConfig("triggers.txt")

    
    guidShown = []
    
    while True:
        print "Polling..."

        # Get stories from Google's Top Stories RSS news feed
        stories = process("http://news.google.com/?output=rss")
        # Get stories from Yahoo's Top Stories RSS news feed
        stories.extend(process("http://rss.news.yahoo.com/rss/topstories"))
        
        # Only select stories we're interested in
        stories = filter_stories(stories, triggerlist)
        
        # Don't print a story if we have already printed it before
        newstories = []
        for story in stories:
            if story.get_guid() not in guidShown:
                newstories.append(story)
        
        for story in newstories:
            guidShown.append(story.get_guid())
            p.newWindow(story)

        print "Sleeping..."
        time.sleep(SLEEPTIME)

SLEEPTIME = 60 #seconds -- how often we poll
if __name__ == '__main__':
### Note,pop up window doesn't seem to work in Emacs Editor.  Using print command instead to print title and link directly in emacs editor
    p = Popup()
    thread.start_new_thread(main_thread, (p,))
    p.start()

