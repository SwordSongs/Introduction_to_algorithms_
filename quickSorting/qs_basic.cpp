#include<iostream>
using namespace std;

int partition(int A[],int low,int high) {
	int tem = A[low];                                         //将pivot保存起来
	int i = low;
	int j = high;

	while(i != j ){
		while(A[j] > tem && i < j){            //从右端找一个比枢轴元素小的元素
			--j;
		}
		if(i < j){                                             //找到后与i位置元素交换  
			A[i] = A[j];
			++i;
		}

		while(A[i] < tem && i < j){          //从左端找一个比枢轴元素大的元素
			++i;
		}

		if(i < j){
		A[j] = A[i];                                         //找到后与枢轴元素交换
		--j;
		}
	}

	A[i] = tem;				                              //i == j，将枢轴元素放到正确位置
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