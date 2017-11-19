#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define INF 1000000
//#define MAXVEX 10                     //最大顶点数
//#define MAXVEX     6105                //OL
//#define MAXVEX   18263                  //TG
//#define MAXVEX       21048                 //Cgraph
//#define MAXVEX      175813                //North
#define MAXVEX      174956               //San



//#define VN    6105                           //OL
//#define EN    7035

//#define VN    18263                           //TG
//#define EN    23874

//#define VN    21048                           //Cgraph
//#define EN    21693

//#define VN    175813                           //North
//#define EN    179179

#define VN    174956                           //San
#define EN    223001






typedef int VertexType;					//顶点类型
typedef double ArcType;              //边上权值类型

typedef struct ArcNode{
	int adjvex;                         //该边所指向的结点位置
	ArcType weight;                //存储权值
	struct ArcNode *nextarc;         //指向下一条边的指针
}ArcNode;

typedef struct VNode{
	VertexType data;               //顶点信息
	ArcNode *firstarc;              //指向第一条边的指针
}VNode;

typedef struct AGraph{
	VNode adjlist[MAXVEX];         //顶点表
	int vn;                                     //顶点数目
	int en;                                     //边的数目
}AGraph;

void createAGraph(AGraph *g) {
	
	int i,j,k,id;
	ArcType w;
	ArcNode *p;
	
	/*g->vn = 5;
	g->en = 8;*/

	g->vn = VN;                       //顶点数目
	g->en = EN;                      //边的数目
	
	for(i=0;i<g->vn;++i){                         //初始化
		g->adjlist[i].data = i;
		g->adjlist[i].firstarc = NULL;           //将边表置空
	}

	fstream mydata;
	//mydata.open("./xiao.txt");
	//mydata.open("./OL.txt");
	//mydata.open("./TG.txt");
	//mydata.open("./graph.txt");                 //加州
	//mydata.open("./North.txt");  
	mydata.open("./San.txt");  
	string s;
	while(!mydata.eof( )){
		
		for(k=0;k<g->en;++k){              //建立边表
		
			mydata>>id>>i>>j>>w;                   //

			p = new ArcNode;
			p->adjvex = j;                                           //邻接为j
			p->weight = w;                                        //权重
			p->nextarc = g->adjlist[i].firstarc;             //将p指向当前顶点的firstarc
			g->adjlist[i].firstarc = p;                           //将当前顶点的firstarc指向边node
	    
			p = new ArcNode;
			p->adjvex = i;                                            //邻接为i
			p->weight = w;
			p->nextarc = g->adjlist[j].firstarc;
			g->adjlist[j].firstarc = p;
		}
	}
}

void printAGraph(AGraph *g) {

	for(int i=0;i<g->vn;++i){
			if(g->adjlist[i].firstarc != NULL){
				for(ArcNode *p=g->adjlist[i].firstarc;p!=NULL;p=p->nextarc){
					cout<<" ( "<<g->adjlist[i].data<<" , "<<p->adjvex<<" , "<<p->weight<<" ) "<<"  ";
				}
			}
		cout<<endl;
	}

}


//****************************************************************//普利姆算法
void primAGraph(AGraph *g,int v0) {

	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/MST/MST/result(p).txt");

	ArcType *lowcost = new ArcType[MAXVEX];                                       //生成树到剩余各顶点最短边的权值
	VertexType *vset = new VertexType[MAXVEX]( );                                  //表示顶点i是否已经并入生成树中                                                          
	ArcNode *p;

	ArcType min = 0;
	ArcType sum = 0;

	VertexType k;
	VertexType v = v0;                                          //选取一个顶点

	for(int i=0;i<MAXVEX;++i){                            //lowcost初始化
		lowcost[i] = INF;
	}
	
	p = g->adjlist[v].firstarc;                    //从选中v0开始更新lowcost数组
	while(p!=NULL){
		lowcost[p-> adjvex] = p->weight;
		p = p->nextarc;
	}	
	
//***************************************************************
	/*for(int i=0;i<	MAXVEX;++i){
		cout<<lowcost[i]<<"     ";
	}
	system("pause");*/
//***************************************************************

	                                                      
	vset[v0] = 1;                                         //顶点v0被选入生成树
	//result<<"prim,最小生成树的为："<<endl;            //打印边
	//result<<v<<"---->";

	for(int i=0;i<g->vn-1;++i){
		min = INF;

		for(int j=0;j<g->vn;++j){                            //从候选边中选出最小的边
			if(vset[j] == 0 && lowcost[j]<min){
				min = lowcost[j];
				k = j;
			}
		}

		//result<<k<<"---->";
		vset[k] = 1;                                                                    //候选边的顶点并入生成树
		v= k;
		sum += min;

		  p = g->adjlist[v].firstarc;                                             //更新生成树到其他剩余顶点的最短距离
		  while(p != NULL){
			 if(vset[p->adjvex]==0){
				if(p->weight<lowcost[p->adjvex]){
					lowcost[p->adjvex] = p->weight;
				 }
			}
			 p = p->nextarc;
		  }
		
	}
	
	cout<<endl;
	cout<<"最小生成树的权值和为："<<sum<<endl;
	
	delete[ ] lowcost;
	delete[ ] vset;
	result.close( );
}