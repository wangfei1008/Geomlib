/*//////////////////////////////////////////////////////////////////////////
㈤ 矩形的基本运算  
1.已知矩形三点坐标，求第4点坐标 22 
2.判断二个矩形是否相交，即是否有公共部分，并计算二个矩形框重合面积
3.矩形框的面积
4.矩形框的中心  
5.点与矩形框的关系
6.线段与矩形框的关系
7.取矩形框的4条线段，从左上点开始，顺时针为，1，2，3，4号线段
8.矩形框与多边形的关系
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/**************************\  
*						  *  
* 矩形的基本运算          *  
*                         *  
\**************************/  
/*  
说明：因为矩形的特殊性，常用算法可以化简：  
1.判断矩形是否包含点  
只要判断该点的横坐标和纵坐标是否夹在矩形的左右边和上下边之间。  
2.判断线段、折线、多边形是否在矩形中  
因为矩形是个凸集，所以只要判断所有端点是否都在矩形中就可以了。  
3.判断圆是否在矩形中  
圆在矩形中的充要条件是：圆心在矩形中且圆的半径小于等于圆心到矩形四边的距离的最小值。  
*/  
// 已知矩形的三个顶点(a,b,c)，计算第四个顶点d的坐标. 注意：已知的三个顶点可以是无序的  
Geom_Point Geom_Rect_Rect4th(Geom_Point a,Geom_Point b,Geom_Point c)  
{  
	Geom_Point d;  
	if(fabs(Geom_Dot_Dotmultiply(a,b,c))<EP) // 说明c点是直角拐角处  
	{  
		d.x=a.x+b.x-c.x;  
		d.y=a.y+b.y-c.y;  
	}  
	if(fabs(Geom_Dot_Dotmultiply(a,c,b))<EP) // 说明b点是直角拐角处  
	{  
		d.x=a.x+c.x-b.x;  
		d.y=a.y+c.y-b.x;  
	}  
	if(fabs(Geom_Dot_Dotmultiply(c,b,a))<EP) // 说明a点是直角拐角处  
	{  
		d.x=c.x+b.x-a.x;  
		d.y=c.y+b.y-a.y;  
	}  
	return d;  
}  

//////////////////////////////////////////////////////////////////////////
//函数名：OverlapPartRect
//函数功能：判断二个矩形是否相交，即是否有公共部分，并计算二个矩形框重合面积
//算法说明：
/*
假定矩形是用一对点表达的(minx,miny)(maxx,   maxy)   
那么两个矩形rect1{(minx1,miny1)(maxx1,   maxy1)},   rect2{(minx2,miny2)(maxx2,   maxy2)}   

  相交的结果一定是个矩形，构成这个相交矩形rect{(minx,miny)(maxx,   maxy)}的点对坐标是：   
  minx   =   max(minx1,   minx2)   
  miny   =   max(miny1,   miny2)   
  maxx   =   min(maxx1,   maxx2)   
  maxy   =   min(maxy1,   maxy2)   
  
		  如果两个矩形不相交，那么计算得到的点对坐标必然满足   
		  minx   >   maxx   
		  或者   
		  miny   >   maxy   
		  
			判定是否相交，以及相交矩形是什么都可以用这个方法一体计算完成
			从这个算法的结果上，我们还可以简单的生成出下面的两个内容：
			
			  1 相交矩形：  (minx, miny) (maxx, maxy)
			  
				2 面积： 面积的计算可以和判定一起进行
				
				  if ( minx>maxx) return 0;
				  
					if (miny>maxy) return 0;
					
return (maxx-minx)*(maxy-miny)*/
//输入参数：fRect--一个框
//          sRect--一个框
//输出参数：overlapArea--重合面积
//返回值：是否相交
//备注：2008.12.12 wangfei
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

//矩形框的面积
double Geom_Rect_RArea(Geom_Rect rect)
{
	return rect.w*rect.h;
}

//矩形框的中心
Geom_Point Geom_Rect_RCenterP(Geom_Rect rect)
{
	Geom_Point p;
	p.x = (long)(rect.x + rect.w/2);
	p.y = (long)(rect.y + rect.h/2);
	return p;
}

//点与矩形框的关系
//返回值表示：-1：条件错误（矩形框不存在），0：点在矩形框内，1：点在矩形框上，2：点在矩形框外 
int Geom_Rect_PRRelation(Geom_Rect rect,Geom_Point p)
{
   if (rect.x < p.x && p.x < rect.x+  rect.w && rect.y < p.y && p.y < rect.y + rect.h)
	   return 0;  // 点在矩形框内
   else
   {
	   if (  ((p.x == rect.x || p.x == rect.x + rect.w) &&  rect.y <= p.y && p.y <= rect.y + rect.h)
		   || ((p.y == rect.y || p.y == rect.y + rect.h) &&  rect.x <= p.x && p.y <= rect.x + rect.w) )
		   return 1;  //点在矩形框上
	   else
		   return 2;  //点在矩形框外
   }
}

//线段与矩形框的关系
//0：线段在矩形框内，1：线段与矩形框有交点，2：线段在矩形框外 
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

//取矩形框的4条线段，从左上点开始，顺时针为，1，2，3，4号线段
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

//有错误rect(0,0,1,1),Point(33,22,23,32)
//矩形框与多边形的关系,必需四边完整在多边形内才为内部0,内部，1，相交，2，外
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