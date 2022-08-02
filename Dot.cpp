
/*//////////////////////////////////////////////////////////////////////////
�� ��Ļ�������  
1. ƽ��������֮����� 1  
2. �ж������Ƿ��غ� 1  
3. ʸ����� 1  
4. ʸ����� 2  
5. �жϵ��Ƿ����߶��� 2  
6. ��һ����ĳ����ת������� 2  
7. ��ʸ���н� 2 
8.�㵽ƽ��ľ���
9.���Ƿ���ֱ��ͬ�� 
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

// ��������֮��ŷ�Ͼ��� 
double Geom_Dot_Dist(Geom_Point p1,Geom_Point p2)                 
{  
	return(sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ) );  
}

// �ж��������Ƿ��غ�   
bool Geom_Dot_Equal(Geom_Point p1,Geom_Point p2)             
{  
	return ( (abs(p1.x-p2.x)<EP)&&(abs(p1.y-p2.y)<EP) );  
}  

/******************************************************************************  
r=multiply(sp,ep,op),�õ�(sp-op)��(ep-op)�Ĳ��  
r>0��ep��ʸ��opsp����ʱ�뷽��  
r=0��opspep���㹲�ߣ�  
r<0��ep��ʸ��opsp��˳ʱ�뷽��  
*******************************************************************************/  
double Geom_Dot_Multiply(Geom_Point sp,Geom_Point ep,Geom_Point op)  
{  
	return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y));  
}  
/*****************************************************************************  
r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ��  
r<0����ʸ���н�Ϊ��ǣ� 
r=0����ʸ���н�Ϊֱ�ǣ� 
r>0����ʸ���н�Ϊ�۽�  
*******************************************************************************/  
double Geom_Dot_Dotmultiply(Geom_Point p1,Geom_Point p2,Geom_Point p0)  
{  
	return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));  
}  
/******************************************************************************  
�жϵ�p�Ƿ����߶�l�� 
������(p���߶�l���ڵ�ֱ����) && (��p�����߶�lΪ�Խ��ߵľ�����) 
*******************************************************************************/  
bool Geom_Dot_Online(Geom_LineSem l,Geom_Point p)  
{  
	return( (Geom_Dot_Multiply(l.e,p,l.s)==0) &&( ( (p.x-l.s.x)*(p.x-l.e.x)<=0 )&&( (p.y-l.s.y)*(p.y-l.e.y)<=0 ) ) );  
}  
// ���ص�p�Ե�oΪԲ����ʱ����תalpha(��λ������)�����ڵ�λ��  
Geom_Point Geom_Dot_Rotate(Geom_Point o,double alpha,Geom_Point p)  
{  
	Geom_Point tp;  
	p.x-=o.x;  
	p.y-=o.y;  
	tp.x=(long)(p.x*cos(alpha)-p.y*sin(alpha)+o.x);  
	tp.y=(long)(p.y*cos(alpha)+p.x*sin(alpha)+o.y);  
	return tp;  
}  
/* ���ض�����o�㣬��ʼ��Ϊos����ֹ��Ϊoe�ļн�(��λ������)  
�Ƕ�С��pi��������ֵ  
�Ƕȴ���pi�����ظ�ֵ  
�����������߶�֮��ļн�  
ԭ�� 
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
	if (dsx*dey-dsy*dex>0) return fi;      // ˵��ʸ��os ��ʸ�� oe��˳ʱ�뷽��  
	return -fi;  
}  

//�㵽ƽ��ľ��룺  
//�㵽ƽ��ľ���,ƽ����һ��ʽ��ʾax+by+cz+d=0  
double Geom_Dot_P2PlaneDist(double x, double y, double z, double a, double b, double c, double d)  
{  
	return fabs(a*x+b*y+c*z+d) / sqrt(a*a+b*b+c*c);  
}  
//���Ƿ���ֱ��ͬ�ࣺ 
//�������Ƿ���ֱ��ͬ�࣬���򷵻�true  
bool Geom_Dot_SameSide(Geom_Point p1, Geom_Point p2, Geom_Line line)  
{  
	return (line.a * p1.x + line.b * p1.y + line.c) *  
		(line.a * p2.x + line.b * p2.y + line.c) > 0;  
} 

//���������
//////////////////////////////////////////////////////////////////////////
// POINT   ��һ����Ľṹ�壬�������   x,   y   ����     
// ������������Ŀ����ж�   P3   ���������߶�   P1P2(P1ָ��P2)   ����һ��   
// ����ֵ   >   0��   ���   
//         =   0,    ��ֱ��   P1P2��   
//         <   0��   �Ҳ�   
//  ����ֵ������ֵ����   ��P1P2P3   ����� 
//////////////////////////////////////////////////////////////////////////
long  Geom_Dot_TriangleArea(Geom_Point p1, Geom_Point p2, Geom_Point p3)
{
	long area  = (p1.x * p2.y + p2.x*p3.y + p3.x*p1.y) - (p1.x*p3.y + p2.x*p1.y + p3.x*p2.y);		
	return   area/2;  
}