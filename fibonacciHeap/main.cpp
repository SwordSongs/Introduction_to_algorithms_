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
	cout<<"����ʱ��Ϊ��"<<end - start<<"ms"<<endl;
	//f.print( );
	//cout<<"�������������"<<endl;
	//cin>>n;
	//p = new FibNode(n);
	//f.insert(p);
	//cout<<"�����"<<endl;
	//f.print( );
	cout<<"��ȡ��С����"<<endl;
	q = f.extract_min( );
	cout<<"��С����ֵΪ��"<<endl;
	cout<<q->key<<endl;
	cout<<"��ȡ��"<<endl;
	f.print( );
	mydata.close( );
	system("pause");
	return 0;
}