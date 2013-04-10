server:
	g++ -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift -c UserStorage.cpp -o userstorage.o
	g++ -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift -c UserStorage_server.cpp -o server.o
	g++ -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift -c user_constants.cpp -o constants.o
	g++ -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift -c user_types.cpp -o types.o
	g++ -L/usr/local/lib *.o -o UserStorage_server -lthrift -lthriftnb -levent

client:
	g++  -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include/thrift -c UserStorage_client.cpp -o client.o
	g++  -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -L/usr/local/lib client.o userstorage.o constants.o types.o -o UserStorage_client -lthrift

clean:
	rm -f *.o
