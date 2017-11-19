#include<iostream>
#include<fstream>
#include<ctime>
#define NUM 1000000
using namespace std;

int main(){
	fstream result;
	result.open("./result.txt");
	clock_t start,end;
	fstream mydata;
	mydata.open("./raise.txt");
	int *A = new int[NUM];
	int i = 0;
	while(!mydata.eof()){
		mydata>>A[i++];
	}

	//cout<<"未排序前的序列为："<<endl;                //打印未排序序列
	//for(int i=0;i<NUM;++i){
	//	cout<<A[i]<<"   ";
	//}
	//cout<<endl;

	void qs_book(int A[],int low,int high);
	void qs_basic(int A[],int low,int high);
	void qs_random(int A[],int low,int high);
	void qs_middit(int A[],int low,int high);
	void qs_middit_insert_key(int A[],int low,int high);

	start = clock();

	//qs_book(A,0,NUM-1);                             //算法导论的原始快排写法
	qs_basic(A,0,NUM-1);                               //高分笔记的原始快排写法
	//qs_random(A,0,NUM-1);
	//qs_middit(A,0,NUM-1);
	//qs_middit_insert_key(A,0,NUM-1);
	end = clock();

	//result<<"使用快速排序排好的序列为；"<<endl;        
	//for(int i=0;i<NUM;++i){
	//	result<<A[i]<<"   " ;
	//}
	//result<<endl;

	cout<<"快速排序运行时间为：    "<<end - start<<"ms"<<endl;
	delete[] A;
	mydata.close( );
	result.close( );
	system("pause");
	return 0;
}