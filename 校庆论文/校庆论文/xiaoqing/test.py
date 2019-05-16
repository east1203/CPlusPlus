# -*- coding: utf-8 -*-
"""
Created on Sun May  5 18:10:10 2019

@author: dongyongkang
"""

# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
from time import *
from xiaoqing import *

#size = 162
#size = 1728
#size = 1159
size = 162
array_regsdist = np.zeros((size,size))
array_regsloca = np.zeros((size,2))
ind = 0
with open("./s5378/regsloca.data","r") as f:
	for line in f.readlines():
		sline = line.strip("\n")
		lline = line.split(" ")
		array_regsloca[ind][0] = lline[0]
		array_regsloca[ind][1] = lline[1]
		ind = ind+1
## get distance between registers
for i in range(size):
	for j in range(size):
		array_regsdist[i][j] = abs(array_regsloca[i][0]-array_regsloca[j][0]) + abs(array_regsloca[i][1]-array_regsloca[j][1])

#作图时，点的坐标
pos = np.zeros((size,2))
for i in range(size):
	pos[i] = array_regsloca[i]


#xsum,ysum,G2Point = kruskalmst(size,array_regsloca,array_regsdist,pos)
#print(str(xsum)+"***"+str(ysum))


fpWidth = 51.1
fpHeight = 50.4
a = 1.3
num = InitCenters(size,array_regsloca,array_regsdist,fpWidth,fpHeight,a)


