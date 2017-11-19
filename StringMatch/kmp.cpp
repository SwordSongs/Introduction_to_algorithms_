#include<iostream>
#include<string>
#include<fstream>
#define MAX_SIZE 20    //kmp 模式P长度限制
using namespace std;

void prefix(string& P1,int next[]){      //计算next数组
	int m = P1.length();
	next[0] = 0;                        //next[1] = 0;
	int k = 0;
	for(int q=1;q<m;++q){              //q = 2...m
		while(k>0&&P1[k]!=P1[q]){  
			k = next[k-1];               //当后一字符不匹配时，递归回退
		}

		if(P1[k]==P1[q]){            //当第一个字符匹配时，看下一个字符，与P1[q],next[q] = max{k<q  &&  Pk】Pq}  
			k += 1;                    //如果匹配，在前面结果上+1
		}

		next[q] = k;                   //将while(后一字符不匹配)或者if(后一字符匹配)得到最终k值
	}

}

void kmp(string& T1,string& P1){
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/StringMatching(ok)/StringMatch/result.txt");
	int count = 0;
	int n = T1.length();
	int m = P1.length();
	int next[MAX_SIZE] = {0};  //初始化next数组
	prefix(P1,next);
	int q = 0;

	for(int i=0;i<=n-m+1;++i){              //n-m+1是i可能出现的最后一个位置，否则模式p移动会超过T的长度
		while(q>0&&P1[q]!=T1[i]){         //next character does not match,i的位置不变
			q = next[q-1];
		}

		if(P1[q]==T1[i]){
			q = q+1;                       //next character matches
		}

		if(q==m){                         //is all of P matched?
			//result<<"有效偏移s为："<<i-m+1<<endl;
			q = next[q-1];                    //look for the next match,避免出现p[m+1]情形（line36）
			++count;
		}
	}
	result<<endl;
	result<<"有效偏移的个数为："<<count<<endl;
	cout<<"有效偏移的个数为："<<count<<endl;
	result.close();
}