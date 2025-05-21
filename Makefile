CC = gcc -g -fno-stack-protector -Wwrite-strings
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -static

TARGET = simulation

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o