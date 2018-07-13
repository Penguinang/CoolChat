# MESSAGE_OBJECTS := 
COMPILE_OPTIONS=-L ../../lib/linux -lMina -lefc64 -leso64 -liconv -ldl -lpthread -lcrypto -I ../../include -I ../../include/inc -I ../../include/http/inc -I ../../include/CxxJDK/efc -I ../../include/CxxLog4j -fpermissive

testClient: testClient_o ../../src/Messages/Message.o ../../src/Messages/MessageCodecFactory.o ../../src/Server.o
	g++ testClient.o ../../src/Messages/Message.o ../../src/Messages/MessageCodecFactory.o ../../src/Server.o -g -o testClient $(COMPILE_OPTIONS) 

testServer: testServer_o ../../src/Messages/Message.o ../../src/Messages/MessageCodecFactory.o Server.o
	g++ testServer.o ../../src/Messages/Message.o ../../src/Messages/MessageCodecFactory.o ../../src/Server.o -g -o testServer $(COMPILE_OPTIONS)

testClient_o: ../testClient.cpp
	g++ ../testClient.cpp -g -c $(COMPILE_OPTIONS) 
testServer_o: ../testServer.cpp
	g++ ../testServer.cpp -g -c $(COMPILE_OPTIONS) 

lib: testClient
	cp ../../src/*.o ../../obj
	cp ../../src/Messages/*.o ../../obj
	cd ../../obj && ar crv libNetmodule.a *.o && mv libNetmodule.a ../lib
	

%.o: %.cpp
	g++ -c -g $< -o $@ $(COMPILE_OPTIONS)
