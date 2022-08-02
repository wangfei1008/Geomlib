// Point4D.h: interface for the CPoint4D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT4D_H__D297C070_6565_4F68_9695_50C8F5D045B1__INCLUDED_)
#define AFX_POINT4D_H__D297C070_6565_4F68_9695_50C8F5D045B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point3D.h"

template <typename T>
class GEOM_EXP CPoint4D  
{
private:
	T x;
	T y;
	T z;
	T w;
public:
	
	// Default constructor, defined for template classes
    CPoint4D()
    {}
	virtual ~CPoint4D()
	{
	}
    // Construct a point with 4 given inputs
    CPoint4D( T _x, T _y, T _z, T _w=1.f ): x(_x), y(_y), z(_z), w(_w)
    {}
	
    CPoint4D( const CPoint4D& in ): x(in.x), y(in.y), z(in.z), w(in.w)
    {
    }
    CPoint4D( const CPoint3D<T>& in ): x(in.x), y(in.y), z(in.z), w(1.f)
    {
    }
    
    // Reassign a point without making a temporary structure
    void assign( T _x, T _y, T _z, T _w )
    {
        x=_x; y=_y; z=_z; w=_w;
    }
	
    // Negate a vector
    void neg()
    {
        x=-x; y=-y;    z=-z; w=-w;
    }
	
    // Return the magnitude of a point
    T mag()
    {
        return (T) sqrt( x*x + y*y + z*z + w*w );
    }
	
    // Normalizes a vector (makes it's length 1)
    void norm()
    {
        T inv = 1 / mag();
        x *= inv;    
        y *= inv;    
        z *= inv; 
        w *= inv;
    }
};

// Adds two points together: ret = a + b
template<typename T> 
inline const CPoint4D<T> operator + (const CPoint4D<T>& a, const CPoint4D<T>& b)
{
    return CPoint4D<T>( a.x+b.x,a.y+b.y,a.z+b.z,a.w+b.w );
}

// Subtracts to points : ret = a - b
template<typename T> 
inline const CPoint4D<T> operator - (const CPoint4D<T>& a, const CPoint4D<T>& b)
{
    return CPoint4D<T>( a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w );
}

// Scales a vector by a scalar : ret = a * s
template<typename T> 
inline const CPoint4D<T> operator * (const CPoint4D<T>& a, const T &s)
{
    return CPoint4D<T>( a.x*s, a.y*s, a.z*s, a.w*s );
}

// Scales a vector by a scalar : ret = s * a
template<typename T> 
inline const CPoint4D<T> operator * (const T &s, const CPoint4D<T>& a)
{
    return CPoint4D<T>( s*a.x, s*a.y, s*a.z, s*a.w );
}

// Divides a vector by a scalar : ret = a / s
template<typename T>
inline const CPoint4D<T> operator / (const CPoint4D<T> &a, const T &s)
{
    return CPoint4D<T>(a.x/s, a.y/s, a.z/s, a.w/s);
}

// Vector Equality, epsilon used due to numerical imprecision
template<typename T>
inline bool operator == (const CPoint4D<T>& a, const CPoint4D<T>& b)
{
    if(fabs(a.x-b.x)<EPSILON && fabs(a.y-b.y)<EPSILON && fabs(a.z-b.z)<EPSILON && fabs(a.w-b.w)<EPSILON)
        return true;
    return false;
}

// Performs a vector dot product : ret = a dot b
template<typename T>
inline T operator * (const CPoint4D<T>& a, const CPoint4D<T>& b)
{
    return (T) (a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
} 

#endif // !defined(AFX_POINT4D_H__D297C070_6565_4F68_9695_50C8F5D045B1__INCLUDED_)
