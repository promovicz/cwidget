#include "ssprintf.h"

#include "eassert.h"

#include <errno.h>

using namespace std;

namespace cwidget
{
  namespace util
  {
    string ssprintf(const char *format, ...)
    {
      va_list ap;

      va_start(ap, format);
      string rval = vssprintf(format, ap);
      va_end(ap);

      return rval;
    }

    const int initbufsize=512;

    string vssprintf(const char *format, va_list ap)
    {
      // We need to do this because you can't necessarily re-use a
      // va_list after stepping down it.
      va_list ap2;
      va_copy(ap2, ap);
      char buf[initbufsize];
      const int amt = vsnprintf(buf, initbufsize, format, ap);

      if(amt < initbufsize)
	return buf;
      else
	{
	  const int buf2size = amt + 1;
	  char *buf2 = new char[buf2size];

	  const int amt2 = vsnprintf(buf2, buf2size, format, ap2);

	  eassert(amt2 < buf2size);

	  string rval(buf2, amt2);

	  delete[] buf2;

	  return rval;
	}
    }

    wstring swsprintf(const wchar_t *format, ...)
    {
      va_list ap;

      va_start(ap, format);
      wstring rval = vswsprintf(format, ap);
      va_end(ap);

      return rval;
    }

    wstring vswsprintf(const wchar_t *format, va_list ap)
    {
      wchar_t buf[initbufsize];
      int amt = vswprintf(buf, initbufsize, format, ap);

      if(amt < initbufsize)
	return buf;
      else
	{
	  wchar_t *buf2 = new wchar_t[amt+1];

	  int amt2 = vswprintf(buf2, initbufsize, format, ap);

	  eassert(amt2 < amt+1);

	  wstring rval(buf2, amt2);

	  delete[] buf2;

	  return rval;
	}
    }


    string sstrerror(int errnum)
    {
      size_t bufsize = 512;

      while(bufsize < 512 * 512)
	{
	  char *buf = new char[bufsize];

	  char *result = strerror_r(errnum, buf, bufsize);

	  if(result == NULL)
	    {
	      delete[] buf;

	      if(errno == EINVAL)
		return ssprintf("Invalid error code %d", errnum);
	      else if(errno != ERANGE)
		return ssprintf("Unexpected error from strerror_r: %d", errnum);
	      else
		bufsize *= 2;
	    }
	  else
	    {
	      string rval(buf);
	      delete[] buf;
	      return rval;
	    }
	}

      return "";
    }
  }
}
