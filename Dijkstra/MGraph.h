#include<iostream>
using namespace std;

#define INF 1000000
#define MAXVEX  10                                  //��󶥵���Ŀ
typedef  int VertexType;
typedef float ArcType;

class MGraph{
	private:
		VertexType *vex;
		ArcType **edge;
		int vn;                                              //������Ŀ
		int en;                                              //�ߵ���Ŀ
	public:
		MGraph( );
		~MGraph( );
		void createMGraph( );
		void printMGraph( );

};



