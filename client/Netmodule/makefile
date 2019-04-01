# MESSAGE_OBJECTS := 
COMPILE_OPTIONS=-L lib/linux -lMina -lLogger -lefc64 -leso64 -liconv -ldl -lpthread -lcrypto -I include -I include/inc -I include/http/inc -I include/CxxJDK/efc -I include/CxxLog4j -fpermissive

test/testClient: test/testClient.o src/Messages/Message.o src/Messages/MessageCodecFactory.o src/Server.o
	g++ test/testClient.o src/Messages/Message.o src/Messages/MessageCodecFactory.o src/Server.o -g -o test/testClient $(COMPILE_OPTIONS) 

test/testServer: test/testServer.o src/Messages/Message.o src/Messages/MessageCodecFactory.o Server.o
	g++ test/testServer.o src/Messages/Message.o src/Messages/MessageCodecFactory.o src/Server.o -g -o test/testServer $(COMPILE_OPTIONS)

test/testClient.o: test/testClient.cpp
	g++ test/testClient.cpp -g -c $(COMPILE_OPTIONS) -o test/testClient.o
test/testServer.o: test/testServer.cpp
	g++ test/testServer.cpp -g -c $(COMPILE_OPTIONS) -o test/testServer.o

lib: test/testClient
	cp src/*.o obj
	cp src/Messages/*.o obj
	cd obj && ar crv libNetmodule.a *.o && mv libNetmodule.a ../
	cp libNetmodule lib/linux

clean:
	rm src/*.o
	rm obj/*.o
	

%.o: %.cpp
	g++ -c -g $< -o $@ $(COMPILE_OPTIONS)
