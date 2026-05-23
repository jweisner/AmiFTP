# GNUmakefile for tcphook - bebbo/amiga-gcc cross-compiler

CC   = m68k-amigaos-gcc
AR   = m68k-amigaos-ar
NDK  = /opt/amiga/m68k-amigaos/ndk-include

CFLAGS = -noixemul -O2 -fomit-frame-pointer \
         -I$(NDK) \
         -DCLIB_USERGROUP_PROTOS_H

.PHONY: all clean

all: tcp.a

tcp.a: tcp.o amitcp.o
	$(AR) rcs tcp.a tcp.o amitcp.o

tcp.o: tcp.c tcphooks.h
	$(CC) $(CFLAGS) -c -o tcp.o tcp.c

amitcp.o: amitcp.c tcphooks.h
	$(CC) $(CFLAGS) -c -o amitcp.o amitcp.c

clean:
	rm -f tcp.o amitcp.o tcp.a
