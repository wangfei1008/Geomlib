// Point2D.h: interface for the CPoint2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT2D_H__BC6F7D3D_9E2C_44C4_AED0_F94CEA9A7710__INCLUDED_)
#define AFX_POINT2D_H__BC6F7D3D_9E2C_44C4_AED0_F94CEA9A7710__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geomlibdef.h"

template<typename T>
class GEOM_EXP CPoint2D  
{
private:
	T x;
	T y;  
public:
	//Default constructor, defined for template classes
	CPoint2D()
	{}
	virtual ~CPoint2D()
	{}
	// Construct a point with 2 given inputs
    CPoint2D( T _x, T _y ): x(_x), y(_y)
    {}
	CPoint2D( const CPoint2D& in )
    {
        x = in.x;
        y = in.y;
    }
    // Reassign a point without making a temporary structure
    void assign( T _x, T _y)
    {
        x = _x;    y = _y;
    }

   // Return the magnitude of a point
    T mag() const
    {
        return (T) sqrt( x*x + y*y );
    }
	
    // The length of the vector squared (to avoid the sqrt() )
    T magsq() const
    {
        return (T) ( x*x + y*y );
    }
	
    // Normalizes a vector (makes it's length one)
    void norm()
    {
        T invMag = 1.f / mag();
        (*this) *= invMag;
    }
	
    // Computes the distance between two vectors
    static T dist( const CPoint2D &a, const CPoint2D &b )
    {
        // can't use the subtraction operator (it's not defined yet!)
        CPoint2D    vec( b.x - a.x, b.y - a.y );
        return    vec.mag();
    }
	
    // Computes the distance square between two vectors
    static T distsq( const CPoint2D &a, const CPoint2D &b )
    {
        // can't use the subtraction operator (it's not defined yet!)
        CPoint2D    vec( b.x - a.x, b.y - a.y );
        return    vec.magsq();
    }
	
	
    //
    //operators overload:
    //Accumulative addition of two vectors
    CPoint2D& operator += ( const CPoint2D& in )
    {
        x += in.x;   
        y += in.y;   
        
		return *this;
    }
	
    // Accumulative subtraction of two vectors
    CPoint2D& operator -= ( const CPoint2D& in )
    {
        x -= in.x;   
        y -= in.y;
		
        return *this;
    }
	
    // Accumulative multiplication of a vector by a scalar
    CPoint2D& operator *= ( const T& s )
    {
        x *= s;   
        y *= s;   
        return *this;
    }
	
    // Accumulative division of a vector by a scalar
    CPoint2D& operator /= ( const T& s )
    {
        T inv = 1.f / s;
        x *= inv;   
        y *= inv;
        return *this;
    }
	
    CPoint2D  operator - ()
    {
        return CPoint2D(-x, -y);
    }
	
    //
    // Constant vectors
    //
    static const CPoint2D<T>    Zero;
    static const CPoint2D<T>    i;
    static const CPoint2D<T>    j;

};

// Adds two points together: ret = a + b
template<typename T> 
inline const CPoint2D<T> operator + (const CPoint2D<T> &a, const CPoint2D<T> &b)
{
    return CPoint2D<T>( a.x+b.x, a.y+b.y );
}

// Subtracts to points : ret = a - b
template<typename T>
inline const CPoint2D<T> operator - (const CPoint2D<T>  &a, const CPoint2D<T>  &b)
{
    return CPoint2D<T>( a.x-b.x, a.y-b.y );
}

// Scales a vector by a scalar : ret = a * s
template<typename T>
inline const CPoint2D<T> operator * (const CPoint2D<T>  &a, const T& s)
{
    return CPoint2D<T>( a.x*s, a.y*s );
} 

// Scales a vector by a scalar : ret = s * b
template<typename T>
inline const CPoint2D<T> operator * (const T& s, const CPoint2D<T>& b)
{
    return CPoint2D<T>( s*b.x, s*b.y );
} 

// Divides a vector by a scalar : ret = a / f
template<typename T>
inline const CPoint2D<T> operator / (const CPoint2D<T>& a, const T& s)
{
    T inv = 1.f / s;
    return CPoint2D<T>( a.x*inv, a.y*inv );
}

// Performs a vector dot product : ret = a dot b
template<typename T>
inline const T operator * (const CPoint2D<T>& a, const CPoint2D<T>& b)
{
    return a.x*b.x + a.y*b.y;
} 

// Vector Equality, epsilon used due to numerical imprecision
template<typename T>
inline bool operator == (const CPoint2D<T>& a, const CPoint2D<T>& b)
{
    if( fabs(a.x-b.x) < EPSILON && fabs(a.y-b.y) < EPSILON && fabs(a.z-b.z) < EPSILON )
        return true;
    return false;
}

#endif // !defined(AFX_POINT2D_H__BC6F7D3D_9E2C_44C4_AED0_F94CEA9A7710__INCLUDED_)
