// Tests for generic/util/ssprintf.
//
//   Copyright (C) 2007 Daniel Burrows
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

#include <cppunit/extensions/HelperMacros.h>

#include <cwidget/generic/util/ssprintf.h>

#include <errno.h>

using cwidget::util::ssprintf;

class SSPrintfTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(SSPrintfTest);

  CPPUNIT_TEST(test_sstrerror);
  CPPUNIT_TEST(test_ssprintf);

  CPPUNIT_TEST_SUITE_END();
private:
  void do_test_sstrerror(int errnum)
  {
    std::string expected = strerror(errnum);
    CPPUNIT_ASSERT_EQUAL(expected, cwidget::util::sstrerror(errnum));
  }

  // This test was written because the original sstrerror was buggy
  // (returned garbage) on some platforms.  To verify that it works we
  // check that it returns the same thing as strerror for a few error
  // values.
  void test_sstrerror()
  {
    do_test_sstrerror(0);
    do_test_sstrerror(EINVAL);
    do_test_sstrerror(EINTR);
    do_test_sstrerror(EBADF);
  }

  void test_ssprintf()
  {
    // Test that inserting very long strings via ssprintf actually works.
    std::string horriblelongthing = "abcdefghijklmnopqrstuvwxyz";
    while(horriblelongthing.size() < 4096)
      horriblelongthing += horriblelongthing;

    CPPUNIT_ASSERT_EQUAL(horriblelongthing + " 20", ssprintf("%s %d", horriblelongthing.c_str(), 20));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SSPrintfTest);
