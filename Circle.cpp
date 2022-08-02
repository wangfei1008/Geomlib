/*//////////////////////////////////////////////////////////////////////////
㈣ 圆的基本运算  
1 .点是否在圆内 20  
2 .求不共线的三点所确定的圆 21
3.判断圆是否在多边形内 5 
4.两圆关系
5.判断圆是否在矩形内
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/*************************\  
*						 *  
* 圆的基本运算           *  
*					     *  
\*************************/  
template <typename T> 
void swap( T &x, T &y ) 
{ 
	T temp; 
	
	temp = x; 
	x = y; 
	y = temp; 
}
/****************************************************************************** 
返回值	： 点p在圆内(包括边界)时，返回true  
用途	： 因为圆为凸集，所以判断点集，折线，多边形是否在圆内时， 
只需要逐一判断点是否在圆内即可。  
*******************************************************************************/  
bool Geom_Circle_PIC(Geom_Circle c,Geom_Point p)  
{  
	double d2=(p.x-c.O.x)*(p.x-c.O.x)+(p.y-c.O.y)*(p.y-c.O.y);  
	double r2=c.r*c.r;  
	return d2<r2||fabs(d2-r2)<EP;  
}  
/****************************************************************************** 
用 途	：求不共线的三点确定一个圆  
输 入	：三个点p1,p2,p3  
返回值	：如果三点共线，返回false；反之，返回true。圆心由q返回，半径由r返回  
*******************************************************************************/  
bool Geom_Circle_CoC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c)  
{  
	double x12=p2.x-p1.x;  
	double y12=p2.y-p1.y;  
	double x13=p3.x-p1.x;  
	double y13=p3.y-p1.y;  
	double z2=x12*(p1.x+p2.x)+y12*(p1.y+p2.y);  
	double z3=x13*(p1.x+p3.x)+y13*(p1.y+p3.y);  
	double d=2.0*(x12*(p3.y-p2.y)-y12*(p3.x-p2.x));  
	if(fabs(d)<EP) //共线，圆不存在  
		return false;  
	c.O.x=(long)((y13*z2-y12*z3)/d);  
	c.O.y=(long)((x12*z3-x13*z2)/d);  
	c.r=Geom_Dot_Dist(p1,c.O);  
	return true;  
}  

/* 判断圆是否在多边形内.ptolineseg()函数的应用2 */  
bool Geom_Circle_CIPoly(int vcount,Geom_Point polygon[],Geom_Circle c)  
{  
	Geom_Point q;  
	double d;  
	q.x=0;  
	q.y=0;  
	d=Geom_Line_P2PSet(vcount,polygon,c.O,q);  
	if(d<c.r||fabs(d-c.r)<EP)  
		return true;  
	else  
		return false;  
}  

//两圆关系：  
/* 两圆：  
相离： return 1；  
外切： return 2；  
相交： return 3；  
内切： return 4；  
内含： return 5；  
*/  
int Geom_Circle_2CRelation(Geom_Circle c1,Geom_Circle c2)  
{  
	double d = sqrt( (c1.O.x-c2.O.x)*(c1.O.x-c2.O.x)+(c1.O.y-c2.O.y)*(c1.O.y-c2.O.y) );  
	
	if( fabs(d-c1.r-c2.r) < EP ) // 必须保证前两个if先被判定！  
		return 2;  
	if( fabs(d-fabs(c1.r-c2.r)) < EP )  
		return 4;  
	if( d > c1.r+c2.r )  
		return 1;  
	if( d < fabs(c1.r-c2.r) )  
		return 5;  
	if( fabs(c1.r-c2.r) < d && d < c1.r+c2.r )  
		return 3;  
	return 0; // indicate an error!  
}  

//判断圆是否在矩形内： 
// 判定圆是否在矩形内，是就返回true（设矩形水平，且其四个顶点由左上开始按顺时针排列）  
// 调用ptoldist函数，在第4页  
bool Geom_Circle_CRRelation(Geom_Circle c,Geom_Rect rect)  
{  
	Geom_Point pr1, pr2, pr3, pr4;
	pr1.x = (long)rect.x;
	pr1.y = (long)rect.y;
	pr2.x = (long)(rect.x + rect.w);
	pr2.y = pr1.y;
	pr3.x = pr2.x;
	pr3.y = (long)(rect.y + rect.h);
	pr4.x = pr1.x;
	pr4.y = pr3.y;

	if( pr1.x < c.O.x && c.O.x < pr2.x && pr3.y < c.O.y && c.O.y < pr2.y )  
	{  
		Geom_LineSem line1;  
		Geom_Line_PSetLineSem(pr1,pr2,line1);
		Geom_LineSem line2; 
		Geom_Line_PSetLineSem(pr2,pr3,line2);
		Geom_LineSem line3; 
		Geom_Line_PSetLineSem(pr3,pr4,line3);
		Geom_LineSem line4;  
		Geom_Line_PSetLineSem(pr4,pr1,line4);
		if( c.r<Geom_Line_P2LDist(c.O,line1) && c.r<Geom_Line_P2LDist(c.O,line2) &&	c.r<Geom_Line_P2LDist(c.O,line3) && c.r<Geom_Line_P2LDist(c.O,line4) )  
			return true;  
	}  
	return false;  
} 

//两圆交点：  
// 两圆已经相交（相切）  
void  Geom_Circle_2CP(Geom_Circle c1,Geom_Circle c2,Geom_Point &rp1,Geom_Point &rp2)  
{  
	Geom_Point p1,p2;
	double r1,r2;
	double a,b,r;
	p1 = c1.O;
	r1 = c1.r;
	p2 = c2.O;
	r2 = c2.r;

	a=p2.x-p1.x;  
	b=p2.y-p1.y;  
	r=(a*a+b*b+r1*r1-r2*r2)/2;  
	if(a==0&&b!=0)  
	{  
		rp1.y=rp2.y=(long)(r/b);  
		rp1.x=(long)(sqrt(r1*r1-rp1.y*rp1.y));  
		rp2.x=-rp1.x;  
	}  
	else if(a!=0&&b==0)  
	{  
		rp1.x=rp2.x=(long)(r/a);  
		rp1.y=(long)(sqrt(r1*r1-rp1.x*rp2.x));  
		rp2.y=-rp1.y;  
	}  
	else if(a!=0&&b!=0)  
	{  
		double delta;  
		delta=b*b*r*r-(a*a+b*b)*(r*r-r1*r1*a*a);  
		rp1.y=(long)((b*r+sqrt(delta))/(a*a+b*b));  
		rp2.y=(long)((b*r-sqrt(delta))/(a*a+b*b));  
		rp1.x=(long)((r-b*rp1.y)/a);  
		rp2.x=(long)((r-b*rp2.y)/a);  
	}  
 
	rp1.x+=p1.x;  
	rp1.y+=p1.y;  
	rp2.x+=p1.x;  
	rp2.y+=p1.y;  
}  
//两圆公共面积： 
// 必须保证相交  
double Geom_Circle_2CArea(Geom_Circle c1,Geom_Circle c2)  
{  
	Geom_Point p1,p2;
	double r1,r2;
	p1 = c1.O;
	r1 = c1.r;
	p2 = c2.O;
	r2 = c2.r;

	Geom_Point rp1,rp2;  
	Geom_Circle_2CP(c1,c2,rp1,rp2);  
 
	if(r1>r2) //保证r2>r1  
	{  
		swap(p1,p2);  
		swap(r1,r2);  
	}  
	double a,b,rr;  
	a=p1.x-p2.x;  
	b=p1.y-p2.y;  
	rr=sqrt(a*a+b*b);  
 
	double dx1,dy1,dx2,dy2;  
	double sita1,sita2;  
	dx1=rp1.x-p1.x;  
	dy1=rp1.y-p1.y;  
	dx2=rp2.x-p1.x;  
	dy2=rp2.y-p1.y;  
	sita1=acos((dx1*dx2+dy1*dy2)/r1/r1);  
 
	dx1=rp1.x-p2.x;  
	dy1=rp1.y-p2.y;  
	dx2=rp2.x-p2.x;  
	dy2=rp2.y-p2.y;  
	sita2=acos((dx1*dx2+dy1*dy2)/r2/r2);  
	double s=0;  
	if(rr<r2)//相交弧为优弧  
		s=r1*r1*(PI-sita1/2+sin(sita1)/2)+r2*r2*(sita2-sin(sita2))/2;  
	else//相交弧为劣弧  
		s=(r1*r1*(sita1-sin(sita1))+r2*r2*(sita2-sin(sita2)))/2;  
 
	return s;  
}  
//圆和直线关系：  
//0----相离 1----相切 2----相交  
int Geom_Circle_CLRelation(Geom_Circle c,Geom_Line line,Geom_Point &rp1,Geom_Point &rp2)  
{  
	int res=0;  
 
	line.c=line.c+line.a*c.O.x+line.b*c.O.y;  
	double tmp;  
	if(line.a==0&&line.b!=0)  
	{  
		tmp=-line.c/line.b;  
		if(c.r*c.r<tmp*tmp)  
			res=0;  
		else if(c.r*c.r==tmp*tmp)  
		{  
			res=1;  
			rp1.y=(long)tmp;  
			rp1.x=0;  
		}  
		else  
		{  
			res=2;  
			rp1.y=rp2.y=(long)tmp;  
			rp1.x=(long)(sqrt(c.r*c.r-tmp*tmp));  
			rp2.x=-rp1.x;  
		}  
	}  
	else if(line.a!=0&&line.b==0)  
	{  
		tmp=-line.c/line.a;  
		if(c.r*c.r<tmp*tmp)  
			res=0;  
		else if(c.r*c.r==tmp*tmp)  
		{  
			res=1;  
			rp1.x=(long)tmp;  
			rp1.y=0;  
		}  
		else  
		{  
			res=2;  
			rp1.x=rp2.x=(long)tmp;  
			rp1.y=(long)(sqrt(c.r*c.r-tmp*tmp));  
			rp2.y=-rp1.y;  
		}  
	}  
	else if(line.a!=0&&line.b!=0)  
	{  
		double delta;  
		delta=line.b*line.b*line.c*line.c-(line.a*line.a+line.b*line.b)*(line.c*line.c-line.a*line.a*c.r*c.r);  
		if(delta<0)  
			res=0;  
		else if(delta==0)  
		{  
			res=1;  
			rp1.y=(long)(-line.b*line.c/(line.a*line.a+line.b*line.b));  
			rp1.x=(long)((-line.c-line.b*rp1.y)/line.a);  
		}  
		else  
		{  
			res=2;  
			rp1.y=(long)((-line.b*line.c+sqrt(delta))/(line.a*line.a+line.b*line.b));  
			rp2.y=(long)((-line.b*line.c-sqrt(delta))/(line.a*line.a+line.b*line.b));  
			rp1.x=(long)((-line.c-line.b*rp1.y)/line.a);  
			rp2.x=(long)((-line.c-line.b*rp2.y)/line.a);  
		}  
	}  
	rp1.x+=c.O.x;  
	rp1.y+=c.O.y;  
	rp2.x+=c.O.x;  
	rp2.y+=c.O.y;  
	return res;  
}  

//内切圆：  
void Geom_Circle_InC(Geom_Point p1,Geom_Point p2,Geom_Point p3,Geom_Circle &c)  
{  
	double dx31,dy31,dx21,dy21,d31,d21,a1,b1,c1;  
	dx31=p3.x-p1.x;  
	dy31=p3.y-p1.y;  
	dx21=p2.x-p1.x;  
	dy21=p2.y-p1.y;  
 
	d31=sqrt(dx31*dx31+dy31*dy31);  
	d21=sqrt(dx21*dx21+dy21*dy21);  
	a1=dx31*d21-dx21*d31;  
	b1=dy31*d21-dy21*d31;  
	c1=a1*p1.x+b1*p1.y;  
 
	double dx32,dy32,dx12,dy12,d32,d12,a2,b2,c2;  
	dx32=p3.x-p2.x;  
	dy32=p3.y-p2.y;  
	dx12=-dx21;  
	dy12=-dy21;  
 
	d32=sqrt(dx32*dx32+dy32*dy32);  
	d12=d21;  
	a2=dx12*d32-dx32*d12;  
	b2=dy12*d32-dy32*d12;  
	c2=a2*p2.x+b2*p2.y;  
 
	c.O.x=(long)((c1*b2-c2*b1)/(a1*b2-a2*b1));  
	c.O.y=(long)((c2*a1-c1*a2)/(a1*b2-a2*b1));  
	c.r=fabs(dy21*c.O.x-dx21*c.O.y+dx21*p1.y-dy21*p1.x)/d21;  
}  

//求切点：  
// p---圆心坐标， r---圆半径， sp---圆外一点， rp1,rp2---切点坐标  
void Geom_Circle_CutPoint(Geom_Circle c,Geom_Point sp,Geom_Point &rp1,Geom_Point &rp2)  
{  
	Geom_Circle c2;  
	c2.O.x=(c.O.x+sp.x)/2;  
	c2.O.y=(c.O.y+sp.y)/2;  
 
	double dx2,dy2;  
	dx2=c2.O.x-c.O.x;  
	dy2=c2.O.y-c.O.y;  
	c2.r=sqrt(dx2*dx2+dy2*dy2);  

	Geom_Circle_2CP(c,c2,rp1,rp2);  
} 
