#include<iostream>
#include<ctime>
//#include"AGraph.h"                  //运行primAGraph
#include"MGraph.h"              //运行kruskalMGraph
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
	kruskalMGraph( );                        //不需要建图，只需要定义的边集数组 ,需要MGraph.h文件   156ms左右
	//primMGraph(g,0);                        //邻接矩阵只能实现小数据集
	//primAGraph(g,0);                            //邻接表可以实现大数据集，但是时间比较慢      687ms    
	end = clock( );
	cout<<"时间花费为："<<end-start<<"ms"<<endl;

	//deleteMGraph(g);
	system("pause");
	return 0;
}