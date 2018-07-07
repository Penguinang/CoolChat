# MESSAGE_OBJECTS := 
COMPILE_OPTIONS= -L ../lib -lMina -lefc64 -leso64 -liconv -ldl -lpthread -lcrypto -I ../include -I ../include/inc -I ../include/http/inc -I ../include/CxxJDK/efc -I ../include/CxxLog4j -fpermissive

test: testClient

testClient: testClient_o ../src/Messages/Message.o ../src/Messages/MessageCodecFactory.o Server.o
	g++ testClient.o ../src/Messages/Message.o ../src/Messages/MessageCodecFactory.o ../src/Server.o -g -o testClient $(COMPILE_OPTIONS) 

testServer: testServer_o ../src/Messages/Message.o ../src/Messages/MessageCodecFactory.o Server.o
	g++ testServer.o ../src/Messages/Message.o ../src/Messages/MessageCodecFactory.o ../src/Server.o -g -o testServer $(COMPILE_OPTIONS)

testClient_o: testClient.cpp
	g++ testClient.cpp -g -c $(COMPILE_OPTIONS) 
testServer_o: testServer.cpp
	g++ testServer.cpp -g -c $(COMPILE_OPTIONS) 

../src/Messages/%.o: ../src/Messages/%.cpp
	g++ -c -g $< -o $@ $(COMPILE_OPTIONS)


Server.o: ../src/Server.cpp
	g++ -c -g ../src/Server.cpp -o ../src/Server.o $(COMPILE_OPTIONS)