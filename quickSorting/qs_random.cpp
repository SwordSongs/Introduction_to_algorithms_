#include<iostream>
#include<ctime>
using namespace std;

int partition3(int A[], int low, int high) {
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


int randomized_p(int A[],int low,int high){
	int tem = 0;
	srand((unsigned) time(NULL));
	int i = rand()%(high - low +1)+low;   //确定随机i的位置  %（9-0+1）=%10， 从0...9
	tem = A[high];
	A[high] = A[i];
	A[i] = tem;
	return partition3(A,low,high);
}



void qs_random(int A[],int low,int high) {
	if(low < high){
		int pivot = 0;
		pivot = randomized_p(A,low,high);
		qs_random(A,low,pivot-1);
		qs_random(A,pivot+1,high);

	}
}