#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Lockbox-CC], [0.1], [tierney@cs.nyu.edu])
AC_CONFIG_SRCDIR([src/lockbox_main.cc])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([build-aux])

# Checks for programs.
AC_CANONICAL_HOST

AC_PROG_LIBTOOL

AC_PROG_GREP
AC_PROG_EGREP
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

dnl First look for Boost, maybe for a specific minimum version:
BOOST_REQUIRE([1.34])
dnl Then look for specific Boost libraries you need:
BOOST_THREADS

AC_ARG_WITH([thrift-libdir],
    [AS_HELP_STRING([--with-thrift-libdir=LIB_DIR],
        [location of the protocol buffers libraries, defaults to /usr/lib])],
    [THRIFT_LIBDIR="$withval"],
    [THRIFT_LIBDIR='/usr/lib'])
AC_SUBST([THRIFT_LIBDIR])

LDFLAGS="$LDFLAGS -L$THRIFT_LIBDIR"

AC_CHECK_LIB([thrift], [main], [], [AC_MSG_ERROR([cannot find thrift library])])

AC_ARG_WITH([thrift],
    [AS_HELP_STRING([--with-thrift=PATH],
        [location of the thrift protocol compiler binary, defaults to thrift])],
    [THRIFT="$withval"],
    [THRIFT='thrift'])
AC_SUBST([THRIFT])


AC_CHECK_LIB([glib-2.0], [main], [], [AC_MSG_ERROR([cannot find glib library])])

AC_SUBST(COURGETTE_USE_CRC_LIB)

# Should create two variables DEPS_CFLAGS and DEPS_LIBS that allows us to ...
PKG_CHECK_MODULES([DEPS], [glib-2.0 >= 2.24.1])
PKG_CHECK_MODULES([GTK], [gtk+-2.0])
PKG_CHECK_MODULES([LIBEVENT], [libevent >= 2.0.0])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h fenv.h float.h inttypes.h limits.h locale.h mach/mach.h malloc.h netinet/in.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/param.h sys/socket.h sys/statvfs.h sys/time.h sys/vfs.h unistd.h utime.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_STRUCT_TIMEZONE
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_FSEEKO
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_HEADER_MAJOR
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit clock_gettime dup2 fchdir fdatasync floor ftruncate getpagesize gettimeofday localeconv localtime_r memchr memmove memset mkdir munmap realpath rmdir select setenv setlocale strcasecmp strchr strdup strerror strncasecmp strndup strrchr strstr strtol strtoul strtoull tzset uname])

#
# Platform specific setup
#
#############################
AC_CANONICAL_HOST
# Check for which host we are on and setup a few things
# specifically based on the host
case $host_os in
  darwin* )
        # Do something specific for mac
        AC_SUBST(FILE_PATH_WATCHER_SUFFIX, kqueue)
        ;;
  linux*)
        # Do something specific for linux
        AC_SUBST(FILE_PATH_WATCHER_SUFFIX, linux)
        ;;
   *BSD*)
        # Do something specific for BSD
        ;;
    *)
        #Default Case
        AC_MSG_ERROR([Your platform is not currently supported])
        ;;
esac

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 ])
AC_OUTPUT
