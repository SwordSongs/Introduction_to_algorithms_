#include<iostream>
#include<fstream>
#include<ctime>
#include"FH.h"
using namespace std;
int main() {
	clock_t start,end;
	fstream mydata;
	mydata.open("./repeat.txt");
	FibHeap f;
	double n;
	FibNode *p = NULL;
	FibNode *q = NULL;
	/*for(int i=0;i<10;++i){
		p = new FibNode(i);
		f.insert(p);
	}*/
	start = clock( );
	while(!mydata.eof( )){
		mydata>>n;
		p = new FibNode(n);
		f.insert(p);
	}
	end = clock( );
	cout<<"插入时间为："<<end - start<<"ms"<<endl;
	//f.print( );
	//cout<<"请输入插入数字"<<endl;
	//cin>>n;
	//p = new FibNode(n);
	//f.insert(p);
	//cout<<"插入后"<<endl;
	//f.print( );
	cout<<"抽取最小结点后："<<endl;
	q = f.extract_min( );
	cout<<"最小结点键值为："<<endl;
	cout<<q->key<<endl;
	cout<<"抽取后，"<<endl;
	f.print( );
	mydata.close( );
	system("pause");
	return 0;
}