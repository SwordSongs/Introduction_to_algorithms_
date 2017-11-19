#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define C_SIZE 26           //�����ַ�������
#define P_SIZE 20           //ģʽP�ĳ�������

void preBmBc(string P,int bmBc[]){
	int m = P.length();
	for(int i=0;i<C_SIZE;++i){
		bmBc[i] = m;            //BmBc���ַ����ַ���β�ľ��룬������BmBc����ֵ��ʼ��Ϊm  
	}
//*****************************************************************************
		//cout<<"bmBc����Ϊ��"<<endl;
		//for(int i=0;i<C_SIZE;i++){
		//	cout<<bmBc[i]<<"   ";                       //����
		//}
		//cout<<endl;
//*****************************************************************************

	for(int i=0;i<m;++i){
		bmBc[P[i]-'A'] =  m -1- i; //�޸�Pģʽ�г��ֹ����ַ����ַ���β���ľ���ֵ
	}

//*****************************************************************************
		//cout<<"�޸ĺ�bmBc����Ϊ��"<<endl;
		//for(int i=0;i<C_SIZE;i++){
		//	cout<<bmBc[i]<<"   ";                       //����
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
}

void suffix(string &P,int *suffix){
		int m = P.length();
		suffix[m-1] = m;                           //m-1λ�õ�suffixֵΪm
		for(int i=m-2;i>=0;--i){               //��0...m-2��ֵ��ֵ
			int q = i;
			while(q>=0&&P[q]==P[m-1-i+q]){
				--q;
				suffix[i] = i - q;                      //��󹫹���׺����
			}
		} 

}

void preBmGs(string P,int bmGs[]){
		int suff[P_SIZE] = {0};
		int i = 0, j = 0;
		int m = P.length();
		suffix(P,suff);

		for(;i<m;++i){
			bmGs[i] = m;           //������bmGsֵ��ʼ��Ϊm�������
		}
//*****************************************************************************
		//cout<<"suff����Ϊ��"<<endl;
		//for(int i=0;i<P_SIZE;i++){
		//	cout<<suff[i]<<"   ";
		//}
		//cout<<endl;

		//cout<<"��ʼbmGs����Ϊ��"<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                   //����
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
	
		for(i=0;i<=m-2;++i){                           //���һ��ģʽ�������Ӵ�ƥ��ú�׺
					bmGs[m-1-suff[i]] = m-1-i; 
		}
//*****************************************************************************
		//cout<<"�������һ�޸ĺ�bmGs����Ϊ��"<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                 //����
		//}
		//cout<<endl;
		//system("pause");
//*****************************************************************************
				for(i=m-1;i>=0;--i){
			if(suff[i] == i+1){						//�����
				for(;j<m-1-i;++j){
					if(bmGs[j] == m ){           //ģʽ����û���Ӵ�ƥ��ú�׺�������ҵ����ǰ׺
						bmGs[j] = m - 1 -i;
					}
				}
			}                  
		}

//*****************************************************************************
		//cout<<"����������޸ĺ�bmGs����Ϊ��"<<endl;
		//for(int i=0;i<m;++i){
		//	cout<<bmGs[i]<<"   ";                 //����
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
		for( i=m-1;i>=0&&P[i]==T[s+i];--i);          //�ַ��ȶԣ�
		if(i<0){
			//result<<"��Чƫ��sΪ��"<<s<<endl;
			s+=bmGs[0];                                       //��������������޸�bmGs[0],����������T : ABABABA (p : ABA)
			++count;
		}
		else{
			s += max(bmGs[i],bmBc[T[s+i]-'A']-(m-1-i));
		}
		//cout<<"s = "<<endl;
	}
	result<<endl;
	result<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	cout<<"��Чƫ�Ƶĸ���Ϊ��"<<count<<endl;
	result.close();
}