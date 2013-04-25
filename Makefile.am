AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src \
	-I$(top_srcdir)/src/testing/gtest/include
aclocaldir = $(datadir)/aclocal

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src/testing/gtest src src/crypto src/file_watcher

aclocal_DATA = m4/boost.m4

bin_PROGRAMS =

bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = src/lockbox_main.cc
lockbox_main_LDADD = $(DEPS_LIBS)
lockbox_main_LDADD += $(GFLAGS_LIBS)
lockbox_main_LDADD += src/base/libfile_util.la
lockbox_main_LDADD += src/crypto/librsa_private_key.la
lockbox_main_LDADD += src/base/threading/libthread.la
lockbox_main_LDADD += src/libclient_initialization.la
lockbox_main_LDADD += src/base/files/libfile_path_watcher.la
lockbox_main_LDADD += src/base/librun_loop.la
lockbox_main_LDADD += src/base/synchronization/libwaitable_event.la
