#include<iostream>
#include"AGraph.h"
#include<stack>
#include<ctime>
using namespace std;

int main( ) {

	AGraph g;
	AGraph tg;                                            //ת��ͼ
	clock_t start,end;

	g.createAGraph( );                                //����ͼ
	//g.printAGraph( );

	
	cout<<endl;

	start = clock( );
	tg.createTAG(g);                                  //����ת��ͼ,kosarajuʹ��
	//tg.printAGraph( );
	g.kosaraju(1,tg);
	end = clock( );
	cout<<"Kosaraju�㷨ʱ��Ϊ��"<<end - start<<"ms"<<endl;

	system("pause");
	return 0;
}