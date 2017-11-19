#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
 int NUM = 1000000;
 int n = NUM/5 +(NUM % 5 != 0 ? 1 : 0);                   //划分的组数,向上取整

int main(){
	//cout<<" n = "<<n<<endl;
	clock_t start,end;
	fstream mydata;
	int i = 0;
	mydata.open("./random.txt");
	int *A;
	A = new int[NUM]( );
	while(!mydata.eof()){
		mydata >> A[i++];              //输入数据
	}

	cout<<endl;
	cout<<"请输入统计量的序号i:"<<endl;
	cin>>i;

	int r_s(int A[],int p,int r,int i);
	int s(int A[],int p,int r,int i);

	start = clock();
	//int j = r_s(A,0,NUM-1,i);
	int j = s(A,0,NUM-1,i);
	end = clock();

	cout<<"第"<<i<<"统计量为："<<j<<endl;
	cout<<"运行时间为："<<end - start<<"ms"<<endl;
	delete[] A;
	mydata.close();
	system("pause");
	return 0;
}