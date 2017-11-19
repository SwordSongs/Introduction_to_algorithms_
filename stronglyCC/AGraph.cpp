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
	index = 0;
	cnt = 0;
	adjlist = new VNode[MAXSIZE];
	visited = new Visited[MAXSIZE];
	finished = new VertexType[MAXSIZE]( );
	DFN = new Visited[MAXSIZE];
	LOW = new Visited[MAXSIZE];
	pre = new Visited[MAXSIZE];
	sc = new Visited[MAXSIZE];
}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS           
	delete[ ] finished;             // kosaraju
	delete[ ] DFN;					//Tarjan
	delete[ ] LOW;
	delete[ ] pre;
	delete[ ] sc;
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
	//mydata.open("./uniport100m.txt");
	mydata.open("./uniprot150m.txt");

	if(vn > MAXSIZE){
		cout<<"顶点数目超过最大长度！"<<endl;
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
	for(int i=0;i<this->vn;++i){                             //初始化visited数组
		this->visited[i].data = this->adjlist[i].data;
		this->visited[i].flag = 0;
	}
}

void AGraph::initalDFN( ) {
	for(int i=0;i<vn;++i){
		DFN[i].data = adjlist[i].data;
		DFN[i].flag = 0;
	}
}

void AGraph::initalLOW( ) {
	for(int i=0;i<vn;++i){
		LOW[i].data = adjlist[i].data;
		LOW[i].flag = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;
	//int num;

	visited[v].flag = 1;					              //标记已访问
	//cout<<v<<"    ";                                 //访问v

	p = adjlist[v].firstarc;                            // 找到v在adjlist数组中的位置,找到相邻的下一个顶点

	while(p != NULL){

		if(visited[p->adjvex].flag == 0){              //找到相邻节点在visited数组中的位置,找到相邻未访问顶点，递归dfs
			DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
	finished[count++] = v;                      //对最后一个顶点做标记
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

void AGraph::kosaraju(VertexType v,AGraph &g2) {
//	int num;
	int count = 0;
	initalVisited( );
	//cout<<"图的深度优先搜索遍历结果为："<<endl;

	DFS(v);                                                        //深度遍历起始顶点传值

	for(int i=0;i<vn;++i){                                    //对于其它离散结点进行深度遍历
		if(visited[i].flag == 0){
			v = visited[i].data;
			DFS(v);
		}
	}

	g2.initalVisited( );
	//cout<<endl;
	//cout<<"转置图的深度优先搜索所得强连通分量为："<<endl;
//**********************************************************************
	/*for(int i=0;i<vn;++i){
		cout<<finished[i]<<"    ";
	}
	system("pause");*/
//**********************************************************************

	for(int i = vn-1;i>=0;--i){										 //找到完成时间大的点
		v = finished[i];

		if(g2.visited[v].flag==0){							//继续寻找没有遍历过的点
			g2.DFS(v);
			//cout<<endl;
			++count;
		}
	}
	cout<<"强连通分量的个数为：  "<<count<<endl;
}

void AGraph::Tarjan(VertexType v,stack<int> &s) {

	VertexType j;
	//int nv;
	//int nj;
	ArcNode *p = NULL;

	//for(int i=0;i<vn;++i){
	//	if(DFN[i].data == v){
	//		nv = i;
	//		break;
	//	}
	//}
	DFN[v].flag = ++index;
	LOW[v].flag = DFN[v].flag;

	s.push(v);
	adjlist[v].instack = 1;

	p = adjlist[v].firstarc;																				//找到相邻的下一个顶点
		while(p != NULL){
					j = p->adjvex;																				//j指向出边顶点

					//for(int i=0;i<vn;++i){																		//找nj
					//		if(j == LOW[i].data){
					//			nj = i;
					//			break;
					//		}	
					//	}
				
				if(DFN[j].flag == 0){																							                                   //未访问
						Tarjan(j,s);																									                                  //递归
						LOW[v].flag = LOW[v].flag < LOW[j].flag ? LOW[v].flag : LOW[j].flag;                              //找最小值
				}

				else
					if(adjlist[j].instack == 1) {																					//判断顶点v是否在栈中

						LOW[v].flag = LOW[v].flag > DFN[j].flag ? DFN[j].flag : LOW[v].flag;  //找最小值
					}	

					p = p->nextarc;
		}


	if(DFN[v].flag == LOW[v].flag){

		do{                                                      //强连通分量出栈
				if(s.empty( ) == false){

					//for(int i=0;i<vn;++i){																		//找nj
					//			if(j == adjlist[i].data){
					//				nj = i;
					//				break;
					//			}	
					//		}
					j = s.top( );
					adjlist[j].instack = 0;
					//cout<<s.top( )<<"    ";
					s.pop( );
				}
		}
		while(v != j);
		++count;
		//cout<<endl;
	}
}

void AGraph::Gabow(VertexType v,stack<VertexType> &path,stack<VertexType> &root) {
	for(int i=0;i<vn;++i){                                    //初始化pre
		pre[i].data = adjlist[i].data;
		pre[i].flag = -1;
	}

	for(int i=0;i<vn;++i){                                //初始化sc
		sc[i].data = adjlist[i].data;
		sc[i].flag = -1;
	}

	GabowDFS(v,path,root);

	for(int i=0;i<vn;++i){
		if(pre[i].flag == -1){
			GabowDFS(i,path,root);
		}
	}

}

void AGraph::GabowDFS(VertexType v,stack<VertexType> &path,stack<VertexType> &root) {
	ArcNode *p = NULL;
	VertexType w;
	int vnum,wnum;
	int num;

	path.push(v);                                  //将顶点入栈
	root.push(v);

	//for(int i=0;i<vn;++i){                     //找到顶点v的序号
	//	if(adjlist[i].data == v){
	//		vnum = i;
	//		break;
	//	}
	//}

	pre[v].flag = ++cnt;                    //对顶点遍历的顺序编号

	for(p = adjlist[v].firstarc;p!=NULL;p = p->nextarc){                //pre 与 adjlist数据一致
		w = p->adjvex;
		//for(int i=0;i<vn;++i){                                                              //找到顶点w的序号
		//	if(adjlist[i].data == w){
		//		wnum = i;
		//		break;
		//	}
		//}

		if(pre[w].flag == -1)
			GabowDFS(w,path,root);                                                 //w没有访问，递归去访问w
		else
			if(sc[w].flag == -1){                                                         //顶点w被访问过，顶点属于哪个强连通分量还未确定
				//for(int i=0;i<vn;++i){
				//	if(root.top( ) == adjlist[i].data){
				//		num = i;
				//		break;
				//	}
				//}

				while(pre[root.top( )].flag>pre[w].flag){
					 root.pop( );
					//for(int i=0;i<vn;++i){                                       //找到root中新的栈顶元素的序号
					//	if(root.top( ) == adjlist[i].data){
					//		num = i;
					//		break;
					//	}	
					//}
				}

			}
	
	}

	if(root.top( ) == v){                                               //找到强连通分量的根
		if(root.empty( ) == false)
			root.pop( );
		do{
			if(path.empty( ) == false){
				w = path.top( );                                     //将path栈出栈
				//for(int i=0;i<vn;++i){
				//	if(w == adjlist[i].data){
				//		wnum = i;
				//		break;
				//	}
				//}
				sc[w].flag = count;
				//cout<<w<<"    ";
				path.pop( );
			}
		}
		while(v != w);
		++count;                                                  //强连通分量计数
		//cout<<endl;
	}
}
