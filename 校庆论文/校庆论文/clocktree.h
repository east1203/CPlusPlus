#pragma once
#include<iostream>
#include<vector>
#include<tuple>
#include<map>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;
/* kruscal 方法生成MST */
/*Edge 类，代表边*/
class Edge {
public:
	Edge() = default;
	Edge(const int x,const  int y, const float cost_arg);
	friend bool edge_compare( const Edge&, const Edge&);
	int get_u() const; //返回边的节点
	int get_v() const;//返回变得节点
	float get_cost() const;//返回边的权重
	void showEdge() const;
private:
	int u = 0;
	int v = 0;
	float cost=0;
	float cost_x = 0;
	float cost_y = 0;
};
/*MST类，用来表示生成的MST*/
class MST {
public:
	MST() = default;
	MST(const Edge&);
	MST& add_edge(const Edge&); //向mst中添加边
	MST& add_node(const int& num);//添加点
	bool HaveNode(int); //判断节点是否再mst上
	MST& merge(MST&); // 合并mst
	vector<Edge> get_edge() const { return mst_edge; }
	map<int, bool> get_node() const { return mst_node; }
	int get_num() const { return num_edge; }
	float get_x() const	{return sum_x;}
	float get_y() const		{ return sum_y; }
	float get_sum() const { return sum; }
	void showMst()const;
	static int symbol  ;  // 必须在类外初始化静态数据成员
private:
	vector<Edge> mst_edge;
	int num_edge=0;   // 要给num赋初值 0，要不然初值不确定。
	map<int, bool> mst_node; //用来表示这个节点是否添加到了mst
	float sum_x = 0;//所有边权重对应的x方向分量  ，，权重是曼哈顿距离
	float sum_y = 0;
	float sum = 0; //mst中权重和
};
/*群组结构体*/
struct C {
	set<int> cluster;
	pair<float, float> center;
	float mstlength;
};
/*传递个sort函数的比较函数*/
bool edge_compare(const Edge& edge_1, const Edge& edge_2);

/*
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v, int size)
input: 任意点的坐标  和 点个数
output:  mst
AllLoca_v中点的标号从1开始
*/
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v,int size);

tuple<float, float, MST> kruskal2(const vector < tuple<int, float, float>> &AllLoca_v, int size = 0);

void ShowClusters(vector<C> clusters);


tuple<vector<C>, float> WeightCluster(string ReglocaFile, string InitcenterFile); //权重分组，读入初始中心点和
pair<float, float> SplitStr(const string& str); //将文件中的每一行分成两个浮点数返回，表示xy坐标
/*从文件中读取寄存器的位置*/
vector<tuple<int, float, float>>& ReadLoca(vector<tuple<int, float, float>>& v, string ReglocaFile);
vector<C>& OnceIter(const vector<tuple<int, float, float>>& AllLoca_v, vector<C>& clusters);
float kruskal(const C  & cluster, const vector < tuple<int, float, float>> &AllLoca_v, int size);
float Obj(const vector<tuple<int, float, float>>& AllLoca_v, const vector<C>& clusters);
vector<C> ClearClusters(vector<C>& clusters);

void WriteClusters(string filename, vector<C> clusters);

template<class T>
const T& Max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}