#ifndef _QDOCK_H
#define	_QDOCK_H

#include <cmath>

typedef double		qd_double;
typedef	float 		qd_real;
typedef int   		qd_int;
typedef unsigned int	qd_uint;
typedef float		qd_complex[2];

struct score {
	qd_int	i;
	qd_int	j;
	qd_int	k;
	qd_real	R[9];
	qd_real	v;
};

typedef score Cn_score;
typedef score Z_score;

struct Dn_score : public score {
	qd_int	l;
	qd_real	x;
	qd_real	y;
	qd_real z;
	qd_real R_Z[9];
};

#if defined __USE_BSD || defined __USE_XOPEN
#define	PI	M_PI
#define	EULER	M_E
#define	sqrt2	M_SQRT2
#endif

#if defined __USE_GNU
#undef	PI
#define PI	M_PIl
#undef	EULER
#define	EULER	M_El
#undef	sqrt2
#define	sqrt2	M_SQRT2l
#endif

#define	EPS	(1E-5)
#define	SQ(X)	((X) * (X))
#define	IS_EQUAL(A,B) (fabs((A) - (B)) < EPS ? true : false)
#define ANGLE_CONVERSION(F,A)	((F) == 0 ? PI * (A) / 180.0 : (A))

#if defined TEST
#define INTERNAL
#else
#define INTERNAL	static
#endif

#endif /*_QDOCK_H*/
