#include<iostream>
using namespace std;

//#define rb_parent(r)   ((r)->parent)
//#define rb_color(r)     ((r)->color)
// #define rb_is_red(r)     ((r)->color==RED)
// #define rb_is_black(r)  ((r)->color==BLACK)
// #define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
// #define rb_set_red(r)     do { (r)->color = RED; } while (0)
// #define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
// #define rb_set_color(r,c)     do { (r)->color = (c); } while (0)


enum RBTColor{RED, BLACK};
typedef int T;
typedef struct RBNode{
	RBTColor color;                     //结点颜色
	T key;                                    //结点键值
	RBNode *left;                        //结点左孩子指针
	RBNode *right;                      //结点右孩子指针
	RBNode *parent;                  //结点父结点指针
	RBNode(T k,RBTColor c){
		color = c;
		key = k;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
}RBNode;

class RBTree{
	public:
		RBTree( );
		~RBTree( );
        void preOrder( );                                                         // 前序遍历"红黑树"
        void inOrder(fstream &r);                                                           // 中序遍历"红黑树"
        void postOrder( );                                                       // 后序遍历"红黑树"
		void insert(T key);                                                     //插入一个结点
		void remove(T key);                                                 //删除一个结点
		RBNode* search(T key);                                                  //搜索一个结点
		void destroy( );                                                        //销毁
		void print( );                                                            //打印
	private:
		RBNode *root;
		RBNode *nil;

		void preOrder(RBNode *p) const;
		void inOrder(RBNode *p,fstream& r) const;
		void postOrder(RBNode *p) const;
	
		RBNode* search(RBNode *p,T key) const;
		void insert(RBNode* p);
		void left_rotate(RBNode* x);
		void right_rotate(RBNode* y);
		void insert_fixup(RBNode *z);

		void transplant(RBNode *u,RBNode *v);
		void remove(RBNode* p);
		void remove_fixup(RBNode *x);
		RBNode* minimum(RBNode *p);
		RBNode* maximum(RBNode *p);

		void destroy(RBNode* p);
};