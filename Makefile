.POSIX:
.SUFFIXES:.lua .luac .ppm

CC=c99
CFLAGS=-c -s -O
LDFLAGS=-s
LDLIBS=-lglfw -lGLESv2 -lopenal -lvorbisfile -llz4

OBJ=src/main.o src/bio.o src/image.o src/renderer.o
DST=sss

LVL=lvl/1
LC=lvl/lvl.luac

all: $(DST) $(LVL)

$(DST): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)

bio.o: bio.h
image.o: bio.h image.h
renderer.o: image.h renderer.h
.c.o:
	$(CC) -o $@ $(CFLAGS) $<

.lua.luac:
	luac5.3 -o $@ $<

$(LVL): $(LC)
.ppm:
	lua5.3 -- $(LC) < $< > $@

clean:
	rm -f $(OBJ) $(LC)

distclean:
	rm -f $(OBJ) $(LC) $(DST) $(LVL)
