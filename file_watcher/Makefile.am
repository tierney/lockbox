AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CXXFLAGS = -Wall -Wextra
if DARWIN
AM_CXXFLAGS += -std=gnu++11 -stdlib=libc++
endif

bin_PROGRAMS =
noinst_LTLIBRARIES =

bin_PROGRAMS += file_watcher_main
file_watcher_main_SOURCES = file_watcher_main.cc
file_watcher_main_LDADD = libfile_watcher.la

noinst_LTLIBRARIES += libfile_watcher.la
libfile_watcher_la_SOURCES = file_watcher.h
libfile_watcher_la_SOURCES += file_watcher_impl.h
libfile_watcher_la_SOURCES += file_watcher.cc
if LINUX
libfile_watcher_la_SOURCES += file_watcher_linux.h
libfile_watcher_la_SOURCES += file_watcher_linux.cc
endif
if DARWIN
libfile_watcher_la_SOURCES += file_watcher_mac.h
libfile_watcher_la_SOURCES += file_watcher_mac.cc
endif
