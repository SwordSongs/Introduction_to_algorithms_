#include<iostream>
#include"AGraph.h"
#include<stack>
#include<ctime>
using namespace std;

int main() {

	AGraph g;
	AGraph tg;                                            //ת��ͼ
	clock_t start,end;

	g.createAGraph( );                                //����ͼ
	//g.printAGraph( );

	
	cout<<endl;
	tg.createTAG(g);                                  //����ת��ͼ,kosarajuʹ��
	//tg.printAGraph( );
//******************************************************
	start = clock( );
	g.kosaraju(1,tg);
	end = clock( );
	cout<<"Kosaraju�㷨ʱ��Ϊ��"<<end - start<<"ms"<<endl;
//*******************************************************
	//g.initalDFN( );										 //��ʼ����������,Tarjan�㷨
	//g.initalLOW( );
	//stack<VertexType> s;
	//cout<<"Tarjan�㷨��ͼ��ǿ��ͨ����Ϊ��"<<endl;
	//start = clock( );
	//for(int i=0;i<VN;++i){                                 //����������ȣ���ɭ�ֽṹ��ͼ
	//	if(g.DFN[i].flag==0)
	//		g.Tarjan(i,s);
	//	
	//}
	//end = clock( );
	//cout<<"ͼ��ǿ��ͨ�����ĸ���Ϊ��"<<endl;
	//cout<<g.count<<endl;
	//cout<<"Tarjan�㷨ʱ��Ϊ��"<<end - start<<"ms"<<endl;
//********************************************************
	//stack<VertexType> path;                         //Gabow�㷨,�Ҷ���̫�鷳�����㲻֧��ͨ���ԣ���Ŵ�0��ʼ
	//stack<VertexType> root;
	//cout<<"Gabow�㷨��ͼ��ǿ��ͨ����Ϊ��"<<endl;
	//start = clock( );
	//g.Gabow(1,path,root);
	//end = clock( );
	//cout<<"ͼ��ǿ��ͨ�����ĸ���Ϊ��"<<endl;
	//cout<<g.count<<endl;
	//cout<<"Gabow�㷨ʱ��Ϊ��"<<end - start<<"ms"<<endl;
//***********************************************************************
	//g.initalFinished( );
	//g.initalVisited( );
	//cout<<"ͼ��������������������Ϊ��"<<endl;
	//g.DFS(1);                                                        //��ȱ�����ʼ���㴫ֵ
	//cout<<endl;
	//g.initalVisited( );
	//cout<<"ͼ�Ĺ�����������������Ϊ��"<<endl;
	//g.BFS(1);
	//cout<<endl;
//**************************************************************************
	system("pause");
	return 0;
}