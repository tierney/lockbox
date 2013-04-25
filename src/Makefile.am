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
# libleveldb_base_la_LIBADD = $(LEVELDB_LIBS)

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

TESTS += db_email_user_test
bin_PROGRAMS += db_email_user_test
db_email_user_test_SOURCES = db_email_user_test.cc
db_email_user_test_CXXFLAGS = $(LEVELDB_CFLAGS)
db_email_user_test_LDADD = $(top_builddir)/testing/gtest/lib/libgtest.la
db_email_user_test_LDADD += $(top_builddir)/testing/gtest/lib/libgtest_main.la
db_email_user_test_LDADD += libdb_email_user.la
db_email_user_test_LDADD += $(top_builddir)/base/files/libfile_path.la
db_email_user_test_LDADD += $(top_builddir)/base/liblogging.la
db_email_user_test_LDADD += libleveldb_util.la
db_email_user_test_LDADD += $(LEVELDB_BIN_LIBS)


bin_PROGRAMS += server
server_SOURCES = UserStorage_server.cpp
server_LDADD =
server_LDADD += libuserthrift.la
server_LDADD += -lthrift -lthriftnb -levent -lpthread -lc
server_LDADD += $(BOOST_THREAD_LIBS)


bin_PROGRAMS += client
client_SOURCES = UserStorage_client.cpp
client_LDADD =
client_LDADD += libuserthrift.la
client_LDADD += -lthrift


# thrift compiler command. Note that the --out value for the output
# directory.
THRIFT_BUILD = $(THRIFT) --gen cpp --out . $<


noinst_LTLIBRARIES += libuserthrift.la
libuserthrift_la_SOURCES =
libuserthrift_la_SOURCES += UserStorage.cpp
libuserthrift_la_SOURCES += UserStorage.h
libuserthrift_la_SOURCES += user_constants.cpp
libuserthrift_la_SOURCES += user_types.cpp
libuserthrift_la_SOURCES += user_constants.h
libuserthrift_la_SOURCES += user_types.h

$(libuserthrift_la_SOURCES): $(srcdir)/user.thrift
	$(THRIFT_BUILD)


noinst_LTLIBRARIES += libhash_chain_digestthrift.la
libhash_chain_digestthrift_la_SOURCES =
libhash_chain_digestthrift_la_SOURCES += VersionExchange.cpp
libhash_chain_digestthrift_la_SOURCES += VersionExchange.h
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_constants.cpp
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_constants.h
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_types.cpp
libhash_chain_digestthrift_la_SOURCES += hash_chain_digest_types.h

$(libhash_chain_digestthrift_la_SOURCES): $(srcdir)/hash_chain_digest.thrift
	$(THRIFT_BUILD)


clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf \
		$(libuserthrift_la_SOURCES) \
		$(libhash_chain_digestthrift_la_SOURCES) \
		*.skeleton.cpp


# Delta encoding pieces.
bin_PROGRAMS += delta_encoding_main
delta_encoding_main_SOURCES = delta_encoding_main.cc
delta_encoding_main_LDADD =
delta_encoding_main_LDADD += $(top_builddir)/courgette/libsimple_delta.la
delta_encoding_main_LDADD += $(top_builddir)/courgette/libstreams.la

# Database pieces.
noinst_LTLIBRARIES += libleveldb_util.la
libleveldb_util_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libleveldb_util_la_SOURCES = leveldb_util.h
libleveldb_util_la_SOURCES += leveldb_util.cc

noinst_LTLIBRARIES += libdb_email_user.la
libdb_email_user_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_email_user_la_SOURCES = db_email_user.h
libdb_email_user_la_SOURCES += db_email_user.cc

noinst_LTLIBRARIES += libdb_user_device.la
libdb_user_device_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_user_device_la_SOURCES = db_user_device.h
libdb_user_device_la_SOURCES += db_user_device.cc

noinst_LTLIBRARIES += libdb_device_sync.la
libdb_device_sync_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_device_sync_la_SOURCES = db_device_sync.h
libdb_device_sync_la_SOURCES += db_device_sync.cc

noinst_LTLIBRARIES += libdb_user_top_dir.la
libdb_user_top_dir_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_user_top_dir_la_SOURCES = db_user_top_dir.h
libdb_user_top_dir_la_SOURCES += db_user_top_dir.cc

noinst_LTLIBRARIES += libdb_email_key.la
libdb_email_key_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_email_key_la_SOURCES = db_email_key.h
libdb_email_key_la_SOURCES += db_email_key.cc

noinst_LTLIBRARIES += libdb_top_dir_meta.la
libdb_top_dir_meta_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_top_dir_meta_la_SOURCES = db_top_dir_meta.h
libdb_top_dir_meta_la_SOURCES += db_top_dir_meta.cc

noinst_LTLIBRARIES += libdb_top_dir_relpath_lock.la
libdb_top_dir_relpath_lock_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_top_dir_relpath_lock_la_SOURCES = db_top_dir_relpath_lock.h
libdb_top_dir_relpath_lock_la_SOURCES += db_top_dir_relpath_lock.cc

noinst_LTLIBRARIES += libdb_top_dir_snaps.la
libdb_top_dir_snaps_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_top_dir_snaps_la_SOURCES = db_top_dir_snaps.h
libdb_top_dir_snaps_la_SOURCES += db_top_dir_snaps.cc

noinst_LTLIBRARIES += libdb_top_dir_data.la
libdb_top_dir_data_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_top_dir_data_la_SOURCES = db_top_dir_data.h
libdb_top_dir_data_la_SOURCES += db_top_dir_data.cc

noinst_LTLIBRARIES += libdb_top_dir_fptrs.la
libdb_top_dir_fptrs_la_CXXFLAGS = $(LEVELDB_CFLAGS)
libdb_top_dir_fptrs_la_SOURCES = db_top_dir_fptrs.h
libdb_top_dir_fptrs_la_SOURCES += db_top_dir_fptrs.cc
