#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define C_SIZE 26           //有限字符集长度
#define P_SIZE 20           //模式P的长度限制

void preBmBc(string P,int bmBc[]){
	int m = P.length();
	for(int i=0;i<C_SIZE;++i){
		bmBc[i] = m;            //BmBc是字符到字符串尾的距离，对所有BmBc数组值初始化为m  
	}
//*****************************************************************************
		//cout<<"bmBc数组为："<<endl;
		//for(int i=0;i<C_SIZE;i++){
		//	cout<<bmBc[i]<<"   ";                       //测试
		//}
		//cout<<endl;
//*****************************************************************************

	for(int i=0;i<m;++i){
		bmBc[P[i]-'A'] =  m -1- i; //修改P模式中出现过的字符到字符串尾部的距离值
	}

//*****************************************************************************
		//cout<<"修改后，bmBc数组为："<<endl;
		//for(int i=0;i<C_SIZE;i++){
		//	cout<<bmBc[i]<<"   ";                       //测试
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
}

void suffix(string &P,int *suffix){
		int m = P.length();
		suffix[m-1] = m;                           //m-1位置的suffix值为m
		for(int i=m-2;i>=0;--i){               //对0...m-2的值赋值
			int q = i;
			while(q>=0&&P[q]==P[m-1-i+q]){
				--q;
				suffix[i] = i - q;                      //最大公共后缀长度
			}
		} 

}

void preBmGs(string P,int bmGs[]){
		int suff[P_SIZE] = {0};
		int i = 0, j = 0;
		int m = P.length();
		suffix(P,suff);

		for(;i<m;++i){
			bmGs[i] = m;           //对所有bmGs值初始化为m，情况三
		}
//*****************************************************************************
		//cout<<"suff数组为："<<endl;
		//for(int i=0;i<P_SIZE;i++){
		//	cout<<suff[i]<<"   ";
		//}
		//cout<<endl;

		//cout<<"初始bmGs数组为："<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                   //测试
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
	
		for(i=0;i<=m-2;++i){                           //情况一，模式串中有子串匹配好后缀
					bmGs[m-1-suff[i]] = m-1-i; 
		}
//*****************************************************************************
		//cout<<"考虑情况一修改后，bmGs数组为："<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                 //测试
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
				for(i=m-1;i>=0;--i){
			if(suff[i] == i+1){						//情况二
				for(;j<m-1-i;++j){
					if(bmGs[j] == m ){           //模式串中没有子串匹配好后缀，但是找到最大前缀
						bmGs[j] = m - 1 -i;
					}
				}
			}                  
		}

//*****************************************************************************
		//cout<<"考虑情况二修改后，bmGs数组为："<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                 //测试
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************	
		
 }

int  max(int i,int j){
	return i>=j ? i : j;
}

void bm(string& T,string& P){
	fstream result;
	result.open("D:/My Documents/Visual Studio 2010/Projects/StringMatching(ok)/StringMatch/result.txt");
	int count = 0;

	int bmBc[C_SIZE] = {0};
	int bmGs[P_SIZE] = {0};

	preBmGs(P,bmGs);
	preBmBc(P,bmBc);

	int n = T.length();
	int m = P.length();
	int s = 0;
	int i = 0;

	while(s <= n-m ){
		for( i=m-1;i>=0&&P[i]==T[s+i];--i);          //字符比对；
		if(i<0){
			//result<<"有效偏移s为："<<s<<endl;
			s+=bmGs[0];                                       //三种情况都可以修改bmGs[0],这样适用于T : ABABABA (p : ABA)
			++count;
		}
		else{
			s += max(bmGs[i],bmBc[T[s+i]-'A']-(m-1-i));
		}
		//cout<<"s = "<<endl;
	}
	result<<endl;
	result<<"有效偏移的个数为："<<count<<endl;
	cout<<"有效偏移的个数为："<<count<<endl;
	result.close();
}