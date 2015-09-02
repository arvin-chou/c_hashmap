vpath %.h ./
vpath %.c ./
TARGET := hashmap

all: $(TARGET)

objects := $(patsubst %.c,%.o,$(wildcard *.c))
#$(objects): %.o: %.c
#	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: $(TARGET)
$(TARGET): $(objects)
	$(CC) -o $@ $(objects)

test:
	@echo test

.PHONY: clean
clean:
	-rm $(TARGET) *.o

