#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include"unionFind.h"
using namespace std;



int main() {
	clock_t start,end;
	int en = EN;                  //输入图的顶点数目和边数
	int vn = VN;
	int x,y;
	int i=0;
	int count = 0;

	fstream mydata;
	mydata.open("./uniprot22m.txt");
	//mydata.open("./uniprot100m.txt");
	//mydata.open("./uniprot150m.txt");
	//mydata.open("./vchocyc.txt");
	makeSet(vn);
	
	while(!mydata.eof()) {
		if(mydata.fail( ))                     //跳过#标记
			break;
		
		mydata>>road[i].start>>road[i].end;
			++i;
	}
	//****************************************************************
	//cout<<"图的数据为"<<endl;                                         //测试
	//for(int i=0;i<en;++i){
	//	cout<<"   "<<road[i].start<<"   "<<road[i].end<<endl;
	//}
	//system("pause");
	//****************************************************************


	cout<<"边和顶点的数目为(从零计数)：";
	cout<<en<<"     "<<vn<<endl;

	start = clock( );
	for(int i=0;i<en;++i){
		_union(road[i].start,road[i].end);
	}

	for(int i=0;i<vn;++i){
		if(root[i] == i)
			count++;
	}
	cout<<"连通分量的个数为："<<count<<endl;
	end = clock( );
	cout<<"查询时间为： "<<end-start<<"ms"<<endl;
	
	mydata.close( );
	system("pause");
	return 0;
}