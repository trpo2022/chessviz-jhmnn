.PHONY: all clean test run

CFLAGS = -Wall -Werror -g3
ADDPATH = -I src
CPPFLAGS = -MMD
CPPFLAGS_TEST = -I thirdparty $(CPPFLAGS)

OSC = obj/src/chessviz/
OSL = obj/src/libchessviz/
OT = obj/test/
SC = src/chessviz/
SL = src/libchessviz/
TEST = test/

all: bin/main

bin/main: $(OSC)main.o $(OSL)libchessviz.a
	$(CC) $(CFLAGS) $(ADDPATH) -o $@ $^

$(OSC)main.o: $(SC)main.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

$(OSL)libchessviz.a: $(OSC)board.o
	ar rcs $@ $^

$(OSC)board.o: $(SL)board.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) -o $@ $<

bin/main-test: $(OT)test.o $(OSC)board.o
	$(CC) $(CFLAGS) $(ADDPATH) -o $@ $^

$(OT)test.o: $(TEST)main.c
	$(CC) -c $(CFLAGS) $(ADDPATH) $(CPPFLAGS) $(CPPFLAGS_TEST) -o $@ $<

clean:
	rm -f $(OSC)*.o $(OSC)*.d $(OSL)*.a $(OT)*.o

test: ./bin/main-test
	./bin/main-test

run: ./bin/main
	./bin/main

-include main.d board.d
