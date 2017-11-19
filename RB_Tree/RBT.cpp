#include"RBT.h"
#include<fstream>

RBTree::RBTree( ) {
	nil = new RBNode(-1,BLACK);                  //��ʼ��RBTree��ֻ���ڱ����
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	root = nil;
}

RBTree::~RBTree( ) {
	destroy( );
}

void RBTree::preOrder(RBNode *p)const {
	/*if(p == nil)
	cout<<"������"<<endl;*/
	if(p != nil){
		cout<<"( "<<p->key<<","<<(p->color==0?"RED":"BLACK")<<" )"<<endl;
		preOrder(p->left);
		preOrder(p->right);
	}
} 

void RBTree::preOrder( ) {
	preOrder(root);
}

void RBTree::inOrder(RBNode *p,fstream& r)const {
	/*if(p == nil)
	cout<<"����!"<<endl;*/
	if(p != nil){
		inOrder(p->left,r);
		cout<<"( "<<p->key<<","<<(p->color==0?"RED":"BLACK")<<" )"<<endl;
		r<<"( "<<p->key<<","<<(p->color==0?"RED":"BLACK")<<" )"<<endl;
		inOrder(p->right,r);
	}
} 

void RBTree::inOrder(fstream& r) {
	inOrder(root,r);
}

void RBTree::postOrder(RBNode *p)const {
	/*if(p == nil)
	cout<<"������"<<endl;*/
	if(p != nil){
		postOrder(p->left);
		postOrder(p->right);
		cout<<"( "<<p->key<<","<<(p->color==0?"RED":"BLACK")<<" )"<<endl;
	}
} 

void RBTree::postOrder( ) {
	postOrder(root);
}

void RBTree::destroy( ) {
	destroy(root);
}

void RBTree::destroy(RBNode* p) {
	if(p == nil)
		return;
	if(p != nil){
		destroy(p->left);
		destroy(p->right);
		delete p;
	}
}

void RBTree::left_rotate(RBNode* x) {
	RBNode *y = x->right;                                      //y = x.right
	x->right = y->left;                                            //x.right = y.right
	if(y->left != nil)
		y->left->parent = x;                                    //y.left.p = x
	y->parent = x->parent;                                   //y.p = x.p
	if(x->parent == nil)
		root = y;
	else if(x->parent->left == x)
			x->parent->left = y;
		else 
			x->parent->right = y;                              //x.parent.right == x
	y->left = x;                                                 //x�ĸ��������Ϊy��y����������Ϊx
	x->parent = y;                                             //put x on y's left
}

void RBTree::right_rotate(RBNode *y) {
	RBNode *x = y->left;                                 //x = y.left
	y->left = x->right;                                     //y.left = x.right
	if(x->right != nil)
		x->right->parent = y;                            //x.right.p = y
	x->parent = y->parent;                             //x.p = y.p
	if(y->parent == nil)
		root = x;
	else if(y->parent->right == y)
		y->parent->right = x;
	else                                                      
		y->parent->left = x;                           //y.p.right == y
	x->right = y;                                       //y�ĸ��������Ϊx��x���Һ�������Ϊy
	y->parent = x;                                     //put y on x's right                                                           
}

void RBTree::insert(T key) {
	RBNode *z = new RBNode(key,RED);               //���ò��������ɫΪ��ɫ
	insert(z);
}

void RBTree::insert(RBNode* p) {
	RBNode *y = nil;                            //��Ǳ߽�
	RBNode *x = root;
	while(x != nil){                              //Ѱ��z�Ĳ���λ��
		y = x;
		if(p->key < x->key)
			x = x->left;
		else
			x= x->right;
	}
	p->parent = y;                          //y��ǲ���λ�õĸ����
	if(y == nil)                               //ֻ���ڱ����ĳ�ʼ���
		root = p;
	else if(p->key < y->key)
		y->left = p;
	else
		y->right = p;
	p->left = nil;                         //p�����Һ���ָ���ڱ�����ɫΪRED
	p->right = nil;
	insert_fixup(p);
}

void RBTree::insert_fixup(RBNode *z) {
	//RBNode *y = NULL;
	while(z->parent->color == RED){                            //z.p.color == red
		if(z->parent == z->parent->parent->left){          //���׽�����游��������
			RBNode *y = z->parent->parent->right;						   //y   (uncle)
			if( y->color == RED){                                        //case1(���׺�ɫ�������ɫ)
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;                              //���ϱ���
			}
			else{                                                                 //�����ɫ
				if(z == z->parent->right){                          //case2(���׺�ɫ�������ɫ����ǰ����Ǹ����Һ���)
					z = z->parent;                                 //�Ե�ǰ���׽��Ϊ֧�㣬����
					left_rotate(z);
				}
				z->parent->color = BLACK;                  //���ױ��
				z->parent->parent->color = RED;        //�游���
				right_rotate(z->parent->parent);         //���游Ϊ֧������          

			}
		}
		else{                                                                     //���׽�����游�����Һ���        
			RBNode *y = z->parent->parent->left;				        //y   (uncle)
			if(y->color == RED){                                    //case1(���׺�ɫ�������ɫ)
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;                              //���ϱ���
			}
			else{                                                                 //�����ɫ
				if(z == z->parent->left){                          //case2(���׺�ɫ�������ɫ����ǰ����Ǹ����Һ���)
					z = z->parent;                                 //�Ե�ǰ���׽��Ϊ֧�㣬����
					right_rotate(z);
				}
				z->parent->color = BLACK;                  //���ױ��
				z->parent->parent->color = RED;        //�游���
				left_rotate(z->parent->parent);         //���游Ϊ֧������          
			}
		}                                                                                                         
	}
	root->color = BLACK;	
}

void RBTree::transplant(RBNode *u,RBNode *v) {
	if(u->parent == nil)                           //��uΪ����ʱ
		root = v;
	else if(u == u->parent->left)             //u�Ǹ���������
		u->parent->left = v; 
	else
		u->parent->right = v;                   //u�Ǹ������Һ���

	v->parent = u->parent;                //v�������ڱ���ͳһ����
}

RBNode* RBTree::minimum(RBNode *p) {
	while(p->left != nil)
		p = p->left;
	return p;
}

RBNode* RBTree::maximum(RBNode *p) {
	while(p->right != nil)
		p = p->right;
	return p;
}

void RBTree::remove(T key) {
	RBNode *p = search(key);
	if(p != nil)
		remove(p);
}

void RBTree::remove(RBNode* p) {
	RBNode *y = p;
	RBNode *x = NULL;
  	RBTColor y_original_color = y->color;           //����y����ʼ��ɫ
	if(p->left == nil){                                         //p���û������
		x = p->right;                                           //xָ��p->right,����p->parent��p->right
		transplant(p,p->right);
	}
	else if(p->right == nil){                               //p���û���Һ���
		x = p->left;                                            //xָ��p->left,����p->parent��p->left
		transplant(p,p->left);
	}               
	else{                                                         //p����������������������
		y = minimum(p->right);                       //����p������������ָ��һ·�����ߣ��ҵ������������һ�����
		//y = maximum(p->left);                      //����p������������ָ��һ·�����ߣ��ҵ����������ұ�һ�����
		y_original_color = y->color;
		x = y->right;                                       //y������ߵĽ�㣬����������������xָ��y��������
		if(y->parent == p)
			x->parent = y;
		else{
			transplant(y,y->right);
			y->right = p->right;
			y->right->parent = y;
		}
		transplant(p,y);
		y->left = p->left;
		y->left->parent = y;
		y->color = p->color;
	}
	if(y_original_color == BLACK)
		remove_fixup(x);
}

void RBTree::remove_fixup(RBNode *x){
	RBNode *w = NULL;
	while(x != root && x->color == BLACK){
		if(x == x->parent->left){
				w = x->parent->right;
				if(w->color == RED){                            
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if(w->left->color == BLACK && w->right->color == BLACK){
					w->color = RED;
					x = x->parent;
				}
		else{
					if(w->right->color == BLACK){
						w->left->color = BLACK;
						w->color = RED;
						right_rotate(w);
						w = x->parent->right;
					}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = root;
		}
	}
	else{
			w = x->parent->left;                                      //w��x���ֵܽ��
			if(w->color == RED){                                     //�ֵ�Ϊ��
				w->color = BLACK;                                    //�ֱ��
				x->parent->color = RED;                         //�����
				right_rotate(x->parent);                           //������
				w = x->parent->left;                              //�ֵܽ���Ϊ�������µ��ֵܽ�㣬������ת��case2��3��4����һ��ȥ����
			}
			if(w->left->color == BLACK && w->right->color == BLACK){          //case2
				w->color = RED;                                    //�ֵܱ��                    
				x = x->parent;                                       //������죬�����
			}
			else{
				if(w->left->color == BLACK){            //��ֶ��Ϊ�ڣ���ֶ��Ϊ��   case3
					w->right->color = BLACK;            //��ֶ�ӱ��
					w->color = RED;
					left_rotate(w);                               //�����ֵ�
					w = x->parent->left;                    //w����µ��ֵܽ��
				}
				w->color =  x->parent->color;
				x->parent->color =	BLACK;
				w->left->color =	BLACK;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

RBNode* RBTree::search(T key){
	return search(root,key);
}

RBNode* RBTree::search(RBNode *p,T key) const {
	while(p != nil && key != p->key){              //����       
		if(key < p->key)
			p = p->left;
		else
			p = p->right;
	}
	return p;												//p == nil or p->key == keys
}