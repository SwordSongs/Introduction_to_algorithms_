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
	//string s = "hello";                          //С��������
	//string s1 = "he";
	//string s3 = "hh";
	//string s4 = "hell";
	int count = 0;
	fstream mydata;
	/*t.insert(s);
	t.insert(s1);
	t.insert(s3);
	t.insert(s4);*/
	mydata.open("./dict.txt");         //���ݼ���ȡ

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
	cout<<"����ʱ�䣺"<<end - start<<"ms"<<endl;
	cout<<"�������ѯ�ַ�ǰ׺��"<<endl;
	cin>>s;
	count = t.search(s);
	cout<<"��ѯǰ׺���ִ���Ϊ��    ";
	cout<<count<<endl;
	cout<<"������ɾ�����ʣ�"<<endl;
	cin>>d;
	t.del(d);
	cout<<"�������ѯ�ַ�ǰ׺��"<<endl;
	cin>>s;
	count = t.search(s);
	cout<<"��ѯǰ׺���ִ���Ϊ��    ";
	cout<<count<<endl;
	mydata.close( );
	system("pause");
	return 0;
}