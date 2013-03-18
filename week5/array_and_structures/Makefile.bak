TARGET = test
CC=gcc
HEADERS = def.h sparse_matrix_types.h
INCLUDES = -I.
CFLAGS = -Wall -g
SRCS = array.c matrix.c sparse_matrix_template.c \
array_and_structures_main.c matrix_template.c sparse_matrix_test.c \
array_template.c matrix_test.c structures.c \
array_test.c sparse_matrix.c structures_template.c


OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADERS) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS)
clean:
	rm -rf *.o $@ 
