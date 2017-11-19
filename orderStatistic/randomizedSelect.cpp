#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;

int partition(int A[],int p,int r) {
	int tem = 0;
	int x = A[r];                  //choose pivot element
	int i = p-1;                    
	for(int j=p;j<=r-1;++j){
			if(A[j]<=x){
				++i;
				tem = A[i];     //exchange A[i] and A[j]
				A[i] = A[j];
				A[j] = tem;
			}
	}

	tem = A[i+1];          //exchange A[i+1] and A[r]
	A[i+1] = A[r];
	A[r] = tem;

	return i+1;              //返回枢轴的位置
} 


int r_p(int A[],int p,int r) {               //Randomized-Partition

	srand((unsigned)time(NULL));
	int i = rand()%(r-p+1)+p;      // 第一次p=0,r=9,rand()%10 = 0~9随机一个数 i = RANDOM(p,r)   加p为了递归时，rand()的范围逐渐缩小并从p开始
	int tem = 0;

	tem = A[r];
	A[r] = A[i];								  //exchange A[r] with A[i]        
	A[i] = tem;

	return partition(A,p,r);
}


int r_s(int A[],int p,int r,int i) {
	if(p == r){                     //basic situation : only one element
		return A[p];
	}

	int q = 0;
	q = r_p(A,p,r);						//q =  RANDOMIZED-PARTITION(A,p,r),
	//cout<<"q = " <<q<<endl;
	int k = q-p+1;							//计算A[p .. q]中元素的个数k
	//cout<<"k = "<<k<<endl;
	if(i == k){                             //the pivot value is the answer
		return A[q];
	}
	else if(i < k){
		return r_s(A,p,q-1,i);
	}
	else{
		return r_s(A,q+1,r,i-k);         //已知有k个元素小于A[p .. r]中第i小的元素即：A[p .. q],
	}													 //所找元素是A[q+1 .. r]中的第i-k小的元素
}