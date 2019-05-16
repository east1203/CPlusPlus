# -*- coding: utf-8 -*-
"""
Created on Sun May  5 18:10:10 2019

@author: dongyongkang
"""

"""
kruksal MST算法，从regsloca.data文件中读取寄存器的坐标，然后生成最小生成树

设有一个有n个顶点的连通网N={V,E},最初先构造一个只有n个顶点，没有边的非连通图T={V, E},
图中每个顶点自成一个连通分量。当在E中选到一条具有最小权值的边时,若该边的两个顶点落在不同的连通分量上，
则将此边加入到T中；否则将此边舍去，重新选择一条权值最小的边。如此重复下去，直到所有顶点在同一个连通分量上为止。
--------------------- 

原文：https://blog.csdn.net/HeiSeDiWei/article/details/50340723 

"""

# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
from time import *
import kruskalmst

#size = 162
#size = 1728
#size = 1159
size = 162
array_regsdist = np.zeros((size,size)) # 保存每两个寄存器之间的距离
array_regsloca = np.zeros((size,2))  # 保存每个寄存器的位置
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


time1 = time()
print("************** start Krukcal minimum spanning tree algorithm***************")

time2 = time()

lengthDist = len(array_regsdist)			#邻接矩阵大小
############ Krukcal minimun spanning tree
xsum = 0; ## 保存MST中连接点之间的x坐标之和   用来后续求电容
ysum = 0; ## 保存MST中连接点之间y坐标之和
group = []
startindex = []  ## 保存边的起点标号
endindex = []    ## 保存边的终点标号
weight = []      ## 保存边的权重

for i in range(lengthDist):
    group.append([i])
    for j in range(i+1,lengthDist):
        startindex.append(i)				#每条边的起点
        endindex.append(j)					#每条边的终点
        weight.append(array_regsdist[i][j])	#每条边的权值

lengthEdge = len(weight)  ## 边的总个数，也就是 size+(size-1)+(size-2)+..+2+1
print("lengthEdge is :"+str(lengthEdge))
G2 = nx.Graph()
G2Point = []
G2Weight = []

time3 = time()
####################
I = np.argsort(weight)				#升序,返回索引  numpy.argsort
                        ## 根据权重对边升序排序，依次判断边是否属于MST
i = 0
for i in range(lengthEdge):
    for j in range(lengthDist):
        if startindex[I[i]] in group[j]:
            m = j
        if endindex[I[i]] in group[j]:
            n = j

    if m != n:				#判断当前这条边是否属于不同的连通分量，如果是，将其合并
        group[m] = group[m] + group[n]
        group[n] = []              
        ## 对MST上每条边的权重的x，y成分分别求和，用来后续求电容
        xsum = xsum + abs(array_regsloca[m][0]-array_regsloca[n][0])
        ysum = ysum + abs(array_regsloca[m][1]-array_regsloca[n][1])
        

        G2.add_edge(startindex[I[i]],endindex[I[i]],weight=array_regsdist[startindex[I[i]]][endindex[I[i]]])
        G2Point.append((startindex[I[i]],endindex[I[i]]))
        G2Weight.append(array_regsdist[startindex[I[i]]][endindex[I[i]]])
        
"""
for i in range(lengthEdge):
    I = np.argsort(weight)[0]				#升序,返回索引  numpy.argsort
    
    for j in range(lengthDist):
        if startindex[I] in group[j]:
            m = j
        if endindex[I] in group[j]:
            n = j

    if m != n:				#判断当前这条边是否属于不同的连通分量，如果是，将其合并
        group[m] = group[m] + group[n]
        group[n] = []              
        ## 对MST上每条边的权重的x，y成分分别求和，用来后续求电容
        xsum = xsum + abs(array_regsloca[m][0]-array_regsloca[n][0])
        ysum = ysum + abs(array_regsloca[m][1]-array_regsloca[n][1])
        

        G2.add_edge(startindex[I],endindex[I],weight=array_regsdist[startindex[I]][endindex[I]])
        G2Point.append((startindex[I],endindex[I]))
        G2Weight.append(array_regsdist[startindex[I]][endindex[I]])
        
    del weight[I]                       #删除遍历过的边以及顶点
    del startindex[I]
    del endindex[I]	
"""
time4 = time()

print(time2 - time1)
print(time3 - time2)
print(time4 - time3)
print(time4 - time1)
#nx.draw(G2,with_labels=True)
#plt.subplot(121)
nx.draw_networkx_nodes(G2, pos,node_size=25)
nx.draw_networkx_edges(G2,pos)
nx.draw_networkx_labels(G2, pos,font_size=8, font_family='sans-serif')
#nx.draw(G2,pos,node_size=50)
plt.savefig("G2.png")  # save as png
#plt.show()

#plt.savefig(str(a)+"-"+str(groupNum)+"-"+"G3.png")  # save as png
print(len(G2Point))