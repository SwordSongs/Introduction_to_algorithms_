#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
 int NUM = 1000000;
 int n = NUM/5 +(NUM % 5 != 0 ? 1 : 0);                   //���ֵ�����,����ȡ��

int main(){
	//cout<<" n = "<<n<<endl;
	clock_t start,end;
	fstream mydata;
	int i = 0;
	mydata.open("./random.txt");
	int *A;
	A = new int[NUM]( );
	while(!mydata.eof()){
		mydata >> A[i++];              //��������
	}

	cout<<endl;
	cout<<"������ͳ���������i:"<<endl;
	cin>>i;

	int r_s(int A[],int p,int r,int i);
	int s(int A[],int p,int r,int i);

	start = clock();
	//int j = r_s(A,0,NUM-1,i);
	int j = s(A,0,NUM-1,i);
	end = clock();

	cout<<"��"<<i<<"ͳ����Ϊ��"<<j<<endl;
	cout<<"����ʱ��Ϊ��"<<end - start<<"ms"<<endl;
	delete[] A;
	mydata.close();
	system("pause");
	return 0;
}