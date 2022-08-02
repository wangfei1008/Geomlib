/*//////////////////////////////////////////////////////////////////////////
㈢ 多边形常用算法模块  
1. 判断多边形是否简单多边形 8  
2. 检查多边形顶点的凸凹性 9  
3. 判断多边形是否凸多边形 9  
4. 求多边形面积 9  
5. 判断多边形顶点的排列方向，方法一 10  
6. 判断多边形顶点的排列方向，方法二 10  
7. 射线法判断点是否在多边形内 10  
8. 判断点是否在凸多边形内 11  
9. 寻找点集的graham算法 12  
10.寻找点集凸包的卷包裹法 13  
11.判断线段是否在多边形内 14  
12.求简单多边形的重心 15  
13.求凸多边形的重心 17  
14.求肯定在给定多边形内的一个点 17  
15.求从多边形外一点出发到该多边形的切线 18  
16.判断多边形的核是否存在 19  
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/******************************\  
*							  *  
* 多边形常用算法模块		  *  
*							  *  
\******************************/  
 
// 如果无特别说明，输入多边形顶点要求按逆时针排列  
 
/*  
返回值：输入的多边形是简单多边形，返回true  
要 求：输入顶点序列按逆时针排序  
说 明：简单多边形定义：  
1：循环排序中相邻线段对的交是他们之间共有的单个点  
2：不相邻的线段不相交  
本程序默认第一个条件已经满足  
*/  
bool Geom_Polygon_IsSimple(int vcount,Geom_Point polygon[])  
{  
	int i,cn;  
	Geom_LineSem l1,l2;  
	for(i=0;i<vcount;i++)  
	{  
		l1.s=polygon[i];  
		l1.e=polygon[(i+1)%vcount];  
		cn=vcount-3;  
		while(cn)  
		{  
			l2.s=polygon[(i+2)%vcount];  
			l2.e=polygon[(i+3)%vcount];  
			if(Geom_Line_Intersect(l1,l2))  
				break;  
			cn--;  
		}  
		if(cn)  
			return false;  
	}  
	return true;  
}  
// 返回值：按输入顺序返回多边形顶点的凸凹性判断，bc[i]=1,iff:第i个顶点是凸顶点  
void Geom_Polygon_CheckConvex(int vcount,Geom_Point polygon[],bool bc[])  
{  
	int i,index=0;  
	Geom_Point tp=polygon[0];  
	for(i=1;i<vcount;i++) // 寻找第一个凸顶点  
	{  
		if(polygon[i].y<tp.y||(polygon[i].y == tp.y&&polygon[i].x<tp.x))  
		{  
			tp=polygon[i];  
			index=i;  
		}  
	}  
	int count=vcount-1;  
	bc[index]=1;  
	while(count) // 判断凸凹性  
	{  
		if(Geom_Dot_Multiply(polygon[(index+1)%vcount],polygon[(index+2)%vcount],polygon[index])>=0 )  
			bc[(index+1)%vcount]=1;  
		else  
			bc[(index+1)%vcount]=0;  
		index++;  
		count--;  
	}  
} 
// 返回值：多边形polygon是凸多边形时，返回true   
bool Geom_Polygon_IsConvex(int vcount,Geom_Point polygon[])  
{  
	bool bc[MAXV];  
	Geom_Polygon_CheckConvex(vcount,polygon,bc);  
	for(int i=0;i<vcount;i++) // 逐一检查顶点，是否全部是凸顶点  
		if(!bc[i])  
			return false;  
	return true;  
}  
// 返回多边形面积(signed)；输入顶点按逆时针排列时，返回正值；否则返回负值  
double Geom_Polygon_Area(int vcount,Geom_Point polygon[])  
{  
	int i;  
	double s;  
	if (vcount<3)  
		return 0;  
	s=polygon[0].y*(polygon[vcount-1].x-polygon[1].x);  
	for (i=1;i<vcount;i++)  
		s+=polygon[i].y*(polygon[(i-1)].x-polygon[(i+1)%vcount].x);  
	return s/2;  
}  
// 如果输入顶点按逆时针排列，返回true  
bool Geom_Polygon_IsConterClock(int vcount,Geom_Point polygon[])  
{  
	return Geom_Polygon_Area(vcount,polygon)>0;  
}  
// 另一种判断多边形顶点排列方向的方法   
bool Geom_Polygon_IsCcwize(int vcount,Geom_Point polygon[])  
{  
	int i,index;  
	Geom_Point a,b,v;  
	v=polygon[0];  
	index=0;  
	for(i=1;i<vcount;i++) // 找到最低且最左顶点，肯定是凸顶点  
	{  
		if(polygon[i].y<v.y||polygon[i].y == v.y && polygon[i].x<v.x)  
		{  
			index=i;  
		}  
	}  
	a=polygon[(index-1+vcount)%vcount]; // 顶点v的前一顶点  
	b=polygon[(index+1)%vcount]; // 顶点v的后一顶点  
	return Geom_Dot_Multiply(v,b,a)>0;  
}  
/********************************************************************************************    
射线法判断点q与多边形polygon的位置关系，要求polygon为简单多边形，顶点逆时针排列  
   如果点在多边形内：   返回0  
   如果点在多边形边上： 返回1  
   如果点在多边形外：	返回2  
*********************************************************************************************/  
int Geom_Polygon_PIPoly(int vcount,Geom_Point Polygon[],Geom_Point q)  
{  
	int c=0,i,n;  
	Geom_LineSem l1,l2;  
	bool bintersect_a,bonline1,bonline2,bonline3;  
	double r1,r2;  
 
	l1.s=q;  
	l1.e=q;  
	l1.e.x=(int)1E10;  
	n=vcount;  
	for (i=0;i<vcount;i++)  
	{  
		l2.s=Polygon[i];  
		l2.e=Polygon[(i+1)%n];  
		if(Geom_Dot_Online(l2,q)) 
			return 1; // 如果点在边上，返回1  
		if ( (bintersect_a=Geom_Line_Intersect_A(l1,l2))|| // 相交且不在端点  
		( (bonline1=Geom_Dot_Online(l1,Polygon[(i+1)%n]))&& // 第二个端点在射线上  
		( (!(bonline2=Geom_Dot_Online(l1,Polygon[(i+2)%n])))&& /* 前一个端点和后一个端点在射线两侧 */  
		((r1=Geom_Dot_Multiply(Polygon[i],Polygon[(i+1)%n],l1.s)*Geom_Dot_Multiply(Polygon[(i+1)%n],Polygon[(i+2)%n],l1.s))>0) ||     
		(bonline3=Geom_Dot_Online(l1,Polygon[(i+2)%n]))&&     /* 下一条边是水平线，前一个端点和后一个端点在射线两侧  */  
			((r2=Geom_Dot_Multiply(Polygon[i],Polygon[(i+2)%n],l1.s)*Geom_Dot_Multiply(Polygon[(i+2)%n],  
		Polygon[(i+3)%n],l1.s))>0)  
				)  
			)  
		) c++;  
	}  
	if(c%2 == 1)  
		return 0;  
	else  
		return 2;  
}  
//点q是凸多边形polygon内时，返回true；注意：多边形polygon一定要是凸多边形   
bool Geom_Polygon_PICPoly(int vcount,Geom_Point polygon[],Geom_Point q) // 可用于三角形！  
{  
	Geom_Point p;  
	Geom_LineSem l;  
	int i;  
	p.x=0;p.y=0;  
	for(i=0;i<vcount;i++) // 寻找一个肯定在多边形polygon内的点p：多边形顶点平均值  
	{  
		p.x+=polygon[i].x;  
		p.y+=polygon[i].y;  
	}  
	p.x /= vcount;  
	p.y /= vcount;  
 
	for(i=0;i<vcount;i++)  
	{  
		l.s=polygon[i];l.e=polygon[(i+1)%vcount];  
		if(Geom_Dot_Multiply(p,l.e,l.s)*Geom_Dot_Multiply(q,l.e,l.s)<0) /* 点p和点q在边l的两侧，说明点q肯定在多边形外 */  
		break;  
	}  
	return (i==vcount);  
}  
/**********************************************  
寻找凸包的graham 扫描法  
PointSet为输入的点集；  
ch为输出的凸包上的点集，按照逆时针方向排列;  
n为PointSet中的点的数目  
len为输出的凸包上的点的个数  
**********************************************/  
void Geom_Polygon_GrahamScan(Geom_Point PointSet[],Geom_Point ch[],int n,int &len)  
{  
	int i,j,k=0,top=2;  
	Geom_Point tmp;  
	// 选取PointSet中y坐标最小的点PointSet[k]，如果这样的点有多个，则取最左边的一个  
	for(i=1;i<n;i++)  
		if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) && (PointSet[i].x<PointSet[k].x) )  
			k=i;  
	tmp=PointSet[0];  
	PointSet[0]=PointSet[k];  
	PointSet[k]=tmp; // 现在PointSet中y坐标最小的点在PointSet[0]  
	for (i=1;i<n-1;i++) /* 对顶点按照相对PointSet[0]的极角从小到大进行排序，极角相同的按照距离PointSet[0]从近到远进行排序 */  
	{  
		k=i;  
		for (j=i+1;j<n;j++)  
			if (Geom_Dot_Multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||  // 极角更小     
				(Geom_Dot_Multiply(PointSet[j],PointSet[k],PointSet[0])==0) && /* 极角相等，距离更短 */         
				Geom_Dot_Dist(PointSet[0],PointSet[j])<Geom_Dot_Dist(PointSet[0],PointSet[k]) 
			   )  
				k=j;  
		tmp=PointSet[i];  
		PointSet[i]=PointSet[k];  
		PointSet[k]=tmp;  
	}  
	ch[0]=PointSet[0];  
	ch[1]=PointSet[1];  
	ch[2]=PointSet[2];  
	for (i=3;i<n;i++)  
	{  
		while (Geom_Dot_Multiply(PointSet[i],ch[top],ch[top-1])>=0)  
			top--;  
		ch[++top]=PointSet[i];  
	}  
	len=top+1;  
}  
// 卷包裹法求点集凸壳，参数说明同graham算法     
void Geom_Polygon_ConvexClosure(Geom_Point PointSet[],Geom_Point ch[],int n,int &len)  
{  
	int top=0,i,index,first;  
	double curmax,curcos,curdis;  
	Geom_Point tmp;  
	Geom_LineSem l1,l2;  
	bool use[MAXV];  
	tmp=PointSet[0];  
	index=0;  
	// 选取y最小点，如果多于一个，则选取最左点  
	for(i=1;i<n;i++)  
	{  
		if(PointSet[i].y<tmp.y||PointSet[i].y == tmp.y&&PointSet[i].x<tmp.x)  
		{  
			index=i;  
		}  
		use[i]=false;  
	}  
	tmp=PointSet[index];  
	first=index;  
	use[index]=true;  
 
	index=-1;  
	ch[top++]=tmp;  
	tmp.x-=100;  
	l1.s=tmp;  
	l1.e=ch[0];  
	l2.s=ch[0];  
 
	while(index!=first)  
	{  
		curmax=-100;  
		curdis=0;  
		// 选取与最后一条确定边夹角最小的点，即余弦值最大者  
		for(i=0;i<n;i++)  
		{  
			if(use[i])continue;  
			l2.e=PointSet[i];  
			curcos=Geom_Line_Cosine(l1,l2); // 根据cos值求夹角余弦，范围在 （-1 -- 1 ）  
			if(curcos>curmax || fabs(curcos-curmax)<1e-6 && Geom_Dot_Dist(l2.s,l2.e)>curdis)  
			{  
				curmax=curcos;  
				index=i;  
				curdis=Geom_Dot_Dist(l2.s,l2.e);  
			}  
		}  
		use[first]=false;            //清空第first个顶点标志，使最后能形成封闭的hull  
		use[index]=true;  
		ch[top++]=PointSet[index];  
		l1.s=ch[top-2];  
		l1.e=ch[top-1];  
		l2.s=ch[top-1];  
	}  
	len=top-1;  
}  
/*********************************************************************************************   
	判断线段是否在简单多边形内(注意：如果多边形是凸多边形，下面的算法可以化简)  
   	必要条件一：线段的两个端点都在多边形内；  
	必要条件二：线段和多边形的所有边都不内交；  
	用途：	1. 判断折线是否在简单多边形内  
			2. 判断简单多边形是否在另一个简单多边形内  
**********************************************************************************************/  
bool Geom_Polygon_LineSemIPoly(int vcount,Geom_Point polygon[],Geom_LineSem l)  
{  	
	// 判断线端l的端点是否不都在多边形内  
	if(!Geom_Polygon_PICPoly(vcount,polygon,l.s)||!Geom_Polygon_PICPoly(vcount,polygon,l.e))  
		return false;
	
	int top=0,i,j;  
	Geom_Point PointSet[MAXV],tmp;  
	Geom_LineSem s;  
 
	for(i=0;i<vcount;i++)  
	{  
		s.s=polygon[i];  
		s.e=polygon[(i+1)%vcount];  
		if(Geom_Dot_Online(s,l.s)) //线段l的起始端点在线段s上  
			PointSet[top++]=l.s;  
		else 
			if(Geom_Dot_Online(s,l.e)) //线段l的终止端点在线段s上 
				PointSet[top++]=l.e; 
			else  
			{  
				if(Geom_Dot_Online(l,s.s)) //线段s的起始端点在线段l上  
					PointSet[top++]=s.s;  
				else if(Geom_Dot_Online(l,s.e)) // 线段s的终止端点在线段l上  
					PointSet[top++]=s.e;  
				else  
				{  
					if(Geom_Line_Intersect(l,s)) // 这个时候如果相交，肯定是内交，返回false  
					return false;  
				}  
			}  
	}  
	
	for(i=0;i<top-1;i++) // 冒泡排序，x坐标小的排在前面；x坐标相同者，y坐标小的排在前面 
	{  
		for(j=i+1;j<top;j++)  
		{  
			if( PointSet[i].x>PointSet[j].x || fabs(PointSet[i].x-PointSet[j].x)<EP && PointSet[i].y>PointSet[j].y )  
			{  
				tmp=PointSet[i];  
				PointSet[i]=PointSet[j];  
				PointSet[j]=tmp;  
			}  
		}  
	}  
 
	for(i=0;i<top-1;i++)  
	{  
		tmp.x=(PointSet[i].x+PointSet[i+1].x)/2; //得到两个相邻交点的中点  
		tmp.y=(PointSet[i].y+PointSet[i+1].y)/2;  
		if(!Geom_Polygon_PIPoly(vcount,polygon,tmp))  
			return false;  
	}  
	return true;
} 

 
/*********************************************************************************************   
求任意简单多边形polygon的重心  
需要调用下面几个函数：  
	void AddPosPart(); 增加右边区域的面积  
	void AddNegPart(); 增加左边区域的面积  
	void AddRegion(); 增加区域面积  
在使用该程序时，如果把xtr,ytr,wtr,xtl,ytl,wtl设成全局变量就可以使这些函数的形式得到化简, 
但要注意函数的声明和调用要做相应变化  
**********************************************************************************************/  
void Geom_Polygon_AddPosPart(double x, double y, double w, double &xtr, double &ytr, double &wtr)  
{  
	if (fabs(wtr + w)<1e-10 ) return; // detect zero regions  
	xtr = ( wtr*xtr + w*x ) / ( wtr + w );  
	ytr = ( wtr*ytr + w*y ) / ( wtr + w );  
	wtr = w + wtr;  
	return;  
}  
void Geom_Polygon_AddNegPart(double x, double y, double w, double &xtl, double &ytl, double &wtl)  
{  
	if ( fabs(wtl + w)<1e-10 )  
		return; // detect zero regions  
 
	xtl = ( wtl*xtl + w*x ) / ( wtl + w );  
	ytl = ( wtl*ytl + w*y ) / ( wtl + w );  
	wtl = w + wtl;  
	return;  
}  
void Geom_Polygon_AddRegion ( double x1, double y1, double x2, double y2, double &xtr, double &ytr,  
		double &wtr, double &xtl, double &ytl, double &wtl )  
{  
	if ( fabs (x1 - x2)< 1e-10 )  
		return;  
 
	if ( x2 > x1 )  
	{  
		Geom_Polygon_AddPosPart ((x2+x1)/2, y1/2, (x2-x1) * y1,xtr,ytr,wtr); /* rectangle 全局变量变化处 */  
		Geom_Polygon_AddPosPart ((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtr,ytr,wtr);     
		// triangle 全局变量变化处  
	}  
	else  
	{  
		Geom_Polygon_AddNegPart((x2+x1)/2, y1/2, (x2-x1) * y1,xtl,ytl,wtl);   
		// rectangle 全局变量变化处  
		Geom_Polygon_AddNegPart((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtl,ytl,wtl);   
		// triangle  全局变量变化处  
	}  
}  
Geom_Point Geom_Polygon_CgSimple(int vcount,Geom_Point polygon[])  
{  
	double xtr,ytr,wtr,xtl,ytl,wtl;         
	//注意： 如果把xtr,ytr,wtr,xtl,ytl,wtl改成全局变量后这里要删去  
	Geom_Point p1,p2,tp;  
	xtr = ytr = wtr = 0.0;  
	xtl = ytl = wtl = 0.0;  
	for(int i=0;i<vcount;i++)  
	{  
		p1=polygon[i];  
		p2=polygon[(i+1)%vcount];  
		Geom_Polygon_AddRegion(p1.x,p1.y,p2.x,p2.y,xtr,ytr,wtr,xtl,ytl,wtl); //全局变量变化处  
	}  
	tp.x = (long)((wtr*xtr + wtl*xtl) / (wtr + wtl));  
	tp.y = (long)((wtr*ytr + wtl*ytl) / (wtr + wtl));  
	return tp;  
}  
// 求凸多边形的重心,要求输入多边形按逆时针排序  
Geom_Point Geom_Polygon_GravityCenter(int vcount,Geom_Point polygon[])  
{  
	Geom_Point tp;  
	double x,y,s,x0,y0,cs,k;  
	x=0;y=0;s=0;  
	for(int i=1;i<vcount-1;i++)  
	{  
		x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;  
		y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //求当前三角形的重心  
		cs=Geom_Dot_Multiply(polygon[i],polygon[i+1],polygon[0])/2;  
		//三角形面积可以直接利用该公式求解  
		if(fabs(s)<1e-20)  
		{  
			x=x0;y=y0;s+=cs;continue;  
		}  
		k=cs/s; //求面积比例  
		x=(x+k*x0)/(1+k);  
		y=(y+k*y0)/(1+k);  
		s += cs;  
	}  
	tp.x=(long)x;  
	tp.y=(long)y;  
	return tp;  
}  
 
/************************************************ 
给定一简单多边形，找出一个肯定在该多边形内的点  
定理1	：每个多边形至少有一个凸顶点  
定理2	：顶点数>=4的简单多边形至少有一条对角线  
结论	： x坐标最大，最小的点肯定是凸顶点  
	y坐标最大，最小的点肯定是凸顶点             
************************************************/  
Geom_Point Geom_Polygon_FinePInsidePoly(int vcount,Geom_Point polygon[])  
{  
	Geom_Point v,a,b,r;  
	int i,index;  
	v=polygon[0];  
	index=0;  
	for(i=1;i<vcount;i++) //寻找一个凸顶点  
	{  
		if(polygon[i].y<v.y)  
		{  
			v=polygon[i];  
			index=i;  
		}  
	}  
	a=polygon[(index-1+vcount)%vcount]; //得到v的前一个顶点  
	b=polygon[(index+1)%vcount]; //得到v的后一个顶点  
	Geom_Point tri[3],q;  
	tri[0]=a;tri[1]=v;tri[2]=b;  
	double md=INF;  
	int in1=index;  
	bool bin=false;  
	for(i=0;i<vcount;i++) //寻找在三角形avb内且离顶点v最近的顶点q  
	{  
		if(i == index)continue;  
		if(i == (index-1+vcount)%vcount)continue;  
		if(i == (index+1)%vcount)continue;  
		if(!Geom_Polygon_PICPoly(3,tri,polygon[i]))continue;  
		bin=true;  
		if(Geom_Dot_Dist(v,polygon[i])<md)  
		{  
			q=polygon[i];  
			md=Geom_Dot_Dist(v,q);  
		}  
	}  
	if(!bin) //没有顶点在三角形avb内，返回线段ab中点  
	{  
		r.x=(a.x+b.x)/2;  
		r.y=(a.y+b.y)/2;  
		return r;  
	}  
	r.x=(v.x+q.x)/2; //返回线段vq的中点  
	r.y=(v.y+q.y)/2;  
	return r;  
}  
/*********************************************************************************************** 
求从多边形外一点p出发到一个简单多边形的切线,如果存在返回切点,其中rp点是右切点,lp是左切点  
注意：p点一定要在多边形外 ,输入顶点序列是逆时针排列  
原 理：	如果点在多边形内肯定无切线;凸多边形有唯一的两个切点,凹多边形就可能有多于两个的切点;  
		如果polygon是凸多边形，切点只有两个只要找到就可以,可以化简此算法  
		如果是凹多边形还有一种算法可以求解:先求凹多边形的凸包,然后求凸包的切线  
/***********************************************************************************************/  
void Geom_Polygon_PTangent(int vcount,Geom_Point polygon[],Geom_Point p,Geom_Point &rp,Geom_Point &lp)  
{  
	Geom_LineSem ep,en;  
	bool blp,bln;  
	rp=polygon[0];  
	lp=polygon[0];  
	for(int i=1;i<vcount;i++)  
	{  
		ep.s=polygon[(i+vcount-1)%vcount];  
		ep.e=polygon[i];  
		en.s=polygon[i];  
		en.e=polygon[(i+1)%vcount];  
		blp=Geom_Dot_Multiply(ep.e,p,ep.s)>=0;                // p is to the left of pre edge  
		bln=Geom_Dot_Multiply(en.e,p,en.s)>=0;                // p is to the left of next edge  
		if(!blp&&bln)  
		{  
			if(Geom_Dot_Multiply(polygon[i],rp,p)>0)           // polygon[i] is above rp  
			rp=polygon[i];  
		}  
		if(blp&&!bln)  
		{  
			if(Geom_Dot_Multiply(lp,polygon[i],p)>0)           // polygon[i] is below lp  
			lp=polygon[i];  
		}  
	}  
	return ;  
}  
// 如果多边形polygon的核存在，返回true，返回核上的一点p.顶点按逆时针方向输入   
bool Geom_Polygon_CoreExist(int vcount,Geom_Point polygon[],Geom_Point &p)  
{  
	int i,j,k;  
	Geom_LineSem l;  
	Geom_Line lineset[MAXV];  
	for(i=0;i<vcount;i++)  
	{  
		lineset[i]=Geom_Line_MakeLine(polygon[i],polygon[(i+1)%vcount]);  
	}  
	for(i=0;i<vcount;i++)  
	{  
		for(j=0;j<vcount;j++)  
		{  
			if(i == j)continue;  
			if(Geom_Line_LIntersect(lineset[i],lineset[j],p))  
			{  
				for(k=0;k<vcount;k++)  
				{  
					l.s=polygon[k];  
					l.e=polygon[(k+1)%vcount];  
					if(Geom_Dot_Multiply(p,l.e,l.s)>0)       
					//多边形顶点按逆时针方向排列，核肯定在每条边的左侧或边上  
					break;  
				}  
				if(k == vcount)             //找到了一个核上的点  
				break;  
			}  
		}  
		if(j<vcount) break;  
	}  
	if(i<vcount)  
		return true;  
	else  
		return false;  
}  

// 二个多边形的相交面积
// int Geom_Polygon_InArea(int scrT,Geom_Point scr[],int trgT,Geom_Point trg[])
// {
// 	//判断点是否在多边形内
// 	if (scrT<trgT)
// 	{
// 		for (int i = 0;i<scrT;i++)
// 		{
// 			int err = Geom_Polygon_PIPoly(trgT,trg,scr[i]);
// 		}
// 		
// 	}
// 	else
// 	{
// 
// 	}
// }  