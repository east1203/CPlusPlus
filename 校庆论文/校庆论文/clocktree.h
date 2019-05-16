#pragma once
#include<iostream>
#include<vector>
#include<tuple>
#include<map>
#include<fstream>
#include<sstream>
#include<set>
using namespace std;
/* kruscal ��������MST */
/*Edge �࣬�����*/
class Edge {
public:
	Edge() = default;
	Edge(const int x,const  int y, const float cost_arg);
	friend bool edge_compare( const Edge&, const Edge&);
	int get_u() const; //���رߵĽڵ�
	int get_v() const;//���ر�ýڵ�
	float get_cost() const;//���رߵ�Ȩ��
	void showEdge() const;
private:
	int u = 0;
	int v = 0;
	float cost=0;
	float cost_x = 0;
	float cost_y = 0;
};
/*MST�࣬������ʾ���ɵ�MST*/
class MST {
public:
	MST() = default;
	MST(const Edge&);
	MST& add_edge(const Edge&); //��mst����ӱ�
	MST& add_node(const int& num);//��ӵ�
	bool HaveNode(int); //�жϽڵ��Ƿ���mst��
	MST& merge(MST&); // �ϲ�mst
	vector<Edge> get_edge() const { return mst_edge; }
	map<int, bool> get_node() const { return mst_node; }
	int get_num() const { return num_edge; }
	float get_x() const	{return sum_x;}
	float get_y() const		{ return sum_y; }
	float get_sum() const { return sum; }
	void showMst()const;
	static int symbol  ;  // �����������ʼ����̬���ݳ�Ա
private:
	vector<Edge> mst_edge;
	int num_edge=0;   // Ҫ��num����ֵ 0��Ҫ��Ȼ��ֵ��ȷ����
	map<int, bool> mst_node; //������ʾ����ڵ��Ƿ���ӵ���mst
	float sum_x = 0;//���б�Ȩ�ض�Ӧ��x�������  ����Ȩ���������پ���
	float sum_y = 0;
	float sum = 0; //mst��Ȩ�غ�
};
/*Ⱥ��ṹ��*/
struct C {
	set<int> cluster;
	pair<float, float> center;
	float mstlength;
};
/*���ݸ�sort�����ıȽϺ���*/
bool edge_compare(const Edge& edge_1, const Edge& edge_2);

/*
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v, int size)
input: ����������  �� �����
output:  mst
AllLoca_v�е�ı�Ŵ�1��ʼ
*/
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v,int size);

tuple<float, float, MST> kruskal2(const vector < tuple<int, float, float>> &AllLoca_v, int size = 0);

void ShowClusters(vector<C> clusters);


tuple<vector<C>, float> WeightCluster(string ReglocaFile, string InitcenterFile); //Ȩ�ط��飬�����ʼ���ĵ��
pair<float, float> SplitStr(const string& str); //���ļ��е�ÿһ�зֳ��������������أ���ʾxy����
/*���ļ��ж�ȡ�Ĵ�����λ��*/
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