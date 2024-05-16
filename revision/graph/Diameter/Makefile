
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testDiameter.c
EXERCISE_FILE = diameter.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testDiameter

testDiameter: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testDiameter $(SRC_FILES)

clean:
	rm -f testDiameter

