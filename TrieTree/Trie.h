#include<iostream>
using namespace std;
#define MAXSIZE 26           //字符集长度

typedef struct TNode{
	TNode* child[MAXSIZE];     //每个节点26叉
	int num[MAXSIZE];                             //表示存储孩子节点个数
	TNode(){
		for(int i=0;i<MAXSIZE;++i){
			child[i] = NULL;
		}
		for(int i=0;i<MAXSIZE;++i){
			num[i] = 0;
		}
	}
}Node;							 //顶点表

class Trie{
	
	public:
		TNode *root;
		Trie( ): root(NULL) { }
		~Trie( );
		TNode * createTrie( );
		void insert(string &s);
		int search(string &s);
		bool del(string &s);
		
};