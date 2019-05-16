# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
import PseudoCenter
## centers 群组中心点
## clusternum 群组个数
## array_regsloca 寄存器位置
## size 寄存器数目
def ClusterFunc(centers,clustersnum,array_regsloca,size):

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
    
    return clusters,centers,WL





