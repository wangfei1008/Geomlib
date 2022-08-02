
#ifndef        _GEOMEXP_GEOMTYPE_H
#define        _GEOMEXP_GEOMTYPE_H

#if defined(_AFXDLL) || defined(_USRDLL)
#define GEOM_EXP __declspec(dllexport)
#elif defined(_MSC_VER)&&(_MSC_VER<1200)
#define GEOM_EXP __declspec(dllimport)
#else
#define GEOM_EXP
#endif

//Geom Type

//point
typedef struct Geom_Point
{
    int  x;
    int  y;
} Geom_Point;

//line secm
typedef struct Geom_LineSem  
{  
	Geom_Point s;  
	Geom_Point e;   
}Geom_LineSem;  

//line//直线的解析方程 a*x+b*y+c=0  为统一表示，约定 a >= 0  
typedef struct Geom_Line           
{  
	double a;  
	double b;  
	double c;  
}Geom_Line;  

//Circle
typedef struct Geom_Circle
{
	Geom_Point O;
	double r;
}Geom_Circle;

//Rectangle
typedef struct Geom_Rect
{
	double x;
	double y;
	double w;
	double h;
}Geom_Rect;

#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////////////////////////////////////////////////
//㈠ 点的基本运算 
//////////////////////////////////////////////////////////////////////////
//1. 平面上两点之间距离 
GEOM_EXP double Geom_Dot_Dist(Geom_Point p1,Geom_Point p2);

//2. 判断两点是否重合   
GEOM_EXP bool Geom_Dot_Equal(Geom_Point p1,Geom_Point p2);  
           
//3. 矢量叉乘
GEOM_EXP double Geom_Dot_Multiply(Geom_Point sp,Geom_Point ep,Geom_Point op); 
 
// 4. 矢量点乘 
GEOM_EXP double Geom_Dot_Dotmultiply(Geom_Point p1,Geom_Point p2,Geom_Point p0);  
  
// 5. 判断点是否在线段上
GEOM_EXP bool Geom_Dot_Online(Geom_LineSem l,Geom_Point p); 
 
//6. 求一点饶某点旋转后的坐标 
GEOM_EXP Geom_Point Geom_Dot_Rotate(Geom_Point o,double alpha,Geom_Point p); 
 
//7. 求矢量夹角 
GEOM_EXP double Geom_Dot_Angle(Geom_Point o,Geom_Point s,Geom_Point e) ; 

//8.点到平面的距离
GEOM_EXP double Geom_Dot_P2PlaneDist(double x, double y, double z, double a, double b, double c, double d); 

//9.点是否在直线同侧
GEOM_EXP bool Geom_Dot_SameSide(Geom_Point p1,Geom_Point p2, Geom_Line line);

//10.上面这个函数的可以判断P3点在有向线段P1P2(P1指向P2) 的哪一侧 :返回值>0，左侧 ;=0,在直线P1P2上; <0,右侧 . 返回值到绝对值就是△P1P2P3的面积 
GEOM_EXP long  Geom_Dot_TriangleArea(Geom_Point p1, Geom_Point p2, Geom_Point p3);

//////////////////////////////////////////////////////////////////////////
//㈡ 线段及直线的基本运算 
//////////////////////////////////////////////////////////////////////////
//1. 点与线段的关系 
GEOM_EXP double Geom_Line_Relation(Geom_Point p,Geom_LineSem l); 

//2. 求点到线段所在直线垂线的垂足
GEOM_EXP Geom_Point Geom_Line_Perpendicular(Geom_Point p,Geom_LineSem l); 

//3. 点到线段的最近点
GEOM_EXP double Geom_Line_P2LSemDist(Geom_Point p,Geom_LineSem l,Geom_Point &np);
  
//4. 点到线段所在直线的距离
GEOM_EXP double Geom_Line_P2LDist(Geom_Point p,Geom_LineSem l); 
 
//5. 点到折线集的最近距离
GEOM_EXP double Geom_Line_P2PSet(int vcount,Geom_Point Pointset[],Geom_Point p,Geom_Point &q);  
 
//6. 求矢量夹角余弦
GEOM_EXP double Geom_Line_Cosine(Geom_LineSem l1,Geom_LineSem l2);  

//7. 求线段之间的夹角
GEOM_EXP double Geom_Line_LSAngle(Geom_LineSem l1,Geom_LineSem l2);  
  
//8. 判断线段是否相交
//如果线段u和v相交(包括相交在端点处)时，返回true
GEOM_EXP bool Geom_Line_Intersect(Geom_LineSem u,Geom_LineSem v); 
//(线段u和v相交)&&(交点不是双方的端点) 时返回true
GEOM_EXP bool Geom_Line_Intersect_A(Geom_LineSem u,Geom_LineSem v); 
 
//9.判断线段是否相交但不交在端点处 
GEOM_EXP bool Geom_Line_Intersect_l(Geom_LineSem u,Geom_LineSem v); 

//10.求线段所在直线的方程
GEOM_EXP Geom_Line Geom_Line_MakeLine(Geom_Point p1,Geom_Point p2);  

//11.求直线的斜率
GEOM_EXP double Geom_Line_Slope(Geom_Line l);  

//12.求直线的倾斜角 
GEOM_EXP double Geom_Line_Alpha(Geom_Line l);  

//13.求点关于某直线的对称点
GEOM_EXP Geom_Point Geom_Line_Symmetry(Geom_Line l,Geom_Point p);
 
//14.判断两条直线是否相交及求直线交点
GEOM_EXP bool Geom_Line_LIntersect(Geom_Line l1,Geom_Line l2,Geom_Point &p); 

//15.判断线段是否相交，如果相交返回交点
GEOM_EXP bool Geom_Line_Intersection(Geom_LineSem l1,Geom_LineSem l2,Geom_Point &inter);   

//16.镜面反射线
GEOM_EXP void Geom_Line_Reflect(double a1,double b1,double c1,double a2,double b2,double c2,double &a,double &b,double &c);  

//17.线段的左右旋
GEOM_EXP int Geom_Line_Rotat(Geom_LineSem l1,Geom_LineSem l2);  

//18.把点赋值给线段
GEOM_EXP void Geom_Line_PSetLineSem(Geom_Point ps,Geom_Point pe,Geom_LineSem &lineSem);

//////////////////////////////////////////////////////////////////////////
//㈢ 多边形常用算法模块 
//////////////////////////////////////////////////////////////////////////
//1. 判断多边形是否简单多边形   
GEOM_EXP bool Geom_Polygon_IsSimple(int vcount,Geom_Point polygon[]);

//2. 检查多边形顶点的凸凹性  
GEOM_EXP void Geom_Polygon_CheckConvex(int vcount,Geom_Point polygon[],bool bc[]); 

//3. 判断多边形是否凸多边形  
GEOM_EXP bool Geom_Polygon_IsConvex(int vcount,Geom_Point polygon[]);

//4. 求多边形面积
GEOM_EXP double Geom_Polygon_Area(int vcount,Geom_Point polygon[]); 

//5. 判断多边形顶点的排列方向，方法一
GEOM_EXP bool Geom_Polygon_IsConterClock(int vcount,Geom_Point polygon[]); 

//6. 判断多边形顶点的排列方向，方法二   
GEOM_EXP bool Geom_Polygon_IsCcwize(int vcount,Geom_Point polygon[]); 

//7. 射线法判断点是否在多边形内  
GEOM_EXP int Geom_Polygon_PIPoly(int vcount,Geom_Point Polygon[],Geom_Point q);  

//8. 判断点是否在凸多边形内     
GEOM_EXP bool Geom_Polygon_PICPoly(int vcount,Geom_Point polygon[],Geom_Point q);  

//9. 寻找点集的graham算法
GEOM_EXP void Geom_Polygon_GrahamScan(Geom_Point PointSet[],Geom_Point ch[],int n,int &len); 
 
//10.寻找点集凸包的卷包裹法 
GEOM_EXP void Geom_Polygon_ConvexClosure(Geom_Point PointSet[],Geom_Point ch[],int n,int &len);  

//11.判断线段是否在多边形内  
GEOM_EXP bool Geom_Polygon_LineSemIPoly(int vcount,Geom_Point polygon[],Geom_LineSem l);  

//12.求简单多边形的重心
GEOM_EXP Geom_Point Geom_Polygon_CgSimple(int vcount,Geom_Point polygon[]); 
 
//13.求凸多边形的重心
GEOM_EXP Geom_Point Geom_Polygon_GravityCenter(int vcount,Geom_Point polygon[]);
  
//14.求肯定在给定多边形内的一个点
GEOM_EXP Geom_Point Geom_Polygon_FinePInsidePoly(int vcount,Geom_Point polygon[]);

//15.求从多边形外一点出发到该多边形的切线 
GEOM_EXP void Geom_Polygon_PTangent(int vcount,Geom_Point polygon[],Geom_Point p,Geom_Point &rp,Geom_Point &lp);
  
//16.判断多边形的核是否存在  
GEOM_EXP bool Geom_Polygon_CoreExist(int vcount,Geom_Point polygon[],Geom_Point &p); 


//////////////////////////////////////////////////////////////////////////
//㈣ 圆的基本运算 
//////////////////////////////////////////////////////////////////////////
//1 .点是否在圆内 
GEOM_EXP bool Geom_Circle_PIC(Geom_Circle c,Geom_Point p);  

//2 .求不共线的三点所确定的圆
GEOM_EXP bool Geom_Circle_CoC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c);  

//3.判断圆是否在多边形内  
GEOM_EXP bool Geom_Circle_CIPoly(int vcount,Geom_Point polygon[],Geom_Circle c);  

//4.两圆关系
GEOM_EXP int Geom_Circle_2CRelation(Geom_Circle c1,Geom_Circle c2);

//5.判断圆是否在矩形内
GEOM_EXP bool Geom_Circle_CRRelation(Geom_Circle c,Geom_Rect rect);

//6．两圆交点 
GEOM_EXP void  Geom_Circle_2CP(Geom_Circle c1,Geom_Circle c2,Geom_Point &rp1,Geom_Point &rp2); 

//7．两圆公共面积
GEOM_EXP double Geom_Circle_2CArea(Geom_Circle c1,Geom_Circle c2);  

//8. 圆和直线关系 
int Geom_Circle_CLRelation(Geom_Circle c,Geom_Line line,Geom_Point &rp1,Geom_Point &rp2);  

//9. 内切圆  
GEOM_EXP void Geom_Circle_InC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c); 
 
//10. 求切点
GEOM_EXP void Geom_Circle_CutPoint(Geom_Circle c,Geom_Point sp,Geom_Point &rp1,Geom_Point &rp2);  

//////////////////////////////////////////////////////////////////////////
//㈤ 矩形的基本运算  
//////////////////////////////////////////////////////////////////////////
//1.已知矩形三点坐标，求第4点坐标
GEOM_EXP Geom_Point Geom_Rect_Rect4th(Geom_Point a,Geom_Point b,Geom_Point c);

//2.判断二个矩形是否相交，即是否有公共部分，并计算二个矩形框重合面积
GEOM_EXP bool Geom_Rect_2ROPart(Geom_Rect fRect, Geom_Rect sRect, double &overlapArea);

//3.矩形框的面积
GEOM_EXP double Geom_Rect_RArea(Geom_Rect rect);

//4.矩形框的中心
GEOM_EXP Geom_Point Geom_Rect_RCenterP(Geom_Rect rect);

//5.点与矩形框的关系,返回值表示：-1：条件错误（矩形框不存在），0：点在矩形框内，1：点在矩形框上，2：点在矩形框外 
GEOM_EXP int Geom_Rect_PRRelation(Geom_Rect rect,Geom_Point p);

//6.线段与矩形框的关系0：线段在矩形框内，1：线段与矩形框有交点，2：线段在矩形框外 
GEOM_EXP int Geom_Rect_LSRRalation(Geom_Rect rect,Geom_LineSem l);

//7.取矩形框的4条线段，从左上点开始，顺时针为，1，2，3，4号线段
GEOM_EXP void Geom_Rect_RTLS(Geom_Rect rect,Geom_LineSem *ls);

//8.矩形框与多边形的关系,必需四边完整在多边形内才为内部0,内部，1，相交，2，外
GEOM_EXP int Geom_Rect_RPolyRalation(Geom_Rect rect,Geom_Point p[],int vcount);


#ifdef __cplusplus
}
#endif


#endif //_GEOMEXP_GEOMTYPE_H




















