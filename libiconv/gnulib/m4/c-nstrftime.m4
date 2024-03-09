# c-nstrftime.m4 serial 1
dnl Copyright (C) 1996-2024 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_C_GNU_STRFTIME],
[
  AC_REQUIRE([AC_C_RESTRICT])

  # This defines (or not) HAVE_TZNAME and HAVE_STRUCT_TM_TM_ZONE.
  AC_REQUIRE([AC_STRUCT_TIMEZONE])

  AC_REQUIRE([gl_TM_GMTOFF])

  dnl Test for strftime_l. It exists in
  dnl glibc >= 2.3, musl libc,
  dnl macOS >= 10.4, FreeBSD >= 9.0, NetBSD >= 8.0, OpenBSD >= 6.2, Minix >= 3.3,
  dnl AIX >= 7.2, Solaris >= 11.4, Cygwin >= 2.6, Android API level >= 21.
  gl_CHECK_FUNCS_ANDROID([strftime_l], [[#include <time.h>]])
])
