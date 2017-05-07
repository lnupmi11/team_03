CC = g++
CFLAGS  = -g -std=c++11 -Wall -Wno-sign-compare -Wextra -Wformat -Wformat-security -Wpedantic

default: bin/start

bin/start: Main.o User.o Event.o Comment.o Functions.o NiceOut.o DataParser.o DataProcessor.o 
	if [ ! -d "bin" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) -o bin/start Main.o User.o Event.o Comment.o Functions.o NiceOut.o DataProcessor.o DataParser.o
	$(RM) *.o *~

Main.o: Main.cpp Utils/NiceOut.h Utils/Header.h Entity/User.h Entity/Event.h Entity/Comment.h DTO/DataParser.h DTO/DataProcessor.h 
	$(CC) $(CFLAGS) -c Main.cpp

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

run:
	./bin/start

debug:
	gdb -q bin/start

clean:
	$(RM) bin/start *.o *~
