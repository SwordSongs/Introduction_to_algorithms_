#include"RBT.h"
#include<fstream>

RBTree::RBTree( ) {
	nil = new RBNode(-1,BLACK);                  //初始化RBTree，只有哨兵结点
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
	cout<<"空树！"<<endl;*/
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
	cout<<"空树!"<<endl;*/
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
	cout<<"空树！"<<endl;*/
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
	y->left = x;                                                 //x的父结点设置为y，y的左孩子设置为x
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
	x->right = y;                                       //y的父结点设置为x，x的右孩子设置为y
	y->parent = x;                                     //put y on x's right                                                           
}

void RBTree::insert(T key) {
	RBNode *z = new RBNode(key,RED);               //设置插入结点的颜色为红色
	insert(z);
}

void RBTree::insert(RBNode* p) {
	RBNode *y = nil;                            //标记边界
	RBNode *x = root;
	while(x != nil){                              //寻找z的插入位置
		y = x;
		if(p->key < x->key)
			x = x->left;
		else
			x= x->right;
	}
	p->parent = y;                          //y标记插入位置的父结点
	if(y == nil)                               //只有哨兵结点的初始情况
		root = p;
	else if(p->key < y->key)
		y->left = p;
	else
		y->right = p;
	p->left = nil;                         //p的左右孩子指向哨兵，颜色为RED
	p->right = nil;
	insert_fixup(p);
}

void RBTree::insert_fixup(RBNode *z) {
	//RBNode *y = NULL;
	while(z->parent->color == RED){                            //z.p.color == red
		if(z->parent == z->parent->parent->left){          //父亲结点是祖父结点的左孩子
			RBNode *y = z->parent->parent->right;						   //y   (uncle)
			if( y->color == RED){                                        //case1(父亲红色，叔叔红色)
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;                              //向上遍历
			}
			else{                                                                 //叔叔黑色
				if(z == z->parent->right){                          //case2(父亲红色，叔叔黑色，当前结点是父亲右孩子)
					z = z->parent;                                 //以当前父亲结点为支点，左旋
					left_rotate(z);
				}
				z->parent->color = BLACK;                  //父亲变黑
				z->parent->parent->color = RED;        //祖父变红
				right_rotate(z->parent->parent);         //以祖父为支点右旋          

			}
		}
		else{                                                                     //父亲结点是祖父结点的右孩子        
			RBNode *y = z->parent->parent->left;				        //y   (uncle)
			if(y->color == RED){                                    //case1(父亲红色，叔叔红色)
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;                              //向上遍历
			}
			else{                                                                 //叔叔黑色
				if(z == z->parent->left){                          //case2(父亲红色，叔叔黑色，当前结点是父亲右孩子)
					z = z->parent;                                 //以当前父亲结点为支点，左旋
					right_rotate(z);
				}
				z->parent->color = BLACK;                  //父亲变黑
				z->parent->parent->color = RED;        //祖父变红
				left_rotate(z->parent->parent);         //以祖父为支点右旋          
			}
		}                                                                                                         
	}
	root->color = BLACK;	
}

void RBTree::transplant(RBNode *u,RBNode *v) {
	if(u->parent == nil)                           //当u为树根时
		root = v;
	else if(u == u->parent->left)             //u是父结点的左孩子
		u->parent->left = v; 
	else
		u->parent->right = v;                   //u是父结点的右孩子

	v->parent = u->parent;                //v可以是哨兵，统一代码
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
  	RBTColor y_original_color = y->color;           //保存y的起始颜色
	if(p->left == nil){                                         //p结点没有左孩子
		x = p->right;                                           //x指向p->right,连接p->parent与p->right
		transplant(p,p->right);
	}
	else if(p->right == nil){                               //p结点没有右孩子
		x = p->left;                                            //x指向p->left,连接p->parent与p->left
		transplant(p,p->left);
	}               
	else{                                                         //p结点既有左子树又有右子树
		y = minimum(p->right);                       //沿着p的右子树的左指针一路往左走，找到右子树最左边一个结点
		//y = maximum(p->left);                      //沿着p的左子树的右指针一路向右走，找到左子树最右边一个结点
		y_original_color = y->color;
		x = y->right;                                       //y是最左边的结点，不会再有左子树，x指向y的右子树
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
			w = x->parent->left;                                      //w是x的兄弟结点
			if(w->color == RED){                                     //兄弟为红
				w->color = BLACK;                                    //兄变黑
				x->parent->color = RED;                         //父变红
				right_rotate(x->parent);                           //父右旋
				w = x->parent->left;                              //兄弟结点变为右旋后新的兄弟结点，处理完转到case2，3，4其中一种去处理
			}
			if(w->left->color == BLACK && w->right->color == BLACK){          //case2
				w->color = RED;                                    //兄弟变红                    
				x = x->parent;                                       //如果父红，最后变黑
			}
			else{
				if(w->left->color == BLACK){            //左侄子为黑，右侄子为红   case3
					w->right->color = BLACK;            //右侄子变黑
					w->color = RED;
					left_rotate(w);                               //左旋兄弟
					w = x->parent->left;                    //w变成新的兄弟结点
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
	while(p != nil && key != p->key){              //迭代       
		if(key < p->key)
			p = p->left;
		else
			p = p->right;
	}
	return p;												//p == nil or p->key == keys
}