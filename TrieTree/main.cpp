#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include"Trie.h"
using namespace std;

int main( ) {
	clock_t start,end;
	Trie t;
	t.root = t.createTrie( );
	string s;
	string d;
	//string s = "hello";                          //小测试用例
	//string s1 = "he";
	//string s3 = "hh";
	//string s4 = "hell";
	int count = 0;
	fstream mydata;
	/*t.insert(s);
	t.insert(s1);
	t.insert(s3);
	t.insert(s4);*/
	mydata.open("./dict.txt");         //数据集读取

	start = clock( );
	while(!mydata.eof( )){
		if(mydata.fail( )){
			break;
		}
		mydata>>s;
		t.insert(s);
		//cout<<s<<endl;
	}
	end = clock( );
	cout<<"插入时间："<<end - start<<"ms"<<endl;
	cout<<"请输入查询字符前缀："<<endl;
	cin>>s;
	count = t.search(s);
	cout<<"查询前缀出现次数为：    ";
	cout<<count<<endl;
	cout<<"请输入删除单词："<<endl;
	cin>>d;
	t.del(d);
	cout<<"请输入查询字符前缀："<<endl;
	cin>>s;
	count = t.search(s);
	cout<<"查询前缀出现次数为：    ";
	cout<<count<<endl;
	mydata.close( );
	system("pause");
	return 0;
}