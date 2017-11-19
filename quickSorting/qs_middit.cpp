#include<iostream>
using namespace std;

int partition4(int A[],int low,int high){
	int pivot = A[high];
	int i = low - 1;
	int tem = 0;
	for(int j = low;j <= high-1;++j){
		if(A[j] <= pivot){
			++i;
			tem = A[i];         //exchange A[i] with A[j]
			A[i] = A[j];
			A[j] = tem;
		}
	}

	tem = A[i+1];          // exchange A[i+1] with A[high]
	A[i+1] = A[high];
	A[high] = tem;

	return i+1;               //return pivot's position
}

int middit(int A[],int low,int high){
	int tem = 0;
	int mid = (low + high)/2;
	if(A[low] > A[mid] ){                   //给三个数排序
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
	tem = A[high];
	A[high] = A[mid];                //将三数取中者放到partition方法取枢轴的位置
	A[mid] = tem;
	return partition4(A,low,high);
}


void qs_middit(int A[],int low,int high) {
	if(low < high){
		int pivot = 0;
		pivot =middit(A,low,high); 
		qs_middit(A,low,pivot-1);
		qs_middit(A,pivot+1,high);
	}
}