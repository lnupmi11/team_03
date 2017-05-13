CC = g++
CFLAGS  = -g -std=c++11 -Wall -Wno-sign-compare -Wextra -Wformat -Wformat-security -Wpedantic

GTEST_HOME = /usr/src/gtest

GTEST_LIB = -I $(GTEST_HOME)/include -L $(GTEST_HOME)/lib -lgtest -lgtest_main -lpthread

TEST_SRC := $(wildcard test/*.cpp)
TEST_OBJ := $(TEST_SRC:.cpp=.o)

default: bin/start bin/test
	$(RM) *.o *~ $(TEST_OBJ)

bin/start: Main.o User.o Event.o Comment.o Functions.o NiceOut.o DataParser.o DataProcessor.o 
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(CFLAGS) -o bin/start Main.o User.o Event.o Comment.o Functions.o NiceOut.o DataProcessor.o DataParser.o

bin/test: $(TEST_OBJ) User.o Event.o Comment.o Functions.o NiceOut.o DataParser.o DataProcessor.o 
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $(GTEST_LIB) -o bin/test $(TEST_OBJ) User.o Event.o Comment.o Functions.o NiceOut.o DataProcessor.o DataParser.o

Main.o: Main.cpp Utils/NiceOut.h Utils/Header.h Entity/User.h Entity/Event.h Entity/Comment.h DTO/DataParser.h DTO/DataProcessor.h 
	$(CC) $(CFLAGS) -c Main.cpp

test/%.o: $(TEST_SRC) Utils/NiceOut.h Utils/Header.h Entity/User.h Entity/Event.h Entity/Comment.h DTO/DataParser.h DTO/DataProcessor.h 
	$(CC) $(CFLAGS) $(GTEST_LIB) -c -o $@ $<

DataParser.o: DTO/DataParser.cpp DTO/DataParser.h
	$(CC) $(CFLAGS) -c DTO/DataParser.cpp

DataProcessor.o: DTO/DataProcessor.cpp DTO/DataProcessor.h Entity/User.h
	$(CC) $(CFLAGS) -c DTO/DataProcessor.cpp

User.o: Entity/User.cpp Entity/User.h Entity/Event.h Utils/Header.h 
	$(CC) $(CFLAGS) -c Entity/User.cpp

Event.o: Entity/Event.cpp Entity/Event.h Utils/Header.h Entity/Comment.h
	$(CC) $(CFLAGS) -c Entity/Event.cpp

Comment.o: Entity/Comment.cpp Entity/Comment.h Utils/Header.h Entity/User.h
	$(CC) $(CFLAGS) -c Entity/Comment.cpp

Functions.o: BL/Functions.cpp BL/Functions.h Utils/Header.h Entity/Event.h Entity/User.h Utils/NiceOut.h
	$(CC) $(CFLAGS) -c BL/Functions.cpp

NiceOut.o: Utils/NiceOut.h
	$(CC) $(CFLAGS) -c Utils/NiceOut.cpp

.PHONY: run
run:
	@if [ ! -d data ]; then mkdir data; fi
	@./bin/start

.PHONY: test
test:
	@if [ ! -d data ]; then mkdir data; fi
	@./bin/test

.PHONY: debug
debug:
	@if [ ! -d data ]; then mkdir data; fi
	@gdb -q bin/start

.PHONY: clean
clean:
	$(RM) bin/start bin/test data/* *.o *~ $(TEST_OBJ)
