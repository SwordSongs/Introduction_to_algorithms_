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
	int next[26] = {0};			//�������ַ�������

	for(int i=0;i<26;++i){		//��ʼ����+1
		next[i] = len_p + 1;
	}

	for(int j=0;j<len_p;++j){           //����P�г��ֹ����ַ���next����
		 next[P1[j]-'A'] = len_p - j;   //���Ǹ���Ϊ�ַ�����β��̾���+1
	}

	int pos = 0;
	while(pos <= len_t-len_p&&pos<=len_t){  //len_t-len_p�����һ��λ�ã������ޱȶԱ�Ҫ
		int i = pos;
		int j;                  //while������õ���һ���ֲ�����j

		for(j=0;j<len_p;++j,++i){

			if(T1[i] != P1[j]){
				pos += next[T1[pos+len_p]-'A'];  //���ֻ��ַ���Ծ
				break;
			}

			if(j == len_p-1){
				//result<<"��Чƫ��sΪ��"<<pos<<endl;     //�����Чƫ��s
				pos  += 1;                           //��ȫƥ�䣬pos����ƶ�һ��λ��
				++count;
			}
			
		}
	}
	result<<endl;
	result<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	cout<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	result.close();
	        
}