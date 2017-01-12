#!/usr/bin/python
# A python2.7 test file to check that my python library.
# 

import os
import sys
import numpy as np
import random as rnd

# need to change chdir to be able to load my c++/python library
sys.path.append(os.getcwd()+"/lib")
import huffman
print "huffman library imported "

my_input = [1,2,3,4]
output = huffman.getCode(my_input)
print "for the probabilities ",my_input 
print output

int_entered = int(raw_input( "enter the number of symbols you want to consider"))

my_input = [rnd.randrange(100) for i in range(int_entered)]
proba = np.array(my_input)/float(sum(my_input))  
output = huffman.getCode(my_input)

def printer(x): 
    print "symbol :", x[0], " proba : ", x[1] , "code : ", x[2] 

map( printer , zip(range(int_entered),proba,output))
