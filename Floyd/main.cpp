#include<iostream>
#include<ctime>
#include"MGraph.h"
using namespace std;

int main( ) {
	clock_t start,end;
	MGraph g;
	//AGraph  g;
	//AGraph tg;                           //ת��ͼ

	g.createMGraph( );
	g.printMGraph( );

	/*g.createAGraph( );
	g.printAGraph( );*/

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
	g.Floyd();
	end = clock( );
	cout<<"���������㷨 , ���Դ���·��������ʱ��Ϊ��"<<end-start<<"ms"<<endl;
	system("pause");
	return 0;
}