#ifndef _GENMALLOC_H
#define _GENMALLOC_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <genericerror.hpp>

template<typename T>
void genfree (T *p)
{
	if (p != 0)
		free (p);
}

template<typename T>
void genmalloc(T **p, size_t num, const char *file, int line)
{
        if (num == 0) {
		*p = 0;
		return;
	}

	void *ptr = 0;
	ptr = malloc(num);
	if (ptr == NULL)
		gen_error(FATAL, file, line,
			  "Memory exhausted. Failed to malloc %u bytes", num);

	memset(ptr,0,num);
	*p = reinterpret_cast<T*>(ptr);
}

template<typename T>
void align_genmalloc(T **p, size_t num,size_t alignment, const char *file, int line)
{	
	if (num == 0) {
		*p = 0;
		return;
	}

	void *ptr = 0;	
	posix_memalign(&ptr,alignment,num);
	if (ptr == 0)
		gen_error(FATAL, file, line,
			  "Memory exhausted. Failed to posix_memalign %ld bytes", num);

	memset(ptr,0,num);
	*p = reinterpret_cast<T*>(ptr);
}

template<typename T>
void genrealloc (T **p, size_t num, const char *file, int line)
{
	if (*p == 0 && num > 0) {
		genmalloc(p, num, file, line);		
		return;
	}

	if (*p != 0 && num == 0) {
		genfree(*p);
		return;
	}

	void *ptr = 0;
	ptr = realloc(p, num);
	if (ptr == 0)
		gen_error(FATAL, file, line,
			  "Memory exhausted. Failed to realloc %u bytes", num);

	*p = reinterpret_cast<T*>(ptr);
}

template<typename T>
void gencalloc (T **p, size_t num, size_t size, const char *file, int line)
{
	if (num == 0 || size == 0) {
		*p = 0;
		return;
	}

	void *ptr = 0;
	ptr = calloc(num, size);
	if (ptr == 0)
		gen_error(FATAL, file, line,
			  "Memory exhausted. Failed to calloc %u bytes)", num * size);

	memset (ptr, 0, (size_t)(num * size));
	*p = reinterpret_cast<T*>(ptr);
}

#endif /*_GENMALLOC_H*/
