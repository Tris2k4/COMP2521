
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testFindTheCrotch.c
EXERCISE_FILE = findTheCrotch.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testFindTheCrotch

testFindTheCrotch: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testFindTheCrotch $(SRC_FILES)

clean:
	rm -f testFindTheCrotch

