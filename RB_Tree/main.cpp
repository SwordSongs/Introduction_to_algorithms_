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
	while(!del.eof( )){                              //删除
		del>>n;
		tree.remove(n);
	}
	end1 = clock( );
	cout<<"红黑树的中序遍历为："<<endl;
	result<<"红黑树的中序遍历为："<<endl;
	//tree.inOrder(result);
	cout<<endl<<"红黑树的建立时间为："<<end-start<<" ms"<<endl;
	cout<<endl<<"红黑树的删除时间为："<<end1 - start1<<"ms"<<endl;
	mydata.close( );
	del.close( );
	result.close( );
	system("pause");
	return 0;
}