SUBDIRS = files

AM_CPPFLAGS = -I -I$(top_srcdir)/include -I$(top_srcdir)/src
noinst_LIBRARIES =

noinst_LIBRARIES += libmessage_loop.a
libmessage_loop_a_SOURCES = message_loop.h
libmessage_loop_a_SOURCES += message_loop.cc

noinst_LIBRARIES += libmessage_loop_proxy.a
libmessage_loop_proxy_a_SOURCES = message_loop_proxy.h
libmessage_loop_proxy_a_SOURCES += message_loop_proxy.cc

noinst_LIBRARIES += libtracked_objects.a
libtracked_objects_a_SOURCES = tracked_objects.h
libtracked_objects_a_SOURCES += tracked_objects.cc
