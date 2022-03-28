.PHONY: all clean run

CFLAGS = -Wall -Werror -g3
CPPFLAGS = -MMD
OSC = obj/src/chessviz/
OSL = obj/src/libchessviz/
SC = src/chessviz/
SL = src/libchessviz/
ADDPATH = -Isrc

all: bin/main

bin/main: $(OSC)main.o $(OSL)libchessviz.a
	$(CC) $(CFLAGS) $(ADDPATH) -o $@ $^

$(OSC)main.o: $(SC)main.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

$(OSL)libchessviz.a: $(OSC)board.o
	ar rcs $@ $^

$(OSC)board.o: $(SL)board.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

clean:
	rm -f $(OSC)*.o $(OSC)*.d $(OSL)*.a

run:
	./bin/main

-include main.d board.d
