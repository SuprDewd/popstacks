
AC_INIT([popstacks], [0.1], [bjarki.agust@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror -pg foreign])
AC_PROG_CXX
AC_CONFIG_FILES([
    Makefile
])

AX_CXXFLAGS_WARN_ALL

AC_CHECK_LIB(gmp, mpz_init)
AC_CHECK_LIB(gmpxx, mpz_class)
# AC_CHECK_HEADERS([gmp.h gmpxx.h], )

AC_OUTPUT

