#include<iostream>
#include"AGraph.h"
#include<stack>
#include<ctime>
using namespace std;

int main() {

	AGraph g;
	AGraph tg;                                            //转置图
	clock_t start,end;

	g.createAGraph( );                                //创建图
	//g.printAGraph( );

	
	cout<<endl;
	tg.createTAG(g);                                  //创建转置图,kosaraju使用
	//tg.printAGraph( );
//******************************************************
	start = clock( );
	g.kosaraju(1,tg);
	end = clock( );
	cout<<"Kosaraju算法时间为："<<end - start<<"ms"<<endl;
//*******************************************************
	//g.initalDFN( );										 //初始化两个数组,Tarjan算法
	//g.initalLOW( );
	//stack<VertexType> s;
	//cout<<"Tarjan算法，图的强连通分量为："<<endl;
	//start = clock( );
	//for(int i=0;i<VN;++i){                                 //类似深度优先，是森林结构的图
	//	if(g.DFN[i].flag==0)
	//		g.Tarjan(i,s);
	//	
	//}
	//end = clock( );
	//cout<<"图的强连通分量的个数为："<<endl;
	//cout<<g.count<<endl;
	//cout<<"Tarjan算法时间为："<<end - start<<"ms"<<endl;
//********************************************************
	//stack<VertexType> path;                         //Gabow算法,找顶点太麻烦，顶点不支持通用性，编号从0开始
	//stack<VertexType> root;
	//cout<<"Gabow算法，图的强连通分量为："<<endl;
	//start = clock( );
	//g.Gabow(1,path,root);
	//end = clock( );
	//cout<<"图的强连通分量的个数为："<<endl;
	//cout<<g.count<<endl;
	//cout<<"Gabow算法时间为："<<end - start<<"ms"<<endl;
//***********************************************************************
	//g.initalFinished( );
	//g.initalVisited( );
	//cout<<"图的深度优先搜索遍历结果为："<<endl;
	//g.DFS(1);                                                        //深度遍历起始顶点传值
	//cout<<endl;
	//g.initalVisited( );
	//cout<<"图的广度优先搜索遍历结果为："<<endl;
	//g.BFS(1);
	//cout<<endl;
//**************************************************************************
	system("pause");
	return 0;
}