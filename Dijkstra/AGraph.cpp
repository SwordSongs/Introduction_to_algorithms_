#include"AGraph.h"
#include<iostream>
#include<fstream>
#include<queue>                        //BFS
#include<stack>
using namespace std;
//#define VN	7
//#define EN  12

#define INF  1000000.0                   //表示不可达

AGraph::AGraph( ) {
	vn = 0;
	en = 0;
	
	adjlist = new VNode[MAXSIZE];
	visited = new Visited[MAXSIZE];
	  dist   =  new ArcType[MAXSIZE];
	path = new VertexType[MAXSIZE];
	set   =  new int[MAXSIZE]( );
}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS       
	delete[ ] dist;
	delete[ ] path;
	delete[ ] set;
}

void AGraph::createAGraph( ) {
	ArcNode *p= NULL;
	 VertexType start,end;
	 int id;
	 ArcType weight;
	 int num;


	 vn = VN;
	 en = EN;
	/*cout<<"请输入顶点的数目："<<endl;
	cin>>vn;*/
	 fstream mydata;
	// mydata.open("./OL.txt");
     //mydata.open("./TG.txt");
	//mydata.open("./Cgraph.txt");
	//mydata.open("./North.txt");
	mydata.open("./San.txt");
	 //mydata.open("./xiao.txt");

	if(vn > MAXSIZE){
		cout<<"顶点数目超过最大长度！"<<endl;
		exit(-1);
	}
	/*cout<<"请输入边的数目："<<endl;
	cin>>en;*/

	//cout<<"请输入顶点的信息：（空格分隔）"<<endl;
	for(int i=0;i<vn;++i){														//初始化顶点表

		adjlist[i].data = i;
		adjlist[i].firstarc = NULL;
	}

	//cout<<"请输入边的信息(strat end weight)："<<endl;
	while(!mydata.eof( )){
		
		for(int i=0;i<en;++i){
			mydata>>id>>start>>end>>weight;
			p = new ArcNode;
			p->id = id;
			p->adjvex = end;
			p->weight = weight;

			for(int i=0;i<vn;++i){                                     //找到起始边在顶点表中的位置
				if(adjlist[i].data == start){
					num = i;
					break;
				}	
			}
				p->nextarc = adjlist[num].firstarc;                        //头插
				adjlist[num].firstarc = p;

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
	mydata.close( );
}

void AGraph::createTAG(AGraph &g) {
	ArcNode *p= NULL;
	ArcNode *q = NULL;
	 VertexType start,end;
	 ArcType weight;
	 int num;

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
				weight = p->weight;
	
				q = new ArcNode;
				q->adjvex = end;
				q->weight = weight;

				for(int j=0;j<vn;++j){                                     //找到起始边在顶点表中的位置
					if(this->adjlist[j].data == start){
						num = j;
						break;
					}
				}

				q->nextarc = adjlist[num].firstarc;                        //头插
				adjlist[num].firstarc = q;

			//for(int i=0;i<vn;++i){                                     //找到结束边在顶点表中的位置
			//	if(adjlist[i].data == end){
				//		num = i;
		//			break;
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
				cout<<"( "<<adjlist[i].data<<" , "<<p->adjvex<<" , "<<p->weight<<" )"<<"   ";
			}
				cout<<endl;
		}
	
	}

}

void AGraph::initalVisited( ){
	for(int i=0;i<this->vn;++i){                             //初始化visited数组
		this->visited[i].data = this->adjlist[i].data;
		this->visited[i].flag = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;
	int num;
	for(int i=0;i<vn;++i){                      //找到v在visited数组中的位置
		if(visited[i].data == v){
			num = i;
			break;
		}
	}

	visited[num].flag = 1;              //标记已访问
	cout<<v<<"    ";                    //访问v

	for(int i=0;i<vn;++i){              //找到v在adjlist数组中的位置
		if(adjlist[i].data == v){
			num = i;
			break;
		}
	}

	p = adjlist[num].firstarc; //找到相邻的下一个顶点

	while(p != NULL){
		for(int i=0;i<vn;++i){                   //找到相邻节点在visited数组中的位置
			if(p-> adjvex == visited[i].data){
				num = i;
				break;
			}
		}

		if(visited[num].flag == 0){              //找到相邻未访问顶点，递归dfs
			(*this).DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
}

void AGraph::BFS(VertexType v) {
	ArcNode *p = NULL;
	queue<char> q;
	int num;
	char c;

	for(int i=0;i<vn;++i){                      //找到v在visited数组中的位置
		if(visited[i].data == v){
			num = i;
			break;
		}
	}

	this->visited[num].flag = 1;              //标记已访问
	cout<<v<<"    ";                    //访问v

	q.push(v);                              //v进队

	while(!q.empty()){
		c = q.front( );                          //返回队首元素
		q.pop( );                                //顶点出队

		for(int i=0;i<vn;++i){
			if(c == adjlist[i].data){
				num = i;
				break;
			}
		}

		p = adjlist[num].firstarc;                      //p指向相邻顶点

		while(p != NULL){

			for(int i=0;i<vn;++i){                   //找到相邻节点在visited数组中的位置
				if(p-> adjvex == visited[i].data){
					num = i;
					break;
				}
			}

			if(visited[num].flag == 0){
				cout<<p->adjvex<<"    ";
				visited[num].flag = 1;                //标记已访问
				q.push(p->adjvex);                             //将顶点入队
			}
			p = p->nextarc;
		}
	}
}

void AGraph::Dijkstra(VertexType v) {
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/Dijkstra/Dijkstra/result.txt");

	ArcNode *p = NULL;
	int num;
	ArcType w = INF;                            //记录权值
	ArcType min;
	

	for(int i=0;i<vn;++i){                      //初始化dist
		if(i == v)
			dist[i] = 0.0;
		else
			dist[i] = INF;
		path[i] = -1;                              //初始化path
	}
	
	if(adjlist[v].firstarc != NULL){                   
			for(p = adjlist[v].firstarc;p!=NULL;p= p->nextarc){
				dist[p->adjvex] = p->weight;   
				if(p->weight < INF)
					path[p->adjvex] = v;
			}
	}
	
	set[v] = 1;                                              //初始化set

	                                                             //三个数组完成初始化
//***********************************************************
	/*for(int i=0;i<vn;++i){
		cout<<dist[i]<<"      ";
	}
	cout<<endl;
	for(int i=0;i<vn;++i){
		cout<<path[i]<<"     ";
	}
	cout<<endl;
	for(int i=0;i<vn;++i){
		cout<<set[i]<<"      ";
	}
	cout<<endl;
	system("pause");*/
//***********************************************************

	for(int i=0;i<vn;++i){
		 min = INF;
		for(int j=0;j<vn;++j){                         
			if(set[j] == 0 && dist[j] < min){
				num = j;
				min = dist[j];
			}
		} 
		set[num] = 1;                                  //选中dist中最小的那个顶点j,步骤1

//		for(int k=0;k<vn;++k){                   //扫描未选中顶点，更新选中顶点与未选中点的新路径
//			if(set[k] == 0){
//				for(p = adjlist[num].firstarc;p!=NULL;p=p->nextarc){
//					if(p->adjvex == k)
//						w = p->weight;             //有num到k的一条边，记录w值
//				}
//				
//				if(dist[k] > dist[num]+w){
//					dist[k] = dist[num]+w;
//					path[k] = num;
//				}
//				w = INF;                             //用完w后，将w恢复INF
//			}
////*********************************************
//		/*for(int i=0;i<vn;++i){
//			if(dist[i] > 1000000.0)
//				cout<<"( "<<v<<" , "<<i<<" , "<<"∞"<<" ) "<<endl;
//			else
//				cout<<"( "<<v<<" , "<<i<<" , "<<dist[i]<<" ) "<<endl;
//		}
//		cout<<endl;*/
////*********************************************
//		}

		for(p = adjlist[num].firstarc;p;p=p->nextarc){      //扫描未选中顶点，更新选中顶点与未选中点的新路径
			if(set[p->adjvex]==0 && dist[num]+p->weight<dist[p->adjvex]){
				dist[p->adjvex] = dist[num] + p->weight;
				path[p->adjvex] = num;
			}
		}

	}

	/*result<<"单源顶点为：    "<<v<<endl;
	result<<"迪杰斯特拉算法所求单源最短路径为："<<endl;

	for(int i=0;i<vn;++i){
		if(dist[i] >= 1000000.0)
			result<<"( "<<v<<" , "<<i<<" , "<<"∞"<<" ) "<<endl;
		else
			result<<"( "<<v<<" , "<<i<<" , "<<dist[i]<<" ) "<<endl;
	}*/
	result.close( );

}
