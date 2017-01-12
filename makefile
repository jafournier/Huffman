DEBUG=yes
CC=g++
LIBRARY=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-W -Wall -ansi -pedantic -g  -I include/ -I/usr/include/python2.7  -lpython2.7 -std=c++11
	LDFLAGS=
else
	CFLAGS=-W -Wall -ansi -pedantic  -I include -I/usr/include/python2.7 -lpython2.7  -std=c++11
	LDFLAGS=
endif
EXEC=exec
LIB=huffman.so
SRC=$(notdir $(wildcard src/*.c))
OBJDIR=obj
OBJ= $(subst PytHuffman.o,,$(SRC:.c=.o))
OBJLIB=  $(subst main.o,,$(SRC:.c=.o))

all: $(EXEC) $(LIB)

ifeq ($(DEBUG),yes)
	echo "debug mode"
else
	echo "release mode"
endif

$(EXEC): $(addprefix $(OBJDIR)/, $(OBJ))
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB): $(addprefix $(OBJDIR)/, $(OBJLIB))
	@echo "in lib"
	@echo $@ $^        
	$(CC) -o lib/$@ $^ -shared $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) -o $@ -c  $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf obj/*.o
	rm lib/huffman.so
	rm exec

mrproper: clean
	rm -rf $(EXEC)
