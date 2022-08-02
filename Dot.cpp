
/*//////////////////////////////////////////////////////////////////////////
㈠ 点的基本运算  
1. 平面上两点之间距离 1  
2. 判断两点是否重合 1  
3. 矢量叉乘 1  
4. 矢量点乘 2  
5. 判断点是否在线段上 2  
6. 求一点饶某点旋转后的坐标 2  
7. 求矢量夹角 2 
8.点到平面的距离
9.点是否在直线同侧 
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

// 返回两点之间欧氏距离 
double Geom_Dot_Dist(Geom_Point p1,Geom_Point p2)                 
{  
	return(sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ) );  
}

// 判断两个点是否重合   
bool Geom_Dot_Equal(Geom_Point p1,Geom_Point p2)             
{  
	return ( (abs(p1.x-p2.x)<EP)&&(abs(p1.y-p2.y)<EP) );  
}  

/******************************************************************************  
r=multiply(sp,ep,op),得到(sp-op)和(ep-op)的叉积  
r>0：ep在矢量opsp的逆时针方向；  
r=0：opspep三点共线；  
r<0：ep在矢量opsp的顺时针方向  
*******************************************************************************/  
double Geom_Dot_Multiply(Geom_Point sp,Geom_Point ep,Geom_Point op)  
{  
	return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y));  
}  
/*****************************************************************************  
r=dotmultiply(p1,p2,op),得到矢量(p1-op)和(p2-op)的点积，如果两个矢量都非零矢量  
r<0：两矢量夹角为锐角； 
r=0：两矢量夹角为直角； 
r>0：两矢量夹角为钝角  
*******************************************************************************/  
double Geom_Dot_Dotmultiply(Geom_Point p1,Geom_Point p2,Geom_Point p0)  
{  
	return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));  
}  
/******************************************************************************  
判断点p是否在线段l上 
条件：(p在线段l所在的直线上) && (点p在以线段l为对角线的矩形内) 
*******************************************************************************/  
bool Geom_Dot_Online(Geom_LineSem l,Geom_Point p)  
{  
	return( (Geom_Dot_Multiply(l.e,p,l.s)==0) &&( ( (p.x-l.s.x)*(p.x-l.e.x)<=0 )&&( (p.y-l.s.y)*(p.y-l.e.y)<=0 ) ) );  
}  
// 返回点p以点o为圆心逆时针旋转alpha(单位：弧度)后所在的位置  
Geom_Point Geom_Dot_Rotate(Geom_Point o,double alpha,Geom_Point p)  
{  
	Geom_Point tp;  
	p.x-=o.x;  
	p.y-=o.y;  
	tp.x=(long)(p.x*cos(alpha)-p.y*sin(alpha)+o.x);  
	tp.y=(long)(p.y*cos(alpha)+p.x*sin(alpha)+o.y);  
	return tp;  
}  
/* 返回顶角在o点，起始边为os，终止边为oe的夹角(单位：弧度)  
角度小于pi，返回正值  
角度大于pi，返回负值  
可以用于求线段之间的夹角  
原理： 
r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e)) 
r'= multiply(s,e,o) 

  r >= 1	angle = 0; 
  r <= -1	angle = -PI 
  -1<r<1 && r'>0	angle = arccos(r) 
  -1<r<1 && r'<=0	angle = -arccos(r) 
*/  
double Geom_Dot_Angle(Geom_Point o,Geom_Point s,Geom_Point e)  
{  
	double cosfi,fi,norm;  
	double dsx = s.x - o.x;  
	double dsy = s.y - o.y;  
	double dex = e.x - o.x;  
	double dey = e.y - o.y;  
	
	cosfi=dsx*dex+dsy*dey;  
	norm=(dsx*dsx+dsy*dsy)*(dex*dex+dey*dey);  
	cosfi /= sqrt( norm );  
	
	if (cosfi >=  1.0 ) return 0;  
	if (cosfi <= -1.0 ) return -3.1415926;  
	
	fi=acos(cosfi);  
	if (dsx*dey-dsy*dex>0) return fi;      // 说明矢量os 在矢量 oe的顺时针方向  
	return -fi;  
}  

//点到平面的距离：  
//点到平面的距离,平面用一般式表示ax+by+cz+d=0  
double Geom_Dot_P2PlaneDist(double x, double y, double z, double a, double b, double c, double d)  
{  
	return fabs(a*x+b*y+c*z+d) / sqrt(a*a+b*b+c*c);  
}  
//点是否在直线同侧： 
//两个点是否在直线同侧，是则返回true  
bool Geom_Dot_SameSide(Geom_Point p1, Geom_Point p2, Geom_Line line)  
{  
	return (line.a * p1.x + line.b * p1.y + line.c) *  
		(line.a * p2.x + line.b * p2.y + line.c) > 0;  
} 

//求三角面积
//////////////////////////////////////////////////////////////////////////
// POINT   是一个点的结构体，包含点的   x,   y   坐标     
// 上面这个函数的可以判断   P3   点在有向线段   P1P2(P1指向P2)   的哪一侧   
// 返回值   >   0，   左侧   
//         =   0,    在直线   P1P2上   
//         <   0，   右侧   
//  返回值到绝对值就是   △P1P2P3   的面积 
//////////////////////////////////////////////////////////////////////////
long  Geom_Dot_TriangleArea(Geom_Point p1, Geom_Point p2, Geom_Point p3)
{
	long area  = (p1.x * p2.y + p2.x*p3.y + p3.x*p1.y) - (p1.x*p3.y + p2.x*p1.y + p3.x*p2.y);		
	return   area/2;  
}