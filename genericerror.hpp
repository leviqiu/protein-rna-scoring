#ifndef _GEN_ERROR_H
#define _GEN_ERROR_H

#include <cstdio>
#include <qdock.hpp>

#define	FATAL	0
#define ERROR	-1
#define	WARNING	-2

extern	FILE *LOG;

void 
gen_error (const int, const char*, const int, const char*, ...);

void 
gen_closelog(void);

#endif /*_GEN_ERROR_H*/
