#include<iostream>
#include<ctime>
#include"AGraph.h"
using namespace std;

int main( ) {
	clock_t start,end;
	bool b;
	AGraph  g;
	//AGraph tg;                           //转置图

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
		cout<<"存在负权回路，BellmanFord算法无法求得最短路径！"<<endl;
	}
	cout<<"BellmanFord , 求单源路径的运行时间为："<<end-start<<"ms"<<endl;
	system("pause");
	return 0;
}