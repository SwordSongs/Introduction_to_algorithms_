#include<iostream>
#include<ctime>
#include"AGraph.h"
using namespace std;

int main( ) {
	clock_t start,end;
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
	g.Johnson( );
	end = clock( );
	cout<<"求单源路径的运行时间为："<<end-start<<"ms"<<endl;
	system("pause");
	return 0;
}