CC = g++
<<<<<<< HEAD
CFLAGS  = -g -std=c++0x -Wall -Wno-sign-compare -Wextra -Wformat -Wformat-security -Wpedantic 
=======
CFLAGS  = -std=c++11 -g -Wall -Wno-sign-compare -Wextra -Wformat -Wformat-security -Wpedantic 
>>>>>>> 7d5d5b385344db76c9a8bfec1092de14c1610f39

default: bin/start

bin/start: Main.o User.o Event.o Comment.o Functions.o NiceOut.o #DataParser.o 
	$(CC) $(CFLAGS) -o bin/start Main.o User.o Event.o Comment.o Functions.o NiceOut.o
	$(RM) *.o *~

Main.o: Main.cpp Utils/NiceOut.h Utils/Header.h Entity/User.h Entity/Event.h Entity/Comment.h #DTO/DataParser.h 
	$(CC) $(CFLAGS) -c Main.cpp

#DataParser.o: DTO/DataParser.cpp DTO/DataParser.h Entity/User.h
#	$(CC) $(CFLAGS) -c DTO/DataParser.cpp

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
