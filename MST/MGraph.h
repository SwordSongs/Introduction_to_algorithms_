#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
using namespace std;

#define INF 1000000
#define MAXEDG  223001                //��³˹�����㷨��

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
#define MAXVEX  223001                 //��󶥵���
//#define MAXVEX  10
typedef int VertexType;					//��������
typedef float ArcType;                      //����Ȩֵ����

typedef struct MGraph{
	VertexType *vex;
	ArcType **edges;
	int vn;                                              //������Ŀ
	int en;                                              //�ߵ���Ŀ
}MGraph;

void createMGraph(MGraph *g) {

	g->vex = new int[MAXVEX]( );          //��ʼ��
//*******************************************************************************
	/*for(int i=0;i<MAXVEX;++i){              //����
		cout<<g->vex[i]<<endl;
	}
	system("pause");*/
//*******************************************************************************

	g->edges = new ArcType* [MAXVEX]( );
	for(int i=0;i<MAXVEX;++i){
		g->edges[i] = new ArcType[MAXVEX]( );
	}
	//**************************************************************************
	//for(int i=0;i<MAXVEX;++i){             //����
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

	//cout<<"�����붥����Ŀvn�ͱߵ���Ŀen(ʹ�ÿո�ָ�) : "<<endl;
	//g->vn = 21048;                             //������Ŀ
	//g->en = 21693;                             //�ߵ���Ŀ
	g->vn = 5;                             //������Ŀ
	g->en = 8;                             //�ߵ���Ŀ


	//cout<<"�����붥�����Ϣ(ʹ�ÿո�ָ�)"<<endl;
	for(int i=0;i<g->vn;++i){                              //¼�붥����Ϣ
		g->vex[i] = i;
	}
//**************************************************************************
	/*for(int i=0;i<g->vn;++i){
		cout<<g->vex[i]<<"   ";                        //����
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
				g->edges[m][n] = w;            //��Ȩֵ
				g->edges[n][m] = w;
		}

	}
	mydata.close( );

	//for(int j=0;j<g->en;++j){
	//	cout<<"������ߣ�vi��vj���Ķ���ͱ��ϵ�Ȩ��(�ÿո�ָ�)��"<<endl;
	//	cin>>start>>end>>w;
	//	for(int i=0;i<g->vn;++i){        //�Ӷ���������ȡ���±꣨���㲻�ظ���
	//		if(g->vex[i] == start){
	//			m = i;
	//		}
	//		if(g->vex[i] == end){
	//			n = i;
	//		}
	//	}

	//	g->edges[m][n] = w;            //��Ȩֵ
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
	cout<<"������ϢΪ��"<<endl;
	for(int i=0;i<g->vn;++i){
		cout<<g->vex[i]<<"       ";             //��ӡ������Ϣ
	}
//***************************************
	/*system("pause");*/
//**************************************
	cout<<endl;
	cout<<"�ߵ���ϢΪ��"<<endl;                  //��ӡ�ߵ���Ϣ
	for(int i=0;i<g->vn;++i){
		for(int j=0;j<g->vn;++j){
			cout<<g->edges[i][j]<<"       ";
		}
		cout<<endl<<endl<<endl<<endl;
	}

}

//***************************************************************//                prim�㷨

void primMGraph(MGraph *g,VertexType v0) {
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/MST/MST/result(p).txt");
	ArcType *lowcost = new ArcType[MAXVEX]();                           //��������ʣ���������̱ߵ�Ȩֵ
	VertexType *vset = new VertexType[MAXVEX]();                                  //��ʾ����i�Ƿ��Ѿ�������������
	
	ArcType min = 0;
	ArcType sum = 0;
	VertexType k;
	VertexType v = v0;                                                                //ѡȡһ������

	for(int i=0;i<g->vn;++i){
		lowcost[i] = g->edges[v][i];                              //��ѡ��v0��ʼ����lowcost����
	}
	//******************************************************************
	//cout<<"lowcost����Ϊ��"<<endl;                        //����
	//for(int i=0;i<g->vn;++i){
	//	cout<<lowcost[i]<<"    ";
	//}
	//system("pause");
	//*****************************************************************

	vset[v0] = 1;                                                       //����v0��ѡ��������

	result<<"prim,��С��������Ϊ��"<<endl;            //��ӡ��
	result<<v<<"---->";

	for(int i=0;i<g->vn-1;++i){
		min = INF;

		for(int j=0;j<g->vn;++j){                            //�Ӻ�ѡ����ѡ����С�ı�
			if(vset[j] == 0 && lowcost[j]<min){
				min = lowcost[j];
				k = j;
			}
		}

		result<<k<<"---->";
		vset[k] = 1;  //��ѡ�ߵĶ��㲢��������
		v= k;
		sum += min;

		for(int i=0;i<g->vn;++i){                                             //����������������ʣ�ඥ�����̾���
			if(vset[i]==0 && g->edges[v][i] < lowcost[i]){
					lowcost[i] = g->edges[v][i];
			}
		}

//******************************************************************
	//cout<<"lowcost����Ϊ��"<<endl;                        //����
	//for(int i=0;i<g->vn;++i){
	//	cout<<lowcost[i]<<"    ";
	//}
	//system("pause");
//*****************************************************************
		
	}

	cout<<endl;
	cout<<"��С��������Ȩֵ��Ϊ��"<<sum<<endl;
	
	delete[ ] lowcost;
	delete[ ] vset;
	result.close( );
}
//*************************************************************//  kruskal�㷨

//����߼�����
typedef struct edges{
	int id;
	int start;
	int end;
	double weight;
}edges;


edges road[MAXEDG];                                //����߼�����
int *root;									              //���岢�鼯������������Ƿ���ڻ�·


int findRoot(int a) {									//���ҽڵ�ĸ����,·��ѹ��
	while(a != root[a]){
		a = findRoot(root[a]);
	}
	return a;
}


int cmp(const void *a,const  void *b) {              //�Ƚ���
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
	//mydata.open("./graph.txt");              //����
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
	for(int i=0;i<vn;++i){                  //��ʼ��
		root[i] = i;
	}
	
//****************************************************************
	/*for(int i=0;i<vn;++i){
		cout<<root[i]<<endl;
	}
	system("pause");*/
//***************************************************************

	qsort(road,MAXEDG,sizeof(road[0]),cmp);             //�Ա߼����п���

//***************************************************************
	/*for(int i=0;i<en;++i){
		cout<<road[i].id<<"    "<<road[i].start<<"    "<<road[i].end<<"    "<<road[i].weight<<endl;
	}
	system("pause");*/
//***************************************************************

	result<<"kruskal����С������Ϊ��"<<endl;
	for(int i=0;i<en;++i){
		a = findRoot(road[i].start);                              //�ҵ��ڵ�Ĵ���
		b = findRoot(road[i].end);
		
		if(a != b) {												         //a��b������������
		
			root[b] = a;                                             //��b���ϲ���a���ļ�����
			sum += road[i].weight;
			//result<<road[i].start<<"<---->"<<road[i].end<<"              ";
			/*if(i%10 == 0){
				result<<endl;
			}*/
		}
	}

	cout<<endl;
	cout<<"��С��������Ȩֵ��Ϊ��"<<sum<<endl;

	delete[ ] root;
	mydata.close( );
	result.close( );

}

