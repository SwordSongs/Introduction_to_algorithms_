#include<iostream>
using namespace std;

int partition(int A[],int low,int high) {
	int tem = A[low];                                         //��pivot��������
	int i = low;
	int j = high;

	while(i != j ){
		while(A[j] > tem && i < j){            //���Ҷ���һ��������Ԫ��С��Ԫ��
			--j;
		}
		if(i < j){                                             //�ҵ�����iλ��Ԫ�ؽ���  
			A[i] = A[j];
			++i;
		}

		while(A[i] < tem && i < j){          //�������һ��������Ԫ�ش��Ԫ��
			++i;
		}

		if(i < j){
		A[j] = A[i];                                         //�ҵ���������Ԫ�ؽ���
		--j;
		}
	}

	A[i] = tem;				                              //i == j��������Ԫ�طŵ���ȷλ��
	return i;                                                       //return pivot's position

}
void qs_basic(int A[],int low,int high) {
	if(low < high){
		int pivot = 0;
		pivot = partition(A,low,high);
		qs_basic(A,low,pivot-1);
		qs_basic(A,pivot+1,high);

	}

}