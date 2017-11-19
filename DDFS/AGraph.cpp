#include"AGraph.h"
#include<iostream>
#include<fstream>
#include<string>
#include<queue>                             //BFS
#include<stack>
using namespace std;

AGraph::AGraph( ) {
	vn = 0;
	en = 0;
	count = 0;
	
	adjlist = new VNode[MAXSIZE];
	visited = new int[MAXSIZE]( );
	finished = new VertexType[MAXSIZE]( );

}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS           
	delete[ ] finished;             // kosaraju
}

void AGraph::createAGraph( ) {
	ArcNode *p= NULL;
	 VertexType start,end;
	 string s;

	 vn = VN;
	 en = EN;
	 fstream mydata;
	//mydata.open("./xiao.txt");
	//mydata.open("./vchocyc.txt");
	//mydata.open("./uniprot22m.txt");
	//mydata.open("./uniprot100m.txt");
	mydata.open("./uniprot150m.txt");

	if(vn > MAXSIZE){
		cout<<"������Ŀ������󳤶ȣ�"<<endl;
		system("pause");
		exit(-1);
	}

	for(int i=0;i<vn;++i){														//��ʼ�������

		adjlist[i].data = i;
		adjlist[i].instack = 0;
		adjlist[i].firstarc = NULL;
	}


	while(!mydata.eof( )){
		if(mydata.fail()){
			break;
		}
		for(int i=0;i<en;++i){
			mydata>>start>>end;
			p = new ArcNode;
			p->adjvex = end;

			p->nextarc = adjlist[start].firstarc;                        //ͷ��
			adjlist[start].firstarc = p;

		//for(int i=0;i<vn;++i){                                     //�ҵ��������ڶ�����е�λ��
		//	if(adjlist[i].data == end){
		//		num = i;
		//		break;
		//	}
		//}

		//p->nextarc = adjlist[num].firstarc;                 //��������ͼ�������һ����
		//adjlist[num].firstarc = p;
		}
	}
}
void AGraph::createTAG(AGraph &g) {
	ArcNode *p= NULL;
	ArcNode *q = NULL;
	 VertexType start,end;

	this->vn = g.vn;
	this->en = g.en;


	for(int i=0;i<vn;++i){                                   //��ʼ�������
	this->adjlist[i].data = g.adjlist[i].data;
	this->adjlist[i].firstarc = NULL;
	}

	for(int i=0;i<vn;++i){
		if(g.adjlist[i].firstarc != NULL){
			for(p = g.adjlist[i].firstarc;p!=NULL;p = p->nextarc){      //ȡ���ߺ�Ȩֵ
				start = p->adjvex; 
				end =  g.adjlist[i].data;
				
				q = new ArcNode;
				q->adjvex = end;
				
				q->nextarc = adjlist[start].firstarc;                        //ͷ��
				adjlist[start].firstarc = q;

			//for(int i=0;i<vn;++i){                                     //�ҵ��������ڶ�����е�λ��
			//	if(adjlist[i].data == end){
				//		num = i;
				//break;
			//	}
			//}

			//q->nextarc = adjlist[num].firstarc;                 //��������ͼ�������һ����
			//adjlist[num].firstarc = q;
			}
		}
	}

}

void AGraph::printAGraph( ) {
	cout<<"ͼ�Ĵ�ӡ���Ϊ��"<<endl;
	for(int i=0;i<vn;++i){
		if(adjlist[i].firstarc != NULL){
			for(ArcNode *p = adjlist[i].firstarc;p!=NULL;p = p->nextarc){
				cout<<"( "<<adjlist[i].data<<" , "<<p->adjvex<<" )"<<"   ";
			}
				cout<<endl;
		}
	
	}

}

void AGraph::initalVisited( ){
	for(int i=0;i<vn;++i){                             //��ʼ��visited����
			visited[i] = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;

	visited[v] = 1;					              //����ѷ���
	                                                                 //����v

	p = adjlist[v].firstarc;                            // �ҵ�v��adjlist�����е�λ��,�ҵ����ڵ���һ������

	while(p != NULL){

		if(visited[p->adjvex] == 0){              //�ҵ����ڽڵ���visited�����е�λ��,�ҵ�����δ���ʶ��㣬�ݹ�dfs
			DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
	finished[count++] = v;                      //�����һ�����������
}

void AGraph::kosaraju(VertexType v,AGraph &g2) {

	int count = 0;
	//initalVisited( );

	DFS(v);                                                              //��ȱ�����ʼ���㴫ֵ

	for(int i=0;i<vn;++i){                                    //����������ɢ��������ȱ���
		if(visited[i] == 0){
			v = i;
			DFS(v);
		}
	}

	g2.initalVisited( );

	for(int i = vn-1;i>=0;--i){										 //�ҵ����ʱ���ĵ�
		v = finished[i];

		if(g2.visited[v] ==0){							//����Ѱ��û�б������ĵ�
			g2.DFS(v);
			++count;
		}
	}
	cout<<"ǿ��ͨ�����ĸ���Ϊ��  "<<count<<endl;
}

