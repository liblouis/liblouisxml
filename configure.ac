# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(liblouisxml, 1.8.0, john.boyer@abilitiessoft.com)
AC_CONFIG_SRCDIR([liblouisxml/semantics.c])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADER([liblouisxml/config.h])
# AM_MAINTAINER_MODE

# libtool versioning for libwnck

# increment if the interface has additions, changes, removals.
LIBLOUISXML_CURRENT=1

# increment any time the source changes; set to
#  0 if you increment CURRENT
LIBLOUISXML_REVISION=5


# increment if any interfaces have been added; set to 0
#  if any interfaces have been changed or removed. removal has
#  precedence over adding, so set to 0 if both happened.
LIBLOUISXML_AGE=0

AC_SUBST(LIBLOUISXML_CURRENT)
AC_SUBST(LIBLOUISXML_REVISION)
AC_SUBST(LIBLOUISXML_AGE)

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
# AC_PROG_RANLIB
AC_ISC_POSIX
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL

AC_PATH_PROG(PKG_CONFIG, pkg-config)

PKG_CHECK_MODULES(BASE_DEPENDENCIES, [liblouis, libxml-2.0])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([memset])

case $host in
  *mingw* | *cygwin*)
    LDFLAGS="$LDFLAGS -avoid-version"
    CFLAGS="$CFLAGS -Wl,--add-stdcall-alias"
  ;;
esac

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 lbx_files/Makefile
                 liblouisxml/Makefile
                 tests/Makefile
		 liblouisxml.pc
                 tools/Makefile])

AC_CONFIG_FILES([tools/msword2brl], [chmod +x tools/msword2brl])

AC_OUTPUT

