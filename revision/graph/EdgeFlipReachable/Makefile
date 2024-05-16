
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testEdgeFlipReachable.c
EXERCISE_FILE = edgeFlipReachable.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testEdgeFlipReachable

testEdgeFlipReachable: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testEdgeFlipReachable $(SRC_FILES)

clean:
	rm -f testEdgeFlipReachable

