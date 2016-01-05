#include<iostream>
#include<malloc.h>
#include<conio.h>
using namespace std;
#define ERROR 0                 /*错误标识*/

/* 图的邻接矩阵表示法 */
#define MaxVertexNum 100        /* 最大顶点数设为100 */
#define INFINITY 99              /*∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;             /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;         /* 边的权值设为整型 */
typedef char DataType;          /* 顶点存储的数据类型设为字符型 */
bool  Visited[MaxVertexNum];    /*访问标识数组*/

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* 顶点数 */
	int Ne;  /* 边数   */
	WeightType G[MaxVertexNum][MaxVertexNum];  /* 邻接矩阵 */
	DataType Data[MaxVertexNum];               /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

MGraph CreateMGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		for (W = 0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* 若是无向图，还要插入边<V2, V1> */
	//Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "输入顶点的个数和边数" << endl;
	cin >> Nv;   /* 读入顶点个数 */
	Graph = CreateMGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */
	cin >> Graph->Ne; /* 读入边数 */
	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i<Graph->Ne; i++) {
			cout << "读入边，格式为 起点 终点 权重 " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}

	/* 如果顶点有数据的话，读入数据 */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "第" << V << "个顶点的数据 " << endl;
	cin >> Graph->Data[V];
	}*/

	return Graph;
}

void ShowGraph(MGraph Graph){

	/*邻接矩阵显示*/
	cout << endl << "邻接矩阵" << endl;
	for (int i = 0; i < Graph->Nv; ++i)
	{
		cout << "  " << i;
	}
	cout << endl;
	for (int i = 0; i < Graph->Nv; ++i)
	{
		cout << i << "|";
		for (int j = 0; j<Graph->Nv; ++j)
		{
			cout << Graph->G[i][j] << "  ";
		}
		cout << endl;
	}
}


/* 邻接矩阵存储 - 多源最短路算法 */
bool Floyd(MGraph Graph, WeightType Distance[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
	Vertex i, j, k;

	/* 初始化 */
	for (i = 0; i<Graph->Nv; i++)
		for (j = 0; j<Graph->Nv; j++) {
			Distance[i][j] = Graph->G[i][j];
			path[i][j] = -1;                  /*初始化路径为-1*/
		}
	for (k = 0; k<Graph->Nv; k++)
		for (i = 0; i<Graph->Nv; i++)
			for (j = 0; j<Graph->Nv; j++)
				if (Distance[i][k]<INFINITY&&Distance[k][j]<INFINITY&&Distance[i][k] + Distance[k][j] < Distance[i][j]) {
					if (i == j && Distance[i][j]<0) /* 若发现负值圈 */
						return false; /* 不能正确解决，返回错误标记 */
					Distance[i][j] = Distance[i][k] + Distance[k][j];/*记录当前新增顶点的距离*/
					path[i][j] = k;                                  /*记录路径*/
				}
	return true; /* 算法执行完毕，返回正确标记 */
}

/*打印任意两点的路径*/
void PrintPath(Vertex path[][MaxVertexNum], int begin, int end)
{
	/*省略边界检查*/
	int index;           /*当前路径下标*/
	index = end;
	while (index>=0)
	{
		cout << index << "->";   /*打印一个顶点*/
		index = path[begin][index];
	}
	cout << begin << "->end";
	cout << endl;
}