// test_eassert.cc
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

// TODO: eassert lives in cwidget now, this test should perhaps move
// there.

#include <cwidget/generic/util/eassert.h>

#include <cppunit/extensions/HelperMacros.h>

class EassertTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(EassertTest);

  CPPUNIT_TEST(testEassert);

  CPPUNIT_TEST_SUITE_END();
public:
  void testEassert()
  {
    const int a = 5;
    const int b = 6;

    eassert(a == 5);
    eassert(b != 6 ||
	    a != 2);

    size_t failureLine;

    // Failing asserts:
    try
      {
	failureLine = __LINE__; eassert(a == 1);
      }
    catch(cwidget::util::AssertionFailure &e)
      {
	CPPUNIT_ASSERT_EQUAL(std::string("a == 1"), e.get_exp());
	CPPUNIT_ASSERT_EQUAL(failureLine, e.get_line());
	CPPUNIT_ASSERT_EQUAL(std::string("void EassertTest::testEassert()"), e.get_func());
	// Having to use __FILE__ is unfortunate, but with staged
	// builds the filename isn't predictable (e.g., with
	// "distcheck" it's "../../tests/test_eassert.cc").
	CPPUNIT_ASSERT_EQUAL(std::string(__FILE__), e.get_file());
      }
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(EassertTest);
