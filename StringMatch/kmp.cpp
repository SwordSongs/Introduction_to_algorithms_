#include<iostream>
#include<string>
#include<fstream>
#define MAX_SIZE 20    //kmp ģʽP��������
using namespace std;

void prefix(string& P1,int next[]){      //����next����
	int m = P1.length();
	next[0] = 0;                        //next[1] = 0;
	int k = 0;
	for(int q=1;q<m;++q){              //q = 2...m
		while(k>0&&P1[k]!=P1[q]){  
			k = next[k-1];               //����һ�ַ���ƥ��ʱ���ݹ����
		}

		if(P1[k]==P1[q]){            //����һ���ַ�ƥ��ʱ������һ���ַ�����P1[q],next[q] = max{k<q  &&  Pk��Pq}  
			k += 1;                    //���ƥ�䣬��ǰ������+1
		}

		next[q] = k;                   //��while(��һ�ַ���ƥ��)����if(��һ�ַ�ƥ��)�õ�����kֵ
	}

}

void kmp(string& T1,string& P1){
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/StringMatching(ok)/StringMatch/result.txt");
	int count = 0;
	int n = T1.length();
	int m = P1.length();
	int next[MAX_SIZE] = {0};  //��ʼ��next����
	prefix(P1,next);
	int q = 0;

	for(int i=0;i<=n-m+1;++i){              //n-m+1��i���ܳ��ֵ����һ��λ�ã�����ģʽp�ƶ��ᳬ��T�ĳ���
		while(q>0&&P1[q]!=T1[i]){         //next character does not match,i��λ�ò���
			q = next[q-1];
		}

		if(P1[q]==T1[i]){
			q = q+1;                       //next character matches
		}

		if(q==m){                         //is all of P matched?
			//result<<"��Чƫ��sΪ��"<<i-m+1<<endl;
			q = next[q-1];                    //look for the next match,�������p[m+1]���Σ�line36��
			++count;
		}
	}
	result<<endl;
	result<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	cout<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	result.close();
}