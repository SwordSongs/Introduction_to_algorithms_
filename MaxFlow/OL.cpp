#include"OL.h"
#include<fstream>

OLGraph::OLGraph( ) {						//给定顶点个数构建链表
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
	head->high = vn;                    //源点的高度为vn
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
			if(mydata.fail( )){                                                     //检验空格
				break;
			}
			for(q = head;q->data != start;q = q->next);          //链接十字链表
				if(q->data == start){
					p->ivex = q;                                                       //在边表中设置指向起点的指针
					p->hlink = q->firstout;
					q->firstout = p;
				}
			for(q = head;q->data != end;q = q->next);
				if(q->data == end){
					p->jvex = q;                                                      //在边表中设置指向终点的指针
					p->tlink = q->firstin;
					q->firstin = p;
				}
			for(q = head;q;q = q->next){                               //将u.current设置为u.N.head(firstin),被释放顶点是除去s和t的其余顶点                                         
				q->current = q->firstin;
			}
	}
	mydata.close( );

}

void OLGraph::printOLGraph( ){
	fstream p1;
	p1.open("D:/My Documents/Visual Studio 2010/Projects/MaxFlow/MaxFlow/p.txt");
	//cout<<"十字链表的打印结果为："<<endl;
	p1<<"十字链表的打印结果为："<<endl;
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
	if(u->data == v->headvex){                               //代表入边
		if(v->flow >0)                                                //入边有流
			return true;
	}
	else
		if(u->data == v->tailvex){                            //代表出边
			if(v->cap - v->flow >0)                            //出边有残存容量
				return true;
		}
		return false;
}

bool OLGraph::judge2(VNode *&u,ArcNode *&v) {
	int high;
	if(u->data == v->headvex){                             //代表入边
				high = v->ivex->high;
		if(u->high == high+1)                             //判断高度差是否为1
			return true;
		else
			return false;
	}
	else
	if(u->data == v->tailvex){                             //代表出边	
				high = v->jvex->high;
		if(u->high == high+1)                        //判断高度差是否为1
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
		if(q->ivex->high < high_min && q->flow > 0)										//（v，u)入边
			high_min = q->ivex->high;
			q = q->tlink; 
	}
	q = u->firstout;
	while(q != NULL){
		if(q->jvex->high < high_min && q->flow != q->cap)							 //(u,v)出边
			high_min = q->jvex->high;
		q = q->hlink;
	}
	u->high = high_min + 1;                                                                          //重贴标签
}

void OLGraph::discharge(VNode *&u) {
	ArcNode *v = NULL;
	VNode *p = NULL;
	while(u->exflow > 0){ 
		v = u->current;																	//将u.current初始化为u.N.head(firstin)              
		if(flag == 1){
			//u->high += 1;															  //relabel(u)
			relable(u);
			u->current = u->firstin;								             //u.current = u.Nhead 重置	
			flag1 = 0;
			flag = 0;
		}
		else
			if(judge1(u,v)&&judge2(u,v)){				               //如果是入边判断法f>0,如果是出边判断cap-flow>0
																													 //Push(u,v)
				if(u->data == v->headvex && v->flow >=0){                             //入边push
					//if(v->flow == 0);                                                                      //flow值为0，不做释放
							if(u->exflow<=v->flow){
								v->flow -=u->exflow;						                             
								v->ivex->exflow += u->exflow;								 //增加超额流
								u->exflow = 0;                                                         //入边上的flow值大于0，u结点回流，减小入边的flow值
							}
							else{
								u->exflow -= v->flow;                                                                  				
								v->ivex->exflow += v->flow;                                         //增加超额流		                      
								v->flow=0;
							}
				} 
				else
					if(u->data == v->tailvex && v->flow <= v->cap){				 //出边push
						//if(v->flow == v->cap);                                                     //v->flow == v->cap,不做释放
							if(u->exflow <= (v->cap - v->flow)){                            //u->exflow较小，完全释放
								v->flow = v->flow + u->exflow;
								v->jvex->exflow += u->exflow;                                 //v增加超额流
								u->exflow = 0;
							}
							else{
								u->exflow = u->exflow - (v->cap - v->flow);         //exflow较大，释放残存容量
								v->jvex->exflow += (v->cap - v->flow);                         //v增加超额流
								v->flow = v->cap;	
							}
					}
			} 
			else{                                                                          //u.current = v.next-neighbour,不存在源点和汇点
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
	for (ArcNode *p=head->firstout;p;p=p->hlink){         //从源点预推送
			p->flow=p->cap;
			p->jvex->exflow=p->cap;                                   //对顶点更新超额流		
	}
//*******************************************************      //测试预推送(正确)
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

	while(u->next != NULL){			                                                             //除去源点和汇点u != NIL
			old_high = u->high;																		 //保存顶点的high旧值
			discharge(u);																					 //检测并释放顶点
			if(u->high > old_high){ 
				pre->next = u->next;																  //move u to the front 
				u->next = head->next;
				head->next = u;
				pre = head;
			}                                                                                         
				pre = u;                                                                                    //正常后移动，u = u.next
				u = u->next;
	}
	cout<<"图的最大流为：";
	for(ArcNode *p = head->firstout;p;p=p->hlink){
		flow_sum += p->flow;
	}
	cout<<flow_sum<<endl;
	/*result<<"各个结点超额流为："<<endl;
	for(e=head;e;e=e->next){
		result<<e->exflow<<endl;
	}*/
	result.close( );
}