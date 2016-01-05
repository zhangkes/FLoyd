// FLoyd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"MGraph.h"
void FloydTest()
{

	cout << "最短路径问题-弗洛伊德算法求解" << endl;
	MGraph Graph = BuildMGraph();
	ShowGraph(Graph);
	WeightType Distance[MaxVertexNum][MaxVertexNum];
	Vertex path[MaxVertexNum][MaxVertexNum];
	Floyd(Graph, Distance, path);
loop:cout << "请输入要求任意两点" << endl;
	int begin, end;
	cin >> begin >> end;
	PrintPath(path, begin, end);
	cout << "*********************" << endl;
	goto loop;
}
void main()
{
	FloydTest();
}

