#include<iostream>
#include<vector>
#include<tuple>
#include "clocktree.h"
using namespace std;
#include<map>
#include<stdlib.h>
#include<string>
#include<sstream>
#include<fstream>
#include<ctime>


void RunKruscal(string filename_i, string filename_o)
{
	long start;
	start = clock();
	vector<tuple<int, float, float>> loca;
	ReadLoca(loca,filename_i);
	long read_t = clock() - start;
	MST mst = kruskal(loca, 5);
	long kruscak_t = read_t - start;
	mst.showMst();
	cout << "read_t  : " << read_t << endl;
	cout << "kruscal time : " << kruscak_t << endl;
	ofstream FileWrite(filename_o, std::ios::out);
	for (auto ele : mst.get_edge())
	{ // 写  点--点--权重   格式到文件
		FileWrite << ele.get_u() << " " << ele.get_v() << " " << ele.get_cost() << endl;
	}
	FileWrite.flush();
	FileWrite.close();
}
void TestKruskal()
{

	//MST& kruskal(const vector < tuple<int, float, float>> &AllLoca_v,int size)
	vector<tuple<int, float, float>> loca;
	loca.push_back(make_tuple(1, 0, 0));
	loca.push_back(make_tuple(2, 0, 1));
	loca.push_back(make_tuple(3, 3, 0));
	loca.push_back(make_tuple(4, 4, 0));
	loca.push_back(make_tuple(5, 1, 2));
	//
//	MST mst = kruskal(loca, 5);
	//mst.showMst();
	//ofstream FileWrite("mst.data", std::ios::out);
	//for (auto ele : mst.get_edge())
	//{
	//	FileWrite << ele.get_u() << " " << ele.get_v() << " " << ele.get_cost() << endl;
	//}
	//FileWrite.flush();
	//FileWrite.close();
	cout << "************ "<< endl;
	C c;
	c.cluster = { 1,2,4,3,5 };
//	cout << kruskal(c, loca, c.cluster.size()) << endl;
}
void RunWeight()
{
	long start;
	start = clock();
	long read_t = clock() - start;
	tuple<vector<C>,float> Result = WeightCluster("./xiaoqing/regsloca.data", "./xiaoqing/init_centers.data");
	vector<C> clusters = get<0>(Result);
	//long weight_t = clock() - read_t;
	//cout << "read_t  : " << read_t << endl;
	//cout << "kruscal time : " << weight_t << endl;
	cout << "分组结果：" << endl;
	PrintClusters(clusters);
	cout << "cost ：" << get<1>(Result) << endl;
	WriteClusters("./xiaoqing/clusters.data", clusters);
}
void TestWeight()
{
	long start;
	start = clock();
	vector<tuple<int, float, float>> loca;
	loca.push_back(make_tuple(1, 0, 0));
	loca.push_back(make_tuple(2, 0, 1));
	loca.push_back(make_tuple(3, 3, 0));
	loca.push_back(make_tuple(4, 4, 0));
	loca.push_back(make_tuple(5, 1, 2));
	loca.push_back(make_tuple(6, 8, 2));
	loca.push_back(make_tuple(7, 11,16));
	loca.push_back(make_tuple(8, 13, 21));
	loca.push_back(make_tuple(9, 11,22));
	loca.push_back(make_tuple(10, 10, 2));
	loca.push_back(make_tuple(11, 31, 2));
	long read_t = clock() - start;
	tuple<vector<C>, float> Result = WeightCluster("./xiaoqing/regsloca.data", "./xiaoqing/init_centers.data");
	vector<C> clusters = get<0>(Result);
	//long weight_t = clock() - read_t;
	//cout << "read_t  : " << read_t << endl;
	//cout << "kruscal time : " << weight_t << endl;
	cout << "分组结果：" << endl;
	for (auto &iter = clusters.begin(); iter != clusters.end(); ++iter)
	{
		for (auto& ele : iter->cluster)
			cout << ele << " "; cout << endl;
	}
	cout << "cost ：" << get<1>(Result) << endl;
	WriteClusters("clusters.data", clusters);
}


int main(void)
{
	//RunKruscal("regsloca.data", "mst.data");
	//TestKruskal();
	RunWeight();
	//TestWeight();


	system("pause");
	return 0;
}