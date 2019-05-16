# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
##def EL(centers,clusters:

print("************** start ***************")
size = 162
clustersnum = 8
array_regsloca = np.zeros((size,2))
ind = 0
with open("./regsloca.data","r") as f:
	for line in f.readlines():
		sline = line.strip("\n")
		lline = line.split(" ")
		array_regsloca[ind][0] = lline[0]
		array_regsloca[ind][1] = lline[1]
		ind = ind+1
ind = 0
centers = np.zeros((clustersnum,2))
with open("./init_centers.data","r") as f:
	for line in f.readlines():
		sline = line.strip("\n")
		lline = line.split(" ")
		centers[ind][0] = lline[0]
		centers[ind][1] = lline[1]
		ind = ind+1
stop = False

while not stop:
	dis0 = 0
	distmp = float('inf')
	num = 0
	clusters = [[0],[0],[0],[0],[0],[0],[0],[0]]
	## clustering for every register
	for i in range(size):
		dis0 = 0
		distmp = float('inf')
		for j in range(clustersnum):
			dis0 = abs(array_regsloca[i][0]-centers[j][0])+abs(array_regsloca[i][1]-centers[j][0])
			if distmp > dis0:
				distmp = dis0
				num = j
		clusters[num].append(i)
	
	
	centerstmp = np.zeros((clustersnum,2))
	EL = 0
	ELpre = float('inf')
	for i in range(clustersnum):
		del clusters[i][0]
		print(clusters[i])
		print('\n')
		x0 = 0
		y0 = 0
		xc = 0
		yc = 0
		for j in range(len(clusters[i])):
			x0 = x0 + array_regsloca[clusters[i][j]][0]
			y0 = y0 + array_regsloca[clusters[i][j]][1]
			EL = EL + abs(array_regsloca[clusters[i][j]][0]-centers[i][0])+abs(array_regsloca[clusters[i][j]][1]-centers[i][1])
		if len(clusters[i])==0:
			continue
		xc = "%.2f" % (x0/len(clusters[i]))
		yc = "%.2f" % (y0/len(clusters[i]))
		centerstmp[i][0] = xc
		centerstmp[i][1] = yc
	#if ELpre > EL:
	#	ELpre = EL
	centers = centerstmp
	alp = abs(EL-ELpre)/ELpre
	if alp<0.05:
		stop = True
	else:
		ELpre = EL

print(clustersnum)
print("EL is "+str(EL))
print("ELpre is " + str(ELpre))
print(centers)









print("************** end ***************")









