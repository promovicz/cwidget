// eassert.h                          -*-c++-*-
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

#ifndef EASSERT_H
#define EASSERT_H

namespace cwidget
{
  namespace util
  {
    /** Represents an assertion failure. */
    class AssertionFailure : public Exception
    {
      std::string file;
      std::string func;
      std::string exp;
      std::string msg;
      size_t line;
    public:
      /** \brief Create a new AssertionFailure.
       *
       *  \param file The file in which the failing assertion occurred.
       *  \param line The line on which the failing assertion occurred.
       *  \param func The function in which the failing assertion occurred.
       *  \param exp  The failing assertion.
       *  \param msg  An extra message to include in the assertion.
       */
      AssertionFailure(const std::string &file,
		       size_t line,
		       const std::string &func,
		       const std::string &exp,
		       const std::string &msg);

      std::string errmsg() const;

      /** \return The source file in which the failing assertion occurred. */
      std::string get_file() const
      {
	return file;
      }

      /** \return The source line at which the failing assertion occurred. */
      size_t get_line() const
      {
	return line;
      }

      /** \return The function in which the assertion failure occurres. */
      std::string get_func() const
      {
	return func;
      }

      /** \return The assertion that failed. */
      std::string get_exp() const
      {
	return exp;
      }
    };
  }
}

/** \brief Like eassert, but includes the given extra information
 *  with a failed assertion.
 */
#define eassert2(invariant, msg) \
  do { if(!(invariant)) \
         throw cwidget::util::AssertionFailure(__FILE__, __LINE__, __PRETTY_FUNCTION__, #invariant, msg); \
     } while(0)

/** Similar to assert, but throws an exception instead of printing to
 *  stderr and aborting.
 *
 *  \todo be portable by only compiling the gcc stuff conditionally?
 */
#define eassert(invariant) eassert2(invariant, "")

#endif
