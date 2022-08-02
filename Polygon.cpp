/*//////////////////////////////////////////////////////////////////////////
�� ����γ����㷨ģ��  
1. �ж϶�����Ƿ�򵥶���� 8  
2. ������ζ����͹���� 9  
3. �ж϶�����Ƿ�͹����� 9  
4. ��������� 9  
5. �ж϶���ζ�������з��򣬷���һ 10  
6. �ж϶���ζ�������з��򣬷����� 10  
7. ���߷��жϵ��Ƿ��ڶ������ 10  
8. �жϵ��Ƿ���͹������� 11  
9. Ѱ�ҵ㼯��graham�㷨 12  
10.Ѱ�ҵ㼯͹���ľ������ 13  
11.�ж��߶��Ƿ��ڶ������ 14  
12.��򵥶���ε����� 15  
13.��͹����ε����� 17  
14.��϶��ڸ���������ڵ�һ���� 17  
15.��Ӷ������һ��������ö���ε����� 18  
16.�ж϶���εĺ��Ƿ���� 19  
//////////////////////////////////////////////////////////////////////////*/

#include "StdAfx.h"
#include "Geom.h"
#include "Geomlibdef.h"

/******************************\  
*							  *  
* ����γ����㷨ģ��		  *  
*							  *  
\******************************/  
 
// ������ر�˵�����������ζ���Ҫ����ʱ������  
 
/*  
����ֵ������Ķ�����Ǽ򵥶���Σ�����true  
Ҫ �����붥�����а���ʱ������  
˵ �����򵥶���ζ��壺  
1��ѭ�������������߶ζԵĽ�������֮�乲�еĵ�����  
2�������ڵ��߶β��ཻ  
������Ĭ�ϵ�һ�������Ѿ�����  
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
// ����ֵ��������˳�򷵻ض���ζ����͹�����жϣ�bc[i]=1,iff:��i��������͹����  
void Geom_Polygon_CheckConvex(int vcount,Geom_Point polygon[],bool bc[])  
{  
	int i,index=0;  
	Geom_Point tp=polygon[0];  
	for(i=1;i<vcount;i++) // Ѱ�ҵ�һ��͹����  
	{  
		if(polygon[i].y<tp.y||(polygon[i].y == tp.y&&polygon[i].x<tp.x))  
		{  
			tp=polygon[i];  
			index=i;  
		}  
	}  
	int count=vcount-1;  
	bc[index]=1;  
	while(count) // �ж�͹����  
	{  
		if(Geom_Dot_Multiply(polygon[(index+1)%vcount],polygon[(index+2)%vcount],polygon[index])>=0 )  
			bc[(index+1)%vcount]=1;  
		else  
			bc[(index+1)%vcount]=0;  
		index++;  
		count--;  
	}  
} 
// ����ֵ�������polygon��͹�����ʱ������true   
bool Geom_Polygon_IsConvex(int vcount,Geom_Point polygon[])  
{  
	bool bc[MAXV];  
	Geom_Polygon_CheckConvex(vcount,polygon,bc);  
	for(int i=0;i<vcount;i++) // ��һ��鶥�㣬�Ƿ�ȫ����͹����  
		if(!bc[i])  
			return false;  
	return true;  
}  
// ���ض�������(signed)�����붥�㰴��ʱ������ʱ��������ֵ�����򷵻ظ�ֵ  
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
// ������붥�㰴��ʱ�����У�����true  
bool Geom_Polygon_IsConterClock(int vcount,Geom_Point polygon[])  
{  
	return Geom_Polygon_Area(vcount,polygon)>0;  
}  
// ��һ���ж϶���ζ������з���ķ���   
bool Geom_Polygon_IsCcwize(int vcount,Geom_Point polygon[])  
{  
	int i,index;  
	Geom_Point a,b,v;  
	v=polygon[0];  
	index=0;  
	for(i=1;i<vcount;i++) // �ҵ���������󶥵㣬�϶���͹����  
	{  
		if(polygon[i].y<v.y||polygon[i].y == v.y && polygon[i].x<v.x)  
		{  
			index=i;  
		}  
	}  
	a=polygon[(index-1+vcount)%vcount]; // ����v��ǰһ����  
	b=polygon[(index+1)%vcount]; // ����v�ĺ�һ����  
	return Geom_Dot_Multiply(v,b,a)>0;  
}  
/********************************************************************************************    
���߷��жϵ�q������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ������  
   ������ڶ�����ڣ�   ����0  
   ������ڶ���α��ϣ� ����1  
   ������ڶ�����⣺	����2  
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
			return 1; // ������ڱ��ϣ�����1  
		if ( (bintersect_a=Geom_Line_Intersect_A(l1,l2))|| // �ཻ�Ҳ��ڶ˵�  
		( (bonline1=Geom_Dot_Online(l1,Polygon[(i+1)%n]))&& // �ڶ����˵���������  
		( (!(bonline2=Geom_Dot_Online(l1,Polygon[(i+2)%n])))&& /* ǰһ���˵�ͺ�һ���˵����������� */  
		((r1=Geom_Dot_Multiply(Polygon[i],Polygon[(i+1)%n],l1.s)*Geom_Dot_Multiply(Polygon[(i+1)%n],Polygon[(i+2)%n],l1.s))>0) ||     
		(bonline3=Geom_Dot_Online(l1,Polygon[(i+2)%n]))&&     /* ��һ������ˮƽ�ߣ�ǰһ���˵�ͺ�һ���˵�����������  */  
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
//��q��͹�����polygon��ʱ������true��ע�⣺�����polygonһ��Ҫ��͹�����   
bool Geom_Polygon_PICPoly(int vcount,Geom_Point polygon[],Geom_Point q) // �����������Σ�  
{  
	Geom_Point p;  
	Geom_LineSem l;  
	int i;  
	p.x=0;p.y=0;  
	for(i=0;i<vcount;i++) // Ѱ��һ���϶��ڶ����polygon�ڵĵ�p������ζ���ƽ��ֵ  
	{  
		p.x+=polygon[i].x;  
		p.y+=polygon[i].y;  
	}  
	p.x /= vcount;  
	p.y /= vcount;  
 
	for(i=0;i<vcount;i++)  
	{  
		l.s=polygon[i];l.e=polygon[(i+1)%vcount];  
		if(Geom_Dot_Multiply(p,l.e,l.s)*Geom_Dot_Multiply(q,l.e,l.s)<0) /* ��p�͵�q�ڱ�l�����࣬˵����q�϶��ڶ������ */  
		break;  
	}  
	return (i==vcount);  
}  
/**********************************************  
Ѱ��͹����graham ɨ�跨  
PointSetΪ����ĵ㼯��  
chΪ�����͹���ϵĵ㼯��������ʱ�뷽������;  
nΪPointSet�еĵ����Ŀ  
lenΪ�����͹���ϵĵ�ĸ���  
**********************************************/  
void Geom_Polygon_GrahamScan(Geom_Point PointSet[],Geom_Point ch[],int n,int &len)  
{  
	int i,j,k=0,top=2;  
	Geom_Point tmp;  
	// ѡȡPointSet��y������С�ĵ�PointSet[k]����������ĵ��ж������ȡ����ߵ�һ��  
	for(i=1;i<n;i++)  
		if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) && (PointSet[i].x<PointSet[k].x) )  
			k=i;  
	tmp=PointSet[0];  
	PointSet[0]=PointSet[k];  
	PointSet[k]=tmp; // ����PointSet��y������С�ĵ���PointSet[0]  
	for (i=1;i<n-1;i++) /* �Զ��㰴�����PointSet[0]�ļ��Ǵ�С����������򣬼�����ͬ�İ��վ���PointSet[0]�ӽ���Զ�������� */  
	{  
		k=i;  
		for (j=i+1;j<n;j++)  
			if (Geom_Dot_Multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||  // ���Ǹ�С     
				(Geom_Dot_Multiply(PointSet[j],PointSet[k],PointSet[0])==0) && /* ������ȣ�������� */         
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
// ���������㼯͹�ǣ�����˵��ͬgraham�㷨     
void Geom_Polygon_ConvexClosure(Geom_Point PointSet[],Geom_Point ch[],int n,int &len)  
{  
	int top=0,i,index,first;  
	double curmax,curcos,curdis;  
	Geom_Point tmp;  
	Geom_LineSem l1,l2;  
	bool use[MAXV];  
	tmp=PointSet[0];  
	index=0;  
	// ѡȡy��С�㣬�������һ������ѡȡ�����  
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
		// ѡȡ�����һ��ȷ���߼н���С�ĵ㣬������ֵ�����  
		for(i=0;i<n;i++)  
		{  
			if(use[i])continue;  
			l2.e=PointSet[i];  
			curcos=Geom_Line_Cosine(l1,l2); // ����cosֵ��н����ң���Χ�� ��-1 -- 1 ��  
			if(curcos>curmax || fabs(curcos-curmax)<1e-6 && Geom_Dot_Dist(l2.s,l2.e)>curdis)  
			{  
				curmax=curcos;  
				index=i;  
				curdis=Geom_Dot_Dist(l2.s,l2.e);  
			}  
		}  
		use[first]=false;            //��յ�first�������־��ʹ������γɷ�յ�hull  
		use[index]=true;  
		ch[top++]=PointSet[index];  
		l1.s=ch[top-2];  
		l1.e=ch[top-1];  
		l2.s=ch[top-1];  
	}  
	len=top-1;  
}  
/*********************************************************************************************   
	�ж��߶��Ƿ��ڼ򵥶������(ע�⣺����������͹����Σ�������㷨���Ի���)  
   	��Ҫ����һ���߶ε������˵㶼�ڶ�����ڣ�  
	��Ҫ���������߶κͶ���ε����б߶����ڽ���  
	��;��	1. �ж������Ƿ��ڼ򵥶������  
			2. �жϼ򵥶�����Ƿ�����һ���򵥶������  
**********************************************************************************************/  
bool Geom_Polygon_LineSemIPoly(int vcount,Geom_Point polygon[],Geom_LineSem l)  
{  	
	// �ж��߶�l�Ķ˵��Ƿ񲻶��ڶ������  
	if(!Geom_Polygon_PICPoly(vcount,polygon,l.s)||!Geom_Polygon_PICPoly(vcount,polygon,l.e))  
		return false;
	
	int top=0,i,j;  
	Geom_Point PointSet[MAXV],tmp;  
	Geom_LineSem s;  
 
	for(i=0;i<vcount;i++)  
	{  
		s.s=polygon[i];  
		s.e=polygon[(i+1)%vcount];  
		if(Geom_Dot_Online(s,l.s)) //�߶�l����ʼ�˵����߶�s��  
			PointSet[top++]=l.s;  
		else 
			if(Geom_Dot_Online(s,l.e)) //�߶�l����ֹ�˵����߶�s�� 
				PointSet[top++]=l.e; 
			else  
			{  
				if(Geom_Dot_Online(l,s.s)) //�߶�s����ʼ�˵����߶�l��  
					PointSet[top++]=s.s;  
				else if(Geom_Dot_Online(l,s.e)) // �߶�s����ֹ�˵����߶�l��  
					PointSet[top++]=s.e;  
				else  
				{  
					if(Geom_Line_Intersect(l,s)) // ���ʱ������ཻ���϶����ڽ�������false  
					return false;  
				}  
			}  
	}  
	
	for(i=0;i<top-1;i++) // ð������x����С������ǰ�棻x������ͬ�ߣ�y����С������ǰ�� 
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
		tmp.x=(PointSet[i].x+PointSet[i+1].x)/2; //�õ��������ڽ�����е�  
		tmp.y=(PointSet[i].y+PointSet[i+1].y)/2;  
		if(!Geom_Polygon_PIPoly(vcount,polygon,tmp))  
			return false;  
	}  
	return true;
} 

 
/*********************************************************************************************   
������򵥶����polygon������  
��Ҫ�������漸��������  
	void AddPosPart(); �����ұ���������  
	void AddNegPart(); ���������������  
	void AddRegion(); �����������  
��ʹ�øó���ʱ�������xtr,ytr,wtr,xtl,ytl,wtl���ȫ�ֱ����Ϳ���ʹ��Щ��������ʽ�õ�����, 
��Ҫע�⺯���������͵���Ҫ����Ӧ�仯  
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
		Geom_Polygon_AddPosPart ((x2+x1)/2, y1/2, (x2-x1) * y1,xtr,ytr,wtr); /* rectangle ȫ�ֱ����仯�� */  
		Geom_Polygon_AddPosPart ((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtr,ytr,wtr);     
		// triangle ȫ�ֱ����仯��  
	}  
	else  
	{  
		Geom_Polygon_AddNegPart((x2+x1)/2, y1/2, (x2-x1) * y1,xtl,ytl,wtl);   
		// rectangle ȫ�ֱ����仯��  
		Geom_Polygon_AddNegPart((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtl,ytl,wtl);   
		// triangle  ȫ�ֱ����仯��  
	}  
}  
Geom_Point Geom_Polygon_CgSimple(int vcount,Geom_Point polygon[])  
{  
	double xtr,ytr,wtr,xtl,ytl,wtl;         
	//ע�⣺ �����xtr,ytr,wtr,xtl,ytl,wtl�ĳ�ȫ�ֱ���������Ҫɾȥ  
	Geom_Point p1,p2,tp;  
	xtr = ytr = wtr = 0.0;  
	xtl = ytl = wtl = 0.0;  
	for(int i=0;i<vcount;i++)  
	{  
		p1=polygon[i];  
		p2=polygon[(i+1)%vcount];  
		Geom_Polygon_AddRegion(p1.x,p1.y,p2.x,p2.y,xtr,ytr,wtr,xtl,ytl,wtl); //ȫ�ֱ����仯��  
	}  
	tp.x = (long)((wtr*xtr + wtl*xtl) / (wtr + wtl));  
	tp.y = (long)((wtr*ytr + wtl*ytl) / (wtr + wtl));  
	return tp;  
}  
// ��͹����ε�����,Ҫ���������ΰ���ʱ������  
Geom_Point Geom_Polygon_GravityCenter(int vcount,Geom_Point polygon[])  
{  
	Geom_Point tp;  
	double x,y,s,x0,y0,cs,k;  
	x=0;y=0;s=0;  
	for(int i=1;i<vcount-1;i++)  
	{  
		x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;  
		y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //��ǰ�����ε�����  
		cs=Geom_Dot_Multiply(polygon[i],polygon[i+1],polygon[0])/2;  
		//�������������ֱ�����øù�ʽ���  
		if(fabs(s)<1e-20)  
		{  
			x=x0;y=y0;s+=cs;continue;  
		}  
		k=cs/s; //���������  
		x=(x+k*x0)/(1+k);  
		y=(y+k*y0)/(1+k);  
		s += cs;  
	}  
	tp.x=(long)x;  
	tp.y=(long)y;  
	return tp;  
}  
 
/************************************************ 
����һ�򵥶���Σ��ҳ�һ���϶��ڸö�����ڵĵ�  
����1	��ÿ�������������һ��͹����  
����2	��������>=4�ļ򵥶����������һ���Խ���  
����	�� x���������С�ĵ�϶���͹����  
	y���������С�ĵ�϶���͹����             
************************************************/  
Geom_Point Geom_Polygon_FinePInsidePoly(int vcount,Geom_Point polygon[])  
{  
	Geom_Point v,a,b,r;  
	int i,index;  
	v=polygon[0];  
	index=0;  
	for(i=1;i<vcount;i++) //Ѱ��һ��͹����  
	{  
		if(polygon[i].y<v.y)  
		{  
			v=polygon[i];  
			index=i;  
		}  
	}  
	a=polygon[(index-1+vcount)%vcount]; //�õ�v��ǰһ������  
	b=polygon[(index+1)%vcount]; //�õ�v�ĺ�һ������  
	Geom_Point tri[3],q;  
	tri[0]=a;tri[1]=v;tri[2]=b;  
	double md=INF;  
	int in1=index;  
	bool bin=false;  
	for(i=0;i<vcount;i++) //Ѱ����������avb�����붥��v����Ķ���q  
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
	if(!bin) //û�ж�����������avb�ڣ������߶�ab�е�  
	{  
		r.x=(a.x+b.x)/2;  
		r.y=(a.y+b.y)/2;  
		return r;  
	}  
	r.x=(v.x+q.x)/2; //�����߶�vq���е�  
	r.y=(v.y+q.y)/2;  
	return r;  
}  
/*********************************************************************************************** 
��Ӷ������һ��p������һ���򵥶���ε�����,������ڷ����е�,����rp�������е�,lp�����е�  
ע�⣺p��һ��Ҫ�ڶ������ ,���붥����������ʱ������  
ԭ ��	������ڶ�����ڿ϶�������;͹�������Ψһ�������е�,������ξͿ����ж����������е�;  
		���polygon��͹����Σ��е�ֻ������ֻҪ�ҵ��Ϳ���,���Ի�����㷨  
		����ǰ�����λ���һ���㷨�������:���󰼶���ε�͹��,Ȼ����͹��������  
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
// ��������polygon�ĺ˴��ڣ�����true�����غ��ϵ�һ��p.���㰴��ʱ�뷽������   
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
					//����ζ��㰴��ʱ�뷽�����У��˿϶���ÿ���ߵ��������  
					break;  
				}  
				if(k == vcount)             //�ҵ���һ�����ϵĵ�  
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

// ��������ε��ཻ���
// int Geom_Polygon_InArea(int scrT,Geom_Point scr[],int trgT,Geom_Point trg[])
// {
// 	//�жϵ��Ƿ��ڶ������
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