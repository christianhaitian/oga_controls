CC = gcc
CCFLAGS = -W -Wall

BINARY = oga_controls
LIBRARIES = -levdev
SOURCES = "main.c"
INCLUDES = /usr/include/libevdev-1.0/

all:
	$(CC) $(CCFLAGS) $(CXFLAGS) -I$(INCLUDES) $(SOURCES) -o $(BINARY) $(LIBRARIES)

clean:
	rm -f $(BINARY)
