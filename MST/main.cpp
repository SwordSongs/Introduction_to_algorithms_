#include<iostream>
#include<ctime>
//#include"AGraph.h"                  //����primAGraph
#include"MGraph.h"              //����kruskalMGraph
using namespace std;

int main() {

	clock_t start,end;

	//MGraph *g = new MGraph;
	//AGraph *g = new AGraph;

	//createAGraph(g);
	//printAGraph(g);
	//system("pause");
	
	//createMGraph(g);
	//printMGraph(g);

	start = clock( );
	kruskalMGraph( );                        //����Ҫ��ͼ��ֻ��Ҫ����ı߼����� ,��ҪMGraph.h�ļ�   156ms����
	//primMGraph(g,0);                        //�ڽӾ���ֻ��ʵ��С���ݼ�
	//primAGraph(g,0);                            //�ڽӱ����ʵ�ִ����ݼ�������ʱ��Ƚ���      687ms    
	end = clock( );
	cout<<"ʱ�仨��Ϊ��"<<end-start<<"ms"<<endl;

	//deleteMGraph(g);
	system("pause");
	return 0;
}