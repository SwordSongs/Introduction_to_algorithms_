#include<iostream>
using namespace std;

#define MAXVEX  10                                  //最大顶点数目
typedef  int VertexType;
typedef float ArcType;

class MGraph{
	private:
		VertexType *vex;
		ArcType **edge;
		VertexType **path;
		ArcType **dist;
		int vn;                                              //顶点数目
		int en;                                              //边的数目
	public:
		MGraph( );
		~MGraph( );
		void createMGraph( );
		void printMGraph( );
		void Floyd( );

};



