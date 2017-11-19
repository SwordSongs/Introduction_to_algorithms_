#include<iostream>
using namespace std;
int leftLen = 0;
int rightLen = 0;

int partition5(int A[],int low,int high){
	int tem = A[low];                                         //将pivot保存起来
	int tem1 = 0;
	int i = low;
	int j = high;

	int left = low;
	int right = high;

	while(i != j ){
		while(A[j] > tem && i < j){            //从右端找一个比枢轴元素小的元素
			if(A[j] == tem){                          //处理相等元素,为了防止过程中打乱，先把相等元素放在序列两端
				tem1 = A[j];
				A[j] = A[right];
				A[right] = tem1;
				--right;
				++rightLen;
			}
			--j;
		}
		if(i < j){                                             //找到后与i位置元素交换  
			A[i] = A[j];
			++i;
		}

		while(A[i] < tem && i < j){          //从左端找一个比枢轴元素大的元素
			if(A[i] == tem){                             //处理相等元素
				tem1 = A[i];
				A[i] = A[left];
				A[left] = tem1;
				++left;
				++leftLen;
			}
			++i;
		}

		if(i < j){
		A[j] = A[i];                                         //找到后与枢轴元素交换
		--j;
		}
	}

	A[i] = tem;				                              //i == j，将枢轴元素放到正确位置
	/******************************************************************/
	//将与枢轴元素相等的元素移动到枢轴的周围
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
	tem = A[low];
	A[low] = A[mid];                //将三数取中者放到partition方法取枢轴的位置
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
			if(high-low+1<=10){                         //序列长度小于10，调用插入排序
				insertSort(A,low,high);
			}
			else{                                                        //否则，快速排序
				int pivot = 0;
				pivot =middit1(A,low,high); 
				qs_middit_insert_key(A,low,pivot-1-leftLen);
				qs_middit_insert_key(A,pivot+1+rightLen,high);
			}
	}
}