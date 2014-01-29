dnl ######################################################################
dnl ##### Configure script for mkpwd
dnl ##### (c) 2014 Oliver Schröder
dnl ######################################################################

AC_INIT(mkpwd.c)
AM_INIT_AUTOMAKE(mkpwd, 1.6)
AC_CHECK_PROG(GMAKE, gmake, yes, no)
if test "x$GMAKE" = "xno"; then
        AC_PATH_PROG(MAKE, make, /usr/local/bin/make)
else   
	AC_PATH_PROG(MAKE, gmake, /usr/local/gnu/bin/make)
fi

AM_CONFIG_HEADER(config.h)
AC_PROG_CC
AC_PROG_INSTALL
AC_OUTPUT(Makefile)
