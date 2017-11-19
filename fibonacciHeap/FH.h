#include<iostream>
using namespace std;

typedef struct FibNode{
	double key;
	int degree;                                 //结点的孩子链表数目
	bool mark;                                 //自从上一次成为另一个结点的孩子后，是否失去过孩子（与DECREASE-KEY操作有关）
	FibNode *parent;                        //结点的父结点指针
	FibNode *left;                             //孩子链表中的左指针
	FibNode *right;                          //孩子链表中的右指针
	FibNode *child;                          //指向某一个孩子的指针

	FibNode(double key){
		this->key = key;
		degree = 0;
		mark = false;
		parent = NULL;
		left = this;
		right = this;
		child = NULL;
	}
}FibNode;

class FibHeap{
	private:
		int num;																				   //表示H中当前结点的数目
		FibNode *min;																	    //指向根链表中关键字最小的那个结点

		void addNode(FibNode *&node,FibNode *&root);					  //在根循环链表中加入一个堆结点，在root左侧
		void removeNode(FibNode *&node);
		void consolidate();
		void link(FibNode *y,FibNode *x);                                               //y->key是较大值
	public:
		FibHeap( );
		~FibHeap( );
		void insert(FibNode *&node);
		FibHeap* combine(FibHeap *&h1,FibHeap *&h2);
		double find_min_key( );
		FibNode* extract_min( );
		void print( ); 



};