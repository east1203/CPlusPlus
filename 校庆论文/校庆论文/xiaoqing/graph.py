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

size = 162 -1
edges= np.zeros((size,3))
pos = np.zeros((size+1,2))
ind = 0

with open("./mst.data","r") as f:
    for line in f.readlines():
        sline = line.strip("\n")
        lline = sline.split(" ")
        edges[ind][0] = lline[0]
        edges[ind][1] = lline[1]
        edges[ind][2] = lline[2]
        ind = ind+1

ind = 0
with open("./regsloca.data") as f:
    for line in f.readlines():
        sline  = line.strip("\n")
        lline = sline.split(" ")
        pos[ind][0] = lline[0]
        pos[ind][1] = lline[1]
        ind = ind+1

G = nx.Graph();
for i in range(0,size+1):
    G.add_node(i)

for i in range(size):
    G.add_edge(int(edges[i][0]-1),int(edges[i][1]-1),weight=edges[i][2])
#plt.subplot(121)
#nx.draw_networkx_nodes(G2, pos,node_size=25)
#nx.draw_networkx_edges(G2,pos)
#nx.draw_networkx_labels(G, pos,font_size=8, font_family='sans-serif')
#nx.draw(G2,pos,node_size=50)
#plt.savefig("G2.png")  # save as png
#plt.show()

#nx.draw(G,pos,node_size=50)
nx.draw_networkx_nodes(G,pos,node_size=30)
nx.draw_networkx_edges(G,pos)
plt.show()
plt.savefig("G.png")
print ("success!")