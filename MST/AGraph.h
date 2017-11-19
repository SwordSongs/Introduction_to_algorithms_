#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define INF 1000000
//#define MAXVEX 10                     //��󶥵���
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






typedef int VertexType;					//��������
typedef double ArcType;              //����Ȩֵ����

typedef struct ArcNode{
	int adjvex;                         //�ñ���ָ��Ľ��λ��
	ArcType weight;                //�洢Ȩֵ
	struct ArcNode *nextarc;         //ָ����һ���ߵ�ָ��
}ArcNode;

typedef struct VNode{
	VertexType data;               //������Ϣ
	ArcNode *firstarc;              //ָ���һ���ߵ�ָ��
}VNode;

typedef struct AGraph{
	VNode adjlist[MAXVEX];         //�����
	int vn;                                     //������Ŀ
	int en;                                     //�ߵ���Ŀ
}AGraph;

void createAGraph(AGraph *g) {
	
	int i,j,k,id;
	ArcType w;
	ArcNode *p;
	
	/*g->vn = 5;
	g->en = 8;*/

	g->vn = VN;                       //������Ŀ
	g->en = EN;                      //�ߵ���Ŀ
	
	for(i=0;i<g->vn;++i){                         //��ʼ��
		g->adjlist[i].data = i;
		g->adjlist[i].firstarc = NULL;           //���߱��ÿ�
	}

	fstream mydata;
	//mydata.open("./xiao.txt");
	//mydata.open("./OL.txt");
	//mydata.open("./TG.txt");
	//mydata.open("./graph.txt");                 //����
	//mydata.open("./North.txt");  
	mydata.open("./San.txt");  
	string s;
	while(!mydata.eof( )){
		
		for(k=0;k<g->en;++k){              //�����߱�
		
			mydata>>id>>i>>j>>w;                   //

			p = new ArcNode;
			p->adjvex = j;                                           //�ڽ�Ϊj
			p->weight = w;                                        //Ȩ��
			p->nextarc = g->adjlist[i].firstarc;             //��pָ��ǰ�����firstarc
			g->adjlist[i].firstarc = p;                           //����ǰ�����firstarcָ���node
	    
			p = new ArcNode;
			p->adjvex = i;                                            //�ڽ�Ϊi
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


//****************************************************************//����ķ�㷨
void primAGraph(AGraph *g,int v0) {

	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/MST/MST/result(p).txt");

	ArcType *lowcost = new ArcType[MAXVEX];                                       //��������ʣ���������̱ߵ�Ȩֵ
	VertexType *vset = new VertexType[MAXVEX]( );                                  //��ʾ����i�Ƿ��Ѿ�������������                                                          
	ArcNode *p;

	ArcType min = 0;
	ArcType sum = 0;

	VertexType k;
	VertexType v = v0;                                          //ѡȡһ������

	for(int i=0;i<MAXVEX;++i){                            //lowcost��ʼ��
		lowcost[i] = INF;
	}
	
	p = g->adjlist[v].firstarc;                    //��ѡ��v0��ʼ����lowcost����
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

	                                                      
	vset[v0] = 1;                                         //����v0��ѡ��������
	//result<<"prim,��С��������Ϊ��"<<endl;            //��ӡ��
	//result<<v<<"---->";

	for(int i=0;i<g->vn-1;++i){
		min = INF;

		for(int j=0;j<g->vn;++j){                            //�Ӻ�ѡ����ѡ����С�ı�
			if(vset[j] == 0 && lowcost[j]<min){
				min = lowcost[j];
				k = j;
			}
		}

		//result<<k<<"---->";
		vset[k] = 1;                                                                    //��ѡ�ߵĶ��㲢��������
		v= k;
		sum += min;

		  p = g->adjlist[v].firstarc;                                             //����������������ʣ�ඥ�����̾���
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
	cout<<"��С��������Ȩֵ��Ϊ��"<<sum<<endl;
	
	delete[ ] lowcost;
	delete[ ] vset;
	result.close( );
}