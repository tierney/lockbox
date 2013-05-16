LEVELDB_CFLAGS = -I$(top_builddir)/leveldb/include

AM_CPPFLAGS = -I$(top_srcdir)/testing/gtest/include
AM_CPPFLAGS += -I$(top_srcdir) -I$(top_builddir) $(LEVELDB_CFLAGS)
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -DUSE_OPENSSL
AM_CFLAGS = -Wall -Wextra -g -O0
AM_CXXFLAGS = -Wall -Wextra -g -O0
AM_LDFLAGS = -L$(top_builddir) -static
if DARWIN
AM_LDFLAGS += -framework Foundation -framework Cocoa -framework Security -framework IOKit
AM_CXXFLAGS += -std=gnu++11 -stdlib=libc++
endif

TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

LEVELDB_BIN_LIBS = $(top_builddir)/leveldb/libleveldb.a
if DARWIN
LEVELDB_BIN_LIBS += -L/usr/local/Cellar/snappy/1.0.5/lib
endif
LEVELDB_BIN_LIBS += -lsnappy

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


# bin_PROGRAMS += lockbox_main
# lockbox_main_SOURCES = lockbox_main.cc
# lockbox_main_LDADD =
# lockbox_main_LDADD += $(GFLAGS_LIBS)
# lockbox_main_LDADD += $(top_builddir)/base/libfile_util.la
# lockbox_main_LDADD += $(top_builddir)/crypto/librsa_private_key.la
# lockbox_main_LDADD += $(top_builddir)/base/threading/libthread.la
# lockbox_main_LDADD += $(top_builddir)/base/files/libfile_path_watcher.la
# lockbox_main_LDADD += $(top_builddir)/base/librun_loop.la
# lockbox_main_LDADD += $(top_builddir)/base/synchronization/libwaitable_event.la
# lockbox_main_LDADD += libclient_initialization.la
# lockbox_main_LDADD += libfile_watcher.la
# lockbox_main_LDADD += libnegotiator.la
# lockbox_main_LDADD += $(BOOST_SYSTEM_LIBS)

# bin_PROGRAMS += leveldb_sb
# leveldb_sb_SOURCES = leveldb_sb.cc
# leveldb_sb_CXXFLAGS = $(LEVELDB_CFLAGS)
# leveldb_sb_LDADD = $(LEVELDB_BIN_LIBS)
# leveldb_sb_LDADD += $(GLOG_LIBS)

# noinst_LTLIBRARIES += libleveldb_base.la
# libleveldb_base_la_SOURCES = leveldb_base.h
# libleveldb_base_la_SOURCES += leveldb_base.cc
# libleveldb_base_la_CXXFLAGS = $(LEVELDB_CFLAGS)
# libleveldb_base_la_LIBADD = $(LEVELDB_BIN_LIBS)

noinst_LTLIBRARIES += libsimple_delta.la
libsimple_delta_la_SOURCES = \
	simple_delta.cc \
	simple_delta.h
libsimple_delta_la_LIBADD = \
	$(top_builddir)/courgette/libsimple_delta.la \
	$(top_builddir)/courgette/libstreams.la


noinst_LTLIBRARIES += libupdate_queuer.la
libupdate_queuer_la_SOURCES = update_queuer.h
libupdate_queuer_la_SOURCES += update_queuer.cc
libupdate_queuer_la_CXXFLAGS = $(BOOST_THREAD_CFLAGS)
if DARWIN
libupdate_queuer_la_CXXFLAGS += $(AM_CXXFLAGS)
endif
libupdate_queuer_la_LIBADD = $(GLOG_LIBS)
libupdate_queuer_la_LIBADD += $(BOOST_THREAD_LIBS)
libupdate_queuer_la_LIBADD += libdb_manager_server.la

noinst_LTLIBRARIES += libclient_initialization.la
libclient_initialization_la_SOURCES = client_initialization.h
libclient_initialization_la_SOURCES += client_initialization.cc

# noinst_LTLIBRARIES += libfile_watcher.la
# libfile_watcher_la_SOURCES = file_watcher.h

# noinst_LTLIBRARIES += libnegotiator.la
# libnegotiator_la_SOURCES = negotiator

# bin_PROGRAMS += user_device_queue_main
# user_device_queue_main_SOURCES = user_device_queue_main.cc
# user_device_queue_main_CXXFLAGS = -static
# user_device_queue_main_CXXFLAGS += $(GFLAGS_CFLAGS)
# user_device_queue_main_CXXFLAGS += $(LEVELDB_CFLAGS)
# user_device_queue_main_LDADD = $(LEVELDB_BIN_LIBS)
# user_device_queue_main_LDADD += $(GFLAGS_LIBS)
# user_device_queue_main_LDADD += $(top_builddir)/base/libstringprintf.la
# user_device_queue_main_LDADD += $(GLOG_LIBS)

# TESTS += db_email_user_test
# bin_PROGRAMS += db_email_user_test
# db_email_user_test_SOURCES = db_email_user_test.cc
# db_email_user_test_CXXFLAGS = $(LEVELDB_CFLAGS)
# db_email_user_test_LDADD = $(top_builddir)/testing/gtest/lib/libgtest.la
# db_email_user_test_LDADD += $(top_builddir)/testing/gtest/lib/libgtest_main.la
# db_email_user_test_LDADD += libdb_email_user.la
# db_email_user_test_LDADD += $(top_builddir)/base/files/libfile_path.la
# db_email_user_test_LDADD += $(GLOG_LIBS)
# db_email_user_test_LDADD += libleveldb_util.la
# db_email_user_test_LDADD += $(LEVELDB_BIN_LIBS)

noinst_LTLIBRARIES += libguid_creator.la
libguid_creator_la_SOURCES = guid_creator.h
libguid_creator_la_SOURCES += guid_creator.cc

noinst_LTLIBRARIES += liblockbox_service_handler.la
liblockbox_service_handler_la_SOURCES = lockbox_service_handler.h
liblockbox_service_handler_la_SOURCES += lockbox_service_handler.cc
liblockbox_service_handler_la_CXXFLAGS = $(AM_CXXFLAGS) $(LEVELDB_CFLAGS)
liblockbox_service_handler_la_LIBADD = liblockbox_thrift.la
liblockbox_service_handler_la_LIBADD += libdb_manager_server.la
liblockbox_service_handler_la_LIBADD += $(top_builddir)/base/libsha1.la
liblockbox_service_handler_la_LIBADD += $(top_builddir)/base/liblogging.la
liblockbox_service_handler_la_LIBADD += $(top_builddir)/base/libbase64.la
liblockbox_service_handler_la_LIBADD += $(top_builddir)/base/libstring_util.la
liblockbox_service_handler_la_LIBADD += $(top_builddir)/base/libprocess_util.la

noinst_LTLIBRARIES += libhash_util.la
libhash_util_la_SOURCES = \
  hash_util.h \
  hash_util.cc
libhash_util_la_LIBADD = \
  $(top_builddir)/base/strings/libstring_number_conversions.la \
  $(top_builddir)/base/libsha1.la

bin_PROGRAMS += server
server_SOURCES = server.cc
server_CXXFLAGS = $(LEVELDB_CFLAGS) $(AM_CXXFLAGS)
server_LDADD =
server_LDADD += liblockbox_service_handler.la
server_LDADD += $(LEVELDB_BIN_LIBS)
server_LDADD += libupdate_queuer.la
server_LDADD += liblockbox_thrift.la
server_LDADD += libdb_manager_server.la
server_LDADD += libcounter.la
server_LDADD += libguid_creator.la
server_LDADD += $(top_builddir)/crypto/librandom.la
server_LDADD += libleveldb_util.la
server_LDADD += $(top_builddir)/base/files/libfile_path.la
server_LDADD += $(GLOG_LIBS)
server_LDADD += $(THRIFT_LIBS)
server_LDADD += $(LIBEVENT_LIBS)
server_LDADD += $(PTHREAD_LIBS)
server_LDADD += $(BOOST_THREAD_LIBS)

noinst_LTLIBRARIES += libfile_util.la
libfile_util_la_SOURCES = file_util.h
libfile_util_la_SOURCES += file_util.cc

noinst_LTLIBRARIES += libupdate_from_server.la
libupdate_from_server_la_SOURCES = update_from_server.h
libupdate_from_server_la_SOURCES += update_from_server.cc

bin_PROGRAMS += client_main
client_main_SOURCES = client_main.cc
client_main_LDADD =
client_main_LDADD += $(GFLAGS_LIBS)
client_main_LDADD += libclient.la
client_main_LDADD += $(LEVELDB_BIN_LIBS)

noinst_LTLIBRARIES += libclient.la
libclient_la_SOURCES = client.h
libclient_la_SOURCES += client.cc
libclient_la_LIBADD =
libclient_la_LIBADD += libupdate_from_server.la
libclient_la_LIBADD += libqueue_filter.la
libclient_la_LIBADD += librsa.la
libclient_la_LIBADD += librsa_public_key_openssl.la
libclient_la_LIBADD += liblockbox_thrift.la
libclient_la_LIBADD += libfile_util.la
libclient_la_LIBADD += $(THRIFT_LIBS)
libclient_la_LIBADD += libdb_manager_client.la
libclient_la_LIBADD += libfile_watcher_thread.la
libclient_la_LIBADD += libfile_event_queue_handler.la
libclient_la_LIBADD += libencryptor.la
libclient_la_LIBADD += libleveldb_util.la
libclient_la_LIBADD += $(BOOST_THREAD_LIBS)

# Delta encoding pieces.
bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_CXXFLAGS = $(AM_CXXFLAGS)
delta_encoding_main_LDADD =
delta_encoding_main_LDADD += $(top_builddir)/courgette/libsimple_delta.la
delta_encoding_main_LDADD += $(top_builddir)/courgette/libstreams.la
if DARWIN
delta_encoding_main_LDADD += -L$(ZLIB_LIBS) -lz
endif


noinst_LTLIBRARIES += libfile_watcher_thread.la
libfile_watcher_thread_la_SOURCES = file_watcher_thread.h
libfile_watcher_thread_la_SOURCES += file_watcher_thread.cc
libfile_watcher_thread_la_LIBADD = $(top_builddir)/file_watcher/libfile_watcher.la

# Counter helper library.
noinst_LTLIBRARIES += libcounter.la
libcounter_la_SOURCES =
libcounter_la_SOURCES += counter.h
libcounter_la_SOURCES += counter.cc
libcounter_la_LIBADD = $(BOOST_THREAD_LIBS)

noinst_LTLIBRARIES += libutil.la
libutil_la_SOURCES = util.h
libutil_la_SOURCES += util.cc

# Encryptor.

noinst_LTLIBRARIES += libencryptor.la
libencryptor_la_SOURCES = encryptor.h
libencryptor_la_SOURCES += encryptor.cc
libencryptor_la_CXXFLAGS = $(AM_CXXFLAGS)
if DARWIN
libencryptor_la_CXXFLAGS += -I$(NSS_CFLAGS)/nss $(NSPR_CFLAGS)
endif
libencryptor_la_LIBADD =
libencryptor_la_LIBADD += librsa.la
libencryptor_la_LIBADD += libhash_util.la
libencryptor_la_LIBADD += librsa_public_key_openssl.la
libencryptor_la_LIBADD += libblock_cipher.la
libencryptor_la_LIBADD += $(top_builddir)/crypto/libsymmetric_key.la
libencryptor_la_LIBADD += $(top_builddir)/crypto/libencryptor.la
libencryptor_la_LIBADD += $(top_builddir)/crypto/librandom.la
libencryptor_la_LIBADD += $(top_builddir)/crypto/librsa_private_key.la

noinst_LTLIBRARIES += libblock_cipher.la
libblock_cipher_la_SOURCES = block_cipher.cc
libblock_cipher_la_SOURCES += block_cipher.h

noinst_LTLIBRARIES += librsa_public_key_openssl.la
librsa_public_key_openssl_la_SOURCES = rsa_public_key_openssl.cc
librsa_public_key_openssl_la_SOURCES += rsa_public_key_openssl.h

noinst_LTLIBRARIES += librsa.la
librsa_la_SOURCES = rsa.h
librsa_la_SOURCES += rsa.cc

# Event helpers.
noinst_LTLIBRARIES += libqueue_filter.la
libqueue_filter_la_SOURCES = queue_filter.h
libqueue_filter_la_SOURCES += queue_filter.cc
libqueue_filter_la_LIBADD = $(BOOST_THREAD_LIBS)
libqueue_filter_la_LIBADD += libdb_manager.la
libqueue_filter_la_LIBADD += libutil.la
libqueue_filter_la_LIBADD += $(top_builddir)/base/strings/libstring_split.la

noinst_LTLIBRARIES += libfile_event_queue_handler.la
libfile_event_queue_handler_la_SOURCES =
libfile_event_queue_handler_la_SOURCES += file_event_queue_handler.h
libfile_event_queue_handler_la_SOURCES += file_event_queue_handler.cc
libfile_event_queue_handler_la_LIBADD = $(top_builddir)/base/libmd5.la \
	$(top_builddir)/base/libsha1.la \
	libsimple_delta.la \
	libhash_util.la

# Database pieces.
noinst_LTLIBRARIES += libdb_manager.la
libdb_manager_la_CXXFLAGS = $(LEVELDB_CFLAGS) $(AM_CXXFLAGS)
libdb_manager_la_SOURCES = db_manager.h
libdb_manager_la_SOURCES += db_manager.cc
libdb_manager_la_LIBADD = libleveldb_util.la
libdb_manager_la_LIBADD += liblockbox_thrift.la
libdb_manager_la_LIBADD += libguid_creator.la
libdb_manager_la_LIBADD += $(top_builddir)/base/libstring_util.la

noinst_LTLIBRARIES += libdb_manager_client.la
libdb_manager_client_la_CXXFLAGS = $(LEVELDB_CFLAGS) $(AM_CXXFLAGS)
libdb_manager_client_la_SOURCES = db_manager_client.h
libdb_manager_client_la_SOURCES += db_manager_client.cc
libdb_manager_client_la_LIBADD =
libdb_manager_client_la_LIBADD += $(top_builddir)/base/libfile_util.la
libdb_manager_client_la_LIBADD += $(GLOG_LIBS)
libdb_manager_client_la_LIBADD += libleveldb_util.la
libdb_manager_client_la_LIBADD += liblockbox_thrift.la
libdb_manager_client_la_LIBADD += libdb_manager.la

noinst_LTLIBRARIES += libdb_manager_server.la
libdb_manager_server_la_CXXFLAGS = $(LEVELDB_CFLAGS)  $(AM_CXXFLAGS)
libdb_manager_server_la_SOURCES = db_manager_server.h
libdb_manager_server_la_SOURCES += db_manager_server.cc
libdb_manager_server_la_LIBADD = libleveldb_util.la
libdb_manager_server_la_LIBADD += liblockbox_thrift.la
libdb_manager_server_la_LIBADD += libdb_manager.la

noinst_LTLIBRARIES += libleveldb_util.la
libleveldb_util_la_CXXFLAGS =  $(AM_CXXFLAGS) $(LEVELDB_CFLAGS)
libleveldb_util_la_SOURCES = leveldb_util.h
libleveldb_util_la_SOURCES += leveldb_util.cc
libleveldb_util_la_LIBADD = $(top_builddir)/base/libfile_util.la

# noinst_LTLIBRARIES += libdb_email_user.la
# libdb_email_user_la_CXXFLAGS = $(LEVELDB_CFLAGS)
# libdb_email_user_la_SOURCES = db_email_user.h
# libdb_email_user_la_SOURCES += db_email_user.cc
