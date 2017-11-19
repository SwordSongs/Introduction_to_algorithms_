#include<iostream>
#include<fstream>
#include<ctime>
#include"BPT.h"
using namespace std;

int main( ) {
	clock_t start,end;
	clock_t start1,end1;
	fstream mydata;
	fstream d;
	BP b;
	int key;
	mydata.open("./xiao.txt");
	d.open("./xiao.txt");
	start = clock( );
	while(!mydata.eof( )){
		mydata>>key;
		b.insert(key);
	}
	end = clock( );
	//b.display( );
	//cout<<endl;
	//b.search(78);
	//cout<<endl
	start1 = clock();
	while(!d.eof()){
		d>>key;
		b.del(key);
	}
	end1 = clock();
	cout<<"插入时间："<<end-start<<"ms"<<endl;
	cout<<"删除时间："<<end1-start1<<"ms"<<endl;
	//b.del(78);
	//b.display( );
	//cout<<endl;
	//b.search(78);
	system("pause");
	return 0;
}