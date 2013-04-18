AM_CXXFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -Wextra -g

bin_PROGRAMS =

bin_PROGRAMS += server
server_SOURCES = UserStorage_server.cpp
server_LDADD =
server_LDADD += libuserstorage.a
server_LDADD += libuser_constants.a
server_LDADD += libuser_types.a
server_LDADD += -lthrift -lthriftnb -levent -lboost_thread-mt -lpthread -lc


bin_PROGRAMS += client
client_SOURCES = UserStorage_client.cpp
client_LDADD =
client_LDADD += libuserstorage.a
client_LDADD += libuser_constants.a
client_LDADD += libuser_types.a
client_LDADD += -lthrift

noinst_LIBRARIES =

noinst_LIBRARIES += libuserstorage.a
libuserstorage_a_SOURCES = UserStorage.cpp UserStorage.h

noinst_LIBRARIES += libuser_constants.a
libuser_constants_a_SOURCES = user_constants.cpp user_constants.h

noinst_LIBRARIES += libuser_types.a
libuser_types_a_SOURCES = user_types.cpp user_types.h
