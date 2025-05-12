CC=gcc
OBJS=tool/AsciiArtTool.o RLEList.o tool/main.o
EXEC=AsciiArtTool
DEBUG=-g
CFLAGS=-std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror #-DNDEBUG#

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $(EXEC)

tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
RLEList.o: RLEList.c RLEList.h
tool/main.o: tool/main.c RLEList.h tool/AsciiArtTool.h

clean:
	rm -f $(OBJS) $(EXEC)