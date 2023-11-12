CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
FILEOUT = out/execute.out
MAIN_SOURCES = execute.c
GLOBALS_SOURCES = student.c
CONV = convert.c
CONVOUT = out/conv.out
GEN = db_generator.c
GENOUT = out/db.out

all: out cmp convert generate

clean:
	rm -rf ./out
out:
	mkdir ./out

cmp:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(MAIN_SOURCES) -o $(FILEOUT)

main:
	./$(FILEOUT) $(FILE)

convertation:
	./$(CONVOUT) $(FILE1) $(FILE2)

generation:
	./$(GENOUT) $(FILE) $(COUNT)

convert:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(CONV) -o $(CONVOUT)

generate:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(GEN) -o $(GENOUT)
