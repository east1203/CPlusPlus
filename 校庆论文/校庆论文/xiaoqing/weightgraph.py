# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
import clusterDemo
print("************** start ***************")
#size = 128
#size = 1728
#size = 1159
size = 214
fpWidth = 53.7
fpHeight = 53.76

a = 1.2
array_regsdist = np.zeros((size,size))
array_regsloca = np.zeros((size,2))
ind = 0
## 从文件regsloca.data中读取每个寄存器的位置
with open("./regsloca.data","r") as f:
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

lengthDist = len(array_regsdist)			#邻接矩阵大小

############ Krukcal minimun spanning tree
group = []
startindex = []
endindex = []
weight = []

for i in range(lengthDist):
	group.append([i])
	for j in range(i+1,lengthDist):
		startindex.append(i)				#每条边的起点
		endindex.append(j)					#每条边的终点
		weight.append(array_regsdist[i][j])	#每条边的权值

lengthEdge = len(weight)
print("lengthEdge is :"+str(lengthEdge))

G3 = nx.Graph()
for i in range(size):
    G3.add_node(i)


print("a' value is "+str(a))
NumRegs = size
EL = a*sqrt(fpWidth*fpHeight/NumRegs)
print("the EL is " + str(EL))
groupNum = 1

G3startindex = []
G3endindex = []
G3weight = []
G3group = []
for i in range(lengthDist):
	G3group.append([i])

I = np.argsort(weight)				#升序,返回索引  numpy.argsort
for i in range(lengthEdge):
	
	for j in range(lengthDist):
		if startindex[I[i]] in group[j]:
			m = j
		if endindex[I[i]] in group[j]:
			n = j
	if m != n:				#判断当前这条边是否属于不同的连通分量，如果是，将其合并
		group[m] = group[m] + group[n]
		group[n] = []
       # G2.add_edge(startindex[I],endindex[I],weight=array_regsdist[startindex[I]][endindex[I]])
		## 边长小于EL的边保存到新图G3中，G3作为截断长边后的新图
		if array_regsdist[startindex[I[i]]][endindex[I[i]]] <= EL:
				G3.add_edge(startindex[I[i]],endindex[I[i]],weight=array_regsdist[startindex[I[i]]][endindex[I[i]]])
				G3startindex.append(startindex[I[i]])				#每条边的起点
				G3endindex.append(endindex[I[i]])					#每条边的终点
				G3weight.append(array_regsdist[startindex[I[i]]][endindex[I[i]]])	#每条边的权
		else:
			groupNum = groupNum + 1


for i in range(len(G3weight)):
	for j in range(lengthDist):
		if G3startindex[i] in G3group[j]:
			m = j
		if G3endindex[i] in G3group[j]:
			n = j
	if m!= n:	
		if array_regsdist[G3startindex[i]][G3endindex[i]] <= EL:
			G3group[m] = G3group[m] + G3group[n]
			G3group[n] = []

print("the register clusters number is : "+str(groupNum))


nx.draw_networkx_nodes(G3, pos,node_size=25)
nx.draw_networkx_edges(G3,pos)
#nx.draw_networkx_labels(G3, pos,font_size=8, font_family='sans-serif')
#nx.draw(G3,pos,node_size=50,with_labels=True,font_size=8)
#plt.savefig(str(a)+"-"+str(groupNum)+"-"+"G3.png")  # save as png
plt.show()

x0 = 0
y0 = 0
xc = 0
yc = 0
print("G3group is : ")
print(G3group)
## 求每个群组的初始中心点并保存到文件 init_centers.data中
with open("init_centers.data","w") as f:
	for i in range(lengthDist):
		tmplen = len(G3group[i])
		if tmplen >= 1:
			for j in range(tmplen):
				x0 = x0+array_regsloca[G3group[i][j]][0]
				y0 = y0+array_regsloca[G3group[i][j]][1]
			#f.write(str(xc)+" "+str(yc)+" "+"\n")
			xc = "%.2f" % (x0/tmplen)
			yc = "%.2f" % (y0/tmplen)
			#f.write(xc+" "+yc+" "+"\n")
			f.write(str(xc)+" "+str(yc)+" "+"\n")
			x0 = 0
			y0 = 0




print("************** end ******************")
