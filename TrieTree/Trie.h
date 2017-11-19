#include<iostream>
using namespace std;
#define MAXSIZE 26           //�ַ�������

typedef struct TNode{
	TNode* child[MAXSIZE];     //ÿ���ڵ�26��
	int num[MAXSIZE];                             //��ʾ�洢���ӽڵ����
	TNode(){
		for(int i=0;i<MAXSIZE;++i){
			child[i] = NULL;
		}
		for(int i=0;i<MAXSIZE;++i){
			num[i] = 0;
		}
	}
}Node;							 //�����

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