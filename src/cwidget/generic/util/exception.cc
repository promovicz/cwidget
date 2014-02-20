// exception.cc
//
//   Copyright (C) 2005, 2007 Daniel Burrows
//
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2 of
//   the License, or (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; see the file COPYING.  If not, write to
//   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
//   Boston, MA 02111-1307, USA.

#include "exception.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if defined(HAVE_EXECINFO_H) && defined(ENABLE_DYNAMIC_BACKTRACE)

#include <execinfo.h>

namespace cwidget
{
  namespace util
  {
    Exception::Exception()
    {
      void * backtrace_array[100];
      int symbol_count = backtrace(backtrace_array, sizeof(backtrace_array)/sizeof(backtrace_array[0]));
      char **symbols = backtrace_symbols(backtrace_array, symbol_count);

      for(int i = 0; i < symbol_count; ++i)
	{
	  bt += symbols[i];
	  bt += "\n";
	}

      free(symbols);
    }
  }
}

#else

namespace cwidget
{
  namespace util
  {
    Exception::Exception()
    {
    }
  }
}

#endif
