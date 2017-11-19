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

	return i+1;              //���������λ��
} 


int r_p(int A[],int p,int r) {               //Randomized-Partition

	srand((unsigned)time(NULL));
	int i = rand()%(r-p+1)+p;      // ��һ��p=0,r=9,rand()%10 = 0~9���һ���� i = RANDOM(p,r)   ��pΪ�˵ݹ�ʱ��rand()�ķ�Χ����С����p��ʼ
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
	int k = q-p+1;							//����A[p .. q]��Ԫ�صĸ���k
	//cout<<"k = "<<k<<endl;
	if(i == k){                             //the pivot value is the answer
		return A[q];
	}
	else if(i < k){
		return r_s(A,p,q-1,i);
	}
	else{
		return r_s(A,q+1,r,i-k);         //��֪��k��Ԫ��С��A[p .. r]�е�iС��Ԫ�ؼ���A[p .. q],
	}													 //����Ԫ����A[q+1 .. r]�еĵ�i-kС��Ԫ��
}