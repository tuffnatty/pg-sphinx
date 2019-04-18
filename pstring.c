#include <stdlib.h>
#include <stdarg.h>
#include "pstring.h"

int pstring_is_one_of(const PString *pstr, ...)
{
  va_list argp;
  const char *p;

  if (PSTR_EMPTY(pstr))
    return 0;

  va_start(argp, pstr);
  while ((p = va_arg(argp, const char *)) != NULL)
    {
      if (PSRT_IS_EQUAL_TO(pstr, p))
	return 1;
    }
  va_end(argp);

  return 0;
}

int pstring_to_integer(const PString *pstr)
{
  char buf[40] = {0};
  strncpy(buf, pstr->str, 39);
  return atoi(buf);
}

char* pstring_replace(const PString *pstr, char* a, char* b)
{
    char* p;
    int len  = strlen(pstr->str);
    int lena = strlen(a), lenb = strlen(b);
    for (p = pstr->str; p = strstr(p, a); ++p) {
        if (lena != lenb) {
            memmove(p+lenb, p+lena, len - (p - pstr->str) + lenb);
        }

        memcpy(p, b, lenb);
    }
    return pstr;
}