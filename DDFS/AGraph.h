#include<iostream>
#include<stack>
using namespace std;

//#define MAXSIZE 10                               //最大顶点数目 xiao

//#define MAXSIZE 9495                                  //vchocyc
//#define MAXSIZE 1595450							 //uniprot22m
//#define  MAXSIZE   16087297                      //uniprot100m
#define MAXSIZE 25037700                     //uniprot150m

//#define VN 6                                 //xiao
//#define EN  8

//#define VN 9493                          //vchocyc
//#define EN 18951

//#define VN  1595446                //uniprot22m
//#define EN   3151602

//#define VN   16087295              //uniprot100m
//#define EN   16087293  

#define VN  25037600              //uniport150m
#define EN  25037598

typedef int VertexType;	            //顶点类型可变
typedef double ArcType;

typedef struct ArcNode{             //结构体中用到ArcNode
	VertexType adjvex;
    ArcNode *nextarc;            
}ArcNode;

typedef struct {
	VertexType data;
	int instack;
	ArcNode *firstarc;
}VNode;

class AGraph {
	private:
		int vn;
		int en;

		VNode *adjlist;
		//Visited *visited;								
		int *visited;                                        //需要维护的已访问数组
		VertexType *finished;						//结束顶点标记数组
		
	public:
		int count;                                      //强连通分量个数计数器
		AGraph( );
        ~AGraph( );
		void createAGraph( );
		void createTAG(AGraph &g);       //求转置图
		void printAGraph( );
		void initalVisited( );
		void DFS(VertexType v);
		void kosaraju(VertexType v,AGraph &g2);
		
};





