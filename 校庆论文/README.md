### 内容介绍

这是校庆论文中的实验。用C++实现的，虽然最后的结果不好，但还是把实验记录一下。

#### 主要内容

1. 边类Edge，主要用来记录边的两个点和权重。应该都用共有成员的，这样读取数据成员的时候方便，不过已经用了private。

   ```c++
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
   ```

   

2. 最小生成树类 MST，用来记录每个群组内的节点，根据这些点生成的最小生成树的边和最小生成树的权重。

   ```c++
   
   ​```
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
   ​```
   ```

3. 群组结构体

   ```c++
   /*群组结构体*/
   struct C {
   	set<int> cluster;
   	pair<float, float> center;
   	float mstlength;
   };
   ```

   

4. **生成最小生成树的函数**

  ```C++
float kruskal(const C  & cluster, const vector < tuple<int, float, float>> &AllLoca_v, int size);
  ```



#### END

