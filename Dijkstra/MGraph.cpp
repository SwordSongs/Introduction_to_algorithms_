#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include"MGraph.h"
using namespace std;

MGraph::MGraph( ) {
	vn = 0;
	en = 0;
	vex = new VertexType[MAXVEX]( );
	edge = new ArcType* [MAXVEX];
	for(int i=0;i<MAXVEX;++i){
		edge[i] = new ArcType[MAXVEX];
	}

	for(int i=0;i<MAXVEX;++i){                              //初始化邻接矩阵
		for(int j=0;j<MAXVEX;++j){
			if(i == j){
				edge[i][j] = 0;                                 
			}
			else{
				edge[i][j] = INF;
			}
		}
	}
}

MGraph::~MGraph( ) {
	delete[ ] vex;
	for(int i=0;i<MAXVEX;++i){
		delete[ ] edge[i];
	}
	delete[ ] edge;
}

void MGraph::createMGraph( ) {
	//cout<<"请输入顶点数目和边的数目（空格分隔）："<<endl;
	vn = 7;
	en = 12;
	//cout<<"请输入顶点的信息："<<endl;
	for(int i=0;i<vn;++i){
		vex[i] = i;
	}

	//cout<<"请输入边的信息(start end weight)："<<endl;
	VertexType id,start,end;
	ArcType w;
	int m,n;
	fstream mydata;
	string s;

	mydata.open("./xiao.txt");
	while(!mydata.eof( )){
		getline(mydata,s);
		if(s.find("#")){
			continue;
		}

		for(int i=0;i<en;++i){
			mydata>>id>>start>>end>>w;
			for(int j=0;j<vn;++j){
				if(start == vex[j]){
					m = j;
				}
				if(end == vex[j]){
					n = j;
				}
			}
			edge[m][n] = w;                          //有向图
		}
	}
	mydata.close( );
}

void MGraph::printMGraph( ) {
	cout<<"顶点信息为："<<endl;
	for(int i=0;i<vn;++i){
		cout<<vex[i]<<"      ";                  //打印顶点信息
	}
	cout<<endl;
	
	cout<<"边的信息为："<<endl;
	for(int i=0;i<vn;++i){
		for(int j=0;j<vn;++j){
			if(edge[i][j] == INF){
			cout<<setw(8)<<"∞";
			}
			else{
				cout<<setw(8)<<edge[i][j]; 
			}
		}
		cout<<endl;
	}
}