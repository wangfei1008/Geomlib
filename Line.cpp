 /************************************************************************/
/*�� �߶μ�ֱ�ߵĻ�������  
 1. �����߶εĹ�ϵ 3  
 2. ��㵽�߶�����ֱ�ߴ��ߵĴ��� 4  
 3. �㵽�߶ε������ 4  
 4. �㵽�߶�����ֱ�ߵľ��� 4  
 5. �㵽���߼���������� 4   
 7. ��ʸ���н����� 5  
 8. ���߶�֮��ļн� 5  
 9. �ж��߶��Ƿ��ཻ 6  
 10.�ж��߶��Ƿ��ཻ�������ڶ˵㴦 6  
 11.���߶�����ֱ�ߵķ��� 6  
 12.��ֱ�ߵ�б�� 7  
 13.��ֱ�ߵ���б�� 7  
 14.������ĳֱ�ߵĶԳƵ� 7  
 15.�ж�����ֱ���Ƿ��ཻ����ֱ�߽��� 7  
 16.�ж��߶��Ƿ��ཻ������ཻ���ؽ��� 7
 16.���淴����  
 17.�߶ε�������
 18.�㸳ֵ���߶�
*/
 /************************************************************************/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/*****************************\  
  *                             *  
  *      �߶μ�ֱ�ߵĻ�������   *  
  *                             *  
\*****************************/  
 
/* �жϵ����߶εĹ�ϵ,��;�ܹ㷺  
�������Ǹ�������Ĺ�ʽд�ģ�P�ǵ�C���߶�AB����ֱ�ߵĴ���  
 
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
// ���C���߶�AB����ֱ�ߵĴ��� P  
Geom_Point Geom_Line_Perpendicular(Geom_Point p,Geom_LineSem l)  
{  
	double r=Geom_Line_Relation(p,l);  
	Geom_Point tp;  
	tp.x=(long)(l.s.x+r*(l.e.x-l.s.x));  
	tp.y=(long)(l.s.y+r*(l.e.y-l.s.y));  
	return tp;  
}  
/* ���p���߶�l����̾���,�������߶��Ͼ�õ�����ĵ�np  
ע�⣺np���߶�l�ϵ���p����ĵ㣬��һ���Ǵ��� */  
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
// ���p���߶�l����ֱ�ߵľ���,��ע�Ȿ�������ϸ�����������   
double Geom_Line_P2LDist(Geom_Point p,Geom_LineSem l)  
{  
	return fabs(Geom_Dot_Multiply(p,l.e,l.s))/Geom_Dot_Dist(l.s,l.e);  
}  
/* ����㵽���߼����������,�����������.  
ע�⣺���õ���ptoLineSem()���� */  
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

/* �ж�Բ�Ƿ��ڶ������.ptoLineSem()������Ӧ��2 */  
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
/* ��������ʸ��l1��l2�ļнǵ�����(-1 --- 1)ע�⣺������������нǵĻ���ע�ⷴ���Һ����Ķ������Ǵ� 0��pi */  
double Geom_Line_Cosine(Geom_LineSem l1,Geom_LineSem l2)  
{  
	return (((l1.e.x-l1.s.x)*(l2.e.x-l2.s.x) +  
	(l1.e.y-l1.s.y)*(l2.e.y-l2.s.y))/(Geom_Dot_Dist(l1.e,l1.s)*Geom_Dot_Dist(l2.e,l2.s)));  
}  
// �����߶�l1��l2֮��ļн� ��λ������ ��Χ(-pi��pi)  
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
// ����߶�u��v�ཻ(�����ཻ�ڶ˵㴦)ʱ������true  
// 
//�ж�P1P2����Q1Q2�������ǣ�( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) >= 0�� 
//�ж�Q1Q2����P1P2�������ǣ�( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0�� 
bool Geom_Line_Intersect(Geom_LineSem u,Geom_LineSem v)  
{  
	return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //�ų�ʵ��  
			(max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&  
			(max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&  
			(max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&  
			(Geom_Dot_Multiply(v.s,u.e,u.s)*Geom_Dot_Multiply(u.e,v.e,u.s)>=0)&&         //����ʵ��  
			(Geom_Dot_Multiply(u.s,v.e,v.s)*Geom_Dot_Multiply(v.e,u.e,v.s)>=0));  
}  
//  (�߶�u��v�ཻ)&&(���㲻��˫���Ķ˵�) ʱ����true     
bool Geom_Line_Intersect_A(Geom_LineSem u,Geom_LineSem v)  
{  
	return	((Geom_Line_Intersect(u,v))&&  
			(!Geom_Dot_Online(u,v.s))&&  
			(!Geom_Dot_Online(u,v.e))&&  
			(!Geom_Dot_Online(v,u.e))&&  
			(!Geom_Dot_Online(v,u.s)));  
}  
// �߶�v����ֱ�����߶�u�ཻʱ����true���������ж��߶�u�Ƿ�����߶�v   
bool Geom_Line_Intersect_l(Geom_LineSem u,Geom_LineSem v)  
{  
	return Geom_Dot_Multiply(u.s,v.e,v.s)*Geom_Dot_Multiply(v.e,u.e,v.s)>=0;  
}  
// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)   
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
// ����ֱ�߽������̷���ֱ�ߵ�б��k,ˮƽ�߷��� 0,��ֱ�߷��� 1e200  
double Geom_Line_Slope(Geom_Line l)  
{  
	if(fabs(l.a) < 1e-20) 
		return 0;  
	if(fabs(l.b) < 1e-20) 
		return INF;  
	return -(l.a/l.b);  
}  
// ����ֱ�ߵ���б��alpha ( 0 - pi)  
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
// ���p����ֱ��l�ĶԳƵ�   
Geom_Point Geom_Line_Symmetry(Geom_Line l,Geom_Point p)  
{  
   Geom_Point tp;  
   tp.x=(long)(((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b));  
   tp.y=(long)(((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b));  
   return tp;  
}  
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p   
bool Geom_Line_LIntersect(Geom_Line l1,Geom_Line l2,Geom_Point &p) // �� L1��L2  
{  
	double d=l1.a*l2.b-l2.a*l1.b;  
	if(fabs(d)<EP) // ���ཻ  
		return false;  
	p.x = (long)((l2.c*l1.b-l1.c*l2.b)/d);  
	p.y = (long)((l2.a*l1.c-l1.a*l2.c)/d);  
	return true;  
}  
// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false  
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
 
//���淴���ߣ� 
// ��֪�����ߡ����棬�����ߡ�  
// a1,b1,c1Ϊ����ֱ�߷���(a1 x + b1 y + c1 = 0 ,��ͬ)ϵ��;   
//a2,b2,c2Ϊ�����ֱ�߷���ϵ��;   
//a,b,cΪ�����ֱ�߷���ϵ��.  
// �����з���ģ�ʹ��ʱע�⣺���������:<-b2,a2>�����������:<b,-a>.  
// ��Ҫ���ǽ���п��ܻ���"negative zeros"  
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
	double xx,yy; //(xx,yy)���������뾵��Ľ��㡣  
	xx=(b1*c2-b2*c1)/(a1*b2-a2*b1);  
	yy=(a2*c1-a1*c2)/(a1*b2-a2*b1);  
	a=n;  
	b=-m;  
	c=m*yy-xx*n;  
}  

//�߶ε���������  
/* l2��l1����/�ҷ���l1Ϊ��׼�ߣ�  
����	0	�� �غϣ�  
����	1	�� ������  
����	�C1 �� ������  
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

//�ѵ㸳ֵ���߶�
void Geom_Line_PSetLineSem(Geom_Point ps,Geom_Point pe,Geom_LineSem &lineSem)
{
	Geom_LineSem lineS;
	memcpy(&lineS.s,&ps,sizeof(Geom_Point));
	memcpy(&lineS.e,&pe,sizeof(Geom_Point));
	memcpy(&lineSem,&lineS,sizeof(Geom_LineSem));
}