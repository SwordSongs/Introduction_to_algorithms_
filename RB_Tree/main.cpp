#include<iostream>
#include<fstream>
#include<ctime>
#include"RBT.h"

using namespace std;

int main( ) {
	clock_t start,end;
	clock_t start1,end1;
	fstream mydata;
	fstream del;
	fstream result("./result.txt");
	RBTree tree;
	int n;
	mydata.open("./large.txt");
	del.open("./large.txt");
	start = clock( );
	while(!mydata.eof( )){
		mydata>>n;
		if(mydata.fail( ))
			break;
		tree.insert(n);
	}
	end = clock( );
	start1 = clock( );
	while(!del.eof( )){                              //ɾ��
		del>>n;
		tree.remove(n);
	}
	end1 = clock( );
	cout<<"��������������Ϊ��"<<endl;
	result<<"��������������Ϊ��"<<endl;
	//tree.inOrder(result);
	cout<<endl<<"������Ľ���ʱ��Ϊ��"<<end-start<<" ms"<<endl;
	cout<<endl<<"�������ɾ��ʱ��Ϊ��"<<end1 - start1<<"ms"<<endl;
	mydata.close( );
	del.close( );
	result.close( );
	system("pause");
	return 0;
}