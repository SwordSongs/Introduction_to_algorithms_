#include<iostream>
#include"OL.h"
#include<ctime>
using namespace std;

int main( ){
	clock_t start,end;
	OLGraph g;
	g.createOLGraph( );
	//g.printOLGraph( );
	start = clock( );
	g.relabel_to_front( );
	end = clock( );
	cout<<"Ê±¼äÎª£º"<<end-start<<" ms"<<endl;
	system("pause");
	return 0;
}