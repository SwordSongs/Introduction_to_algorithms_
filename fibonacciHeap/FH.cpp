#include"FH.h"
#include<math.h>

FibHeap::FibHeap( ) {
	num = 0;
	min = NULL;
}

FibHeap::~FibHeap( ) {

}

void FibHeap::addNode(FibNode *&node,FibNode *&root) {          
		node->left = root->left;
		root->left->right = node;
		root->left = node;
		node->right = root;
}

void FibHeap::removeNode(FibNode *&node) {
		node->left->right = node->right;
		node->right->left = node->left;
}

void FibHeap::insert(FibNode *&node) {
		if(num == 0)
			min = node;
		else{
			addNode(node,min);
			if(node->key < min->key)
				min = node;
		}
		num++;
}

FibHeap* FibHeap::combine(FibHeap *&h1,FibHeap *&h2) {
	FibHeap *h = new FibHeap;                                  //make-FibHeap
	h->min = h1->min;                                              //H.min = H1.min

	h2->min->right = h1->min->right;                      //根链表连接
	h2->min->left = h1->min;
	h1->min->right = h2->min;
	h2->min->right->left = h2->min;

	if(h1->min == NULL || (h2->min != NULL && h2->min->key < h1->min->key))
		h->min = h2->min;
	h->num = h1->num + h2->num;
	return h;
}

double FibHeap::find_min_key( ) {
	if(min == NULL){
		cout<<"h->min为空，无法找到最小key！"<<
			system("pause");
		return 10000000,0;
	}
		return min->key;		
}

void FibHeap::link(FibNode *y,FibNode *x) {                           //y->key是较大值
		removeNode(y);                                                           //将y从rootlist中删除
		if(x->child == NULL)
			x->child = y;
		else
			addNode(y,x->child);

		y->parent = x;
		x->degree++;
		y->mark = false;
}

void FibHeap::consolidate( ) {
	FibNode *x = NULL;
	FibNode *y = NULL;
	FibNode *w = NULL;
	double temp;																//交换x，y
	int d;

  // long double golden = (1+sqrt(5.0))/2;
	int D = (int)(log((double)num)/log(1.4))+1;                   //向上取整,标准应该为黄金分割率1.618
	//int D = num;

	FibNode **A = new FibNode*[D];
	for(int i=0;i<D;++i)																	//初始化辅助数组A
		A[i] = NULL;

	for(w=min;w->right!=w;w=w->right){										 //for each node w in the root list of H
		x = w;
		d = x->degree;
		while(A[d] != NULL){																		 //while A[d] != NULL
				y = A[d];																	 //another node with the same degree as x
				if(x->key > y->key){
					temp = x->key;															//exchange x with y , y中存放的是较大值
					x->key = y->key;
					y->key = temp;                  
				}
				link(y,x);
				A[d] = NULL;
				d += 1;
		}
		A[d] = x;
	}
	min = NULL;                                                            //H.min = NIL
	for(int i=0;i<D;++i){
		if(A[i] != NULL){
			if(min == NULL){
				min = A[i];
			}
			else{
				addNode(A[i],min);
				if(A[i]->key < min->key)
					min = A[i];
			}
		}
	}




	
}

FibNode* FibHeap::extract_min( ) {
	FibNode *z = min;																	//z = H.min
	FibNode *p1 = NULL;
	FibNode *p2 = NULL;

	if(z){																							//z!=NULL
		for(int i=0;i<z->degree;++i){                                                //for each child of z
			for(p1 = z->child,p2 = z->child;p1->left!=p2;p1=p1->left,p2=p2->right){	//add x to the root list of H
				p1->parent = NULL;                                                                //x.p == NULL(x is child of z)
				p2->parent = NULL;
			}
					min->left->right = p1;                                                       //连接左边
					p1->left = min->left;

					min->right->left = p2;                                                     //连接右边
					p2->right = min->right;
		}   
		                                                                                                    //remove z from the root list of H
		z->left->right = z->right;
		z->right->left = z->left;

		if(z == z->right)
			min = NULL;
		else{
			min = z->right;                                                                     //min指向后一个结点
			consolidate( );
		}
		--num;
	}                                                            
	return z;
}

void FibHeap::print( ) {
	FibNode* p;
	cout<<"斐波那契堆的根链表为："<<endl;
	for(p=min;p->right!=min;p=p->right){
		if(p == min)
			cout<<"--"<<p->key<<"-----";
		else
			cout<<p->key<<"-----";
	}
	if(p->right == min)
		cout<<p->key<<"--";
	cout<<endl;
}



