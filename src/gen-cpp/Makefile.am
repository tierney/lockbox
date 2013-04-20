AM_CXXFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -Wextra -g

EXTRA_DIST = attack.py

bin_PROGRAMS =

bin_PROGRAMS += server
server_SOURCES = UserStorage_server.cpp
server_LDADD =
server_LDADD += libuserstorage.la
server_LDADD += libuser_constants.la
server_LDADD += libuser_types.la
server_LDADD += -lthrift -lthriftnb -levent -lpthread -lc
server_LDADD += $(BOOST_THREAD_LIBS)

bin_PROGRAMS += client
client_SOURCES = UserStorage_client.cpp
client_LDADD =
client_LDADD += libuserstorage.la
client_LDADD += libuser_constants.la
client_LDADD += libuser_types.la
client_LDADD += -lthrift

noinst_LTLIBRARIES =

noinst_LTLIBRARIES += libuserstorage.la
libuserstorage_la_SOURCES = UserStorage.cpp UserStorage.h

noinst_LTLIBRARIES += libuser_constants.la
libuser_constants_la_SOURCES = user_constants.cpp user_constants.h

noinst_LTLIBRARIES += libuser_types.la
libuser_types_la_SOURCES = user_types.cpp user_types.h
