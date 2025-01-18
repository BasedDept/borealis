.POSIX:

.PRECIOUS:
.SUFFIXES: .c .h .S .s .o

LIBA= libcrypto.a
LIBSO= libcrypto.so
OBJS= api.o siphash/siphash24.o siphash/siphash48.o siphash/siphashx24.o siphash/siphashx48.o chacha/chacha20.o chacha/chacha20ietf.o chacha/xchacha20.o

CFLAGS= $(CFLAGS_GLOBAL) -std=c17 -Wall -I"$(PROJECTDIR)/head" -ffreestanding -fpic
LDFLAGS= $(LDFLAGS_GLOBAL) -nostdlib -z relro -z now

all: $(LIBA) $(LIBSO)

clean:
	-rm -r $(OBJS) $(LIBA) $(LIBSO)

api.o: api.c
siphash/siphash24.o: siphash/siphash24.c
siphash/siphash48.o: siphash/siphash48.c
siphash/siphashx24.o: siphash/siphashx24.c
siphash/siphashx48.o: siphash/siphashx48.c
chacha/chacha20.o: chacha/chacha20.c
chacha/chacha20ietf.o: chacha/chacha20ietf.c
chacha/xchacha20.o: chacha/xchacha20.c

$(LIBA): $(OBJS)
	$(AR) -c -r -s $(LIBA) $(OBJS)

$(LIBSO): $(OBJS)
	$(LD) $(LDFLAGS) -shared -o $(LIBSO) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -c $< -o $@
