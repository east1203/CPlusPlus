# -*- coding: utf-8 -*-
"""
Created on Wed Mar  6 18:58:37 2019

@author: dongyongkang
"""
'''
封装成函数直接调用
'''


# coding=utf-8
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from math import *
import PseudoCenter
import ClusterFunc
##def EL(centers,clusters:

def clusterDemo(size,clustersnum):
    print("************** start ***************")
    #size = 162
    #size = 214
    #clustersnum = 10
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
    
    TMP = []
    TMPA = []
    count = 0
    continueFlag = True
    ## 调用寄存器分组函数
    while continueFlag:
        clusterstmp,centerstmp,WL = ClusterFunc.ClusterFunc(centers,clustersnum,array_regsloca,size)
        TMP.append(WL)
        if WL < WLpre:
            WLpre = WL
            centers = centerstmp
            clusters = clusterstmp
            TMPA.append(WL)
            count = 0
            ## 写回分组中心点
            with open("init_centers.data","w") as f:
                for i in range(clustersnum):
                    f.write(str(centers[i][0])+" "+str(centers[i][1])+"\n")
        else:
            ## 连续多次连线总长没有减小就停止分组
            count+=1
            if count>15:
                continueFlag = False
        
    
    print("wl长度是 ")
    print(TMP)
    print(TMPA)
    
    # for i in range(1):
    #     clusters,centerstmp,WL = ClusterFunc.ClusterFunc(centers,clustersnum,array_regsloca,size)
    #     centers = centerstmp
    #     TMP.append(WL)
    #     with open("init_centers.data","w") as f:
    #         for i in range(clustersnum):
    #             f.write(str(centers[i][0])+" "+str(centers[i][1])+"\n")
    # print("wl长度是 ")
    # print(TMP)
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
    # print("WL is "+str(WL))
    # print("WLpre is " + str(WLpre))
    print(centers)
    print("每个群组中寄存器的数目")
    for i in range(clustersnum):
    	print(len(clusters[i]))
    
    
    ##输出每一个群组中寄存器的位置
    #for i in range(clustersnum):
     #   print("群组"+str(i)+"的寄存器位置如下:")
      #  for j in range(len(clusters[i])):
       #     print(str(array_regsloca[clusters[i][j]][0])+" "+str(array_regsloca[clusters[i][j]][1]))
    '''
    for i in range(clustersnum):
        print("群组"+str(i)+"的寄存器位置如下:")
        print("群组"+str(i)+"的x坐标: ")
        for j in range(len(clusters[i])):
            print(str(array_regsloca[clusters[i][j]][0]))
        print("群组"+str(i)+"的y坐标: ")
        for j in range(len(clusters[i])):
            print(str(array_regsloca[clusters[i][j]][1]))
    
    '''
    
    
    
    print("************** end ***************")









