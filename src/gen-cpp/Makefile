CXX=clang++
CXXFLAGS= -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -Wextra -g -I/usr/local/include/thrift

all: server client

server:
	$(CXX) $(CXXFLAGS) -c UserStorage.cpp -o userstorage.o
	$(CXX) $(CXXFLAGS) -c UserStorage_server.cpp -o server.o
	$(CXX) $(CXXFLAGS) -c user_constants.cpp -o constants.o
	$(CXX) $(CXXFLAGS) -c user_types.cpp -o types.o
	$(CXX) -L/usr/local/lib userstorage.o server.o constants.o types.o -o UserStorage_server \
		-lthrift -lthriftnb -levent -lboost_thread-mt

client:
	$(CXX) $(CXXFLAGS) -c UserStorage_client.cpp -o client.o
	$(CXX) $(CXXFLAGS) -L/usr/local/lib client.o userstorage.o constants.o types.o -o UserStorage_client -lthrift

clean:
	rm -f *.o UserStorage_server UserStorage_client
