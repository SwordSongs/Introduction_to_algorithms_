#include<iostream>
#include<ctime>
//#include"MGraph.h"
#include"AGraph.h"
using namespace std;

int main( ) {
	clock_t start,end;
	/*MGraph g;*/
	AGraph  g;
	//AGraph tg;                           //转置图

	/*g.createMGraph( );
	g.printMGraph( );*/

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
	g.Dijkstra(0);
	end = clock( );
	cout<<"迪杰斯特拉 , 求单源路径的运行时间为："<<end-start<<"ms"<<endl;
	system("pause");
	return 0;
}