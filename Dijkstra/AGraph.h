#include<iostream>
#include<stack>
using namespace std;

#define MAXSIZE  174956                 //最大顶点数目

//#define VN 6105                           //OL
//#define EN 7035

//#define VN 18263                            //TG
//#define EN 23874

//#define VN 21048                            //加州
//#define EN 21693

//#define VN 175813                            //North
//#define EN 179179

#define VN 174956                            //San
#define EN 223001




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

