# -*- coding: utf-8 -*-
"""
Created on Wed Apr 10 16:26:20 2019
This reads a file containing a list of strings, and will write to a file which shows the minimum
unique substring that identifies the string.
"""
import copy

class MySuffixTree(object):
    class Node(object):
        def __init__(self, refs):
            self.ref = refs
            self.labels = []
            self.edge = []
            
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
    
    def __init__(self):
        self.root = self.Node("")
        self.words = []
    
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
                    curlen += 1
                    curnode.edge.append(self.Node(curstr[0]))
                    nextnode = curnode.edge[-1]
                    nextnode.labels.append([curword, i, curlen])
                    curnode = nextnode
                    curstr = curstr[1:]
                elif preflen[nextind] == len((curnode.edge[nextind]).ref): # perfect match found
                    print("Perfect Match: %s" % ((curnode.edge[nextind]).ref))
                    curnode = curnode.edge[nextind] # move to next node
                    curlen += len(curnode.ref)
                    curnode.labels.append([curword, i, curlen])
                    curstr = curstr[len(curnode.ref):]
                else: # imperfect match found
                    curnode = curnode.edge[nextind]
                    matchlen = preflen[nextind]
                    print("Imperfect Match: %s out of %s" % (curnode.ref[:matchlen], curnode.ref))
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
    
def finduniqquery(tree, ban = "\n"):
    query = []
    for entry in tree.words:
        query.append(None)
    queue = [tree.root]
    while None in query:
        curnode = queue.pop(0)
        if ban in curnode.ref:
            None
        elif (len(curnode.labels) > 0) and \
             (len(set(map(lambda x: x[0], curnode.labels))) == 1):
            curlab = min(curnode.labels, key = lambda x: x[2])
            if (query[curlab[0]] is None) or \
               (len(query[curlab[0]]) > (curlab[2]-len(curnode.ref)+1)):
                query[curlab[0]] = (tree.words[curlab[0]])[curlab[1]:
                      curlab[1]+curlab[2]-len(curnode.ref)+1]
        else:
            queue += curnode.edge
    out = {}
    for i in zip(tree.words, query):
        out[i[0]] = i[1]
    return out

def createtreefromfile(fname):
    f = open(fname, "r")
    out = MySuffixTree()
    for x in f:
        if x[-1] == '\n':
            x = x[:-1]
        out.addword(x)
    return out

t = MySuffixTree()