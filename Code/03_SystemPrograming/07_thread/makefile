SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%,$(SRC))

ALL:$(OBJ)
%:%.c
	$(CC) $< -o $@

clean:
	$(RM) $(OBJ)

.PHONEY: ALL clean
