// Point3D.h: interface for the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT3D_H__CCE31A21_10A8_4FCC_B4F9_D16471412EE7__INCLUDED_)
#define AFX_POINT3D_H__CCE31A21_10A8_4FCC_B4F9_D16471412EE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point2D.h"

template <typename T>
class GEOM_EXP CPoint3D  
{
private:
	T x;
	T y;
	T z;
public:
	
	// Default constructor, defined for template classes
    CPoint3D()
    {}
	virtual ~CPoint3D()
	{}
    // Construct a point with 3 given inputs
    CPoint3D( T _x, T _y, T _z ): x(_x), y(_y), z(_z)
    {}

    CPoint3D( const CPoint3D& in ): x(in.x), y(in.y), z(in.z)
    {
    }

    CPoint3D( const CPoint2D<T>& in ): x(in.x), y(in.y), z(0.f)
    {
    }
    
    // Construct a point using spherical coordinates
    template<typename T> static const CPoint3D<T> Spherical( T theta, T rho, T phi )
    {
        return CPoint3D<T>((T)(phi*cos(rho)*sin(theta)), (T)(phi*sin(rho)), (T)(phi*cos(rho)*cos(theta)));
    }

    // Reassign a point without making a temporary structure
    void assign( T _x, T _y, T _z)
    {
        x = _x;    y = _y; z = _z;
    }
    
    // Return the magnitude of a point
    T mag() const
    {
        return (T) sqrt( x*x + y*y + z*z);
    }

    // The length of the vector squared (to avoid the sqrt() )
    T magsq() const
    {
        return (T) ( x*x + y*y + z*z);
    }

    // Normalizes a vector (makes it's length 1)
    void norm()
    {
        T invMag = 1.f / mag();
        (*this) *= invMag;
    }

    // Computes the distance between two vectors
    static T dist( const CPoint3D &a, const CPoint3D &b )
    {
        // can't use the subtraction operator (it's not defined yet!)
        CPoint3D vec( b.x - a.x, b.y - a.y, b.z - a.z );
        return    vec.mag();
    }

    // Computes the distance square between two vectors
    static T distsq( const CPoint3D &a, const CPoint3D &b )
    {
        // can't use the subtraction operator (it's not defined yet!)
        CPoint3D vec( b.x - a.x, b.y - a.y, b.z - a.z );
        return    vec.magsq();
    }
    
    //
    // operators overload:
    //
    // Accumulative addition of two vectors
    CPoint3D& operator += ( const CPoint3D& in )
    {
        x += in.x;   
        y += in.y;   
        z += in.z; 
        return *this;
    }

    // Accumulative subtraction of two vectors
    CPoint3D& operator -= ( const CPoint3D& in )
    {
        x -= in.x;   
        y -= in.y;   
        z -= in.z;   
        return *this;
    }

    // Accumulative multiplication of a vector by a scalar
    CPoint3D& operator *= ( const T& s )
    {
        x *= s;   
        y *= s;   
        z *= s;   
        return *this;
    }

    // Accumulative division of a vector by a scalar
    CPoint3D& operator /= ( const T& s )
    {
        T inv = 1.f / s;
        x *= inv;   
        y *= inv;
        z *= inv;
        return *this;
    }

    CPoint3D  operator -  ()
    {
        return CPoint3D(-x, -y, -z);
    }

    //
    // Constant vectors
    //
    static const CPoint3D<T>    Zero;
    static const CPoint3D<T>    i;
    static const CPoint3D<T>    j;
    static const CPoint3D<T>    k;
};

// Adds two points together: ret = a + b
template<typename T> 
inline const CPoint3D<T> operator + (const CPoint3D<T>& a, const CPoint3D<T>& b)
{
    return CPoint3D<T>( a.x+b.x, a.y+b.y, a.z+b.z );
}

// Subtracts to points : ret = a - b
template<typename T> 
inline const CPoint3D<T> operator - (const CPoint3D<T>& a, const CPoint3D<T>& b)
{
    return CPoint3D<T>( a.x-b.x, a.y-b.y, a.z-b.z );
}

// Scales a vector by a scalar : ret = a * s
template<typename T> 
inline const CPoint3D<T> operator * (const CPoint3D<T>& a, const T &s)
{
    return CPoint3D<T>( a.x*s, a.y*s, a.z*s );
}

// Scales a vector by a scalar : ret = s * b
template<typename T> 
inline const CPoint3D<T> operator * (const T& s, const CPoint3D<T>& b)
{
    return CPoint3D<T>( s*b.x, s*b.y, s*b.z );
}

// Divides a vector by a scalar : ret = a / s
template<typename T> 
inline const CPoint3D<T> operator / (const CPoint3D<T>& a, float const &s)
{
    T inv = 1.0 / s;
    return CPoint3D<T>( a.x*inv, a.y*inv, a.z*inv );
}

// Performs a vector cross product : ret = a cross b
template<typename T> 
inline const CPoint3D<T> operator ^ (const CPoint3D<T>& a, const CPoint3D<T>& b)
{
    return CPoint3D<T>( (a.y*b.z-a.z*b.y), (a.z*b.x-a.x*b.z), (a.x*b.y-a.y*b.x) );
} 

// Performs a vector dot product : ret = a dot b
template<typename T> 
inline const T operator * (const CPoint3D<T>& a, const CPoint3D<T>& b)
{
    return (T) (a.x*b.x + a.y*b.y + a.z*b.z);
} 

// Vector Equality, epsilon used due to numerical imprecision
template<typename T> 
inline bool operator == (const CPoint3D<T>& a, const CPoint3D<T>& b)
{
    if(fabs(a.x-b.x) < EPSILON && fabs(a.y-b.y) < EPSILON && fabs(a.z-b.z) < EPSILON )
        return true;        
    return false;
}

#endif // !defined(AFX_POINT3D_H__CCE31A21_10A8_4FCC_B4F9_D16471412EE7__INCLUDED_)
