#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

#define INF 1000000
#define MAXEDG  223001                //克鲁斯卡尔算法用

//#define VN  6105                                 //OL
//#define EN   7035

//#define VN 18263                                 //TG
//#define EN   23874

//#define VN    21048                           //Cgraph
//#define EN    21693

//#define VN    175813                           //North
//#define EN    179179

#define VN    174956                           //San
#define EN    223001


//#define MAXEDG 8
#define MAXVEX  223001                 //最大顶点数
//#define MAXVEX  10
typedef int VertexType;					//顶点类型
typedef float ArcType;                      //边上权值类型

typedef struct MGraph{
	VertexType *vex;
	ArcType **edges;
	int vn;                                              //顶点数目
	int en;                                              //边的数目
}MGraph;

void createMGraph(MGraph *g) {

	g->vex = new int[MAXVEX]( );          //初始化
//*******************************************************************************
	/*for(int i=0;i<MAXVEX;++i){              //测试
		cout<<g->vex[i]<<endl;
	}
	system("pause");*/
//*******************************************************************************

	g->edges = new ArcType* [MAXVEX]( );
	for(int i=0;i<MAXVEX;++i){
		g->edges[i] = new ArcType[MAXVEX]( );
	}
	//**************************************************************************
	//for(int i=0;i<MAXVEX;++i){             //测试
	//	for(int j=0;j<MAXVEX;++j){
	//		cout<<g->edges[i][j]<<endl;
	//	}
	//}
	//system("pause");
//**************************************************************************

	for(int i=0;i<MAXVEX;++i){
		for(int j=0;j<MAXVEX;++j){
			if(i == j){
				g->edges[i][j] = 0;
			}
			else{
				g->edges[i][j] = 1000000;
			}
		}
	}

	//cout<<"请输入顶点数目vn和边的数目en(使用空格分隔) : "<<endl;
	//g->vn = 21048;                             //顶点数目
	//g->en = 21693;                             //边的数目
	g->vn = 5;                             //顶点数目
	g->en = 8;                             //边的数目


	//cout<<"请输入顶点的信息(使用空格分隔)"<<endl;
	for(int i=0;i<g->vn;++i){                              //录入顶点信息
		g->vex[i] = i;
	}
//**************************************************************************
	/*for(int i=0;i<g->vn;++i){
		cout<<g->vex[i]<<"   ";                        //测试
	}
	system("pause");*/
//**************************************************************************

	VertexType start,end;
	ArcType w;
	int id;
	int m,n;
	fstream mydata;
	//mydata.open("./graph.txt");
	mydata.open("./xiao.txt");
	string s;

	while(!mydata.eof()){
		getline(mydata,s);
		if(s.find("#")){
			continue;
		}

		for(int i=0;i<g->en;++i){
			mydata>>id>>start>>end>>w;
			for(int i=0;i<g->vn;++i){
				if(g->vex[i] == start){
					m = i;
				}
				if(g->vex[i] == end){
					n = i;
				}
			}
				g->edges[m][n] = w;            //赋权值
				g->edges[n][m] = w;
		}

	}
	mydata.close( );

	//for(int j=0;j<g->en;++j){
	//	cout<<"请输入边（vi，vj）的顶点和边上的权重(用空格分隔)："<<endl;
	//	cin>>start>>end>>w;
	//	for(int i=0;i<g->vn;++i){        //从顶点数组中取出下标（顶点不重复）
	//		if(g->vex[i] == start){
	//			m = i;
	//		}
	//		if(g->vex[i] == end){
	//			n = i;
	//		}
	//	}

	//	g->edges[m][n] = w;            //赋权值
	//	g->edges[n][m] = w;
	//	
	//}
}

void deleteMGraph(MGraph *g) {
	delete[ ] g->vex;
	for(int i=0;i<MAXVEX;++i){
		delete[ ] g->edges[i];
	}
	delete[ ] g->edges;
}


void printMGraph(MGraph *g) {
	cout<<"顶点信息为："<<endl;
	for(int i=0;i<g->vn;++i){
		cout<<g->vex[i]<<"       ";             //打印顶点信息
	}
//***************************************
	/*system("pause");*/
//**************************************
	cout<<endl;
	cout<<"边的信息为："<<endl;                  //打印边的信息
	for(int i=0;i<g->vn;++i){
		for(int j=0;j<g->vn;++j){
			cout<<g->edges[i][j]<<"       ";
		}
		cout<<endl<<endl<<endl<<endl;
	}

}

//***************************************************************//                prim算法

void primMGraph(MGraph *g,VertexType v0) {
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/MST/MST/result(p).txt");
	ArcType *lowcost = new ArcType[MAXVEX]();                           //生成树到剩余各顶点最短边的权值
	VertexType *vset = new VertexType[MAXVEX]();                                  //表示顶点i是否已经并入生成树中
	
	ArcType min = 0;
	ArcType sum = 0;
	VertexType k;
	VertexType v = v0;                                                                //选取一个顶点

	for(int i=0;i<g->vn;++i){
		lowcost[i] = g->edges[v][i];                              //从选中v0开始更新lowcost数组
	}
	//******************************************************************
	//cout<<"lowcost数组为："<<endl;                        //测试
	//for(int i=0;i<g->vn;++i){
	//	cout<<lowcost[i]<<"    ";
	//}
	//system("pause");
	//*****************************************************************

	vset[v0] = 1;                                                       //顶点v0被选入生成树

	result<<"prim,最小生成树的为："<<endl;            //打印边
	result<<v<<"---->";

	for(int i=0;i<g->vn-1;++i){
		min = INF;

		for(int j=0;j<g->vn;++j){                            //从候选边中选出最小的边
			if(vset[j] == 0 && lowcost[j]<min){
				min = lowcost[j];
				k = j;
			}
		}

		result<<k<<"---->";
		vset[k] = 1;  //候选边的顶点并入生成树
		v= k;
		sum += min;

		for(int i=0;i<g->vn;++i){                                             //更新生成树到其他剩余顶点的最短距离
			if(vset[i]==0 && g->edges[v][i] < lowcost[i]){
					lowcost[i] = g->edges[v][i];
			}
		}

//******************************************************************
	//cout<<"lowcost数组为："<<endl;                        //测试
	//for(int i=0;i<g->vn;++i){
	//	cout<<lowcost[i]<<"    ";
	//}
	//system("pause");
//*****************************************************************
		
	}

	cout<<endl;
	cout<<"最小生成树的权值和为："<<sum<<endl;
	
	delete[ ] lowcost;
	delete[ ] vset;
	result.close( );
}
//*************************************************************//  kruskal算法

//定义边集数组
typedef struct edges{
	int id;
	int start;
	int end;
	double weight;
}edges;


edges road[MAXEDG];                                //定义边集数组
int *root;									              //定义并查集数组用来检测是否存在回路


int findRoot(int a) {									//查找节点的根结点,路径压缩
	while(a != root[a]){
		a = findRoot(root[a]);
	}
	return a;
}


int cmp(const void *a,const  void *b) {              //比较器
	return (((edges *)a)->weight>((edges *)b)->weight?1:-1);
}


void kruskalMGraph( ) {
	int a,b;
	int en = EN;    //  en = 21693;*/
	int vn = VN;     //vn = 21048; 
	/*int en = 8;
	int vn = 5;*/
	float sum = 0;  

	fstream result;
	fstream mydata;

	result.open("D:/My Documents/Visual Studio 2010/Projects/MST/MST/result(k).txt");
	//mydata.open("./OL.txt");
	//mydata.open("./TG.txt");
	//mydata.open("./graph.txt");              //加州
	//mydata.open("./North.txt");            
	mydata.open("./San.txt");              
	//mydata.open("./xiao.txt");

	string s;

	while(!mydata.eof( )){
		for(int i=0;i<en;i++){
			mydata>>road[i].id>>road[i].start>>road[i].end>>road[i].weight;
		}
	}    
//************************************************************************************
	//for(int i=0;i<en;++i){
	//	cout<<road[i].id<<"    "<<road[i].start<<"    "<<road[i].end<<"    "<<road[i].weight<<endl;
	//}
	//system("pause");
//*************************************************************************************

	root = new int[MAXVEX]( );
	for(int i=0;i<vn;++i){                  //初始化
		root[i] = i;
	}
	
//****************************************************************
	/*for(int i=0;i<vn;++i){
		cout<<root[i]<<endl;
	}
	system("pause");*/
//***************************************************************

	qsort(road,MAXEDG,sizeof(road[0]),cmp);             //对边集进行快排

//***************************************************************
	/*for(int i=0;i<en;++i){
		cout<<road[i].id<<"    "<<road[i].start<<"    "<<road[i].end<<"    "<<road[i].weight<<endl;
	}
	system("pause");*/
//***************************************************************

	result<<"kruskal，最小生成树为："<<endl;
	for(int i=0;i<en;++i){
		a = findRoot(road[i].start);                              //找到节点的代表
		b = findRoot(road[i].end);
		
		if(a != b) {												         //a和b属于两个集合
		
			root[b] = a;                                             //将b结点合并到a结点的集合中
			sum += road[i].weight;
			//result<<road[i].start<<"<---->"<<road[i].end<<"              ";
			/*if(i%10 == 0){
				result<<endl;
			}*/
		}
	}

	cout<<endl;
	cout<<"最小生成树的权值和为："<<sum<<endl;

	delete[ ] root;
	mydata.close( );
	result.close( );

}

