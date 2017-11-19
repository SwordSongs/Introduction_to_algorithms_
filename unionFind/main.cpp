#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include"unionFind.h"
using namespace std;



int main() {
	clock_t start,end;
	int en = EN;                  //����ͼ�Ķ�����Ŀ�ͱ���
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
		if(mydata.fail( ))                     //����#���
			break;
		
		mydata>>road[i].start>>road[i].end;
			++i;
	}
	//****************************************************************
	//cout<<"ͼ������Ϊ"<<endl;                                         //����
	//for(int i=0;i<en;++i){
	//	cout<<"   "<<road[i].start<<"   "<<road[i].end<<endl;
	//}
	//system("pause");
	//****************************************************************


	cout<<"�ߺͶ������ĿΪ(�������)��";
	cout<<en<<"     "<<vn<<endl;

	start = clock( );
	for(int i=0;i<en;++i){
		_union(road[i].start,road[i].end);
	}

	for(int i=0;i<vn;++i){
		if(root[i] == i)
			count++;
	}
	cout<<"��ͨ�����ĸ���Ϊ��"<<count<<endl;
	end = clock( );
	cout<<"��ѯʱ��Ϊ�� "<<end-start<<"ms"<<endl;
	
	mydata.close( );
	system("pause");
	return 0;
}