#include<iostream>
#include<ctime>
#include"AGraph.h"
using namespace std;

int main( ) {
	clock_t start,end;
	bool b;
	AGraph  g;
	//AGraph tg;                           //ת��ͼ

	g.createAGraph( );
	//g.printAGraph( );

	//tg.createTAG(g);
	//tg.printAGraph( );
//*********************************************
	/*g.initalVisited( );
	g.DFS(0);

	cout<<endl;
	g.initalVisited( );
	g.BFS(0);*/
//*******************************************
	start = clock( );
	b = g.BellmanFord(0);
	end = clock( );
	if(b == false){
		cout<<"���ڸ�Ȩ��·��BellmanFord�㷨�޷�������·����"<<endl;
	}
	cout<<"BellmanFord , ��Դ·��������ʱ��Ϊ��"<<end-start<<"ms"<<endl;
	system("pause");
	return 0;
}