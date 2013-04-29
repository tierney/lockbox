AM_CPPFLAGS = -I$(top_srcdir)/testing/gtest/include
AM_CPPFLAGS += -I$(top_srcdir) -I$(top_builddir)
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
AM_CXXFLAGS = -Wall -Wextra
AM_LDFLAGS = -L$(top_builddir) -static

TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

LEVELDB_CFLAGS = -I$(top_builddir)/leveldb/include
LEVELDB_BIN_LIBS = $(top_builddir)/leveldb/libleveldb.a -lsnappy

bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_LDADD =
lockbox_main_LDADD += $(GFLAGS_LIBS)
lockbox_main_LDADD += $(top_builddir)/base/libfile_util.la
lockbox_main_LDADD += $(top_builddir)/crypto/librsa_private_key.la
lockbox_main_LDADD += $(top_builddir)/base/threading/libthread.la
lockbox_main_LDADD += $(top_builddir)/base/files/libfile_path_watcher.la
lockbox_main_LDADD += $(top_builddir)/base/librun_loop.la
lockbox_main_LDADD += $(top_builddir)/base/synchronization/libwaitable_event.la
lockbox_main_LDADD += libclient_initialization.la
lockbox_main_LDADD += libfile_watcher.la
lockbox_main_LDADD += libnegotiator.la

# noinst_LTLIBRARIES += libleveldb_base.la
# libleveldb_base_la_SOURCES = leveldb_base.h
# libleveldb_base_la_SOURCES += leveldb_base.cc
# libleveldb_base_la_CXXFLAGS = $(LEVELDB_CFLAGS)
# libleveldb_base_la_LIBADD = $(LEVELDB_BIN_LIBS)

noinst_LTLIBRARIES += libclient_initialization.la
libclient_initialization_la_SOURCES = client_initialization.h
libclient_initialization_la_SOURCES += client_initialization.cc

noinst_LTLIBRARIES += libfile_watcher.la
libfile_watcher_la_SOURCES = file_watcher.h

noinst_LTLIBRARIES += libnegotiator.la
libnegotiator_la_SOURCES = negotiator.h

bin_PROGRAMS += user_device_queue_main
user_device_queue_main_SOURCES = user_device_queue_main.cc
user_device_queue_main_CXXFLAGS = -static
user_device_queue_main_CXXFLAGS += $(GFLAGS_CFLAGS)
user_device_queue_main_CXXFLAGS += $(LEVELDB_CFLAGS)
user_device_queue_main_LDADD = $(LEVELDB_BIN_LIBS)
user_device_queue_main_LDADD += $(GFLAGS_LIBS)
user_device_queue_main_LDADD += $(top_builddir)/base/libstringprintf.la
user_device_queue_main_LDADD += $(top_builddir)/base/liblogging.la

# TESTS += db_email_user_test
# bin_PROGRAMS += db_email_user_test
# db_email_user_test_SOURCES = db_email_user_test.cc
# db_email_user_test_CXXFLAGS = $(LEVELDB_CFLAGS)
# db_email_user_test_LDADD = $(top_builddir)/testing/gtest/lib/libgtest.la
# db_email_user_test_LDADD += $(top_builddir)/testing/gtest/lib/libgtest_main.la
# db_email_user_test_LDADD += libdb_email_user.la
# db_email_user_test_LDADD += $(top_builddir)/base/files/libfile_path.la
# db_email_user_test_LDADD += $(top_builddir)/base/liblogging.la
# db_email_user_test_LDADD += libleveldb_util.la
# db_email_user_test_LDADD += $(LEVELDB_BIN_LIBS)

noinst_LTLIBRARIES += libguid_creator.la
libguid_creator_la_SOURCES = guid_creator.h
libguid_creator_la_SOURCES += guid_creator.cc

noinst_LTLIBRARIES += liblockbox_service_handler.la
liblockbox_service_handler_la_SOURCES = lockbox_service_handler.h
liblockbox_service_handler_la_SOURCES += lockbox_service_handler.cc
liblockbox_service_handler_la_CXXFLAGS = $(LEVELDB_CFLAGS)
liblockbox_service_handler_la_LIBADD = liblockbox_thrift.la
liblockbox_service_handler_la_LIBADD += libdb_manager.la

bin_PROGRAMS += server
server_SOURCES = server.cc
server_CXXFLAGS = $(LEVELDB_CFLAGS)
server_LDADD =
server_LDADD += liblockbox_service_handler.la
server_LDADD += liblockbox_thrift.la
server_LDADD += libdb_manager.la
server_LDADD += libcounter.la
server_LDADD += libguid_creator.la
server_LDADD += $(top_builddir)/crypto/librandom.la
server_LDADD += $(LEVELDB_BIN_LIBS)
server_LDADD += libleveldb_util.la
server_LDADD += $(top_builddir)/base/files/libfile_path.la
server_LDADD += $(top_builddir)/base/liblogging.la
server_LDADD += $(THRIFT_LIBS)
server_LDADD += $(LIBEVENT_LIBS)
server_LDADD += $(PTHREAD_LIBS)
server_LDADD += $(BOOST_THREAD_LIBS)


bin_PROGRAMS += client
client_SOURCES = client.cc
client_LDADD =
client_LDADD += liblockbox_thrift.la
client_LDADD += $(THRIFT_LIBS)


# thrift compiler command. Note that the --out value for the output
# directory.
THRIFT_BUILD = $(THRIFT) --gen cpp --out . $<

####
# Remember to run the generate_thrift_automake.py script once we add a .thrift
# file OR a new service to an existing .thrift file.

# AM_MAKEFLAGS = -W$(top_srcdir)/src/thrift.mk
# $(top_srcdir)/src/thrift.mk:
# 	./generate_thrift_automake.py *.thrift > thrift.mk
####
include thrift.mk


# Delta encoding pieces.
bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_LDADD =
delta_encoding_main_LDADD += $(top_builddir)/courgette/libsimple_delta.la
delta_encoding_main_LDADD += $(top_builddir)/courgette/libstreams.la

# Counter helper library.
noinst_LTLIBRARIES += libcounter.la
libcounter_la_SOURCES =
libcounter_la_SOURCES += counter.h
libcounter_la_SOURCES += counter.cc
libcounter_la_LIBADD = $(BOOST_THREAD_LIBS)

# Database pieces.
noinst_LTLIBRARIES += libdb_manager.la
libdb_manager_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_manager_la_SOURCES = db_manager.h
libdb_manager_la_SOURCES += db_manager.cc
libdb_manager_la_LIBADD = libleveldb_util.la
libdb_manager_la_LIBADD += liblockbox_thrift.la

noinst_LTLIBRARIES += libleveldb_util.la
libleveldb_util_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libleveldb_util_la_SOURCES = leveldb_util.h
libleveldb_util_la_SOURCES += leveldb_util.cc
libleveldb_util_la_LIBADD = $(top_builddir)/base/libfile_util.la

# noinst_LTLIBRARIES += libdb_email_user.la
# libdb_email_user_la_CXXFLAGS = $(LEVELDB_CFLAGS)
# libdb_email_user_la_SOURCES = db_email_user.h
# libdb_email_user_la_SOURCES += db_email_user.cc
