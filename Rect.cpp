/*//////////////////////////////////////////////////////////////////////////
�� ���εĻ�������  
1.��֪�����������꣬���4������ 22 
2.�ж϶��������Ƿ��ཻ�����Ƿ��й������֣�������������ο��غ����
3.���ο�����
4.���ο������  
5.������ο�Ĺ�ϵ
6.�߶�����ο�Ĺ�ϵ
7.ȡ���ο��4���߶Σ������ϵ㿪ʼ��˳ʱ��Ϊ��1��2��3��4���߶�
8.���ο������εĹ�ϵ
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/**************************\  
*						  *  
* ���εĻ�������          *  
*                         *  
\**************************/  
/*  
˵������Ϊ���ε������ԣ������㷨���Ի���  
1.�жϾ����Ƿ������  
ֻҪ�жϸõ�ĺ�������������Ƿ���ھ��ε����ұߺ����±�֮�䡣  
2.�ж��߶Ρ����ߡ�������Ƿ��ھ�����  
��Ϊ�����Ǹ�͹��������ֻҪ�ж����ж˵��Ƿ��ھ����оͿ����ˡ�  
3.�ж�Բ�Ƿ��ھ�����  
Բ�ھ����еĳ�Ҫ�����ǣ�Բ���ھ�������Բ�İ뾶С�ڵ���Բ�ĵ������ıߵľ������Сֵ��  
*/  
// ��֪���ε���������(a,b,c)��������ĸ�����d������. ע�⣺��֪��������������������  
Geom_Point Geom_Rect_Rect4th(Geom_Point a,Geom_Point b,Geom_Point c)  
{  
	Geom_Point d;  
	if(fabs(Geom_Dot_Dotmultiply(a,b,c))<EP) // ˵��c����ֱ�ǹսǴ�  
	{  
		d.x=a.x+b.x-c.x;  
		d.y=a.y+b.y-c.y;  
	}  
	if(fabs(Geom_Dot_Dotmultiply(a,c,b))<EP) // ˵��b����ֱ�ǹսǴ�  
	{  
		d.x=a.x+c.x-b.x;  
		d.y=a.y+c.y-b.x;  
	}  
	if(fabs(Geom_Dot_Dotmultiply(c,b,a))<EP) // ˵��a����ֱ�ǹսǴ�  
	{  
		d.x=c.x+b.x-a.x;  
		d.y=c.y+b.y-a.y;  
	}  
	return d;  
}  

//////////////////////////////////////////////////////////////////////////
//��������OverlapPartRect
//�������ܣ��ж϶��������Ƿ��ཻ�����Ƿ��й������֣�������������ο��غ����
//�㷨˵����
/*
�ٶ���������һ�Ե����(minx,miny)(maxx,   maxy)   
��ô��������rect1{(minx1,miny1)(maxx1,   maxy1)},   rect2{(minx2,miny2)(maxx2,   maxy2)}   

  �ཻ�Ľ��һ���Ǹ����Σ���������ཻ����rect{(minx,miny)(maxx,   maxy)}�ĵ�������ǣ�   
  minx   =   max(minx1,   minx2)   
  miny   =   max(miny1,   miny2)   
  maxx   =   min(maxx1,   maxx2)   
  maxy   =   min(maxy1,   maxy2)   
  
		  ����������β��ཻ����ô����õ��ĵ�������Ȼ����   
		  minx   >   maxx   
		  ����   
		  miny   >   maxy   
		  
			�ж��Ƿ��ཻ���Լ��ཻ������ʲô���������������һ��������
			������㷨�Ľ���ϣ����ǻ����Լ򵥵����ɳ�������������ݣ�
			
			  1 �ཻ���Σ�  (minx, miny) (maxx, maxy)
			  
				2 ����� ����ļ�����Ժ��ж�һ�����
				
				  if ( minx>maxx) return 0;
				  
					if (miny>maxy) return 0;
					
return (maxx-minx)*(maxy-miny)*/
//���������fRect--һ����
//          sRect--һ����
//���������overlapArea--�غ����
//����ֵ���Ƿ��ཻ
//��ע��2008.12.12 wangfei
//////////////////////////////////////////////////////////////////////////
bool Geom_Rect_2ROPart(Geom_Rect fRect, Geom_Rect sRect, double &overlapArea)
{		
	
	int maxx = 0,minx = 0;
	int maxy = 0,miny = 0;
	
	int xf = (int)((fRect.x + fRect.w));
	int xs = (int)((sRect.x + sRect.w));

	minx = (int)max(fRect.x,sRect.x);	
	maxx = min(xf,xs);
	miny = (int)max(fRect.y,sRect.y);
	int yf = (int)((fRect.y + fRect.h));
	int ys = (int)((sRect.y + sRect.h));
		
	maxy = min(yf,ys);
	
	if ((minx > maxx)||(miny > maxy)) 
	{
		return false;
	}
	else
	{
		overlapArea = (maxx-minx)*(maxy-miny);
		return true;
	}
	
	return false;
}

//���ο�����
double Geom_Rect_RArea(Geom_Rect rect)
{
	return rect.w*rect.h;
}

//���ο������
Geom_Point Geom_Rect_RCenterP(Geom_Rect rect)
{
	Geom_Point p;
	p.x = (long)(rect.x + rect.w/2);
	p.y = (long)(rect.y + rect.h/2);
	return p;
}

//������ο�Ĺ�ϵ
//����ֵ��ʾ��-1���������󣨾��ο򲻴��ڣ���0�����ھ��ο��ڣ�1�����ھ��ο��ϣ�2�����ھ��ο��� 
int Geom_Rect_PRRelation(Geom_Rect rect,Geom_Point p)
{
   if (rect.x < p.x && p.x < rect.x+  rect.w && rect.y < p.y && p.y < rect.y + rect.h)
	   return 0;  // ���ھ��ο���
   else
   {
	   if (  ((p.x == rect.x || p.x == rect.x + rect.w) &&  rect.y <= p.y && p.y <= rect.y + rect.h)
		   || ((p.y == rect.y || p.y == rect.y + rect.h) &&  rect.x <= p.x && p.y <= rect.x + rect.w) )
		   return 1;  //���ھ��ο���
	   else
		   return 2;  //���ھ��ο���
   }
}

//�߶�����ο�Ĺ�ϵ
//0���߶��ھ��ο��ڣ�1���߶�����ο��н��㣬2���߶��ھ��ο��� 
int Geom_Rect_LSRRalation(Geom_Rect rect,Geom_LineSem l)
{
	int sI = Geom_Rect_PRRelation(rect,l.s);
	int eI = Geom_Rect_PRRelation(rect,l.e);

	if ((0==sI)&&(0==eI))
	{
		return 0;
	}
	if ((0==sI)||(0==eI))
	{
		return 1;
	}


	Geom_LineSem li[4];

	Geom_Rect_RTLS(rect,li);
		
	for (int i = 0;i<4;i++)
	{
		if(Geom_Line_Intersect(l,li[i]))
		{
			return 1;
		}
	}
		
	return 2;		
}

//ȡ���ο��4���߶Σ������ϵ㿪ʼ��˳ʱ��Ϊ��1��2��3��4���߶�
void Geom_Rect_RTLS(Geom_Rect rect,Geom_LineSem *ls)
{
	ls[0].s.x = (long)rect.x;
	ls[0].s.y = (long)rect.y;
	ls[0].e.x = (long)(rect.x + rect.w);
	ls[0].e.y = ls[0].s.y;
	
	ls[1].s = ls[0].e;
	ls[1].e.x = ls[0].e.x;
	ls[1].e.y = (long)(rect.y + rect.h);
	
	ls[2].s = ls[1].e;
	ls[2].e.x = (long)rect.x;
	ls[2].e.y = ls[1].e.y;
	
	ls[3].s = ls[2].e;
	ls[3].e = ls[0].s;
}

//�д���rect(0,0,1,1),Point(33,22,23,32)
//���ο������εĹ�ϵ,�����ı������ڶ�����ڲ�Ϊ�ڲ�0,�ڲ���1���ཻ��2����
int Geom_Rect_RPolyRalation(Geom_Rect rect,Geom_Point p[],int vcount)
{
	Geom_Point ls[4];
	ls[0].x = rect.x;
	ls[0].y = rect.y;

	ls[1].x = rect.x + rect.w;
	ls[1].y = rect.y;

	ls[2].x = rect.x + rect.w;
	ls[2].y = rect.y + rect.h;

	ls[3].x = rect.x;
	ls[3].y = rect.y + rect.h;

	bool isB[4];
	int iNum = 0;
	for (int i = 0;i<4;i++)
	{
		isB[i] = Geom_Polygon_PICPoly(vcount,p,ls[i]);
		if (isB[i])
		{
			iNum++;
		}
	}

	if (4 == iNum)
	{
		return 0;
	}
	if (iNum>1)
	{
		return 1;
	}
	return 2;	
}