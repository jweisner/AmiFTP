# GNUmakefile for AmiFTP - bebbo/amiga-gcc cross-compiler
# Runs inside the amiga-buildenv container:
#   podman run --rm \
#     -v <repo>:/work \
#     -v <reaction.lib_sasc>:/reaction \
#     -v <rtasl.lib>:/rtasl \
#     amiga-buildenv make -C /work/Source/amiftp -f GNUmakefile
#
# REACTION and RTASL may be overridden on the command line to point at the
# source trees (must be absolute paths visible inside the container).

CC      = m68k-amigaos-gcc
AR      = m68k-amigaos-ar
STRIP   = m68k-amigaos-strip

NDK     = /opt/amiga/m68k-amigaos/ndk-include

REACTION ?= /reaction
RTASL    ?= /rtasl

CFLAGS  = -noixemul -O2 -fomit-frame-pointer \
          -I$(NDK) \
          -Iinc \
          -I../tcphook \
          -I../wb2cli \
          -I$(RTASL)/Source/include \
          -DSOCKIO \
          -DNO_INLINE_STDARG

LDFLAGS = -noixemul
LIBS    = ../tcphook/tcp.a \
          $(REACTION)/src/libreaction.a \
          $(RTASL)/Source/librtasl.a \
          -lamiga

PROG    = AmiFTP

VERSION = 2.1

OBJS =  obj/gcc_compat.o obj/misc.o obj/data.o obj/dofuncs.o \
        obj/change_dir.o obj/readdir.o obj/dirlist.o \
        obj/MainWindow.o obj/AmiFTP.o obj/TransferWindow.o \
        obj/SiteWindow.o obj/config.o obj/PrefsWindow.o \
        obj/ConnectWindow.o obj/ftp.o obj/rexx.o \
        obj/cache.o obj/main.o obj/locale.o obj/AmiFTP_Cat.o \
        obj/aguide.o obj/ADT.o obj/Menu.o obj/SpeedBar.o \
        obj/version.o

EXTOBJS = ../wb2cli/wb2cli.o ../sprintf/sprintf.o

.PHONY: all clean

all: obj $(PROG)

obj:
	mkdir -p obj

$(PROG): $(OBJS) $(EXTOBJS) ../tcphook/tcp.a \
         $(REACTION)/src/libreaction.a $(RTASL)/Source/librtasl.a
	$(CC) $(LDFLAGS) -o $(PROG)_d $(OBJS) $(EXTOBJS) $(LIBS)
	$(STRIP) -o $(PROG) $(PROG)_d

AMIGADATE := $(shell date '+(%d.%m.%y)')

obj/version.o: version.c
	$(CC) $(CFLAGS) -DVERSION='"$(VERSION)"' -D'__AMIGADATE__="$(AMIGADATE)"' -c -o $@ $<

obj/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

../tcphook/tcp.a:
	$(MAKE) -C ../tcphook -f GNUmakefile

$(REACTION)/src/libreaction.a:
	$(MAKE) -C $(REACTION)/src -f GNUmakefile

$(RTASL)/Source/librtasl.a:
	$(MAKE) -C $(RTASL)/Source -f GNUmakefile

../wb2cli/wb2cli.o:
	$(CC) $(CFLAGS) -c -o $@ ../wb2cli/wb2cli.c

../sprintf/sprintf.o:
	$(CC) $(CFLAGS) -c -o $@ ../sprintf/sprintf.c

clean:
	rm -f obj/*.o $(PROG) $(PROG)_d
	$(MAKE) -C ../tcphook -f GNUmakefile clean
	$(MAKE) -C $(REACTION)/src -f GNUmakefile clean
	$(MAKE) -C $(RTASL)/Source -f GNUmakefile clean
