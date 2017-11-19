#include"Trie.h"

Trie::~Trie( ){                             

}

TNode *Trie::createTrie( ){
	TNode *p =	new TNode;
	return p;
}

void Trie::insert(string &s){
	int len = s.length( );
	TNode *p = root;
	TNode *q;
	for(int i=0;i<len;++i){								 //�ж��ַ�����ÿ����ĸ
		if(p->child[s[i]-'a'] == NULL){
			q = new TNode;
			p->child[s[i]-'a'] = q;
			p->num[s[i]-'a']++;
			p = q;												//p�ƶ����½ڵ�
		}
		else{
			p->num[s[i]-'a']++;
			p = p->child[s[i]-'a'];
		}
	}
}

int Trie::search(string &s) {					//��ѯһ���ַ����У�һ��ǰ׺���ֶ��ٴ�
	TNode *p = root;
	int count = 0;                             //�����ַ����ָ���
	int len = s.length( );
	for(int i=0;i<len;++i){
		if(p->child[s[i] - 'a'] == NULL){
			cout<<"�����ڴ��ַ�����"<<endl;
			count = 0;
			return count;
		}
		else{
			count = p->num[s[i]-'a'];
			p = p->child[s[i] - 'a'];
		}
	}
	return count;
}

bool Trie::del(string &s) {
	int len = s.length( );
	char c;
	TNode *p = root;
	TNode *q = root;
	int count = 0;
	for(int i=0;i<len-1;++i){
		if(p->child[s[i]-'a'] == NULL){                                //�Ҳ�������
		cout<<"�ֵ����в����ڴ��ַ�����"<<endl;
		return false;
		} 
		else{                                                                    //�ҵ�����
			q = p;
			p = p->child[s[i]-'a'];
			c = s[i];
		}
	}
	for(int i=0;i<MAXSIZE;++i){                                    //����Ƿ���Ҷ�ӽڵ�
		if(p->child[i] == NULL)
			count++;
	}
	if(count == MAXSIZE-1){
		delete p;
		q->child[c-'a'] = NULL;
		return true;
	}
	else
	{
		cout<<"��ѯ���ʲ���Ҷ�ӽ�㣬����ɾ����"<<endl;
		return false;
	}
}