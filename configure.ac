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
dnl ##################################################
dnl #####
dnl #####       Check for libcrypt
dnl #####       We use crypt(3) which may be in libc,
dnl #####       or in libcrypt (eg FreeBSD)
dnl #####
dnl ##################################################
AC_CHECK_LIB(crypt, crypt, CRYPTLIB="-lcrypt")
if test "x$CRYPTLIB" != "x"; then
        AC_DEFINE([HAVE_CRYPT], [1], [Define to 1 if you have libcrypt])
        AC_SUBST(HAVE_CRYPT)
else
        AC_CHECK_FUNC(crypt,
                AC_DEFINE([HAVE_CRYPT], [1],
                [Define to 1 if you have libcrypt]))
        AC_DEFINE([HAVE_CRYPT], [1], [Define to 1 if you have libcrypt])
        AC_SUBST(HAVE_CRYPT)
fi
if test "x$CRYPTLIB" == "x"; then
        echo
        echo "You need to install libcrypt"
        echo
        exit
fi
AC_OUTPUT(Makefile)
