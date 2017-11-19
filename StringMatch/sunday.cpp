#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void sunday(string& T1,string& P1){
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/StringMatching(ok)/StringMatch/result.txt");
	int count = 0;
	int len_t = T1.length();
	int len_p = P1.length();
	int next[26] = {0};			//对有限字符集长度

	for(int i=0;i<26;++i){		//初始化Δ+1
		next[i] = len_p + 1;
	}

	for(int j=0;j<len_p;++j){           //更改P中出现过的字符的next数组
		 next[P1[j]-'A'] = len_p - j;   //覆盖更改为字符到串尾最短距离+1
	}

	int pos = 0;
	while(pos <= len_t-len_p&&pos<=len_t){  //len_t-len_p是最后一个位置，过界无比对必要
		int i = pos;
		int j;                  //while语句中用的是一个局部变量j

		for(j=0;j<len_p;++j,++i){

			if(T1[i] != P1[j]){
				pos += next[T1[pos+len_p]-'A'];  //出现坏字符跳跃
				break;
			}

			if(j == len_p-1){
				//result<<"有效偏移s为："<<pos<<endl;     //输出有效偏移s
				pos  += 1;                           //完全匹配，pos向后移动一个位置
				++count;
			}
			
		}
	}
	result<<endl;
	result<<"有效偏移的个数为："<<count<<endl;
	cout<<"有效偏移的个数为："<<count<<endl;
	result.close();
	        
}