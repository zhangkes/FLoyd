#include<iostream>
#include<malloc.h>
#include<conio.h>
using namespace std;
#define ERROR 0                 /*�����ʶ*/

/* ͼ���ڽӾ����ʾ�� */
#define MaxVertexNum 100        /* ��󶥵�����Ϊ100 */
#define INFINITY 99              /*����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;             /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;         /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;          /* ����洢������������Ϊ�ַ��� */
bool  Visited[MaxVertexNum];    /*���ʱ�ʶ����*/

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* ������ */
	int Ne;  /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum];  /* �ڽӾ��� */
	DataType Data[MaxVertexNum];               /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */

MGraph CreateMGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		for (W = 0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	//Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "���붥��ĸ����ͱ���" << endl;
	cin >> Nv;   /* ���붥����� */
	Graph = CreateMGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */
	cin >> Graph->Ne; /* ������� */
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i<Graph->Ne; i++) {
			cout << "����ߣ���ʽΪ ��� �յ� Ȩ�� " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}

	/* ������������ݵĻ����������� */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "��" << V << "����������� " << endl;
	cin >> Graph->Data[V];
	}*/

	return Graph;
}

void ShowGraph(MGraph Graph){

	/*�ڽӾ�����ʾ*/
	cout << endl << "�ڽӾ���" << endl;
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


/* �ڽӾ���洢 - ��Դ���·�㷨 */
bool Floyd(MGraph Graph, WeightType Distance[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
	Vertex i, j, k;

	/* ��ʼ�� */
	for (i = 0; i<Graph->Nv; i++)
		for (j = 0; j<Graph->Nv; j++) {
			Distance[i][j] = Graph->G[i][j];
			path[i][j] = -1;                  /*��ʼ��·��Ϊ-1*/
		}
	for (k = 0; k<Graph->Nv; k++)
		for (i = 0; i<Graph->Nv; i++)
			for (j = 0; j<Graph->Nv; j++)
				if (Distance[i][k]<INFINITY&&Distance[k][j]<INFINITY&&Distance[i][k] + Distance[k][j] < Distance[i][j]) {
					if (i == j && Distance[i][j]<0) /* �����ָ�ֵȦ */
						return false; /* ������ȷ��������ش����� */
					Distance[i][j] = Distance[i][k] + Distance[k][j];/*��¼��ǰ��������ľ���*/
					path[i][j] = k;                                  /*��¼·��*/
				}
	return true; /* �㷨ִ����ϣ�������ȷ��� */
}

/*��ӡ���������·��*/
void PrintPath(Vertex path[][MaxVertexNum], int begin, int end)
{
	/*ʡ�Ա߽���*/
	int index;           /*��ǰ·���±�*/
	index = end;
	while (index>=0)
	{
		cout << index << "->";   /*��ӡһ������*/
		index = path[begin][index];
	}
	cout << begin << "->end";
	cout << endl;
}