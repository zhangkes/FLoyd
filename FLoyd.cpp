// FLoyd.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"MGraph.h"
void FloydTest()
{

	cout << "���·������-���������㷨���" << endl;
	MGraph Graph = BuildMGraph();
	ShowGraph(Graph);
	WeightType Distance[MaxVertexNum][MaxVertexNum];
	Vertex path[MaxVertexNum][MaxVertexNum];
	Floyd(Graph, Distance, path);
loop:cout << "������Ҫ����������" << endl;
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

