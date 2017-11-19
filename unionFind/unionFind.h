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

int root[VN];                       //代表数组
int r[VN];                            //秩数组

typedef struct{
		int start,end;
	}Road;

Road road[EN];



void makeSet(int n) {                    //建立代表数组和秩数组
	for(int i=0;i<n;++i){
		root[i] = i;
		r[i] = 0;
	}
}

//int findSet(int x) {                        //find操作(递归的路径压缩)
//	if(x != root[x]){
//		root[x] = findSet(root[x]);      //路径压缩的查找
//	}
//	return root[x];
//}

int findSet(int x) {

	int r,k,i;
	r = x;
	while( r != root[r]){
		r = root[r];
	}
	k = x;                 //用r标记x的代表
	
	while( root[k] != r ){   //非递归路径压缩
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
		root[fy] = fx;                    //将y并入x集合中
	}
	else{
		root[fx] = fy;
		if(r[fx] == r[fy]){
			r[fy]++;
		}
	}
}