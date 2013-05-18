AM_CPPFLAGS = -I$(top_srcdir)/src/testing/gtest/include
aclocaldir = $(datadir)/aclocal

EXTRA_DIST =
EXTRA_DIST += build/build_config.h

ACLOCAL_AMFLAGS = -I m4

SUBDIRS =
# SUBDIRS += testing/gtest
SUBDIRS += leveldb
SUBDIRS += third_party/modp_b64
SUBDIRS += base
SUBDIRS += courgette
SUBDIRS += crypto
SUBDIRS += file_watcher
SUBDIRS += src

aclocal_DATA = m4/boost.m4

bin_PROGRAMS =
