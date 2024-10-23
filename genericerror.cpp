#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cstddef>
#include <cctype>

FILE	*LOG;

static int LENGTH = 1024;

static int getfld (const char **p)
{
	int fld = 0;

 	while (isdigit(**p))
		fld = (fld * 10) + ((*((*p)++)) - '0');

	return fld;
}

static void bputc (char *msg,int *len,char ch)
{
	msg[(*len)++] = ch;
}

static void bputs (char *msg,int *len,const char *s,int fld)
{
	for (fld -= (int)strlen(s); fld > 0; fld--)
		bputc (msg,len,' ');
	while (*s)
		bputc (msg,len,*(s++));
}

static void _error (int exit_status,const char *message,const char *file,int line)
{
	if (exit_status == 0) {
		fprintf (LOG,"FATAL: %s(called from file %s, line %d)\n", message, file, line);
		fflush(LOG);
	}

	if (exit_status == -1) {
		fprintf (LOG,"ERROR: %s(called from file %s, line %d)\n", message, file, line);
		fflush(LOG);
	}

	if (exit_status == -2) {
		fprintf (LOG,"WARNING: %s(called from file %s, line %d)\n", message, file, line);
		fflush(LOG);
	}

	if (exit_status >= 0)
		exit (exit_status);
}

void gen_error (const int exit_status, const char *file, const int line, const char *fmt,...)
{
	va_list ap;
	const char *p;
	char cval,*sval,msg[LENGTH];
	char ibuf[64],ifmt[64];
	int len = 0,fld,ival,index;
	double dval;
	
	va_start (ap,fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			bputc (msg,&len,*p);
		else {
			p++;
			fld = getfld (&p);
			switch (*p) {
			case 'x':
				ival = va_arg (ap,int);
				sprintf (ifmt,"0x%%%dx",fld);
				sprintf (ibuf,ifmt,(unsigned int)ival);
				for (index = 0; (index < (int)strlen (ibuf)); index++)
					bputc (msg,&len,ibuf[index]);
				break;
			case 'd':
				ival = va_arg (ap,int);
				sprintf (ifmt,"%%%dd",fld);
				sprintf (ibuf,ifmt,ival);
				for (index = 0; (index < (int)strlen (ibuf)); index++)
					bputc (msg,&len,ibuf[index]);
				break;
			case 'u':
				ival = va_arg (ap,unsigned);
				sprintf (ifmt,"%%%du",fld);
				sprintf (ibuf,ifmt,ival);
				for (index = 0; (index < (int)strlen (ibuf)); index++)
					bputc (msg,&len,ibuf[index]);
				break;
			case 'f':
				dval = va_arg (ap,double);
				sprintf (ifmt,"%%%df",fld);
				sprintf (ibuf,ifmt,dval);
				for (index = 0; (index < (int)strlen(ibuf)); index++)
					bputc (msg,&len,ibuf[index]);
				break;
			case 'g':
				dval = va_arg (ap,double);
				sprintf (ifmt,"%%%dg",fld);
				sprintf (ibuf,ifmt,dval);
				for (index = 0; (index < (int)strlen(ibuf)); index++)
					bputc (msg,&len,ibuf[index]);
				break;
			case 'c':
				cval = (char) va_arg(ap,int);
				bputc (msg,&len,cval);
				break;
			case 's':
				sval = va_arg (ap,char *);
				bputs (msg,&len,sval,fld);
				break;
			case '%':
				bputc (msg,&len,*p);
				break;
			default :
				break;
			}
		}
	}
	va_end (ap);
	bputc (msg,&len,'\0');

	_error (exit_status,msg,file,line);
}

void gen_closelog(void)
{
	if (LOG) fclose(LOG);
}
