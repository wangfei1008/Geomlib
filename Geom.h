
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

//line//ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0  
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
//�� ��Ļ������� 
//////////////////////////////////////////////////////////////////////////
//1. ƽ��������֮����� 
GEOM_EXP double Geom_Dot_Dist(Geom_Point p1,Geom_Point p2);

//2. �ж������Ƿ��غ�   
GEOM_EXP bool Geom_Dot_Equal(Geom_Point p1,Geom_Point p2);  
           
//3. ʸ�����
GEOM_EXP double Geom_Dot_Multiply(Geom_Point sp,Geom_Point ep,Geom_Point op); 
 
// 4. ʸ����� 
GEOM_EXP double Geom_Dot_Dotmultiply(Geom_Point p1,Geom_Point p2,Geom_Point p0);  
  
// 5. �жϵ��Ƿ����߶���
GEOM_EXP bool Geom_Dot_Online(Geom_LineSem l,Geom_Point p); 
 
//6. ��һ����ĳ����ת������� 
GEOM_EXP Geom_Point Geom_Dot_Rotate(Geom_Point o,double alpha,Geom_Point p); 
 
//7. ��ʸ���н� 
GEOM_EXP double Geom_Dot_Angle(Geom_Point o,Geom_Point s,Geom_Point e) ; 

//8.�㵽ƽ��ľ���
GEOM_EXP double Geom_Dot_P2PlaneDist(double x, double y, double z, double a, double b, double c, double d); 

//9.���Ƿ���ֱ��ͬ��
GEOM_EXP bool Geom_Dot_SameSide(Geom_Point p1,Geom_Point p2, Geom_Line line);

//10.������������Ŀ����ж�P3���������߶�P1P2(P1ָ��P2) ����һ�� :����ֵ>0����� ;=0,��ֱ��P1P2��; <0,�Ҳ� . ����ֵ������ֵ���ǡ�P1P2P3����� 
GEOM_EXP long  Geom_Dot_TriangleArea(Geom_Point p1, Geom_Point p2, Geom_Point p3);

//////////////////////////////////////////////////////////////////////////
//�� �߶μ�ֱ�ߵĻ������� 
//////////////////////////////////////////////////////////////////////////
//1. �����߶εĹ�ϵ 
GEOM_EXP double Geom_Line_Relation(Geom_Point p,Geom_LineSem l); 

//2. ��㵽�߶�����ֱ�ߴ��ߵĴ���
GEOM_EXP Geom_Point Geom_Line_Perpendicular(Geom_Point p,Geom_LineSem l); 

//3. �㵽�߶ε������
GEOM_EXP double Geom_Line_P2LSemDist(Geom_Point p,Geom_LineSem l,Geom_Point &np);
  
//4. �㵽�߶�����ֱ�ߵľ���
GEOM_EXP double Geom_Line_P2LDist(Geom_Point p,Geom_LineSem l); 
 
//5. �㵽���߼����������
GEOM_EXP double Geom_Line_P2PSet(int vcount,Geom_Point Pointset[],Geom_Point p,Geom_Point &q);  
 
//6. ��ʸ���н�����
GEOM_EXP double Geom_Line_Cosine(Geom_LineSem l1,Geom_LineSem l2);  

//7. ���߶�֮��ļн�
GEOM_EXP double Geom_Line_LSAngle(Geom_LineSem l1,Geom_LineSem l2);  
  
//8. �ж��߶��Ƿ��ཻ
//����߶�u��v�ཻ(�����ཻ�ڶ˵㴦)ʱ������true
GEOM_EXP bool Geom_Line_Intersect(Geom_LineSem u,Geom_LineSem v); 
//(�߶�u��v�ཻ)&&(���㲻��˫���Ķ˵�) ʱ����true
GEOM_EXP bool Geom_Line_Intersect_A(Geom_LineSem u,Geom_LineSem v); 
 
//9.�ж��߶��Ƿ��ཻ�������ڶ˵㴦 
GEOM_EXP bool Geom_Line_Intersect_l(Geom_LineSem u,Geom_LineSem v); 

//10.���߶�����ֱ�ߵķ���
GEOM_EXP Geom_Line Geom_Line_MakeLine(Geom_Point p1,Geom_Point p2);  

//11.��ֱ�ߵ�б��
GEOM_EXP double Geom_Line_Slope(Geom_Line l);  

//12.��ֱ�ߵ���б�� 
GEOM_EXP double Geom_Line_Alpha(Geom_Line l);  

//13.������ĳֱ�ߵĶԳƵ�
GEOM_EXP Geom_Point Geom_Line_Symmetry(Geom_Line l,Geom_Point p);
 
//14.�ж�����ֱ���Ƿ��ཻ����ֱ�߽���
GEOM_EXP bool Geom_Line_LIntersect(Geom_Line l1,Geom_Line l2,Geom_Point &p); 

//15.�ж��߶��Ƿ��ཻ������ཻ���ؽ���
GEOM_EXP bool Geom_Line_Intersection(Geom_LineSem l1,Geom_LineSem l2,Geom_Point &inter);   

//16.���淴����
GEOM_EXP void Geom_Line_Reflect(double a1,double b1,double c1,double a2,double b2,double c2,double &a,double &b,double &c);  

//17.�߶ε�������
GEOM_EXP int Geom_Line_Rotat(Geom_LineSem l1,Geom_LineSem l2);  

//18.�ѵ㸳ֵ���߶�
GEOM_EXP void Geom_Line_PSetLineSem(Geom_Point ps,Geom_Point pe,Geom_LineSem &lineSem);

//////////////////////////////////////////////////////////////////////////
//�� ����γ����㷨ģ�� 
//////////////////////////////////////////////////////////////////////////
//1. �ж϶�����Ƿ�򵥶����   
GEOM_EXP bool Geom_Polygon_IsSimple(int vcount,Geom_Point polygon[]);

//2. ������ζ����͹����  
GEOM_EXP void Geom_Polygon_CheckConvex(int vcount,Geom_Point polygon[],bool bc[]); 

//3. �ж϶�����Ƿ�͹�����  
GEOM_EXP bool Geom_Polygon_IsConvex(int vcount,Geom_Point polygon[]);

//4. ���������
GEOM_EXP double Geom_Polygon_Area(int vcount,Geom_Point polygon[]); 

//5. �ж϶���ζ�������з��򣬷���һ
GEOM_EXP bool Geom_Polygon_IsConterClock(int vcount,Geom_Point polygon[]); 

//6. �ж϶���ζ�������з��򣬷�����   
GEOM_EXP bool Geom_Polygon_IsCcwize(int vcount,Geom_Point polygon[]); 

//7. ���߷��жϵ��Ƿ��ڶ������  
GEOM_EXP int Geom_Polygon_PIPoly(int vcount,Geom_Point Polygon[],Geom_Point q);  

//8. �жϵ��Ƿ���͹�������     
GEOM_EXP bool Geom_Polygon_PICPoly(int vcount,Geom_Point polygon[],Geom_Point q);  

//9. Ѱ�ҵ㼯��graham�㷨
GEOM_EXP void Geom_Polygon_GrahamScan(Geom_Point PointSet[],Geom_Point ch[],int n,int &len); 
 
//10.Ѱ�ҵ㼯͹���ľ������ 
GEOM_EXP void Geom_Polygon_ConvexClosure(Geom_Point PointSet[],Geom_Point ch[],int n,int &len);  

//11.�ж��߶��Ƿ��ڶ������  
GEOM_EXP bool Geom_Polygon_LineSemIPoly(int vcount,Geom_Point polygon[],Geom_LineSem l);  

//12.��򵥶���ε�����
GEOM_EXP Geom_Point Geom_Polygon_CgSimple(int vcount,Geom_Point polygon[]); 
 
//13.��͹����ε�����
GEOM_EXP Geom_Point Geom_Polygon_GravityCenter(int vcount,Geom_Point polygon[]);
  
//14.��϶��ڸ���������ڵ�һ����
GEOM_EXP Geom_Point Geom_Polygon_FinePInsidePoly(int vcount,Geom_Point polygon[]);

//15.��Ӷ������һ��������ö���ε����� 
GEOM_EXP void Geom_Polygon_PTangent(int vcount,Geom_Point polygon[],Geom_Point p,Geom_Point &rp,Geom_Point &lp);
  
//16.�ж϶���εĺ��Ƿ����  
GEOM_EXP bool Geom_Polygon_CoreExist(int vcount,Geom_Point polygon[],Geom_Point &p); 


//////////////////////////////////////////////////////////////////////////
//�� Բ�Ļ������� 
//////////////////////////////////////////////////////////////////////////
//1 .���Ƿ���Բ�� 
GEOM_EXP bool Geom_Circle_PIC(Geom_Circle c,Geom_Point p);  

//2 .�󲻹��ߵ�������ȷ����Բ
GEOM_EXP bool Geom_Circle_CoC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c);  

//3.�ж�Բ�Ƿ��ڶ������  
GEOM_EXP bool Geom_Circle_CIPoly(int vcount,Geom_Point polygon[],Geom_Circle c);  

//4.��Բ��ϵ
GEOM_EXP int Geom_Circle_2CRelation(Geom_Circle c1,Geom_Circle c2);

//5.�ж�Բ�Ƿ��ھ�����
GEOM_EXP bool Geom_Circle_CRRelation(Geom_Circle c,Geom_Rect rect);

//6����Բ���� 
GEOM_EXP void  Geom_Circle_2CP(Geom_Circle c1,Geom_Circle c2,Geom_Point &rp1,Geom_Point &rp2); 

//7����Բ�������
GEOM_EXP double Geom_Circle_2CArea(Geom_Circle c1,Geom_Circle c2);  

//8. Բ��ֱ�߹�ϵ 
int Geom_Circle_CLRelation(Geom_Circle c,Geom_Line line,Geom_Point &rp1,Geom_Point &rp2);  

//9. ����Բ  
GEOM_EXP void Geom_Circle_InC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c); 
 
//10. ���е�
GEOM_EXP void Geom_Circle_CutPoint(Geom_Circle c,Geom_Point sp,Geom_Point &rp1,Geom_Point &rp2);  

//////////////////////////////////////////////////////////////////////////
//�� ���εĻ�������  
//////////////////////////////////////////////////////////////////////////
//1.��֪�����������꣬���4������
GEOM_EXP Geom_Point Geom_Rect_Rect4th(Geom_Point a,Geom_Point b,Geom_Point c);

//2.�ж϶��������Ƿ��ཻ�����Ƿ��й������֣�������������ο��غ����
GEOM_EXP bool Geom_Rect_2ROPart(Geom_Rect fRect, Geom_Rect sRect, double &overlapArea);

//3.���ο�����
GEOM_EXP double Geom_Rect_RArea(Geom_Rect rect);

//4.���ο������
GEOM_EXP Geom_Point Geom_Rect_RCenterP(Geom_Rect rect);

//5.������ο�Ĺ�ϵ,����ֵ��ʾ��-1���������󣨾��ο򲻴��ڣ���0�����ھ��ο��ڣ�1�����ھ��ο��ϣ�2�����ھ��ο��� 
GEOM_EXP int Geom_Rect_PRRelation(Geom_Rect rect,Geom_Point p);

//6.�߶�����ο�Ĺ�ϵ0���߶��ھ��ο��ڣ�1���߶�����ο��н��㣬2���߶��ھ��ο��� 
GEOM_EXP int Geom_Rect_LSRRalation(Geom_Rect rect,Geom_LineSem l);

//7.ȡ���ο��4���߶Σ������ϵ㿪ʼ��˳ʱ��Ϊ��1��2��3��4���߶�
GEOM_EXP void Geom_Rect_RTLS(Geom_Rect rect,Geom_LineSem *ls);

//8.���ο������εĹ�ϵ,�����ı������ڶ�����ڲ�Ϊ�ڲ�0,�ڲ���1���ཻ��2����
GEOM_EXP int Geom_Rect_RPolyRalation(Geom_Rect rect,Geom_Point p[],int vcount);


#ifdef __cplusplus
}
#endif


#endif //_GEOMEXP_GEOMTYPE_H




















