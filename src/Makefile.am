AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
SUBDIRS = base
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LIBRARIES =

bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_LDADD = base/files/libfile_path_watcher.a
lockbox_main_LDADD += base/libmessage_loop.a
lockbox_main_LDADD += base/libmessage_loop_proxy.a
lockbox_main_LDADD += base/libtracked_objects.a
