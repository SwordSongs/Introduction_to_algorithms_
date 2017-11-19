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

	for(int i=0;i<MAXVEX;++i){                              //��ʼ���ڽӾ���
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
	//cout<<"�����붥����Ŀ�ͱߵ���Ŀ���ո�ָ�����"<<endl;
	vn = 7;
	en = 12;
	//cout<<"�����붥�����Ϣ��"<<endl;
	for(int i=0;i<vn;++i){
		vex[i] = i;
	}

	//cout<<"������ߵ���Ϣ(start end weight)��"<<endl;
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
			edge[m][n] = w;                          //����ͼ
		}
	}
	mydata.close( );
}

void MGraph::printMGraph( ) {
	cout<<"������ϢΪ��"<<endl;
	for(int i=0;i<vn;++i){
		cout<<vex[i]<<"      ";                  //��ӡ������Ϣ
	}
	cout<<endl;
	
	cout<<"�ߵ���ϢΪ��"<<endl;
	for(int i=0;i<vn;++i){
		for(int j=0;j<vn;++j){
			if(edge[i][j] == INF){
			cout<<setw(8)<<"��";
			}
			else{
				cout<<setw(8)<<edge[i][j]; 
			}
		}
		cout<<endl;
	}
}