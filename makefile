CC = g++
CFLAGS  = -g -Werror

default: bin/start

bin/start: Main.o User.o Event.o Comment.o Functions.o #DataParser.o 
	$(CC) $(CFLAGS) -o bin/start Main.o User.o Event.o Comment.o Functions.o 
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

Functions.o: BL/Functions.cpp BL/Functions.h Utils/Header.h Entity/Event.h Entity/User.h
	$(CC) $(CFLAGS) -c BL/Functions.cpp

run:
	./bin/start

debug:
	gdb -q bin/start

clean:
	$(RM) bin/start *.o *~
