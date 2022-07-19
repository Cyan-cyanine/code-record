CFLAGS = -g -Wall
SRC = $(wildcard *.c)
TAR = $(patsubst %.c,%,$(SRC))

ALL:
$(TAR):%:%.c
	$(CC) $(CFLAGS) $< -o $@

clean: 
	$(RM) $(TAR)

.PHONY:ALL clean
