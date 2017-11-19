#include<iostream>
#include"AGraph.h"
#include<stack>
#include<ctime>
using namespace std;

int main( ) {

	AGraph g;
	AGraph tg;                                            //转置图
	clock_t start,end;

	g.createAGraph( );                                //创建图
	//g.printAGraph( );

	
	cout<<endl;

	start = clock( );
	tg.createTAG(g);                                  //创建转置图,kosaraju使用
	//tg.printAGraph( );
	g.kosaraju(1,tg);
	end = clock( );
	cout<<"Kosaraju算法时间为："<<end - start<<"ms"<<endl;

	system("pause");
	return 0;
}