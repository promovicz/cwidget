dnl Process this file with autoconf to produce a configure script.
AC_INIT(cwidget, 0.5.4)
AC_CONFIG_SRCDIR([src/cwidget/toplevel.cc])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h cwidget-config.h])

dnl Use C++
AC_LANG([C++])

BUILD_LIBRARY=yes
AC_ARG_ENABLE(library, AS_HELP_STRING([--disable-library], [Disable building the library itself; only build documentation.]),
	      [if test x$enableval = xno; then BUILD_LIBRARY=no; fi],
	      )

AM_CONDITIONAL(BUILD_LIBRARY, [test x$BUILD_LIBRARY = xyes])


dnl AM_GNU_GETTEXT needs to be called unconditionally, or the
dnl configure script freaks out.  Otherwise this would be inside the
dnl stuff that gets disabled by --disable-library.
ALL_LINGUAS=""
AM_GNU_GETTEXT([external])

dnl Try to find doxygen in the path.
AC_MSG_CHECKING([for the Doxygen documentation generator (http://www.doxygen.org)])
DOXYGEN=`which doxygen`
AC_SUBST(DOXYGEN)

if test x$DOXYGEN = x
then
  AC_MSG_RESULT([not found])
else
  AC_MSG_RESULT([found at $DOXYGEN])
fi

AM_CONDITIONAL(DOXYGEN, [test x$DOXYGEN != x])



if test x$BUILD_LIBRARY = xyes
then

dnl Find the key tools.
AC_PROG_CXX
AC_PROG_LIBTOOL

dnl Look for ncurses
AC_CHECK_LIB(ncursesw, initscr, ,
	[AC_MSG_ERROR([Can't find libncursesw -- please install libncursesw5-dev])])


dnl We need threading.
AC_CHECK_LIB(pthread, main,
	HAVE_LIBPTHREAD=1
	, [AC_MSG_ERROR([Can't find the POSIX thread libraries])])

if test x$HAVE_LIBPTHREAD = x1
then
  AC_CHECK_HEADER(pthread.h,
	CXXFLAGS="$CXXFLAGS -D_REENTRANT"
	LIBS="$LIBS -lpthread"
	[AC_DEFINE([HAVE_LIBPTHREAD], [] , [Define if pthread is available])]
	,
	[AC_MSG_ERROR([POSIX thread header not installed])])
fi


dnl Find sigc++
PKG_CHECK_MODULES(SIGC, sigc++-2.0)
CXXFLAGS="$CXXFLAGS $SIGC_CFLAGS"
LIBS="$LIBS $SIGC_LIBS"
AC_DEFINE_UNQUOTED(SIGC_VERSION, ["$(pkg-config --modversion sigc++-2.0)"], [The version of libsigc++ with which the program was compiled])

AC_CHECK_HEADER(locale.h, [AC_DEFINE([HAVE_LOCALE_H], [], [Define if locale.h is available])])

AC_CHECK_DECL(setlocale, [AC_DEFINE([HAVE_SETLOCALE], [], [Define if setlocale is available in locale.h])], , [#include <locale.h>])



dnl Find hash tables in the STL.
HASH_INC=""
HASH_CLS=""

AC_CHECK_HEADER(hash_map,
		[HASH_INC="hash_map"
		 HASH_CLS="hash_map"
		 AC_DEFINE(CWIDGET_HAVE_HASH_MAP, ,
			  [Define if the g++ extension hash_map is available])],
	  	[AC_CHECK_HEADER(ext/hash_map,
				 [HASH_INC="ext/hash_map"
				  HASH_CLS="hash_map"
				  AC_DEFINE(CWIDGET_HAVE_EXT_HASH_MAP, , [Define if the g++ extension ext/hash_map is available])])])

AC_CHECK_HEADER(hash_set,
		[HASH_INC="hash_set"
		 HASH_CLS="hash_set"
		 AC_DEFINE(CWIDGET_HAVE_HASH_SET,  , [Define if the g++ extension hash_set is available])],
		[AC_CHECK_HEADER(ext/hash_set,
				[HASH_INC="ext/hash_set"
				 HASH_CLS="hash_set"
				 AC_DEFINE(CWIDGET_HAVE_EXT_HASH_SET,  , [Define if the g++ extension ext/hash_set is available])])])



# Try to guess what namespace the hash stuff is in (maybe I should just
# use rbltrees instead in most places?)
if test x$HASH_INC != x
then
    AC_MSG_CHECKING([which namespace contains the hash extensions])

    CWIDGET_HASH_NAMESPACE=""

    for NS in std __gnu_cxx
    do
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <$HASH_INC>],
	 			         [${NS}::${HASH_CLS} < int, int > foo;])],
			[CWIDGET_HASH_NAMESPACE=$NS])
    done

    if test x$CWIDGET_HASH_NAMESPACE = x
    then
       AC_MSG_ERROR([found hash classes, but they aren't in the std or GNU namespace.])
    fi

    AC_MSG_RESULT($CWIDGET_HASH_NAMESPACE)
else
    # Use the std namespace if all else fails. (the code will fall back
    # to using map instead of hash_map, set instead of hash_set)
    CWIDGET_HASH_NAMESPACE=std
fi

AC_DEFINE_UNQUOTED(CWIDGET_HASH_NAMESPACE, $CWIDGET_HASH_NAMESPACE, [If a hash header is available, define to the namespace in which the hash class resides])



dnl Figure out how to extend string traits
TRAITS_CLASS=""

AC_MSG_CHECKING([for the name of the character traits template])

for T in char_traits string_char_traits
do
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <string>],
				     [std::basic_string<unsigned char,
						        std::$T < unsigned char > > s;])],
		    TRAITS_CLASS=$T)
done

if test x$TRAITS_CLASS = xstring_char_traits
then
    AC_MSG_WARN([Your compiler uses string_char_traits for its character traits.  Some compilers (eg, g++ 2.95) which use this name for the character traits template are known to have hideously broken implementations of the standard string class, which cause aptitude to fail to compile.  If you have a compiler with this problem, please upgrade it to a version that has a more compliant version of the STL (g++ >=3.0 is known to work).  You can specify which compiler this script should use via the CXX environment variable.])
fi

if test x$TRAITS_CLASS = x
then
  AC_MSG_ERROR([can't find the name of the character traits template])
else
  AC_DEFINE_UNQUOTED(TRAITS_CLASS, $TRAITS_CLASS, [The name of the class used by the STL to define character traits])

  AC_MSG_RESULT([$TRAITS_CLASS])
fi



dnl Default to -Werror, but add an easy flag to disable it.
WERROR="-Werror"

AC_ARG_ENABLE(dynamic-backtrace,
	AS_HELP_STRING([--enable-dynamic-backtrace], [Modify the executable so that it can generate a backtrace for uncaught exceptions.  Will double the size of the stripped binary.]),
	[if test x$enableval = xyes
	then
	  AC_DEFINE([ENABLE_DYNAMIC_BACKTRACE], [], [Define to enable dynamic generation of backtraces if HAVE_EXECINFO_H is defined])
	  LDFLAGS="$LDFLAGS -Wl,--export-dynamic"
	fi]
	)
AC_ARG_ENABLE(werror,
	AS_HELP_STRING([--disable-werror], [do not compile with -Werror]),
	if test x$enableval = xno
	then
	  WERROR=""
	fi
	)
AC_SUBST(WERROR)

# END LIBRARY CONFIGURATION
fi



AC_CONFIG_FILES([
	Doxyfile
	Makefile
	cwidget.pc
	doc/Makefile
	src/Makefile
	src/cwidget/Makefile
	src/cwidget/config/Makefile
	src/cwidget/widgets/Makefile
	src/cwidget/generic/Makefile
	src/cwidget/generic/threads/Makefile
	src/cwidget/generic/util/Makefile
])

AC_OUTPUT