SERVER	= server.exe
CLIENT	= client.exe

SERVER_OBJ	= server.o Network.o
CLIENT_OBJ	= client.o Network.o

HEADS	= Network.h

CFLAGS = -lws2_32

all:
	make $(SERVER)
	make $(CLIENT)

run:
	make
	@echo run server
	$(SERVER)

$(SERVER):$(SERVER_OBJ)
	g++ -o $@ $(SERVER_OBJ) $(CFLAGS)

$(CLIENT):$(CLIENT_OBJ)
	g++ -o $@ $(CLIENT_OBJ) $(CFLAGS)

%.o:%.cpp $(HEADS)
	g++ -c $<

