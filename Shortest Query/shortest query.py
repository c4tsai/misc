# -*- coding: utf-8 -*-
"""
Created on Wed Apr 10 16:26:20 2019
This reads a file containing a list of strings, and will output a dict which 
shows the minimum unique substring that identifies the string.
"""
import copy

class MySuffixTree(object):
    class Node(object):
        def __init__(self, refs):
            self.ref = refs  # The string this node represents
            self.labels = [] # Where we can find this string [word#, start position, length]
            self.edge = []   # Which nodes this node links to
            
        def __str__(self):
            out = "{\nRef: %s, Labels: " % (self.ref)
            flag = True
            for i in self.labels:
                if flag:
                    flag = False
                else: 
                    out += ", "
                out += "[%s, %s, %s]" % (i[0], i[1], i[2])
            for i in self.edge:
                out += "\n"
                out += str(i)
            out += "\n}"
            return out
    
    def prefixmatchlen(self, s, node):
        # Helper function that returns how good a match your string is to a node
        out = 0
        tar = node.ref
        for i in range(len(node.ref)):
            try: 
                if s[i] == tar[i]:
                    out += 1
                else: 
                    break
            except:
                break
        return out
    
    def __init__(self, compact = False):
        self.root = self.Node("")
        self.words = []
        self.compact = compact
    
    def addword(self,s):
        self.words.append(s)
        curword = len(self.words) - 1
        for i in range(len(s)):
            curnode = self.root
            curstr = s[i:]
            curlen = 0
            print("\nStarting at Root")
            while curstr:
                print("Current String: %s" % (curstr))
                tmp = "Edges to: "
                for entry in curnode.edge:
                    tmp += entry.ref
                    tmp += ", "
                print(tmp)
                # Check the current node's existing edges
                preflen = list(map(lambda x: self.prefixmatchlen(curstr, x), curnode.edge))
                preflen.append(0) # To remove the case of curnode has no edges
                nextind = max(range(len(preflen)), key = preflen.__getitem__) 
                if preflen[nextind] == 0: # none of the edges matches any character
                    print("No match")
                    if self.compact: # tabulate substrings as well
                        curlen += len(curstr)
                        curnode.edge.append(self.Node(curstr))
                        nextnode = curnode.edge[-1]
                        nextnode.labels.append([curword, i, curlen])
                        curnode = nextnode
                        curstr = ""
                    else: # tabulate every letter seperately
                        curlen += 1
                        curnode.edge.append(self.Node(curstr[0]))
                        nextnode = curnode.edge[-1]
                        nextnode.labels.append([curword, i, curlen])
                        curnode = nextnode
                        curstr = curstr[1:]
                elif preflen[nextind] == len((curnode.edge[nextind]).ref): # perfect match found
                    print("Perfect Match: %s" % 
                          ((curnode.edge[nextind]).ref))
                    curnode = curnode.edge[nextind] # move to next node
                    curlen += len(curnode.ref)
                    curnode.labels.append([curword, i, curlen])
                    curstr = curstr[len(curnode.ref):]
                else: # imperfect match found
                    curnode = curnode.edge[nextind]
                    matchlen = preflen[nextind]
                    print("Imperfect Match: %s out of %s" % 
                          (curnode.ref[:matchlen], curnode.ref))
                    splitnode = self.Node(curnode.ref[matchlen:])
                    splitnode.labels = copy.deepcopy(curnode.labels)
                    splitnode.edge = curnode.edge
                    for entry in curnode.labels:
                        entry[2] -= len(curnode.ref) - matchlen
                    curnode.ref = curnode.ref[:matchlen]
                    curnode.edge = [splitnode]
                    curlen += matchlen
                    curstr = curstr[matchlen:]
                    
    def __str__(self):
        out = "Words: "
        for i in self.words:
            out += "%s, " % (i)
        if len(self.words) > 0:
            out = out[:-2]
        out += "\n"
        out += str(self.root)
        return out
    
def finduniqquery(tree, ban = "\n"): # Note: this only works in compact = False for now
    query = [] # initialize the table
    for entry in tree.words:
        query.append(None)
    queue = [tree.root] # start walking down the tree until we find what we want
    while None in query: # stop when we find at least one entry each
        curnode = queue.pop(0)
        print("Current node %s with labels %s" % (curnode.ref, curnode.labels))
        if len(curnode.ref) > 0 and (ban == curnode.ref[0]): # skip nodes which starts with banned characters
            None # For compact = True this takes care of cases where node is ",s"
        elif (len(curnode.labels) > 0) and \
             (len(set(map(lambda x: x[0], curnode.labels))) == 1):
        # If there is at least one label in the node and all the labels point to the same word
            curlab = min(curnode.labels, key = lambda x: x[2]) # find the shortest
            if (query[curlab[0]] is None) or (len(query[curlab[0]]) > \
                (curlab[2]-len(curnode.ref)+1)):
                # and if the shortest is shorter than what we have
                tmp = query[curlab[0]]
                query[curlab[0]] = (tree.words[curlab[0]])[curlab[1]:
                      curlab[1]+curlab[2]-len(curnode.ref)+1]
                # add everything before the node and the first letter of this node
                print("Changing index %s from %s to %s" % (curlab[0], tmp, query[curlab[0]]))
        else: # otherwise since this node points to more than one word it is not unique
            if ban not in curnode.ref: # if the banned character is not in the rest of ref
                queue += curnode.edge # we look at the node's children
                print("Added %s nodes to queue" % (len(curnode.edge)))
    out = {} # We make a dictionary to return
    for i in zip(tree.words, query):
        out[i[0]] = i[1]
    return out

def createtreefromfile(fname, compact = False):
    f = open(fname, "r")
    out = MySuffixTree(compact)
    for x in f:
        if x[-1] == '\n':
            x = x[:-1]
        out.addword(x)
    return out

t = MySuffixTree()