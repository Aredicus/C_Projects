CC = gcc
CFLAGC = -Wall -Werror -Wextra -g -std=c11
SOURCES_C = *.c

all: clean instal

instal:
	$(CC) $(CFLAGC) $(SOURCES_C) -o tree_zaitsev
	echo "Now create file tree_zaitsev"

clean:
	rm -rf ./tree_zaitsev*
