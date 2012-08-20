all : make
VPATH = zerodb_server:zerodb_slave
CC = gcc
OBJ = zerodb_server.o bloom_filter.o key_slave_map.o hash.o
CFLAGS += -g




make : $(OBJ)
	$(CC) -o zerodb_server/zerodb_server $(OBJ) -g
zerodb_server.o : bloom_filter.h key_slave_map.h
bloom_filter.o : bloom_filter.h hash.h 
key_slave_map.o : key_slave_map.h hash.h
hash.o : hash.h

clean :
	rm -f $(OBJ)
