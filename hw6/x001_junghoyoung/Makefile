TARGET=test

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
%.o: %.c
	$(CC) -c $<
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
clean:
	rm -rf *.o test.exe
