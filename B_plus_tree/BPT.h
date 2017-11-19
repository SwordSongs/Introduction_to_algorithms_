#include<iostream>
using namespace std;
#define ORDER 5                     //秩为5


struct treeNode;
typedef struct keyNode {
	int key;                              //索引
	 treeNode *next;               //指向下一个树结点的指针
}keyNode;

typedef struct treeNode {
	int child_num;                            //结点的单元计数
	treeNode* bro;
	treeNode* parent;
	keyNode child[ORDER];			//数组最多6个结点
	treeNode(int num){
		child_num = 1;
		bro = NULL;
		parent = NULL;
		child[0].next=NULL;
		child[0].key=num;
	}
}treeNode;

class BP {
	public:
		BP( );
		~BP( );
		void insert(int num);
		void del(int num);
		void display( );
		void search(int n);
	private:
		treeNode *head;
		treeNode *first;
};
