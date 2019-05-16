## 如果分组出现空的群组则执行该函数

import numpy as np

# clusters = [[1],[2,3],[4,5,0],[],[]]
# array_regsloca = [[12,32],[1,34],[45,12],[27,9],[41,20],[33,2]]
def PseudoCenter(clusters,array_regsloca):
##def PseudoCenter(clusters):
    # size = 162
    # ind = 0
    # array_regsloca = np.zeros((size,2))
    # with open("./regsloca.data","r") as f:
    #     for line in f.readlines():
    #         sline = line.strip("\n")
    #         lline = line.split(" ")
    #         array_regsloca[ind][0] = lline[0]
    #         array_regsloca[ind][1] = lline[1]
    #         ind = ind+1

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

# clusters,centers =PseudoCenter(clusters,array_regsloca)
# print(clusters)
# print(centers)









