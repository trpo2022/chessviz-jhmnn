.PHONY: all clean run

CFLAGS = -Wall -Werror
CPPFLAGS = -MMD
OSC = obj/src/chessviz/
OSL = obj/src/libchessviz/
SC = src/chessviz/
SL = src/libchessviz/
ADDPATH = -Isrc

all: bin/main

bin/main: $(OSC)main.o $(OSC)board.o
	$(CC) $(CFLAGS) $(ADDPATH) -o $@ $^

$(OSC)main.o: $(SC)main.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

$(OSC)board.o: $(SL)board.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

clean:
	rm -f $(OSC)*.o

run:
	./bin/main

-include main.d board.d