SRC = $(wildcard *.c)
TAR = $(patsubst %.c,%,$(SRC))
RM = rm -rf
CC = arm-linux-gcc

ALL:$(TAR)

$(TAR):$(SRC)
	$(CC) $< -o $@

clean:
	-$(RM) $(TAR)

.PHONY :clean ALL