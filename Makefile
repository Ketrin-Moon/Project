SUBDIRS = src lib 
OBJECTS = client.o lib.o hash.o

vpath %.c src:lib
vpath %.h include
vpath %.o src:lib

CC:=gcc
FLAGS+= -O2 -Wall -pedantic -ansi 
LDFLAGS+=-lncurses -std=c99 -lpthread -g

.PHONY: subdirs $(SUBDIRS)

all: $(OBJECTS)
		$(CC) -o client $^ $(LDFLAGS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@

src: lib

