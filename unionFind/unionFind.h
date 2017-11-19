#include<iostream>
using namespace std;



//#define VN 9493                          //vchocyc
//#define EN 18951

#define VN  1595446                //uniprot22m
#define EN   3151602

//#define VN   16087295              //uniprot100m
//#define EN   16087293  

//#define VN  25037600              //uniport150m
//#define EN  25037598

int root[VN];                       //��������
int r[VN];                            //������

typedef struct{
		int start,end;
	}Road;

Road road[EN];



void makeSet(int n) {                    //�������������������
	for(int i=0;i<n;++i){
		root[i] = i;
		r[i] = 0;
	}
}

//int findSet(int x) {                        //find����(�ݹ��·��ѹ��)
//	if(x != root[x]){
//		root[x] = findSet(root[x]);      //·��ѹ���Ĳ���
//	}
//	return root[x];
//}

int findSet(int x) {

	int r,k,i;
	r = x;
	while( r != root[r]){
		r = root[r];
	}
	k = x;                 //��r���x�Ĵ���
	
	while( root[k] != r ){   //�ǵݹ�·��ѹ��
		i = root[k];
		root[k] = r;
		k = i;
	}
	return r;

}

void _union(int x ,int y){
	int fx = findSet(x);
	int fy = findSet(y);
	if(fx == fy) return;
	if(r[fx] > r[fy]){
		root[fy] = fx;                    //��y����x������
	}
	else{
		root[fx] = fy;
		if(r[fx] == r[fy]){
			r[fy]++;
		}
	}
}