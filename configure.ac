
AC_INIT([popstacks], [0.1], [bjarki.agust@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AC_PROG_CXX
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_LANG_PUSH([C++])
AC_CHECK_LIB(gmp, __gmpz_init)
AC_CHECK_LIB(gmpxx, main)
AC_CHECK_HEADERS([gmp.h])
AC_CHECK_HEADERS([gmpxx.h])
AC_LANG_POP([C++])

AC_OUTPUT

