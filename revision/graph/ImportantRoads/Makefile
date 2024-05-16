
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testImportantRoads.c
EXERCISE_FILE = importantRoads.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testImportantRoads

testImportantRoads: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testImportantRoads $(SRC_FILES)

clean:
	rm -f testImportantRoads

