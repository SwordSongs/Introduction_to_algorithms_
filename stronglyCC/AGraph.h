#include<iostream>
#include<stack>
using namespace std;

//#define MAXSIZE 10                               //��󶥵���Ŀ xiao

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

typedef int VertexType;	            //�������Ϳɱ�
typedef double ArcType;

typedef struct ArcNode{             //�ṹ�����õ�ArcNode
	int id;
	VertexType adjvex;
    ArcNode *nextarc;            
}ArcNode;

typedef struct {
	VertexType data;
	int instack;
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
		int index;										  //Tarjan
		int cnt;                                           //Gabow

		VNode *adjlist;
		Visited *visited;								//��Ҫά�����ѷ�������
		VertexType *finished;						//��������������
		Visited *LOW;									 //�����ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
		Visited *pre;                                        //GabowDFS
		Visited *sc;                                           //�ж��Ƿ�����һ��ǿ��ͨ����
		
	public:
		Visited *DFN;									 //�������������ʱ���
		int count;                                      //ǿ��ͨ��������������
		AGraph( );
        ~AGraph( );
		void createAGraph( );
		void createTAG(AGraph &g);       //��ת��ͼ
		void printAGraph( );
		void initalVisited( );
		void initalDFN( );
		void initalLOW( );
		void DFS(VertexType v);
		void BFS(VertexType v);
		void kosaraju(VertexType v,AGraph &g2);
		void Tarjan(VertexType v,stack<VertexType> &s);
		void Gabow(VertexType v,stack<VertexType> &path,stack<VertexType> &root);
		void GabowDFS(VertexType v,stack<VertexType> &path,stack<VertexType> &root);
};





