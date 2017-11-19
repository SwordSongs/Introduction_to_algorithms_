#include<iostream>
#include<stack>
using namespace std;

//#define MAXSIZE 6105                    //最大顶点数目
#define MAXSIZE 10

typedef int VertexType;	            //顶点类型可变
typedef float ArcType;

typedef struct ArcNode{             //结构体中用到ArcNode
	int id;
	VertexType adjvex;
	ArcType weight;
    ArcNode *nextarc;            
}ArcNode;

typedef struct {
	VertexType data;
	ArcNode *firstarc;
}VNode;

typedef struct {                      //定义访问数组类型
	VertexType data;
	int flag;
}Visited;

class AGraph {
	private:
		int vn;
		int en;

		VNode *adjlist;
		Visited *visited;								//需要维护的已访问数组
		ArcType  *dist;
		VertexType  *path;
		int   *set;
		
	public:
		AGraph( );
        ~AGraph( );
		void createAGraph( );
		void createTAG(AGraph &g);       //求转置图
		void printAGraph( );
		void initalVisited( );
		void DFS(VertexType v);
		void BFS(VertexType v);
		void Dijkstra(VertexType v);
};

