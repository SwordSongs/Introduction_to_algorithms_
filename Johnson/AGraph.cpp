#include"AGraph.h"
#include<iomanip>
#include<iostream>
#include<fstream>
#include<queue>                        //BFS
#include<stack>
using namespace std;

#define INF  1000000.0                   //��ʾ���ɴ�

AGraph::AGraph( ) {
	vn = 0;
	en = 0;
	i1 = 0;
	
	adjlist = new VNode[MAXSIZE];
	visited = new Visited[MAXSIZE];
	  dist   =  new ArcType[MAXSIZE];
	path = new VertexType[MAXSIZE];
	set   =  new int[MAXSIZE]( );
	h = new ArcType[MAXSIZE];
}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS       
	delete[ ] dist;
	delete[ ] path;
	delete[ ] set;
	delete[ ] h;
}

void AGraph::createAGraph( ) {
	ArcNode *p= NULL;
	 VertexType start,end;
	 int id;
	 ArcType weight;
	 int num;


	 vn = VN;
	 en = EN;
	 en = en + vn;                                //���ӱ����붥����Ŀ,14����
	 vn = vn + 1;                                  //6������


	/*cout<<"�����붥�����Ŀ��"<<endl;
	cin>>vn;*/

	 fstream mydata;
	 mydata.open("./OL.txt");
	 //mydata.open("./xiao.txt");

	if(vn > MAXSIZE){
		cout<<"������Ŀ������󳤶ȣ�"<<endl;
		exit(-1);
	}
	/*cout<<"������ߵ���Ŀ��"<<endl;
	cin>>en;*/

	//cout<<"�����붥�����Ϣ�����ո�ָ���"<<endl;
	for(int i=0;i<vn;++i){														//��ʼ�������
		adjlist[i].data = i;
		adjlist[i].firstarc = NULL;
	}


	//cout<<"������ߵ���Ϣ(strat end weight)��"<<endl;
	while(!mydata.eof( )){
		
		for(int i=0;i<EN;++i){
			mydata>>id>>start>>end>>weight;
			p = new ArcNode;
			p->id = id;
			p->adjvex = end;
			p->weight = weight;

			for(int i=0;i<vn;++i){                                     //�ҵ���ʼ���ڶ�����е�λ��
				if(adjlist[i].data == start){
					num = i;
					break;
				}	
			}
				p->nextarc = adjlist[num].firstarc;                        //ͷ��
				adjlist[num].firstarc = p;

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
	int j = 0;
	for(int i=0;i<vn-1;++i){                                                       //��������������ʣ��ߵ���Ϣ
					p = new ArcNode;
					p->id = 0;
					p->adjvex =j++;
					p->weight = 0.0;
					p->nextarc = adjlist[vn-1].firstarc;
					adjlist[vn-1].firstarc = p;
	}
	mydata.close( );
}

void AGraph::createTAG(AGraph &g) {
	ArcNode *p= NULL;
	ArcNode *q = NULL;
	 VertexType start,end;
	 ArcType weight;
	 int num;

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
				weight = p->weight;
	
				q = new ArcNode;
				q->adjvex = end;
				q->weight = weight;

				for(int j=0;j<vn;++j){                                     //�ҵ���ʼ���ڶ�����е�λ��
					if(this->adjlist[j].data == start){
						num = j;
						break;
					}
				}

				q->nextarc = adjlist[num].firstarc;                        //ͷ��
				adjlist[num].firstarc = q;

			//for(int i=0;i<vn;++i){                                     //�ҵ��������ڶ�����е�λ��
			//	if(adjlist[i].data == end){
				//		num = i;
		//			break;
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
				cout<<"( "<<adjlist[i].data<<" , "<<p->adjvex<<" , "<<p->weight<<" )"<<"   ";
			}
				cout<<endl;
		}
	
	}

}

void AGraph::initalVisited( ){
	for(int i=0;i<this->vn;++i){                             //��ʼ��visited����
		this->visited[i].data = this->adjlist[i].data;
		this->visited[i].flag = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;
	int num;
	for(int i=0;i<vn;++i){                      //�ҵ�v��visited�����е�λ��
		if(visited[i].data == v){
			num = i;
			break;
		}
	}

	visited[num].flag = 1;              //����ѷ���
	cout<<v<<"    ";                    //����v

	for(int i=0;i<vn;++i){              //�ҵ�v��adjlist�����е�λ��
		if(adjlist[i].data == v){
			num = i;
			break;
		}
	}

	p = adjlist[num].firstarc; //�ҵ����ڵ���һ������

	while(p != NULL){
		for(int i=0;i<vn;++i){                   //�ҵ����ڽڵ���visited�����е�λ��
			if(p-> adjvex == visited[i].data){
				num = i;
				break;
			}
		}

		if(visited[num].flag == 0){              //�ҵ�����δ���ʶ��㣬�ݹ�dfs
			(*this).DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
}

void AGraph::BFS(VertexType v) {
	ArcNode *p = NULL;
	queue<char> q;
	int num;
	char c;

	for(int i=0;i<vn;++i){                      //�ҵ�v��visited�����е�λ��
		if(visited[i].data == v){
			num = i;
			break;
		}
	}

	this->visited[num].flag = 1;              //����ѷ���
	cout<<v<<"    ";                    //����v

	q.push(v);                              //v����

	while(!q.empty()){
		c = q.front( );                          //���ض���Ԫ��
		q.pop( );                                //�������

		for(int i=0;i<vn;++i){
			if(c == adjlist[i].data){
				num = i;
				break;
			}
		}

		p = adjlist[num].firstarc;                      //pָ�����ڶ���

		while(p != NULL){

			for(int i=0;i<vn;++i){                   //�ҵ����ڽڵ���visited�����е�λ��
				if(p-> adjvex == visited[i].data){
					num = i;
					break;
				}
			}

			if(visited[num].flag == 0){
				cout<<p->adjvex<<"    ";
				visited[num].flag = 1;                //����ѷ���
				q.push(p->adjvex);                             //���������
			}
			p = p->nextarc;
		}
	}
}

void AGraph::Dijkstra(VertexType v) {

	ArcNode *p = NULL;
	int num;
	ArcType w = INF;                            //��¼Ȩֵ
	ArcType min;
	

	for(int i=0;i<vn;++i){                      //��ʼ��dist
		if(i == v)
			dist[i] = 0.0;
		else
			dist[i] = INF;
		path[i] = -1;                              //��ʼ��path
	}
	
	if(adjlist[v].firstarc != NULL){                   
			for(p = adjlist[v].firstarc;p!=NULL;p= p->nextarc){
				dist[p->adjvex] = p->weight;   
				if(p->weight < INF)
					path[p->adjvex] = v;
			}
	}
	
	set[v] = 1;                                              //��ʼ��set

	                                                             //����������ɳ�ʼ��
//***********************************************************
	/*for(int i=0;i<vn;++i){
		cout<<dist[i]<<"      ";
	}
	cout<<endl;
	for(int i=0;i<vn;++i){
		cout<<path[i]<<"     ";
	}
	cout<<endl;
	for(int i=0;i<vn;++i){
		cout<<set[i]<<"      ";
	}
	cout<<endl;
	system("pause");*/
//***********************************************************

	for(int i=0;i<vn;++i){
		 min = INF;
		for(int j=0;j<vn;++j){                         
			if(set[j] == 0 && dist[j] < min){
				num = j;
				min = dist[j];
			}
		} 
		set[num] = 1;                                  //ѡ��dist����С���Ǹ�����j,����1

//		for(int k=0;k<vn;++k){                   //ɨ��δѡ�ж��㣬����ѡ�ж�����δѡ�е����·��
//			if(set[k] == 0){
//				for(p = adjlist[num].firstarc;p!=NULL;p=p->nextarc){
//					if(p->adjvex == k)
//						w = p->weight;             //��num��k��һ���ߣ���¼wֵ
//				}
//				
//				if(dist[k] > dist[num]+w){
//					dist[k] = dist[num]+w;
//					path[k] = num;
//				}
//				w = INF;                             //����w�󣬽�w�ָ�INF
//			}
////*********************************************
//		/*for(int i=0;i<vn;++i){
//			if(dist[i] > 1000000.0)
//				cout<<"( "<<v<<" , "<<i<<" , "<<"��"<<" ) "<<endl;
//			else
//				cout<<"( "<<v<<" , "<<i<<" , "<<dist[i]<<" ) "<<endl;
//		}
//		cout<<endl;*/
////*********************************************
//		}

		for(p = adjlist[num].firstarc;p;p=p->nextarc){
			if(set[p->adjvex]==0 && float(dist[num]+p->weight)<dist[p->adjvex]){
				dist[p->adjvex] = dist[num] + p->weight;
				path[p->adjvex] = num;
			}
		}

	}
//**********************************************************************
	/*for(int i=0;i<vn;++i){
				cout<<dist[i]<<"      ";
			}
	system("pause");*/
//************************************************************************
			for(int i=0;i<vn;++i){                //�ع����
					dist[i] = dist[i] + h[i] - h[v];
			}


		for(int j=0;j<vn-1;++j){
			D[i1][j] = dist[j];
		}
		++i1;
	

	//result<<"��Դ����Ϊ��    "<<v<<endl;
	//result<<"�Ͻ�˹�����㷨����Դ���·��Ϊ��"<<endl;

	for(int i=0;i<vn;++i){                                                //Ϊ��һ�εϽ�˹�����ָ�set����
		set[i] = 0;
	}

}

bool AGraph::BellmanFord(VertexType v) {
	fstream result;
	result.open("D:/�ҵ����Ͽ�/Documents/Visual Studio 2010/Projects/Johnson/Johnson/result.txt");
	bool flag = true;
	ArcNode *p = NULL;

	for(int i=0;i<vn;++i){                      //��ʼ��dist
		if(i == v)
			dist[i] = 0.0;
		else
			dist[i] = INF;
	}
//***************************************
	/*for(int i=0;i<vn;++i){
		cout<<dist[i]<<"    ";
	}
	system("pause");*/
//***************************************
	for(int i=1;i<vn;++i){                                                                 //��Դ�㵽���������ɳ�v-1��
		for(int i=0;i<vn;++i){ 
				for(p=adjlist[i].firstarc;p;p=p->nextarc){                       
					if(dist[p->adjvex] > dist[i] + p->weight){                  //�ɳڲ���
						dist[p->adjvex] = dist[i] + p->weight;
					}
				}
		}
	}
//***************************************
	/*for(int i=0;i<vn;++i){
		cout<<dist[i]<<"    ";
	}
	system("pause");*/
//***************************************

	for(int i=0;i<vn;++i){
		for(p=adjlist[i].firstarc;p;p=p->nextarc){
			if(dist[p->adjvex] > float(dist[i] + p->weight)){              //ע��floatǿ������ת���������ת����������������룬�����жϸ�Ȩ��·
				flag = false;
			}
		}
	}

	/*cout<<"flag = "<<flag<<endl;
	system("pause");*/
	
	if(flag){
		/*result<<"��Դ����Ϊ��    "<<v<<endl;
		result<<"BellmanFord�㷨����Դ���·��Ϊ��"<<endl;

		for(int i=0;i<vn;++i){
			if(dist[i] >= 1000000.0)
				result<<"( "<<v<<" , "<<i<<" , "<<"��"<<" ) "<<endl;
			else
				result<<"( "<<v<<" , "<<i<<" , "<<dist[i]<<" ) "<<endl;
		}	*/
	}
	result.close( );
	return flag;
}

void AGraph::Johnson( ) {
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/Johnson/Johnson/result.txt");
	ArcNode *p = NULL;

	D = new ArcType*[MAXSIZE];
	for(int i=0;i<MAXSIZE;++i){               //����Dist��ά����
		D[i] = new ArcType[MAXSIZE];
	}

	if(BellmanFord(0) == false){
		cout<<"ͼ�д��ڸ�Ȩ��·��"<<endl;
	}
	else{
		BellmanFord(vn-1);                                 //����s��ÿ����������·��

		for(int i=0;i<vn;++i){
		h[i]  = dist[i];
		}
//******************************************************
		/*for(int i=0;i<vn;++i){
			cout<<h[i]<<"      ";
		}
		system("pause");*/
//******************************************************


		for(int i=0;i<vn;++i){
			for(p=adjlist[i].firstarc;p;p=p->nextarc){                     //����Ȩֵ
				p->weight = p->weight+h[i]-h[p->adjvex];
			}
		}
//****************************************************
		//for(int i=0;i<vn;++i){
		//	for(p=adjlist[i].firstarc;p;p=p->nextarc){                     //����Ȩֵ
		//		cout<<p->weight<<"       ";
		//	}
		//	cout<<endl;
		//}
		//system("pause");
//***************************************************


		for(int i=0;i<vn-1;++i){                                                   //��������������õؽ�˹����
			Dijkstra(i);
		}
	}
	result<<"Johnson�㷨�������̽��Եľ���Ϊ��"<<endl;
	//for(int i=0;i<vn-1;++i){
	//	for(int j=0;j<vn-1;++j){
	//		if(D[i][j] >= 1000000.0)
	//			result<<"( "<<i<<" , "<<j<<" , "<<"��"<<" ) ";
	//		else
	//			result<<"( "<<i<<" , "<<j<<" , "<<D[i][j]<<" ) ";
	//	}
	//	result<<endl;
	//}
	result.close( );

	for(int i=0;i<MAXSIZE;++i){               //����Dist��ά����
			delete[ ] D[i];
	}
	delete[ ] D;
}


