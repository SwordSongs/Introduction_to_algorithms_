#include<iostream>
#include<cstdlib>
using namespace std;
extern int NUM;
extern int n;

int partition(int A[], int low, int high,int mid_mid) {          //����λ������λ�����л���
	int pivot = mid_mid;
	int i = low - 1;
	int tem = 0;

	for(int k = low;k<=high;++k){                       //�ҵ�����Ԫ��λ�ò���A[high]����
		if(A[k] == mid_mid){
			//cout<<"k = "<<k<<endl;
			tem = A[high];
			A[high] = A[k];
			A[k] = tem;
			break;
		}
	}

	for(int j = low;j <= high-1;++j){
		if(A[j] <= pivot){
			++i;
			tem = A[i];                                                     //exchange A[i] with A[j]
			A[i] = A[j];
			A[j] = tem;
		}
	}

	tem = A[i+1];          // exchange A[i+1] with A[high]
	A[i+1] = A[high];
	A[high] = tem;

	return i+1;               //return pivot's position
}



int insertSort(int A[],int low,int high) {

	/*for(int i=low;i<=high;++i){
		cout<<A[i]<<" ";
	}
	cout<<endl;*/

	int mid = (low + high)/2;                      //ȡ��

	int i , j;
	int tem = 0;
	for(i=low+1;i<=high;++i){
		tem = A[i];
		for(j=i-1;j>=low&&A[j]>tem;--j){
			A[j+1] = A[j];
		}
		A[j+1] = tem;
	}

	/*for(int i=low;i<=high;++i){
		cout<<A[i]<<" ";
	}
	cout<<endl;*/

	return A[mid];                                                      //������λ��
}

int comp(const void *a,const void *b){
	return *(int *)a-*(int *)b;
}

int mid(int A[],int low,int high) {
	int n = (high-low+1)/5 +((high-low+1) % 5 != 0 ? 1 : 0);                   //���ֵ�����,����ȡ��
	int *mid;
	mid = new int[n]();

	if((high-low+1) % 5 != 0){
		mid[n-1] = insertSort(A,low+((high-low+1)/5)*5,high);      //�����һ�����λ��
	}
	else{
		mid[n-1]=insertSort(A,low,low+4);                        //ȡÿһ�����λ��
		low += 5;
	}


	if((high-low+1)/5 != 0){
		for(int i=0;i<n-1;++i){
			mid[i]=insertSort(A,low,low+4);                        //ȡÿһ�����λ��
			low += 5;
		}
	}

	

	qsort(mid,n,sizeof(mid[0]),comp);                                          //����λ�����򣬿���

	int mid_mid = mid[(n-1)/2];                               //�ҵ���λ������λ��������

	delete[] mid;                                                     //�ͷ�����
	return mid_mid;
	
}

int s(int A[],int p,int r,int i){
	if(p == r){
		return A[p];                          //basic situation : only one element
	}
	
	int mid_mid = mid(A,p,r);
	//cout<<"mid_mid  = "<<mid_mid<<endl;
	int q = partition(A,p,r,mid_mid);
	//cout<<"q = "<<q<<endl;
	int k = q-p+1;                        //����A[p...q]�е�Ԫ�ظ���k��+1Ϊ����Ԫ��
	//cout<<"k = "<<k<<endl;
	if(i == k){
		return A[q];
	}
	else if(i < k){
		return s(A,p,q-1,i);
	}
	else {
		return s(A,q+1,r,i-k);
	}

}