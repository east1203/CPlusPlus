# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
import PseudoCenter
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

dis0 = 0
distmp = float('inf')
num = 0
WL = 0   ## 连线总长度
WLpre = float('inf')
## 建立初始化群组
clusters = []
for i in range(clustersnum):
	clusters.append([0])
## 分配寄存器到距离最近的群组
for i in range(size):
	dis0 = 0
	distmp = float('inf')
	for j in range(clustersnum):
		dis0 = abs(array_regsloca[i][0]-centers[j][0])+abs(array_regsloca[i][1]-centers[j][1])
		if distmp > dis0:
			distmp = dis0
			num = j
	clusters[num].append(i)
## 删除第一个0
for i in range(clustersnum):
            del clusters[i][0]
## 根据分组结果计算新的群组中心点
emptyFlag = False
## 判断是否有空的群组
for i in range(clustersnum):
	if len(clusters[i])==0:        
		print("群组大小：")
		print(len(clusters[i]))
		emptyFlag = True
		print("出现空的群组")
		break


if emptyFlag:
	clusters,centers = PseudoCenter.PseudoCenter(clusters,array_regsloca)
	for i in range(clustersnum):
		for j in range(len(clusters[i])):
			WL = WL + abs(array_regsloca[clusters[i][j]][0]-centers[i][0])+abs(array_regsloca[clusters[i][j]][1]-centers[i][1])
	
else:
	print("没有空群组 ")
	centerstmp = np.zeros((clustersnum,2))
	
	for i in range(clustersnum):
		# del clusters[i][0]
		print(clusters[i])
		print('\n')
		x0 = 0
		y0 = 0
		xc = 0
		yc = 0
		for j in range(len(clusters[i])):
			x0 = x0 + array_regsloca[clusters[i][j]][0]
			y0 = y0 + array_regsloca[clusters[i][j]][1]
			WL = WL + abs(array_regsloca[clusters[i][j]][0]-centers[i][0])+abs(array_regsloca[clusters[i][j]][1]-centers[i][1])
		if len(clusters[i])==0:
			continue
		xc = "%.2f" % (x0/len(clusters[i]))
		yc = "%.2f" % (y0/len(clusters[i]))
		centerstmp[i][0] = xc
		centerstmp[i][1] = yc
	centers = centerstmp
with open("init_centers.data","w") as f:
	for i in range(clustersnum):
		f.write(str(centers[i][0])+" "+str(centers[i][1])+"\n")

## 将分组结果写到文件result.data
with open("result.data","w") as f:
	for i in range(clustersnum):
		if len(clusters[i])>1:
			if clusters[i]:
				#result=result.append(str(clusters[i])+'\n')
				#print("1111")
				l = str(clusters[i]).strip("[")
				ll = l.strip("]")
				lll = ll.split(",")
				for j in range(len(lll)):
					f.write(lll[j]+" ")
				f.write('\n')


print(clustersnum)
print("WL is "+str(WL))
# print("WLpre is " + str(WLpre))
print(centers)
print("每个群组中寄存器的数目")
for i in range(clustersnum):
	print(len(clusters[i]))









print("************** end ***************")









