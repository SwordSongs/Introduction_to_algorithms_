#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

int main(){

	fstream fstrm;
	string T;
	fstrm.open("./DNA.txt");
	fstrm>>T;
	//cout<<T<<endl;
	string P = "GTGCTGACACATCCA";     //注意"GTGCTGACACATCCA"CGGGCC",“TTTTTTGTT”,"TTTTTTGTTTTTTGTT"BM与KMP，sunday结果不一致

	void sunday(string&,string&);
	void kmp(string&,string&);
	void bm(string&,string&);

	clock_t start,end;
	start = clock();
	sunday(T,P);
	//bm(T,P);
  // kmp(T,P);
	end = clock();
	cout<<"运行时间为："<<end - start<<"ms"<<endl;

	fstrm.close();
	system("pause");
	return 0;
}