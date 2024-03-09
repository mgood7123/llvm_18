/* Test of POSIX and GNU compatible dprintf() function.
   Copyright (C) 2007-2024 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2023.  */

#include <config.h>

#include <stdio.h>

#include <stddef.h>
#include <string.h>

#include "macros.h"

static void
test_function (int (*my_dprintf) (int, const char *, ...))
{
  /* Here we don't test output that may be platform dependent.
     The bulk of the tests is done as part of the 'vasnprintf-posix' module.  */

  /* Test the support of the 'B' conversion specifier for binary output of
     integers.  */

  /* Zero.  */
  my_dprintf (fileno (stdout), "%B %d\n", 0, 33, 44, 55);

  /* A positive number.  */
  my_dprintf (fileno (stdout), "%B %d\n", 12345, 33, 44, 55);

  /* A large positive number.  */
  my_dprintf (fileno (stdout), "%B %d\n", 0xFFFFFFFEU, 33, 44, 55);

  /* Width.  */
  my_dprintf (fileno (stdout), "%20B %d\n", 12345, 33, 44, 55);

  /* Width given as argument.  */
  my_dprintf (fileno (stdout), "%*B %d\n", 20, 12345, 33, 44, 55);

  /* Negative width given as argument (cf. FLAG_LEFT below).  */
  my_dprintf (fileno (stdout), "%*B %d\n", -20, 12345, 33, 44, 55);

  /* Precision.  */
  my_dprintf (fileno (stdout), "%.20B %d\n", 12345, 33, 44, 55);

  /* Zero precision and a positive number.  */
  my_dprintf (fileno (stdout), "%.0B %d\n", 12345, 33, 44, 55);

  /* Zero precision and a zero number.  */
  my_dprintf (fileno (stdout), "%.0B %d\n", 0, 33, 44, 55);

  /* Width and precision.  */
  my_dprintf (fileno (stdout), "%25.20B %d\n", 12345, 33, 44, 55);

  /* FLAG_LEFT.  */
  my_dprintf (fileno (stdout), "%-20B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with zero.  */
  my_dprintf (fileno (stdout), "%#B %d\n", 0, 33, 44, 55);

  /* FLAG_ALT with a positive number.  */
  my_dprintf (fileno (stdout), "%#B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with a positive number and width.  */
  my_dprintf (fileno (stdout), "%#20B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with a positive number and padding.  */
  my_dprintf (fileno (stdout), "%0#20B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with a positive number and precision.  */
  my_dprintf (fileno (stdout), "%0#.20B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with a positive number and width and precision.  */
  my_dprintf (fileno (stdout), "%#25.20B %d\n", 12345, 33, 44, 55);

  /* FLAG_ALT with a zero precision and a zero number.  */
  my_dprintf (fileno (stdout), "%#.0B %d\n", 0, 33, 44, 55);
}

int
main (int argc, char *argv[])
{
  test_function (dprintf);
  return 0;
}
