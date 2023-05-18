CC = gcc
CFLAGC = -Wall -Werror -Wextra -g -std=c11
SOURCES_C = *.c

all: clean instal

instal:
	$(CC) $(CFLAGC) $(SOURCES_C) -o deque_zaitsev
	echo "Now create file deque_zaitsev"

clean:
	rm -rf ./deque_zaitsev*
