AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
SUBDIRS = # gen-cpp
TESTS =
bin_PROGRAMS =
noinst_PROGRAMS =
noinst_LTLIBRARIES =

bin_PROGRAMS += lockbox_main
lockbox_main_SOURCES = lockbox_main.cc
lockbox_main_SOURCES +=

noinst_LTLIBRARIES += libusergencpp.la
nodist_libusergencpp_la_SOURCES = \
	UserStorage.cpp \
	UserStorage.h \
	user_constants.cpp \
	user_types.cpp \
	user_constants.h \
	user_types.h

UserStorage.cpp user_constants.cpp user_types.cpp: $(srcdir)/user.thrift
	$(THRIFT) --gen cpp --out . $<

clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf $(nodist_libusergencpp_la_SOURCES) *.skeleton.cpp

# noinst_LTLIBRARIES += libuserstorage.la
# nodist_libuserstorage_la_SOURCES = user.thrift

# lockbox_main_LDADD = base/files/libfile_path_watcher.a
# lockbox_main_LDADD += base/libmessage_loop.a
# lockbox_main_LDADD += base/libmessage_loop_proxy.a
# lockbox_main_LDADD += base/libtracked_objects.a
