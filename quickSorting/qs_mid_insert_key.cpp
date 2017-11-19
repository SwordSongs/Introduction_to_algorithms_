#include<iostream>
using namespace std;
int leftLen = 0;
int rightLen = 0;

int partition5(int A[],int low,int high){
	int tem = A[low];                                         //��pivot��������
	int tem1 = 0;
	int i = low;
	int j = high;

	int left = low;
	int right = high;

	while(i != j ){
		while(A[j] > tem && i < j){            //���Ҷ���һ��������Ԫ��С��Ԫ��
			if(A[j] == tem){                          //�������Ԫ��,Ϊ�˷�ֹ�����д��ң��Ȱ����Ԫ�ط�����������
				tem1 = A[j];
				A[j] = A[right];
				A[right] = tem1;
				--right;
				++rightLen;
			}
			--j;
		}
		if(i < j){                                             //�ҵ�����iλ��Ԫ�ؽ���  
			A[i] = A[j];
			++i;
		}

		while(A[i] < tem && i < j){          //�������һ��������Ԫ�ش��Ԫ��
			if(A[i] == tem){                             //�������Ԫ��
				tem1 = A[i];
				A[i] = A[left];
				A[left] = tem1;
				++left;
				++leftLen;
			}
			++i;
		}

		if(i < j){
		A[j] = A[i];                                         //�ҵ���������Ԫ�ؽ���
		--j;
		}
	}

	A[i] = tem;				                              //i == j��������Ԫ�طŵ���ȷλ��
	/******************************************************************/
	//��������Ԫ����ȵ�Ԫ���ƶ����������Χ
	int a = i-1;
	int b = low;

	while(b < left && A[a] != tem){
		tem1 = A[a];
		A[a] = A[b];
		A[b] = tem1;
		--a;
		++b;
	}

	a = i+1;
	b = high;

	while(b > right && A[a] != tem ){
		tem1 = A[a];
		A[a] = A[b];
		A[b] = tem1;
		++a;
		--b;
	}
	/*************************************************/
	return i;                                                       //return pivot's position
}

int middit1(int A[],int low,int high){
	int tem = 0;
	int mid = (low + high)/2;
	if(A[low] > A[mid] ){                   //������������
		tem = A[low];
		A[low] = A[mid];
		A[mid] = tem;
	}
	if(A[mid] > A[high]){                  
		tem = A[mid];
		A[mid] = A[high];
		A[high] = tem;
	}
	if(A[low] > A[mid]){
		tem = A[low];
		A[low] = A[mid];
		A[mid] = tem;
	}
	tem = A[low];
	A[low] = A[mid];                //������ȡ���߷ŵ�partition����ȡ�����λ��
	A[mid] = tem;
	return partition5(A,low,high);
}

void insertSort(int A[],int low,int high) {
	int i , j;
	int tem = 0;
	for(j=low+1;j<=high;++j){
		tem = A[j];
		for(i=j-1;i>=0&&A[i]>tem;--i){
			A[i+1] = A[i];
		}
		A[i+1] = tem;
	}

}

void qs_middit_insert_key(int A[],int low,int high) {
	if(low < high){
			if(high-low+1<=10){                         //���г���С��10�����ò�������
				insertSort(A,low,high);
			}
			else{                                                        //���򣬿�������
				int pivot = 0;
				pivot =middit1(A,low,high); 
				qs_middit_insert_key(A,low,pivot-1-leftLen);
				qs_middit_insert_key(A,pivot+1+rightLen,high);
			}
	}
}