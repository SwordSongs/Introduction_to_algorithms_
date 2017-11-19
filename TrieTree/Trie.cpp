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
	for(int i=0;i<len;++i){								 //判断字符串的每个字母
		if(p->child[s[i]-'a'] == NULL){
			q = new TNode;
			p->child[s[i]-'a'] = q;
			p->num[s[i]-'a']++;
			p = q;												//p移动到新节点
		}
		else{
			p->num[s[i]-'a']++;
			p = p->child[s[i]-'a'];
		}
	}
}

int Trie::search(string &s) {					//查询一组字符串中，一个前缀出现多少次
	TNode *p = root;
	int count = 0;                             //计算字符出现个数
	int len = s.length( );
	for(int i=0;i<len;++i){
		if(p->child[s[i] - 'a'] == NULL){
			cout<<"不存在此字符串！"<<endl;
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
		if(p->child[s[i]-'a'] == NULL){                                //找不到单词
		cout<<"字典树中不存在此字符串！"<<endl;
		return false;
		} 
		else{                                                                    //找到单词
			q = p;
			p = p->child[s[i]-'a'];
			c = s[i];
		}
	}
	for(int i=0;i<MAXSIZE;++i){                                    //检测是否是叶子节点
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
		cout<<"查询单词不在叶子结点，不能删除！"<<endl;
		return false;
	}
}