#include<iostream>
using namespace std;
#define ORDER 5                     //��Ϊ5


struct treeNode;
typedef struct keyNode {
	int key;                              //����
	 treeNode *next;               //ָ����һ��������ָ��
}keyNode;

typedef struct treeNode {
	int child_num;                            //���ĵ�Ԫ����
	treeNode* bro;
	treeNode* parent;
	keyNode child[ORDER];			//�������6�����
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
