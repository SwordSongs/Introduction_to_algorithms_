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
	RBTColor color;                     //�����ɫ
	T key;                                    //����ֵ
	RBNode *left;                        //�������ָ��
	RBNode *right;                      //����Һ���ָ��
	RBNode *parent;                  //��㸸���ָ��
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
        void preOrder( );                                                         // ǰ�����"�����"
        void inOrder(fstream &r);                                                           // �������"�����"
        void postOrder( );                                                       // �������"�����"
		void insert(T key);                                                     //����һ�����
		void remove(T key);                                                 //ɾ��һ�����
		RBNode* search(T key);                                                  //����һ�����
		void destroy( );                                                        //����
		void print( );                                                            //��ӡ
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