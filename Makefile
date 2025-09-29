CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = my3proc
SRC = main3.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
