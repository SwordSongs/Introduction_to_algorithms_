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
	index = 0;
	cnt = 0;
	adjlist = new VNode[MAXSIZE];
	visited = new Visited[MAXSIZE];
	finished = new VertexType[MAXSIZE]( );
	DFN = new Visited[MAXSIZE];
	LOW = new Visited[MAXSIZE];
	pre = new Visited[MAXSIZE];
	sc = new Visited[MAXSIZE];
}

AGraph::~AGraph( ) {
	delete[ ] adjlist;
	delete[ ] visited;                //DFS           
	delete[ ] finished;             // kosaraju
	delete[ ] DFN;					//Tarjan
	delete[ ] LOW;
	delete[ ] pre;
	delete[ ] sc;
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
	//mydata.open("./uniport100m.txt");
	mydata.open("./uniprot150m.txt");

	if(vn > MAXSIZE){
		cout<<"������Ŀ������󳤶ȣ�"<<endl;
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
	for(int i=0;i<this->vn;++i){                             //��ʼ��visited����
		this->visited[i].data = this->adjlist[i].data;
		this->visited[i].flag = 0;
	}
}

void AGraph::initalDFN( ) {
	for(int i=0;i<vn;++i){
		DFN[i].data = adjlist[i].data;
		DFN[i].flag = 0;
	}
}

void AGraph::initalLOW( ) {
	for(int i=0;i<vn;++i){
		LOW[i].data = adjlist[i].data;
		LOW[i].flag = 0;
	}
}

void AGraph::DFS( VertexType v) {
	ArcNode *p = NULL;
	//int num;

	visited[v].flag = 1;					              //����ѷ���
	//cout<<v<<"    ";                                 //����v

	p = adjlist[v].firstarc;                            // �ҵ�v��adjlist�����е�λ��,�ҵ����ڵ���һ������

	while(p != NULL){

		if(visited[p->adjvex].flag == 0){              //�ҵ����ڽڵ���visited�����е�λ��,�ҵ�����δ���ʶ��㣬�ݹ�dfs
			DFS(p->adjvex);             
		}
		p = p->nextarc;
	}
	finished[count++] = v;                      //�����һ�����������
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

void AGraph::kosaraju(VertexType v,AGraph &g2) {
//	int num;
	int count = 0;
	initalVisited( );
	//cout<<"ͼ��������������������Ϊ��"<<endl;

	DFS(v);                                                        //��ȱ�����ʼ���㴫ֵ

	for(int i=0;i<vn;++i){                                    //����������ɢ��������ȱ���
		if(visited[i].flag == 0){
			v = visited[i].data;
			DFS(v);
		}
	}

	g2.initalVisited( );
	//cout<<endl;
	//cout<<"ת��ͼ�����������������ǿ��ͨ����Ϊ��"<<endl;
//**********************************************************************
	/*for(int i=0;i<vn;++i){
		cout<<finished[i]<<"    ";
	}
	system("pause");*/
//**********************************************************************

	for(int i = vn-1;i>=0;--i){										 //�ҵ����ʱ���ĵ�
		v = finished[i];

		if(g2.visited[v].flag==0){							//����Ѱ��û�б������ĵ�
			g2.DFS(v);
			//cout<<endl;
			++count;
		}
	}
	cout<<"ǿ��ͨ�����ĸ���Ϊ��  "<<count<<endl;
}

void AGraph::Tarjan(VertexType v,stack<int> &s) {

	VertexType j;
	//int nv;
	//int nj;
	ArcNode *p = NULL;

	//for(int i=0;i<vn;++i){
	//	if(DFN[i].data == v){
	//		nv = i;
	//		break;
	//	}
	//}
	DFN[v].flag = ++index;
	LOW[v].flag = DFN[v].flag;

	s.push(v);
	adjlist[v].instack = 1;

	p = adjlist[v].firstarc;																				//�ҵ����ڵ���һ������
		while(p != NULL){
					j = p->adjvex;																				//jָ����߶���

					//for(int i=0;i<vn;++i){																		//��nj
					//		if(j == LOW[i].data){
					//			nj = i;
					//			break;
					//		}	
					//	}
				
				if(DFN[j].flag == 0){																							                                   //δ����
						Tarjan(j,s);																									                                  //�ݹ�
						LOW[v].flag = LOW[v].flag < LOW[j].flag ? LOW[v].flag : LOW[j].flag;                              //����Сֵ
				}

				else
					if(adjlist[j].instack == 1) {																					//�ж϶���v�Ƿ���ջ��

						LOW[v].flag = LOW[v].flag > DFN[j].flag ? DFN[j].flag : LOW[v].flag;  //����Сֵ
					}	

					p = p->nextarc;
		}


	if(DFN[v].flag == LOW[v].flag){

		do{                                                      //ǿ��ͨ������ջ
				if(s.empty( ) == false){

					//for(int i=0;i<vn;++i){																		//��nj
					//			if(j == adjlist[i].data){
					//				nj = i;
					//				break;
					//			}	
					//		}
					j = s.top( );
					adjlist[j].instack = 0;
					//cout<<s.top( )<<"    ";
					s.pop( );
				}
		}
		while(v != j);
		++count;
		//cout<<endl;
	}
}

void AGraph::Gabow(VertexType v,stack<VertexType> &path,stack<VertexType> &root) {
	for(int i=0;i<vn;++i){                                    //��ʼ��pre
		pre[i].data = adjlist[i].data;
		pre[i].flag = -1;
	}

	for(int i=0;i<vn;++i){                                //��ʼ��sc
		sc[i].data = adjlist[i].data;
		sc[i].flag = -1;
	}

	GabowDFS(v,path,root);

	for(int i=0;i<vn;++i){
		if(pre[i].flag == -1){
			GabowDFS(i,path,root);
		}
	}

}

void AGraph::GabowDFS(VertexType v,stack<VertexType> &path,stack<VertexType> &root) {
	ArcNode *p = NULL;
	VertexType w;
	int vnum,wnum;
	int num;

	path.push(v);                                  //��������ջ
	root.push(v);

	//for(int i=0;i<vn;++i){                     //�ҵ�����v�����
	//	if(adjlist[i].data == v){
	//		vnum = i;
	//		break;
	//	}
	//}

	pre[v].flag = ++cnt;                    //�Զ��������˳����

	for(p = adjlist[v].firstarc;p!=NULL;p = p->nextarc){                //pre �� adjlist����һ��
		w = p->adjvex;
		//for(int i=0;i<vn;++i){                                                              //�ҵ�����w�����
		//	if(adjlist[i].data == w){
		//		wnum = i;
		//		break;
		//	}
		//}

		if(pre[w].flag == -1)
			GabowDFS(w,path,root);                                                 //wû�з��ʣ��ݹ�ȥ����w
		else
			if(sc[w].flag == -1){                                                         //����w�����ʹ������������ĸ�ǿ��ͨ������δȷ��
				//for(int i=0;i<vn;++i){
				//	if(root.top( ) == adjlist[i].data){
				//		num = i;
				//		break;
				//	}
				//}

				while(pre[root.top( )].flag>pre[w].flag){
					 root.pop( );
					//for(int i=0;i<vn;++i){                                       //�ҵ�root���µ�ջ��Ԫ�ص����
					//	if(root.top( ) == adjlist[i].data){
					//		num = i;
					//		break;
					//	}	
					//}
				}

			}
	
	}

	if(root.top( ) == v){                                               //�ҵ�ǿ��ͨ�����ĸ�
		if(root.empty( ) == false)
			root.pop( );
		do{
			if(path.empty( ) == false){
				w = path.top( );                                     //��pathջ��ջ
				//for(int i=0;i<vn;++i){
				//	if(w == adjlist[i].data){
				//		wnum = i;
				//		break;
				//	}
				//}
				sc[w].flag = count;
				//cout<<w<<"    ";
				path.pop( );
			}
		}
		while(v != w);
		++count;                                                  //ǿ��ͨ��������
		//cout<<endl;
	}
}
