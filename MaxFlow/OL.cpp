#include"OL.h"
#include<fstream>

OLGraph::OLGraph( ) {						//�������������������
	vn = VN;
	en = EN;
	flag = 0;
	flag1 = 0;
	VNode *p = NULL;
	VNode *last = NULL;

	p = new VNode;
	head = p;
	last = p;
	for(int i=1;i<=vn-1;++i){
		p = new VNode;
		p->data = i;
		last->next = p;
		last = p;
	}
	head->high = vn;                    //Դ��ĸ߶�Ϊvn
}

OLGraph::~OLGraph( ) {

}

void OLGraph::createOLGraph( ){
	fstream mydata;
	//mydata.open("./xiao.txt");
	mydata.open("./MF6.txt");
	VertexType start,end;
	double c;
	ArcNode *p;
	VNode *q;
	while(!mydata.eof( )){
			mydata>>start>>end>>c;
			p = new ArcNode;
			p->tailvex = start;
			p->headvex = end;
			p->cap = c;
			if(mydata.fail( )){                                                     //����ո�
				break;
			}
			for(q = head;q->data != start;q = q->next);          //����ʮ������
				if(q->data == start){
					p->ivex = q;                                                       //�ڱ߱�������ָ������ָ��
					p->hlink = q->firstout;
					q->firstout = p;
				}
			for(q = head;q->data != end;q = q->next);
				if(q->data == end){
					p->jvex = q;                                                      //�ڱ߱�������ָ���յ��ָ��
					p->tlink = q->firstin;
					q->firstin = p;
				}
			for(q = head;q;q = q->next){                               //��u.current����Ϊu.N.head(firstin),���ͷŶ����ǳ�ȥs��t�����ඥ��                                         
				q->current = q->firstin;
			}
	}
	mydata.close( );

}

void OLGraph::printOLGraph( ){
	fstream p1;
	p1.open("D:/My Documents/Visual Studio 2010/Projects/MaxFlow/MaxFlow/p.txt");
	//cout<<"ʮ������Ĵ�ӡ���Ϊ��"<<endl;
	p1<<"ʮ������Ĵ�ӡ���Ϊ��"<<endl;
	VNode *p;
	ArcNode *q;
	for(p=head;p;p=p->next){
		if(p->firstout != NULL){
			for(q = p->firstout;q;q = q->hlink){
				//cout<<"( "<<q->tailvex<<" , "<<q->headvex<<" , "<<q->cap<<" )"<<"  ivex,jvex: "<<q->ivex->data<<"   "<<q->jvex->data<<"    ";
				p1<<"( "<<q->tailvex<<" , "<<q->headvex<<" , "<<q->cap<<" )"<<"  ivex,jvex: "<<q->ivex->data<<"   "<<q->jvex->data<<"    ";
			}
			//cout<<endl;
			p1<<endl;
		}
	}
	//for(p=head;p;p=p->next){
	//	for(q=p->firstin;q;q = q->tlink){
	//		cout<<"( "<<q->tailvex<<" , "<<q->headvex<<" , "<<q->cap<<" )"<<"   ";
	//	}
	//	cout<<endl;
	//}

}

bool OLGraph::judge1(VNode *&u,ArcNode *&v) {
	if(u->data == v->headvex){                               //�������
		if(v->flow >0)                                                //�������
			return true;
	}
	else
		if(u->data == v->tailvex){                            //�������
			if(v->cap - v->flow >0)                            //�����вд�����
				return true;
		}
		return false;
}

bool OLGraph::judge2(VNode *&u,ArcNode *&v) {
	int high;
	if(u->data == v->headvex){                             //�������
				high = v->ivex->high;
		if(u->high == high+1)                             //�жϸ߶Ȳ��Ƿ�Ϊ1
			return true;
		else
			return false;
	}
	else
	if(u->data == v->tailvex){                             //�������	
				high = v->jvex->high;
		if(u->high == high+1)                        //�жϸ߶Ȳ��Ƿ�Ϊ1
			return true;
		else
			return false;
	}
		return false;
}

void OLGraph::relable(VNode *&u) {
	ArcNode *q = u->firstin;
	int high_min = 1000000;
	while(q != NULL ){
		if(q->ivex->high < high_min && q->flow > 0)										//��v��u)���
			high_min = q->ivex->high;
			q = q->tlink; 
	}
	q = u->firstout;
	while(q != NULL){
		if(q->jvex->high < high_min && q->flow != q->cap)							 //(u,v)����
			high_min = q->jvex->high;
		q = q->hlink;
	}
	u->high = high_min + 1;                                                                          //������ǩ
}

void OLGraph::discharge(VNode *&u) {
	ArcNode *v = NULL;
	VNode *p = NULL;
	while(u->exflow > 0){ 
		v = u->current;																	//��u.current��ʼ��Ϊu.N.head(firstin)              
		if(flag == 1){
			//u->high += 1;															  //relabel(u)
			relable(u);
			u->current = u->firstin;								             //u.current = u.Nhead ����	
			flag1 = 0;
			flag = 0;
		}
		else
			if(judge1(u,v)&&judge2(u,v)){				               //���������жϷ�f>0,����ǳ����ж�cap-flow>0
																													 //Push(u,v)
				if(u->data == v->headvex && v->flow >=0){                             //���push
					//if(v->flow == 0);                                                                      //flowֵΪ0�������ͷ�
							if(u->exflow<=v->flow){
								v->flow -=u->exflow;						                             
								v->ivex->exflow += u->exflow;								 //���ӳ�����
								u->exflow = 0;                                                         //����ϵ�flowֵ����0��u����������С��ߵ�flowֵ
							}
							else{
								u->exflow -= v->flow;                                                                  				
								v->ivex->exflow += v->flow;                                         //���ӳ�����		                      
								v->flow=0;
							}
				} 
				else
					if(u->data == v->tailvex && v->flow <= v->cap){				 //����push
						//if(v->flow == v->cap);                                                     //v->flow == v->cap,�����ͷ�
							if(u->exflow <= (v->cap - v->flow)){                            //u->exflow��С����ȫ�ͷ�
								v->flow = v->flow + u->exflow;
								v->jvex->exflow += u->exflow;                                 //v���ӳ�����
								u->exflow = 0;
							}
							else{
								u->exflow = u->exflow - (v->cap - v->flow);         //exflow�ϴ��ͷŲд�����
								v->jvex->exflow += (v->cap - v->flow);                         //v���ӳ�����
								v->flow = v->cap;	
							}
					}
			} 
			else{                                                                          //u.current = v.next-neighbour,������Դ��ͻ��
				if(v->tlink != NULL && flag1==0){
					u->current = v->tlink;
					v = v->tlink;
				}
				else{
					if(flag1 == 0){
						u->current = u->firstout;
						v=u->firstout;
						flag1 = 1;
					}
					else
						if(v != NULL && flag1 == 1){
							v = v->hlink;
							u->current = v;
							
						}
					if(u->current == NULL)
						flag =1;
				}	
			}
	}
}

void OLGraph::relabel_to_front( ) {
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/MaxFlow/MaxFlow/result.txt");
	VNode* e = NULL;
	int old_high = 1000000;
	double flow_sum = 0;
	for (ArcNode *p=head->firstout;p;p=p->hlink){         //��Դ��Ԥ����
			p->flow=p->cap;
			p->jvex->exflow=p->cap;                                   //�Զ�����³�����		
	}
//*******************************************************      //����Ԥ����(��ȷ)
	//fstream out;
	//out.open("D:/My Documents/Visual Studio 2010/Projects/MaxFlow/MaxFlow/p.txt");
	//for(VNode *p=head;p;p=p->next){
	//	out<<p->data<<"     "<<p->exflow<<endl;
	//}
	//out.close( );
	//system("pause");
//*******************************************************
	VNode *u = head->next;
	VNode *pre = head;

	while(u->next != NULL){			                                                             //��ȥԴ��ͻ��u != NIL
			old_high = u->high;																		 //���涥���high��ֵ
			discharge(u);																					 //��Ⲣ�ͷŶ���
			if(u->high > old_high){ 
				pre->next = u->next;																  //move u to the front 
				u->next = head->next;
				head->next = u;
				pre = head;
			}                                                                                         
				pre = u;                                                                                    //�������ƶ���u = u.next
				u = u->next;
	}
	cout<<"ͼ�������Ϊ��";
	for(ArcNode *p = head->firstout;p;p=p->hlink){
		flow_sum += p->flow;
	}
	cout<<flow_sum<<endl;
	/*result<<"������㳬����Ϊ��"<<endl;
	for(e=head;e;e=e->next){
		result<<e->exflow<<endl;
	}*/
	result.close( );
}