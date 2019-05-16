# -*- coding: utf-8 -*-
"""
Created on Sun May  5 16:47:25 2019

@author: dongyongkang
"""
"""
校庆论文中，关于寄存器分组的一些函数


kruskalmst(size,array_regsloca,array_regsdist,pos) :MST生成
"""

# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
from time import *

"""
生成初始中心点
"""
def InitCenters(size,array_regsloca,array_regsdist,fpWidth,fpHeight,a):
	print("start InitCenters")
	
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
	return groupNum


def show():
	print("this is a test")

"""
ClusterFunc(centers,clustersnum,array_regsloca,size) 分组算法
"""
## centers 群组中心点
## clusternum 群组个数
## array_regsloca 寄存器位置
## size 寄存器数目
def ClusterFunc(centers,clustersnum,array_regsloca,size,Cmax,Mmax):

	xcapa = 10 ## 水平单位长度电容
	ycapa = 10 ## 垂直单位长度电容
	regcapa = 10 ## 寄存器栅电容
    ## 建立初始化群组
    WL = 0
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

## 输出信息
    for i in range(clustersnum):
        print("分组后群组大小"+str(len(clusters[i])))

    ## 根据分组结果计算新的群组中心点
    emptyFlag = False
    ## 判断是否有空的群组
    for i in range(clustersnum):
        if len(clusters[i])==0:        
            emptyFlag = True
            print("出现空的群组")
            break


    if emptyFlag:
        clusters,centers = PseudoCenter(clusters,array_regsloca)
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
    
    return clusters,centers,WL



def PseudoCenter(clusters,array_regsloca):
    emptyFlag = True
    clustersnum = len(clusters)
    # print("clustersnum is :",str(clustersnum))
    centers = np.zeros((clustersnum,2))
    while(emptyFlag):
        
        emptyIndex = 0
        maxIndex = 0
        clustersLen = []
        for i in range(clustersnum):
            # del clusters[i][0]
            clustersLen.append(len(clusters[i]))
      
        emptyIndex = np.argsort(clustersLen)[0]
        maxIndex = np.argsort(clustersLen)[clustersnum-1]
        
        # ## 从最大的群组中向空群组移一半的寄存器
        # for i in range(int(clustersLen[maxIndex]/2)):
        #     clusters[emptyIndex].append(clusters[maxIndex][0])
        #     clusters[maxIndex].pop(0)
        # 将最大的群组分成上下两部分
        halfIndex = []
        maxclusterTMP = []
        xmin = 0
        xmax = 0
        ymin = 0
        ymax = 0
        horizonDiv = True
        # xloca = np.zeros((clustersLen[maxIndex],1))
        # yloca = np.zeros((clustersLen[maxIndex],1))
        xloca = []
        yloca = []
        for i in range(clustersLen[maxIndex]):
            ## 求x y坐标的最大值和最小值，如果x坐标横跨距离大，则垂直分开最大的群组
            ## 如果y坐标跨度大，则水平分开最大群组
            if xmin > array_regsloca[clusters[maxIndex][i]][0]:
                xmin = array_regsloca[clusters[maxIndex][i]][0]
            if xmax < array_regsloca[clusters[maxIndex][i]][0]:
                xmax = array_regsloca[clusters[maxIndex][i]][0]
            if ymin > array_regsloca[clusters[maxIndex][i]][1]:
                ymin = array_regsloca[clusters[maxIndex][i]][1]
            if ymax < array_regsloca[clusters[maxIndex][i]][1]:
                ymax = array_regsloca[clusters[maxIndex][i]][1]
            ## 将最大群组的xy坐标保存下来
            # xloca[i] = array_regsloca[clusters[maxIndex][i]][0]
            # yloca[i] = array_regsloca[clusters[maxIndex][i]][1]
            xloca.append(array_regsloca[clusters[maxIndex][i]][0])
            yloca.append(array_regsloca[clusters[maxIndex][i]][1])
        # print("xloca yloca:")
        # print(xloca)
        # print(yloca)
        if (xmax-xmin)>(ymax-ymin):
            horizonDiv = False
            print("垂直分最大群组")
        else:
            print("水平分最大群组")
        # print("半个最大群组的 索引：")
        if horizonDiv:
            halfIndex = np.argsort(yloca)
            # print(halfIndex)
        else:
            halfIndex = np.argsort(xloca)
            # print(halfIndex)
        for i in range(int(clustersLen[maxIndex]/2)):
            clusters[emptyIndex].append(clusters[maxIndex][halfIndex[i]])
        for i in range(int(clustersLen[maxIndex]/2),clustersLen[maxIndex]):
            maxclusterTMP.append(clusters[maxIndex][halfIndex[i]])
        clusters[maxIndex] = maxclusterTMP

        ##更新群组大小
        clustersLen[emptyIndex] = len(clusters[emptyIndex])
        clustersLen[maxIndex] = len(clusters[maxIndex])
        emptyIndex = np.argsort(clustersLen)[0]
        if clustersLen[emptyIndex]==0:
            emptyFlag = True
        else:
            emptyFlag = False
    # print("clusterlen is :")
    # print(clustersLen)
    # print("emtpyflag")
    # print(emptyFlag)
    x0 = 0
    y0 = 0
    # print("cluster is ")
    # print(clusters)
    # print("arrary——regloca")
    # print(array_regsloca)
    # print("群组大小")
    # print(clustersnum)
    print("伪中心点调整后群组大小：")
    for i in range(clustersnum):
        x0 = 0
        y0 = 0
        for j in range(clustersLen[i]):
            x0 = array_regsloca[clusters[i][j]][0] + x0
            y0 = array_regsloca[clusters[i][j]][1] + y0
        xc = "%.2f" % (x0/clustersLen[i])
        yc = "%.2f" % (y0/clustersLen[i])
        print("第"+str(i)+"个群组大小："+str(clustersLen[i]))
        print(xc,yc)
        centers[i][0] = xc
        centers[i][1] = yc

    # print(emptyIndex)
    # print(maxIndex)
    return clusters,centers

"""
    最小生成树算法
    

	设有一个有n个顶点的连通网N={V,E},最初先构造一个只有n个顶点，没有边的非连通图T={V, E},
图中每个顶点自成一个连通分量。当在E中选到一条具有最小权值的边时,若该边的两个顶点落在不同的连通分量上，
则将此边加入到T中；否则将此边舍去，重新选择一条权值最小的边。如此重复下去，直到所有顶点在同一个连通分量上为止。
--------------------- 

原文：https://blog.csdn.net/HeiSeDiWei/article/details/50340723 

"""
def kruskalmst(cluster,array_regsloca,array_regsdist,pos):
	time1 = time()
	print("************** start Krukcal minimum spanning tree algorithm***************")

	time2 = time()
	size = len(cluster)
	regsloca = np.zeros((size,2))
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
	print("************** end Krukcal minimum spanning tree algorithm***************")
	
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
	return xsum,ysum,G2Point
"""
def kruskalmst(size,array_regsloca,array_regsdist,pos):
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
	print("************** end Krukcal minimum spanning tree algorithm***************")
	
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
	return xsum,ysum,G2Point
"""