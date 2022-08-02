
#ifndef        _GEOMDEF_H
#define        _GEOMDEF_H

#if defined(_AFXDLL) || defined(_USRDLL)
    #define GEOM_EXP __declspec(dllexport)
#elif defined(_MSC_VER)&&(_MSC_VER<1200)
    #define GEOM_EXP __declspec(dllimport)
#else
    #define GEOM_EXP
#endif

#ifndef EPSILON
#define EPSILON 0.001f
#endif

#ifndef PI
#define PI 3.1415926f
#endif

#ifndef SIGN_BIT
#define SIGN_BIT 0x80000000
#endif

#ifndef INV_SIGN_BIT
#define INV_SIGN_BIT 0x7FFFFFFF
#endif

#ifndef INF
#define INF 1E200
#endif

#ifndef EP
#define	EP 1E-10
#endif

#ifndef MAXV
#define MAXV 300
#endif


#include <math.h>
#include <stdlib.h>


#endif // _GEOMDEF_H