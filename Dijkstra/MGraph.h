#include<iostream>
using namespace std;

#define INF 1000000
#define MAXVEX  10                                  //最大顶点数目
typedef  int VertexType;
typedef float ArcType;

class MGraph{
	private:
		VertexType *vex;
		ArcType **edge;
		int vn;                                              //顶点数目
		int en;                                              //边的数目
	public:
		MGraph( );
		~MGraph( );
		void createMGraph( );
		void printMGraph( );

};



