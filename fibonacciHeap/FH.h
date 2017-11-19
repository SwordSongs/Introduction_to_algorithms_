#include<iostream>
using namespace std;

typedef struct FibNode{
	double key;
	int degree;                                 //���ĺ���������Ŀ
	bool mark;                                 //�Դ���һ�γ�Ϊ��һ�����ĺ��Ӻ��Ƿ�ʧȥ�����ӣ���DECREASE-KEY�����йأ�
	FibNode *parent;                        //���ĸ����ָ��
	FibNode *left;                             //���������е���ָ��
	FibNode *right;                          //���������е���ָ��
	FibNode *child;                          //ָ��ĳһ�����ӵ�ָ��

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
		int num;																				   //��ʾH�е�ǰ������Ŀ
		FibNode *min;																	    //ָ��������йؼ�����С���Ǹ����

		void addNode(FibNode *&node,FibNode *&root);					  //�ڸ�ѭ�������м���һ���ѽ�㣬��root���
		void removeNode(FibNode *&node);
		void consolidate();
		void link(FibNode *y,FibNode *x);                                               //y->key�ǽϴ�ֵ
	public:
		FibHeap( );
		~FibHeap( );
		void insert(FibNode *&node);
		FibHeap* combine(FibHeap *&h1,FibHeap *&h2);
		double find_min_key( );
		FibNode* extract_min( );
		void print( ); 



};