#include<iostream>
using namespace std;

#define MAXVEX  10                                  //��󶥵���Ŀ
typedef  int VertexType;
typedef float ArcType;

class MGraph{
	private:
		VertexType *vex;
		ArcType **edge;
		VertexType **path;
		ArcType **dist;
		int vn;                                              //������Ŀ
		int en;                                              //�ߵ���Ŀ
	public:
		MGraph( );
		~MGraph( );
		void createMGraph( );
		void printMGraph( );
		void Floyd( );

};



