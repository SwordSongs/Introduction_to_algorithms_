#include<iostream>
#include<stack>
using namespace std;

//#define MAXSIZE 6105                    //��󶥵���Ŀ
#define MAXSIZE 10

typedef int VertexType;	            //�������Ϳɱ�
typedef float ArcType;

typedef struct ArcNode{             //�ṹ�����õ�ArcNode
	int id;
	VertexType adjvex;
	ArcType weight;
    ArcNode *nextarc;            
}ArcNode;

typedef struct {
	VertexType data;
	ArcNode *firstarc;
}VNode;

typedef struct {                      //���������������
	VertexType data;
	int flag;
}Visited;

class AGraph {
	private:
		int vn;
		int en;

		VNode *adjlist;
		Visited *visited;								//��Ҫά�����ѷ�������
		ArcType  *dist;
		VertexType  *path;
		int   *set;
		
	public:
		AGraph( );
        ~AGraph( );
		void createAGraph( );
		void createTAG(AGraph &g);       //��ת��ͼ
		void printAGraph( );
		void initalVisited( );
		void DFS(VertexType v);
		void BFS(VertexType v);
		void Dijkstra(VertexType v);
};

