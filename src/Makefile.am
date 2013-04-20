AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
AM_CPPFLAGS += -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -Wextra -g

SUBDIRS = # gen-cpp
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =


bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_SOURCES +=


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
THRIFT_BUILD = $(THRIFT) --gen cpp --out gen-cpp $<


noinst_LTLIBRARIES += libuserthrift.la
libuserthrift_la_SOURCES =
libuserthrift_la_SOURCES += gen-cpp/UserStorage.cpp
libuserthrift_la_SOURCES += gen-cpp/UserStorage.h
libuserthrift_la_SOURCES += gen-cpp/user_constants.cpp
libuserthrift_la_SOURCES += gen-cpp/user_types.cpp
libuserthrift_la_SOURCES += gen-cpp/user_constants.h
libuserthrift_la_SOURCES += gen-cpp/user_types.h

$(nodist_libuserthrift_la_SOURCES): $(srcdir)/user.thrift
	$(THRIFT_BUILD)


noinst_LTLIBRARIES += libhcdthrift.la
libhcdthrift_la_SOURCES =
libhcdthrift_la_SOURCES += gen-cpp/VersionExchange.cpp
libhcdthrift_la_SOURCES += gen-cpp/VersionExchange.h
libhcdthrift_la_SOURCES += gen-cpp/hcd_constants.cpp
libhcdthrift_la_SOURCES += gen-cpp/hcd_constants.h
libhcdthrift_la_SOURCES += gen-cpp/hcd_types.cpp
libhcdthrift_la_SOURCES += gen-cpp/hcd_types.h

$(nodist_libhcdthrift_la_SOURCES): $(srcdir)/hcd.thrift
	$(THRIFT_BUILD)


clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf \
		$(nodist_libuserthrift_la_SOURCES) \
		$(nodist_libhcdthrift_la_SOURCES) \
		*.skeleton.cpp


# noinst_LTLIBRARIES += libuserstorage.la
# nodist_libuserstorage_la_SOURCES = user.thrift

# lockbox_main_LDADD = base/files/libfile_path_watcher.a
# lockbox_main_LDADD += base/libmessage_loop.a
# lockbox_main_LDADD += base/libmessage_loop_proxy.a
# lockbox_main_LDADD += base/libtracked_objects.a
