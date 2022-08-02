 /************************************************************************/
/*㈡ 线段及直线的基本运算  
 1. 点与线段的关系 3  
 2. 求点到线段所在直线垂线的垂足 4  
 3. 点到线段的最近点 4  
 4. 点到线段所在直线的距离 4  
 5. 点到折线集的最近距离 4   
 7. 求矢量夹角余弦 5  
 8. 求线段之间的夹角 5  
 9. 判断线段是否相交 6  
 10.判断线段是否相交但不交在端点处 6  
 11.求线段所在直线的方程 6  
 12.求直线的斜率 7  
 13.求直线的倾斜角 7  
 14.求点关于某直线的对称点 7  
 15.判断两条直线是否相交及求直线交点 7  
 16.判断线段是否相交，如果相交返回交点 7
 16.镜面反射线  
 17.线段的左右旋
 18.点赋值到线段
*/
 /************************************************************************/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/*****************************\  
  *                             *  
  *      线段及直线的基本运算   *  
  *                             *  
\*****************************/  
 
/* 判断点与线段的关系,用途很广泛  
本函数是根据下面的公式写的，P是点C到线段AB所在直线的垂足  
 
                AC dot AB  
        r =     ---------  
                 ||AB||^2  
             (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)  
          = -------------------------------  
                          L^2  
 
    r has the following meaning:  
 
        r=0      P = A  
        r=1      P = B  
        r<0		 P is on the backward extension of AB  
		r>1      P is on the forward extension of AB  
        0<r<1	 P is interior to AB  
*/  
double Geom_Line_Relation(Geom_Point p,Geom_LineSem l)  
{  
	Geom_LineSem tl;  
	tl.s=l.s;  
	tl.e=p;  
	return Geom_Dot_Dotmultiply(tl.e,l.e,l.s)/(Geom_Dot_Dist(l.s,l.e)*Geom_Dot_Dist(l.s,l.e));  
}  
// 求点C到线段AB所在直线的垂足 P  
Geom_Point Geom_Line_Perpendicular(Geom_Point p,Geom_LineSem l)  
{  
	double r=Geom_Line_Relation(p,l);  
	Geom_Point tp;  
	tp.x=(long)(l.s.x+r*(l.e.x-l.s.x));  
	tp.y=(long)(l.s.y+r*(l.e.y-l.s.y));  
	return tp;  
}  
/* 求点p到线段l的最短距离,并返回线段上距该点最近的点np  
注意：np是线段l上到点p最近的点，不一定是垂足 */  
double Geom_Line_P2LSemDist(Geom_Point p,Geom_LineSem l,Geom_Point &np)  
{  
	double r=Geom_Line_Relation(p,l);  
	if(r<0)  
	{  
		np=l.s;  
		return Geom_Dot_Dist(p,l.s);  
	}  
	if(r>1)  
	{  
		np=l.e;  
		return Geom_Dot_Dist(p,l.e);  
	}  
	np=Geom_Line_Perpendicular(p,l);  
	return Geom_Dot_Dist(p,np);  
}  
// 求点p到线段l所在直线的距离,请注意本函数与上个函数的区别   
double Geom_Line_P2LDist(Geom_Point p,Geom_LineSem l)  
{  
	return fabs(Geom_Dot_Multiply(p,l.e,l.s))/Geom_Dot_Dist(l.s,l.e);  
}  
/* 计算点到折线集的最近距离,并返回最近点.  
注意：调用的是ptoLineSem()函数 */  
double Geom_Line_P2PSet(int vcount,Geom_Point Pointset[],Geom_Point p,Geom_Point &q)  
{  
	int i;  
	double cd=double(INF),td;  
	Geom_LineSem l;  
	Geom_Point tq,cq;  
 
	for(i=0;i<vcount-1;i++)  
	{  
		l.s=Pointset[i];  
 
		l.e=Pointset[i+1];  
		td=Geom_Line_P2LSemDist(p,l,tq);  
		if(td<cd)  
		{  
			cd=td;  
			cq=tq;  
		}  
	}  
	q=cq;  
	return cd;  
}  

/* 判断圆是否在多边形内.ptoLineSem()函数的应用2 */  
/**
bool CircleInsidePolygon(int vcount,Point center,double radius,Point polygon[])  
{  
	Point q;  
	double d;  
	q.x=0;  
	q.y=0;  
	d=ptoPointset(vcount,polygon,center,q);  
	if(d<radius||fabs(d-radius)<EP)  
		return true;  
	else  
		return false;  
}  */
/* 返回两个矢量l1和l2的夹角的余弦(-1 --- 1)注意：如果想从余弦求夹角的话，注意反余弦函数的定义域是从 0到pi */  
double Geom_Line_Cosine(Geom_LineSem l1,Geom_LineSem l2)  
{  
	return (((l1.e.x-l1.s.x)*(l2.e.x-l2.s.x) +  
	(l1.e.y-l1.s.y)*(l2.e.y-l2.s.y))/(Geom_Dot_Dist(l1.e,l1.s)*Geom_Dot_Dist(l2.e,l2.s)));  
}  
// 返回线段l1与l2之间的夹角 单位：弧度 范围(-pi，pi)  
double Geom_Line_LSAngle(Geom_LineSem l1,Geom_LineSem l2)  
{  
	Geom_Point o,s,e;  
	o.x=o.y=0;  
	s.x=l1.e.x-l1.s.x;  
	s.y=l1.e.y-l1.s.y;  
	e.x=l2.e.x-l2.s.x;  
	e.y=l2.e.y-l2.s.y;  
	return Geom_Dot_Angle(o,s,e);  
}  
// 如果线段u和v相交(包括相交在端点处)时，返回true  
// 
//判断P1P2跨立Q1Q2的依据是：( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) >= 0。 
//判断Q1Q2跨立P1P2的依据是：( Q1 - P1 ) × ( P2 - P1 ) * ( P2 - P1 ) × ( Q2 - P1 ) >= 0。 
bool Geom_Line_Intersect(Geom_LineSem u,Geom_LineSem v)  
{  
	return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //排斥实验  
			(max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&  
			(max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&  
			(max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&  
			(Geom_Dot_Multiply(v.s,u.e,u.s)*Geom_Dot_Multiply(u.e,v.e,u.s)>=0)&&         //跨立实验  
			(Geom_Dot_Multiply(u.s,v.e,v.s)*Geom_Dot_Multiply(v.e,u.e,v.s)>=0));  
}  
//  (线段u和v相交)&&(交点不是双方的端点) 时返回true     
bool Geom_Line_Intersect_A(Geom_LineSem u,Geom_LineSem v)  
{  
	return	((Geom_Line_Intersect(u,v))&&  
			(!Geom_Dot_Online(u,v.s))&&  
			(!Geom_Dot_Online(u,v.e))&&  
			(!Geom_Dot_Online(v,u.e))&&  
			(!Geom_Dot_Online(v,u.s)));  
}  
// 线段v所在直线与线段u相交时返回true；方法：判断线段u是否跨立线段v   
bool Geom_Line_Intersect_l(Geom_LineSem u,Geom_LineSem v)  
{  
	return Geom_Dot_Multiply(u.s,v.e,v.s)*Geom_Dot_Multiply(v.e,u.e,v.s)>=0;  
}  
// 根据已知两点坐标，求过这两点的直线解析方程： a*x+b*y+c = 0  (a >= 0)   
Geom_Line Geom_Line_MakeLine(Geom_Point p1,Geom_Point p2)  
{  
	Geom_Line tl;  
	int sign = 1;  
	tl.a=p2.y-p1.y;  
	if(tl.a<0)  
	{  
		sign = -1;  
		tl.a=sign*tl.a;  
	}  
	tl.b=sign*(p1.x-p2.x);  
	tl.c=sign*(p1.y*p2.x-p1.x*p2.y);  
	return tl;  
}  
// 根据直线解析方程返回直线的斜率k,水平线返回 0,竖直线返回 1e200  
double Geom_Line_Slope(Geom_Line l)  
{  
	if(fabs(l.a) < 1e-20) 
		return 0;  
	if(fabs(l.b) < 1e-20) 
		return INF;  
	return -(l.a/l.b);  
}  
// 返回直线的倾斜角alpha ( 0 - pi)  
double Geom_Line_Alpha(Geom_Line l)  
{  
	if(fabs(l.a)< EP) 
		return 0;  
	if(fabs(l.b)< EP) 
		return PI/2;  
	double k=Geom_Line_Slope(l);  
	if(k>0)  
		return atan(k);  
	else  
		return PI+atan(k);  
}  
// 求点p关于直线l的对称点   
Geom_Point Geom_Line_Symmetry(Geom_Line l,Geom_Point p)  
{  
   Geom_Point tp;  
   tp.x=(long)(((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b));  
   tp.y=(long)(((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b));  
   return tp;  
}  
// 如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)相交，返回true，且返回交点p   
bool Geom_Line_LIntersect(Geom_Line l1,Geom_Line l2,Geom_Point &p) // 是 L1，L2  
{  
	double d=l1.a*l2.b-l2.a*l1.b;  
	if(fabs(d)<EP) // 不相交  
		return false;  
	p.x = (long)((l2.c*l1.b-l1.c*l2.b)/d);  
	p.y = (long)((l2.a*l1.c-l1.a*l2.c)/d);  
	return true;  
}  
// 如果线段l1和l2相交，返回true且交点由(inter)返回，否则返回false  
bool Geom_Line_Intersection(Geom_LineSem l1,Geom_LineSem l2,Geom_Point &inter)  
{  
	Geom_Line ll1,ll2;  
	ll1=Geom_Line_MakeLine(l1.s,l1.e);  
	ll2=Geom_Line_MakeLine(l2.s,l2.e);  
	if(Geom_Line_LIntersect(ll1,ll2,inter))  
		return Geom_Dot_Online(l1,inter);  
	else  
		return false;  
}  
 
//镜面反射线： 
// 已知入射线、镜面，求反射线。  
// a1,b1,c1为镜面直线方程(a1 x + b1 y + c1 = 0 ,下同)系数;   
//a2,b2,c2为入射光直线方程系数;   
//a,b,c为反射光直线方程系数.  
// 光是有方向的，使用时注意：入射光向量:<-b2,a2>；反射光向量:<b,-a>.  
// 不要忘记结果中可能会有"negative zeros"  
void Geom_Line_Reflect(double a1,double b1,double c1,double a2,double b2,double c2,double &a,double &b,double &c)  
{  
	double n,m;  
	double tpb,tpa;  
	tpb=b1*b2+a1*a2;  
	tpa=a2*b1-a1*b2;  
	m=(tpb*b1+tpa*a1)/(b1*b1+a1*a1);  
	n=(tpa*b1-tpb*a1)/(b1*b1+a1*a1);  
	if(fabs(a1*b2-a2*b1)<1e-20)  
	{  
		a=a2;b=b2;c=c2;  
		return;  
	}  
	double xx,yy; //(xx,yy)是入射线与镜面的交点。  
	xx=(b1*c2-b2*c1)/(a1*b2-a2*b1);  
	yy=(a2*c1-a1*c2)/(a1*b2-a2*b1);  
	a=n;  
	b=-m;  
	c=m*yy-xx*n;  
}  

//线段的左右旋：  
/* l2在l1的左/右方向（l1为基准线）  
返回	0	： 重合；  
返回	1	： 右旋；  
返回	–1 ： 左旋；  
*/  
int Geom_Line_Rotat(Geom_LineSem l1,Geom_LineSem l2)  
{  
	double dx1,dx2,dy1,dy2;  
	dx1=l1.s.x-l1.e.x;  
	dy1=l1.s.y-l1.e.y;  
	dx2=l2.s.x-l2.e.x;  
	dy2=l2.s.y-l2.e.y;  
	
	double d;  
	d=dx1*dy2-dx2*dy1;  
	if(d==0)  
		return 0;  
	else if(d>0)  
		return -1;  
	else  
		return 1;  
}

//把点赋值给线段
void Geom_Line_PSetLineSem(Geom_Point ps,Geom_Point pe,Geom_LineSem &lineSem)
{
	Geom_LineSem lineS;
	memcpy(&lineS.s,&ps,sizeof(Geom_Point));
	memcpy(&lineS.e,&pe,sizeof(Geom_Point));
	memcpy(&lineSem,&lineS,sizeof(Geom_LineSem));
}