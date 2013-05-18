#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Lockbox-CC], [0.1], [tierney@cs.nyu.edu])
AC_CONFIG_SRCDIR([src/lockbox_main.cc])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([testing/gtest/scripts/gtest-config],
                [chmod +x testing/gtest/scripts/gtest-config])
AM_SILENT_RULES([yes])

# Initialize Automake with various options. We require at least v1.9, prevent
# pedantic complaints about package files, and enable various distribution
# targets.
AM_INIT_AUTOMAKE([1.9 dist-bzip2 dist-zip foreign subdir-objects])

# Checks for programs.
AC_CANONICAL_HOST

AC_PROG_LIBTOOL

AC_PROG_GREP
AC_PROG_EGREP
dnl case $host_os in
dnl   *linux*)
dnl AC_PROG_CXX;;
dnl   *darwin*)
AC_PROG_CXX([clang++])
AC_PROG_OBJCXX([clang++])
dnl ;;
dnl esac

AC_PROG_CC
dnl case $host_os in
dnl      *linux*)
dnl AX_CXX_COMPILE_STDCXX_11;;
dnl esac


# Checks for libraries.

# First look for Boost, maybe for a specific minimum version:
BOOST_REQUIRE([1.34])
# Then look for specific Boost libraries you need:
BOOST_THREADS
BOOST_SYSTEM

# Thrift (serialization and rpc library).
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

# TODO(chandlerc@google.com): Currently we aren't running the Python tests
# against the interpreter detected by AM_PATH_PYTHON, and so we condition
# HAVE_PYTHON by requiring "python" to be in the PATH, and that interpreter's
# version to be >= 2.3. This will allow the scripts to use a "/usr/bin/env"
# hashbang.
PYTHON=  # We *do not* allow the user to specify a python interpreter
AC_PATH_PROG([PYTHON],[python],[:])
AS_IF([test "$PYTHON" != ":"],
      [AM_PYTHON_CHECK_VERSION([$PYTHON],[2.3],[:],[PYTHON=":"])])
AM_CONDITIONAL([HAVE_PYTHON],[test "$PYTHON" != ":"])

# Configure pthreads.
AC_ARG_WITH([pthreads],
            [AS_HELP_STRING([--with-pthreads],
               [use pthreads (default is yes)])],
            [with_pthreads=$withval],
            [with_pthreads=check])

have_pthreads=no
AS_IF([test "x$with_pthreads" != "xno"],
      [ACX_PTHREAD(
        [],
        [AS_IF([test "x$with_pthreads" != "xcheck"],
               [AC_MSG_FAILURE(
                 [--with-pthreads was specified, but unable to be used])])])
       have_pthreads="$acx_pthread_ok"])
AM_CONDITIONAL([HAVE_PTHREADS],[test "x$have_pthreads" == "xyes"])
AC_SUBST(PTHREAD_CFLAGS)
AC_SUBST(PTHREAD_LIBS)

# Should create two variables DEPS_CFLAGS and DEPS_LIBS that allows us to ...
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.24.1])
PKG_CHECK_MODULES([GTK], [gtk+-2.0])
PKG_CHECK_MODULES([LIBEVENT], [libevent >= 2.0.0])
PKG_CHECK_MODULES([ZLIB], [zlib])
PKG_CHECK_MODULES([THRIFT], [thrift])
PKG_CHECK_MODULES([THRIFTNB], [thrift-nb])
PKG_CHECK_MODULES([NSS], [nss])
PKG_CHECK_MODULES([NSPR], [nspr])
PKG_CHECK_MODULES([GFLAGS], [libgflags])
PKG_CHECK_MODULES([GLOG], [libglog])
PKG_CHECK_MODULES([OPENSSL], [openssl])
PKG_CHECK_MODULES([SNAPPY], [snappy])

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
        AC_SUBST(GENERIC_OS_SUFFIX, mac)
        AC_SUBST(OS_LANG_EXT, mm)
        ;;
  linux*)
        # Do something specific for linux
        AC_SUBST(FILE_PATH_WATCHER_SUFFIX, linux)
        AC_SUBST(GENERIC_OS_SUFFIX, linux)
        AC_SUBST(OS_LANG_EXT, cc)
        ;;
    *)
        #Default Case
        AC_MSG_ERROR([Your platform is not currently supported])
        ;;
esac

case $host_os in
     *linux*)	arch=linux;;
     *netbsd*)  arch=netbsd;;
     *bsd*)	arch=bsd;;
     *darwin*)	arch=darwin;;
     *)		arch=unknown;;
esac

AM_CONDITIONAL(LINUX, test "$arch" = linux)
AM_CONDITIONAL(NETBSD, test "$arch" = netbsd)
AM_CONDITIONAL(BSD, test "$arch" = bsd)
AM_CONDITIONAL(DARWIN, test "$arch" = darwin)

AC_CONFIG_FILES([testing/gtest/Makefile
                 third_party/modp_b64/Makefile
                 base/Makefile
                 courgette/Makefile
                 crypto/Makefile
                 file_watcher/Makefile
                 src/Makefile
                 Makefile
                 ])
AC_OUTPUT
