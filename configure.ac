#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([commit_reader], [0.1.0], [kenhys@gmail.com])
AC_CONFIG_SRCDIR([src/commit_reader.c])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE($PACKAGE_NAME, $PACKAGE_VERSION)

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL


AC_DEFUN([CHECK_CFLAG], [
  AC_MSG_CHECKING([if gcc supports $1])
  old_CFLAGS=$CFLAGS
  flag=`echo '$1' | sed -e 's,^-Wno-,-W,'`
  CFLAGS="$CFLAGS $flag -Werror"
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
    [check_cflag=yes],
    [check_cflag=no])
  CFLAGS="$old_CFLAGS"
  if test "x$check_cflag" = "xyes"; then
    CFLAGS="$CFLAGS $1"
  fi
  AC_MSG_RESULT([$check_cflag])
])

if test "$GCC" = "yes"; then
  CHECK_CFLAG([-Wall])
  CHECK_CFLAG([-Wextra])
  if test "x$check_cflag" = "xno"; then
    CHECK_CFLAG([-W])
  fi
  CHECK_CFLAG([-Wno-unused-but-set-variable]) # FIXME: enable it.
  CHECK_CFLAG([-Wno-unused-parameter])
  CHECK_CFLAG([-Wno-sign-compare])
  CHECK_CFLAG([-Wno-pointer-sign])
  CHECK_CFLAG([-Wno-missing-field-initializers])

  CHECK_CFLAG([-Wformat=2])
  CHECK_CFLAG([-Wstrict-aliasing=2])
  if test "x$check_cflag" = "xyes"; then
    NO_STRICT_ALIASING_CFLAGS="-fno-strict-aliasing"
  fi
  CHECK_CFLAG([-Wdisabled-optimization])
  CHECK_CFLAG([-Wfloat-equal])
  CHECK_CFLAG([-Wpointer-arith])
  CHECK_CFLAG([-Wdeclaration-after-statement])
  CHECK_CFLAG([-Wbad-function-cast])
  if test "$CLANG" = "no"; then
    CHECK_CFLAG([-Wcast-align])
  fi
  CHECK_CFLAG([-Wredundant-decls])
fi

AC_ARG_ENABLE(debug,
	      [AS_HELP_STRING([--enable-debug],
                              [use debug flags (default=no)])],
  [plugin_debug="$enableval"],
  [plugin_debug="no"])
if test "x$plugin_debug" != "xno"; then
  plugin_debug="yes"
  if test "$CLANG" = "yes"; then
    CFLAGS="$CFLAGS -O0 -g"
    CXXFLAGS="$CXXFLAGS -O0 -g"
  elif test "$GCC" = "yes"; then
    CFLAGS="$CFLAGS -O0 -ggdb3"
    CXXFLAGS="$CXXFLAGS -O0 -ggdb3"
  fi
fi
AC_SUBST(plugin_debug)

m4_include(../sylplugin_factory/m4/sylplugin_factory.m4)

# Checks for libraries.
AM_PATH_GLIB_2_0(2.8.0,, AC_MSG_ERROR(Test for GLib failed. See the 'INSTALL' for help.))
AM_PATH_GTK_2_0(2.8.0,, AC_MSG_ERROR(Test for Gtk failed. See the 'INSTALL' for help.))
GETTEXT_PACKAGE=commit_reader
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Define text domain.])
AM_GLIB_GNU_GETTEXT

AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_ENABLE([webkitgtk],
	      [AS_HELP_STRING([--enable-webkitgtk],
                              [use WebKitGTK as HTML rendering engine. [default=auto]])],
              [enable_webkitgtk="$enableval"],
              [enable_webkitgtk=no]
)

AC_MSG_CHECKING([whether enable WebKitGTK])
if test "x$enable_webkitgtk" != "xyes"; then
  enable_webkitgtk="no"
fi
AC_MSG_RESULT($enable_webkitgtk)

AC_ARG_ENABLE([gtkhtml],
	      [AS_HELP_STRING([--enable-gtkhtml],
                              [use GtkHTML as HTML rendering engine. [default=no]])],
              [enable_gtkhtml="$enableval"],
              [enable_gtkhtml=no]
)
AC_MSG_CHECKING([whether enable GtkHTML])
if test "x$enable_gtkhtml" != "xyes"; then
  enable_gtkhtml="no"
fi
AC_MSG_RESULT($enable_gtkhtml)

AS_IF([test "x$enable_webkitgtk" != xno && test "x$enable_gtkhtml" != xno],
      [AC_DEFINE([USE_GTKHTML], [1], [GtkHTML support])],
      [test "x$enable_webkitgtk" != xno && test "x$enable_gtkhtml" != xyes],
      [AC_DEFINE([USE_WEBKITGTK], [1], [WebKitGTK support])],
      [test "x$enable_webkitgtk" != xyes && test "x$enable_gtkhtml" != xno],
      [AC_DEFINE([USE_GTKHTML], [1], [GtkHTML support])],
      [AC_MSG_ERROR(use WebKitGTK or GtkHTML exclusively.)]
)

AM_CONDITIONAL([USE_GTKHTML],
	       [test "${enable_gtkhtml}" = "yes"])
AM_CONDITIONAL([USE_WEBKITGTK],
	       [test "${enable_webkitgtk}" = "yes"])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
echo ""
echo "  For Commit Reader Preview..."
echo ""
echo "    WebKitGTK: ${enable_webkitgtk}"
echo "      GtkHTML: ${enable_gtkhtml}"
echo ""
