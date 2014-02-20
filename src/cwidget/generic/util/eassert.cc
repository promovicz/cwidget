// eassert.cc
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

#include "eassert.h"

#include "ssprintf.h"

namespace cwidget
{
  namespace util
  {
    AssertionFailure::AssertionFailure(const std::string &_file,
				       size_t _line,
				       const std::string &_func,
				       const std::string &_exp,
				       const std::string &_msg)
      : file(_file), func(_func), exp(_exp), msg(_msg), line(_line)
    {
    }

    std::string AssertionFailure::errmsg() const
    {
      if(msg.empty())
	return ssprintf("%s:%d: %s: Assertion \"%s\" failed.",
			file.c_str(), static_cast<unsigned int>(line),
			func.c_str(), exp.c_str());
      else
	return ssprintf("%s:%d: %s: %s: Assertion \"%s\" failed.",
			file.c_str(), static_cast<unsigned int>(line),
			func.c_str(), msg.c_str(), exp.c_str());
    }
  }
}
