
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testFriendliestPerson.c
EXERCISE_FILE = friendliestPerson.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testFriendliestPerson

testFriendliestPerson: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testFriendliestPerson $(SRC_FILES)

clean:
	rm -f testFriendliestPerson

