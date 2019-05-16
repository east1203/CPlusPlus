#include<iostream>
#include<vector>
#include<tuple>
#include "clocktree.h"
using namespace std;
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>
/* kruscal 方法生成MST */
/*class Edge implement*/
Edge::Edge(const int x,const int y,const float cost_arg) :u(x), v(y), cost(cost_arg) {};
int Edge::get_u() const{return this->u;}
int Edge::get_v() const{ return this->v; }
float Edge::get_cost() const{ return this->cost; };
void Edge::showEdge() const
{
	cout << this->u << "--" << this->v << "--" << this->cost << endl;
}
/*class MST implement*/
MST::MST(const Edge& e)
{
	this->mst_edge.push_back(e);
	//this->mst_node.insert(make_pair(e.get_u(), true)); // 添加节点
	//this->mst_node.insert(make_pair(e.get_v(), true)); // 添加节点
	this->mst_node[e.get_u()] = true;
	this->mst_node[e.get_v()] = true;
	this->sum = e.get_cost();
	++(this->num_edge);
}
// 添加边
MST& MST::add_edge(const Edge& edge)
{
	this->mst_edge.push_back(edge); //添加边
//	this->mst_node.insert(make_pair(edge.get_u(), true)); // 添加节点
//	this->mst_node.insert(make_pair(edge.get_v(), true)); // 添加节点
//	this->mst_node[edge.get_u()] = true;
	//this->mst_node[edge.get_v()] = true;
	add_node(edge.get_u());
	add_node(edge.get_v());
	++ (this->num_edge);
	this->sum += edge.get_cost();
	return *this;
}
MST& MST::add_node(const int& num)
{
	this->mst_node[num] = true;
	return *this;
}
// 判断MST中是否有某个节点
bool MST::HaveNode(int node)
{
	return mst_node[node];
}
// 合并mst
MST& MST::merge( MST& mst)
{
	vector<Edge> ev = mst.get_edge();
	for (vector<Edge>::iterator iter = ev.begin(); iter != ev.end(); ++iter)
		// 合并边的时候也合并了节点，增加了边的数目
		this->add_edge(*iter); 
	return *this;
}
void MST::showMst() const
{
	if (this->mst_edge.size() == 0) return;
	if (this->mst_node.size() == 0) return;
	cout << "edges : " << endl;
	for (const auto& ele : mst_edge)
		ele.showEdge();
	cout << "nodes : " << endl;
	for (const auto& ele : mst_node)
		if(ele.second) cout << ele.first << " ";
	cout << endl;
	cout << "num_edge is :" << this->num_edge << endl;
	cout << "the cost is : " << this->sum << endl;
}
int MST::symbol = 0;
// 升序排序比较函数
bool edge_compare(const Edge& edge_1, const Edge& edge_2)
{
	return edge_1.cost < edge_2.cost;
}

vector<Edge> CalcuEdge(const vector<tuple<int, float, float>>& AllLoca_v)
{
	vector<Edge> edges_v; //保存n*(n+1)/2条边
	/*只有一个节点情况*/
	if (AllLoca_v.size() <= 1) {
		return edges_v;   // 直接返回空的容器
	}
	/*通过点的坐标计算出每一条边的权重，并将边保存到edges_v中*/
	auto iter_AllLoca_b = AllLoca_v.cbegin();
	auto iter_AllLoca_e = AllLoca_v.cend();
	for (auto iter_i = iter_AllLoca_b; iter_i != iter_AllLoca_e; ++iter_i)
	{
		for (auto iter_j = (iter_i + 1); iter_j != iter_AllLoca_e; ++iter_j)
		{
			edges_v.push_back(Edge(get<0>(*iter_i), get<0>(*iter_j), abs(get<1>(*iter_i) - get<1>(*iter_j)) + abs(get<2>(*iter_i) - get<2>(*iter_j))));
		}
	}
	return edges_v;
}
vector<C> ReadCenters(string filename, vector<C> clusters_v)
{
	ifstream FileCenter(filename, std::ios::in);
	string str;
	while (getline(FileCenter, str))  // 创建多个群组并保存中心点
	{
		C c;
		c.center = SplitStr(str);
		clusters_v.push_back(c);
	}
	return clusters_v;
}
/*
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v, int size)
input: 任意点的坐标  和 点个数
output:  mst
AllLoca_v中点的标号从1开始
*/
MST kruskal(const vector < tuple<int, float, float>> &AllLoca_v, int size)
{
	MST mst;
	/*通过点的坐标计算出每一条边的权重，并将边保存到edges_v中*/
	vector<Edge> edges_v = CalcuEdge(AllLoca_v);
	vector<MST> msts_v; // 在生成最终的MST过程中出现的所有的子树。
	/*按边权重由低到高排序*/
	sort(edges_v.begin(), edges_v.end(), edge_compare);
	for (const auto& ele : edges_v)
		ele.showEdge();
	/*判断每一条边是否属于最终的MST*/
	auto iter_edges_b = edges_v.begin();
	auto iter_edges_e = edges_v.end();
	// 先插入第一条边生成第一个mst子树，要不然下面遍历子树的for循环没法执行
	msts_v.push_back(MST(*iter_edges_b));

	for (auto iter_i = iter_edges_b + 1; iter_i != iter_edges_e; ++iter_i) //对每一条edge进行判断
	{
		if (msts_v[0].get_num() == (size - 1)) break; //如果第一个子树的边数达到 size-1，则说明已经生成了MST，不必再遍历边了；
		vector<MST>::iterator iter_u = msts_v.end(); //迭代器初始化为msts_v的end()位置，在接下来的程序中通过与end()比较来判断是否改变了iter_u
		vector<MST>::iterator iter_v = msts_v.end();
		bool u = false;
		bool v = false;
		for (auto iter_msts = msts_v.begin(); iter_msts != msts_v.end(); ++iter_msts) // 遍历每一个子树
		{
			if (iter_msts->HaveNode(iter_i->get_u())) {
				iter_u = iter_msts; u = true;
			}
			if (iter_msts->HaveNode(iter_i->get_v())) {
				iter_v = iter_msts; v = true;
			}
		}
		//	if(iter_u!=msts_v.end()) iter_u->showMst();
		//   if(iter_v!=msts_v.end())	iter_v->showMst();
		/*
		情况：
		1 边的两个点都在同一个子树中，抛弃这条边
		2 边的一个点在某个子树上，另一个点不在任何子树上 》》 将边假如到这个子树
		3 边的一个点在一个子树，另一个点在另一个子树 》》 合并这两个子树
		4 边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
		*/
		if ((iter_u == iter_v) && u&&v) {} //边的两个点都在同一个子树中，抛弃这条边
										   //if ((iter_u != msts_v.end()) && (iter_v != msts_v.end()) && (iter_u == iter_v)) {}
		else if (!(u&v) && (u || v)) { //边的一个点在某个子树上，另一个点不在任何子树上 》》 将边加入到这个子树
			if (u) iter_u->add_edge(*iter_i);
			else iter_v->add_edge(*iter_i);
		}
		else if (u&&v && (iter_u != iter_v)) { //边的一个点在一个子树，另一个点在另一个子树 》》 将这条边也加入到子树中，并合并这两个子树
			iter_u->add_edge(*iter_i);
			iter_u->merge(*iter_v);
			msts_v.erase(iter_v); // 删除iter_v指向的子树
		}
		else if ((~u) && (~v)) { //边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
			msts_v.push_back(MST(*iter_i));
		}

		//cout << "当前结果：" << endl;
		//cout << "mst数目: " << msts_v.size() << endl;
		//for (const auto& ele : msts_v)
		//	ele.showMst();
	}
	return msts_v[0];

}

tuple<float,float,MST> kruskal2(const vector < tuple<int, float, float>> &AllLoca_v, int size)
{
	tuple<float, float, MST> T(0,0,MST());

	vector<Edge> edges_v; //保存n*(n+1)/2条边
	vector<MST> msts_v; // 在生成最终的MST过程中出现的所有的子树。
						/*通过点的坐标计算出每一条边的权重，并将边保存到edges_v中*/
	auto iter_AllLoca_b = AllLoca_v.cbegin();
	auto iter_AllLoca_e = AllLoca_v.cend();
	for (auto iter_i = iter_AllLoca_b; iter_i != iter_AllLoca_e; ++iter_i)
	{
		for (auto iter_j = (iter_i + 1); iter_j != iter_AllLoca_e; ++iter_j)
		{
			edges_v.push_back(Edge(get<0>(*iter_i), get<0>(*iter_j), abs(get<1>(*iter_i) - get<1>(*iter_j)) + abs(get<2>(*iter_i) - get<2>(*iter_j))));
		}
	}
	/*按边权重由低到高排序*/
	sort(edges_v.begin(), edges_v.end(), edge_compare);
	for (const auto& ele : edges_v)
		ele.showEdge();
	/*判断每一条边是否属于最终的MST*/
	auto iter_edges_b = edges_v.begin();
	auto iter_edges_e = edges_v.end();
	// 先插入第一条边生成第一个mst子树，要不然下面遍历子树的for循环没法执行
	msts_v.push_back(MST(*iter_edges_b));

	for (auto iter_i = iter_edges_b + 1; iter_i != iter_edges_e; ++iter_i) //对每一条edge进行判断
	{
		if (msts_v[0].get_num() == (size - 1)) break; //如果第一个子树的边数达到 size-1，则说明已经生成了MST，不必再遍历边了；
		vector<MST>::iterator iter_u = msts_v.end(); //迭代器初始化为msts_v的end()位置，在接下来的程序中通过与end()比较来判断是否改变了iter_u
		vector<MST>::iterator iter_v = msts_v.end();
		bool u = false;
		bool v = false;
		for (auto iter_msts = msts_v.begin(); iter_msts != msts_v.end(); ++iter_msts) // 遍历每一个子树
		{
			if (iter_msts->HaveNode(iter_i->get_u())) {
				iter_u = iter_msts; u = true;
			}
			if (iter_msts->HaveNode(iter_i->get_v())) {
				iter_v = iter_msts; v = true;
			}
		}
		//	if(iter_u!=msts_v.end()) iter_u->showMst();
		//   if(iter_v!=msts_v.end())	iter_v->showMst();
		/*
		情况：
		1 边的两个点都在同一个子树中，抛弃这条边
		2 边的一个点在某个子树上，另一个点不在任何子树上 》》 将边假如到这个子树
		3 边的一个点在一个子树，另一个点在另一个子树 》》 合并这两个子树
		4 边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
		*/
		if ((iter_u == iter_v) && u&&v) {} //边的两个点都在同一个子树中，抛弃这条边
										   //if ((iter_u != msts_v.end()) && (iter_v != msts_v.end()) && (iter_u == iter_v)) {}
		else if (!(u&v) && (u || v)) { //边的一个点在某个子树上，另一个点不在任何子树上 》》 将边加入到这个子树
			if (u) iter_u->add_edge(*iter_i);
			else iter_v->add_edge(*iter_i);
		}
		else if (u&&v && (iter_u != iter_v)) { //边的一个点在一个子树，另一个点在另一个子树 》》 将这条边也加入到子树中，并合并这两个子树
			iter_u->add_edge(*iter_i);
			iter_u->merge(*iter_v);
			msts_v.erase(iter_v); // 删除iter_v指向的子树
		}
		else if ((~u) && (~v)) { //边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
			msts_v.push_back(MST(*iter_i));
		}

		//cout << "当前结果：" << endl;
		//cout << "mst数目: " << msts_v.size() << endl;
		//for (const auto& ele : msts_v)
		//	ele.showMst();
	}
	//cout << msts_v.size() << endl;

	return T;

}


/*权重分组
input：AllLoca_v传入各个点寄存器的位置, filename文件保存初始中心点
output：返回值是元素是set的vector，每一个set中保存群组内的节点号
Main Function:
	tuple<vector<C>,float> WeightCluster(const vector<tuple<int, float, float>>& AllLoca_v,string filename)
Sub Function:
	pair<float, float> SplitStr(const string& str)
	vector<C>& OnceIter(const vector<tuple<int, float, float>>& AllLoca_v, vector<C>& clusters)
			float kruskal(const C& c, const vector < tuple<int, float, float>> &AllLoca_v,int size)
				bool edge_compare(const Edge& edge_1, const Edge& edge_2)
	float Obj(const vector<tuple<int, float, float>>& AllLoca_v, const vector<C>& clusters)
	void showClusters(vector<C> clusters)
*/
void ShowClusters(vector<C> clusters) 
{
	printf("输出当前群组情况：\n");
	for (int i = 0; i < clusters.size(); ++i) {
		cout << "第 " << i << " 个群组" << endl;
		cout << "clusters center is : ( " << clusters[i].center.first << "," << clusters[i].center.second << ")" << endl;
		cout << "clustes size is : " << clusters[i].cluster.size() << endl;
		cout << "mstlength is : " << clusters[i].mstlength << endl;
		cout << "群组中的点：" << endl;
		for (auto& ele : clusters[i].cluster)
			cout << ele << " "; cout << endl;
	}
}
vector<C> ClearClusters(vector<C>& clusters)  //将群组内的节点都删除，保留中心点
{
	for (auto iter_i = clusters.begin(); iter_i != clusters.end(); ++iter_i) {
		iter_i->cluster = {};
	}
	return clusters;
}
/*从文件中读取寄存器的位置*/
vector<tuple<int, float, float>>& ReadLoca(vector<tuple<int, float, float>>& v, string ReglocaFile)
{//"regsloca.data
	ifstream FileLoca(ReglocaFile, std::ios::in);
	string str;
	tuple<int, float, float> t;
	int num = 0;
	while (getline(FileLoca, str))
	{
		++num;
		get<0>(t) = num;
		get<1>(t) = SplitStr(str).first;
		get<2>(t) = SplitStr(str).second;
		v.push_back(t);
	}
	return v;
}
pair<float, float> SplitStr(const string& str)  //将文件中的每一行分成两个浮点数返回，表示xy坐标
{
	pair<float, float> str_p;
	stringstream ss;
	stringstream sss;
	int index = str.find(' ');
	//cout << "index :" << index << endl;
	ss << str.substr(0, index);
	ss >> str_p.first;
	sss << str.substr(index + 1, str.size() - index - 1);
	sss >> str_p.second;
	return str_p;
}
float kruskal(const C& c, const vector < tuple<int, float, float>> &AllLoca_v, int size)
{
	if (c.cluster.size() <= 1) return 0;  // 如果群组是空或者只有一个点，那么群组的权重和为零
	vector<MST> msts_v; // 在生成最终的MST过程中出现的所有的子树。
						/*通过点的坐标计算出每一条边的权重，并将边保存到edges_v中*/
	vector<tuple<int, float, float>> clusternodes;   //保存群组中对应的点的坐标
	for (auto& iter = c.cluster.begin(); iter != c.cluster.end(); ++iter) {   //在AllLoca_v中寄存器是按照顺序排放的，寄存器标号从1开始，而vector从0开始索引
		clusternodes.push_back(AllLoca_v[*iter - 1]);
	}
	vector<Edge>   edges_v = CalcuEdge(clusternodes);
	//if (edges_v.size() < 1) return 0;	
	/*按边权重由低到高排序*/
	sort(edges_v.begin(), edges_v.end(), edge_compare);
	//for (const auto& ele : edges_v)
	//	ele.showEdge();
	/*判断每一条边是否属于最终的MST*/
	auto iter_edges_b = edges_v.begin();
	auto iter_edges_e = edges_v.end();
	// 先插入第一条边生成第一个mst子树，要不然下面遍历子树的for循环没法执行
	msts_v.push_back(MST(*iter_edges_b));
	for (auto iter_i = iter_edges_b + 1; iter_i != iter_edges_e; ++iter_i) //对每一条edge进行判断
	{
		if (msts_v[0].get_num() == (size - 1)) break; //如果第一个子树的边数达到 size-1，则说明已经生成了MST，不必再遍历边了；
		vector<MST>::iterator iter_u = msts_v.end(); //迭代器初始化为msts_v的end()位置，在接下来的程序中通过与end()比较来判断是否改变了iter_u
		vector<MST>::iterator iter_v = msts_v.end();
		bool u = false;
		bool v = false;
		for (auto iter_msts = msts_v.begin(); iter_msts != msts_v.end(); ++iter_msts) // 遍历每一个子树
		{
			if (iter_msts->HaveNode(iter_i->get_u())) {
				iter_u = iter_msts; u = true;
			}
			if (iter_msts->HaveNode(iter_i->get_v())) {
				iter_v = iter_msts; v = true;
			}
		}
		/*
		情况：
		1 边的两个点都在同一个子树中，抛弃这条边
		2 边的一个点在某个子树上，另一个点不在任何子树上 》》 将边假如到这个子树
		3 边的一个点在一个子树，另一个点在另一个子树 》》 合并这两个子树
		4 边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
		*/
		if ((iter_u == iter_v) && u&&v) {} //边的两个点都在同一个子树中，抛弃这条边
										   //if ((iter_u != msts_v.end()) && (iter_v != msts_v.end()) && (iter_u == iter_v)) {}
		else if (!(u&v) && (u || v)) { //边的一个点在某个子树上，另一个点不在任何子树上 》》 将边加入到这个子树
			if (u) iter_u->add_edge(*iter_i);
			else iter_v->add_edge(*iter_i);
		}
		else if (u&&v && (iter_u != iter_v)) { //边的一个点在一个子树，另一个点在另一个子树 》》 将这条边也加入到子树中，并合并这两个子树
			iter_u->add_edge(*iter_i);
			iter_u->merge(*iter_v);
			msts_v.erase(iter_v); // 删除iter_v指向的子树
		}
		else if ((~u) && (~v)) { //边的两个点都不在任何子树上，创建新的子树加入到 msts_v中
			msts_v.push_back(MST(*iter_i));
		}
		//cout << "当前结果：" << endl;
		//cout << "mst数目: " << msts_v.size() << endl;
		//for (const auto& ele : msts_v)
		//	ele.showMst();
	}
	//msts_v[0].showMst();
	//cout << msts_v[0].get_node().size() << endl;
	//msts_v[1].showMst();
	return msts_v[0].get_sum();
}
/*权重分组的目标函数*/
float Obj(const vector<tuple<int, float, float>>& AllLoca_v, const vector<C>& clusters)
{
	float obj = 0;
	for (auto iter_i = clusters.cbegin(); iter_i != clusters.cend(); ++iter_i) { //遍历每个群组
		for (auto iter_j = iter_i->cluster.cbegin(); iter_j != iter_i->cluster.cend(); ++iter_j) { //遍历群组内的每个点
			obj = obj + abs(get<1>(AllLoca_v[*iter_j - 1]) - iter_i->center.first) + abs(get<2>(AllLoca_v[*iter_j - 1]) - iter_i->center.second);
		}
	}
	return obj;
}
/*一次迭代*/
vector<C>& OnceIter(const vector<tuple<int, float, float>>& AllLoca_v, vector<C>& clusters)
{

	int MaxRegNum = 25;
	int Cmax = 9.5;
	float CapaReg = 0.3776; //fF = e(-15) F
	float  CapaWire = 0.000388; //fF  1um*1um的块电容
	float WireWidth = 0.07; // um
	float cost = 0;
	auto iter_loca_b = AllLoca_v.cbegin();
	auto iter_loca_e = AllLoca_v.cend();
	for (auto iter_i = iter_loca_b; iter_i != iter_loca_e; ++iter_i) //遍历每一个寄存器
	{
		auto iter_tmp = clusters.begin(); //用来记录寄存器属于哪个群组
		float tmp = pow(10, 10);
		for (auto iter_j = clusters.begin(); iter_j != clusters.end(); ++iter_j) //遍历每一个群组
		{
			iter_j->mstlength = kruskal(*iter_j, AllLoca_v, iter_j->cluster.size());
			float wire = iter_j->mstlength*CapaWire *0.07;
			float CapaCluster = wire + iter_j->cluster.size()*CapaReg;
			//cost = (| x_j - X_i | +| y_j - Y_i | )*max⁡(1, (∑_(s_i∈c_i)C_(s_i) + MST(c_i)) / C_max)
			//	cout << "CapaCluster is : " << CapaCluster << "   "<<wire<<endl;
			//	printf("CapaCluster is %f \n", CapaCluster);
			cost = abs(get<1>(*iter_i) - iter_j->center.first) + abs(get<2>(*iter_i) - iter_j->center.second)*Max(float(1), CapaCluster / Cmax);		//计算寄存器到群组的cost
																																						//cost = abs(get<1>(*iter_i) - iter_j->center.first) + abs(get<2>(*iter_i) - iter_j->center.second) ;		//计算寄存器到群组的cost
																																						//cout << "cost is : " << cost << endl;
																																						//if ((cost < tmp)&&(MaxRegNum>iter_j->cluster.size())) {   //如果cost比上一个小，记录下这个群组的迭代器
																																						//	tmp = cost;
																																						//	iter_tmp = iter_j;
																																						//}
			if ((cost < tmp)) {   //如果cost比上一个小，记录下这个群组的迭代器
				tmp = cost;
				iter_tmp = iter_j;
			}
		}
		iter_tmp->cluster.insert(get<0>(*iter_i));  // 将寄存器添加到cost最小的群组中去。
	}
	/*更新群组中心点*/
	for (auto& iter_i = clusters.begin(); iter_i != clusters.end(); ++iter_i)
	{
		float sum_x = 0;
		float sum_y = 0;

		for (auto& iter_j = iter_i->cluster.begin(); iter_j != iter_i->cluster.end(); ++iter_j)
		{
			sum_x = sum_x + get<1>(AllLoca_v[*iter_j - 1]);  // 这里减一是因为寄存器从1开始标号，vector从0开始
			sum_y = sum_y + get<2>(AllLoca_v[*iter_j - 1]);
		}
		if (iter_i->cluster.size()>0) //群组不为空时才更新中心点，为空群组中心点保留
			iter_i->center = make_pair(sum_x / iter_i->cluster.size(), sum_y / iter_i->cluster.size());
	}
	return clusters;
}
tuple<vector<C>,float> WeightCluster(string ReglocaFile,string InitcenterFile)
{
	vector<tuple<int, float, float>> AllLoca_v;
	ReadLoca(AllLoca_v, ReglocaFile);
	float obj = 0;//目标函数
	vector<C> clusters_v;  // 最终的多个群组
	vector<pair<float, float>> InitCenters_v;  // 初始群组中心点
	ifstream FileCenter(InitcenterFile, std::ios::in);
	string str;
	while (getline(FileCenter, str))  // 创建多个群组并保存中心点
	{
		C c;
		c.center = SplitStr(str);
		clusters_v.push_back(c);
	}
//	showClusters(clusters_v);
//	float tmpobj = pow(10,10); //记录临时的目标函数值
	vector<float> f;
	for(int i=0;i<20;++i)
	{
		OnceIter(AllLoca_v, clusters_v);
		obj = Obj(AllLoca_v, clusters_v);
		ClearClusters(clusters_v); //将群组内的节点都删除，保留中心点
		f.push_back(obj);
	}
	OnceIter(AllLoca_v, clusters_v);
	obj = Obj(AllLoca_v, clusters_v);

	f.push_back(obj);
	for (auto ele : f) cout << ele << " " ; cout << endl;
	
	/*for (auto ele : clusters_v) {
		set<int> s = ele.cluster;
		for (auto e : s) cout << e << "--"; cout << endl;
		cout << ele.center.first << "  " << ele.center.second << endl;
	}*/
	return make_tuple(clusters_v,obj);
}

void WriteClusters(string filename, vector<C> clusters)
{ // C++代码中的寄存器标号从1开始，而在ICC中寄存器是从0开始的，要减去1
	ofstream FileClusters(filename, std::ios::out);  // 打开文件
	for (auto iter = clusters.begin(); iter != clusters.end(); ++iter)
	{
		for (auto i = iter->cluster.begin(); i != iter->cluster.end(); ++i)
			FileClusters << (*i) - 1 << " ";
		FileClusters << endl;
		//cout << "end***" << endl;
	}
	FileClusters << "输出当前群组情况：" << endl;
	for (auto &iter = clusters.begin(); iter != clusters.end(); ++iter)
	{
		FileClusters << "cluster center is :( " << iter->center.first << "," << iter->center.second << ")" << endl;
		FileClusters << "cluster size is : " << iter->cluster.size() << endl;
		for (auto& ele : iter->cluster)
			FileClusters << ele << " "; FileClusters << endl;
		FileClusters << "mstlength is : " << iter->mstlength << endl;
	}
	FileClusters.flush();
	FileClusters.close();
}