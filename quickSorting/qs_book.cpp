#include<iostream>
using namespace std;
int partition2(int A[], int low, int high) {
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


void qs_book(int A[],int low,int high) {
	if(low < high){
		int pivot = 0;
		pivot = partition2(A,low,high);
		qs_book(A,low,pivot-1);
		qs_book(A,pivot+1,high);

	}
}