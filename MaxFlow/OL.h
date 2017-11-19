#include<iostream>
using namespace std;

//#define VN 5                                         //xiao
//#define EN 7

#define VN         5001                              //MF6
#define EN          15237

//#define VN            1001                          //MF3
//#define EN             30899

//#define VN            1001                          //MF2
//#define EN             202858

//#define VN            1001                         //MF4
//#define EN           30843

//#define VN        6                               //MF1
//#define EN        9

//#define VN       2001                        //MF5
//#define EN        13920

typedef int VertexType;                //��������
 struct VNode;

typedef struct ArcNode {
	VertexType tailvex,headvex;
	double cap;                                         //�ߵ�����
	double flow;                                       //�ߵ�����
	ArcNode *hlink,* tlink;
	VNode *ivex,*jvex;                            //�߱���ָ�򶥵��ָ��
	ArcNode( ){
		tailvex = 0;
		headvex = 0;
		cap = 0.0;
		flow = 0.0;
		hlink = NULL;
		tlink = NULL;
		ivex = NULL;
		jvex =NULL;
	}
}ArcNode;

typedef struct VNode {
	VertexType data;
	int high;                                           //����߶�
	double exflow;                                //���㳬����
	ArcNode *firstin,*firstout;               //��߱���ص�ָ��
	ArcNode *current;
	VNode *next;                                //��������ָ����һ��Ԫ��ָ��
	VNode( ){
		data = 0;
		high = 0;
		exflow = 0.0;
		firstin = NULL;
		firstout = NULL;
		current = NULL;                    
		next = NULL;
	}
}VNode;

class OLGraph {
	private :
		int vn,en;
		int flag;
		int flag1;
		
	public:
		VNode* head;
		OLGraph( );
		~OLGraph( );
		void createOLGraph( );
		void printOLGraph( );
		void discharge(VNode *&u);
		void relable(VNode *&u);
		bool judge1(VNode *&u,ArcNode *&v);
		bool judge2(VNode *&u,ArcNode *&v);
		void relabel_to_front( );
};