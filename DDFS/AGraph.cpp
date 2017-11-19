#include"AGraph.h"
#include<iostream>
#include<fstream>
#include<string>
#include<queue>                             //BFS
#include<stack>
using namespace std;

AGraph::AGraph( ) {
	vn = 0;
	en = 0;
	count = 0;
	
	adjlist = new VNode[MAXSIZE];
	visited = new int[MAXSIZE]( );
	finished = new VertexType[MAXSIZE]( );

}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS           
	delete[ ] finished;             // kosaraju
}

void AGraph::createAGraph( ) {
	ArcNode *p= NULL;
	 VertexType start,end;
	 string s;

	 vn = VN;
	 en = EN;
	 fstream mydata;
	//mydata.open("./xiao.txt");
	//mydata.open("./vchocyc.txt");
	//mydata.open("./uniprot22m.txt");
	//mydata.open("./uniprot100m.txt");
	mydata.open("./uniprot150m.txt");

	if(vn > MAXSIZE){
		cout<<"顶点数目超过最大长度！"<<endl;
		system("pause");
		exit(-1);
	}

	for(int i=0;i<vn;++i){														//初始化顶点表

		adjlist[i].data = i;
		adjlist[i].instack = 0;
		adjlist[i].firstarc = NULL;
	}


	while(!mydata.eof( )){
		if(mydata.fail()){
			break;
		}
		for(int i=0;i<en;++i){
			mydata>>start>>end;
			p = new ArcNode;
			p->adjvex = end;

			p->nextarc = adjlist[start].firstarc;                        //头插
			adjlist[start].firstarc = p;

		//for(int i=0;i<vn;++i){                                     //找到结束边在顶点表中的位置
		//	if(adjlist[i].data == end){
		//		num = i;
		//		break;
		//	}
		//}

		//p->nextarc = adjlist[num].firstarc;                 //建立无向图反向插入一条边
		//adjlist[num].firstarc = p;
		}
	}
}
void AGraph::createTAG(AGraph &g) {
	ArcNode *p= NULL;
	ArcNode *q = NULL;
	 VertexType start,end;

	this->vn = g.vn;
	this->en = g.en;


	for(int i=0;i<vn;++i){                                   //初始化顶点表
	this->adjlist[i].data = g.adjlist[i].data;
	this->adjlist[i].firstarc = NULL;
	}

	for(int i=0;i<vn;++i){
		if(g.adjlist[i].firstarc != NULL){
			for(p = g.adjlist[i].firstarc;p!=NULL;p = p->nextarc){      //取出边和权值
				start = p->adjvex; 
				end =  g.adjlist[i].data;
				
				q = new ArcNode;
				q->adjvex = end;
				
				q->nextarc = adjlist[start].firstarc;                        //头插
				adjlist[start].firstarc = q;

			//for(int i=0;i<vn;++i){                                     //找到结束边在顶点表中的位置
			//	if(adjlist[i].data == end){
				//		num = i;
				//break;
			//	}
			//}

			//q->nextarc = adjlist[num].firstarc;                 //建立无向图反向插入一条边
			//adjlist[num].firstarc = q;
			}
		}
	}

}

void AGraph::printAGraph( ) {
	cout<<"图的打印结果为："<<endl;
	for(int i=0;i<vn;++i){
		if(adjlist[i].firstarc != NULL){
			for(ArcNode *p = adjlist[i].firstarc;p!=NULL;p = p->nextarc){
				cout<<"( "<<adjlist[i].data<<" , "<<p->adjvex<<" )"<<"   ";
			}
				cout<<endl;
		}
	
	}

}

void AGraph::initalVisited( ){
	for(int i=0;i<vn;++i){                             //初始化visited数组
			visited[i] = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;

	visited[v] = 1;					              //标记已访问
	                                                                 //访问v

	p = adjlist[v].firstarc;                            // 找到v在adjlist数组中的位置,找到相邻的下一个顶点

	while(p != NULL){

		if(visited[p->adjvex] == 0){              //找到相邻节点在visited数组中的位置,找到相邻未访问顶点，递归dfs
			DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
	finished[count++] = v;                      //对最后一个顶点做标记
}

void AGraph::kosaraju(VertexType v,AGraph &g2) {

	int count = 0;
	//initalVisited( );

	DFS(v);                                                              //深度遍历起始顶点传值

	for(int i=0;i<vn;++i){                                    //对于其它离散结点进行深度遍历
		if(visited[i] == 0){
			v = i;
			DFS(v);
		}
	}

	g2.initalVisited( );

	for(int i = vn-1;i>=0;--i){										 //找到完成时间大的点
		v = finished[i];

		if(g2.visited[v] ==0){							//继续寻找没有遍历过的点
			g2.DFS(v);
			++count;
		}
	}
	cout<<"强连通分量的个数为：  "<<count<<endl;
}

