test: testClient testServer

testClient: testClient.cpp
	g++ testClient.cpp -g -o testClient -L ../lib -lMina -lefc64 -leso64 -liconv -ldl -lpthread -lcrypto -I ../include -I ../include/inc -I ../include/http/inc -I ../include/CxxJDK/efc -I ../include/CxxLog4j -fpermissive

testServer: testServer.cpp
	g++ testServer.cpp -g -o testServer -L ../lib -lMina -lefc64 -leso64 -liconv -ldl -lpthread -lcrypto -I ../include -I ../include/inc -I ../include/http/inc -I ../include/CxxJDK/efc -I ../include/CxxLog4j -fpermissive