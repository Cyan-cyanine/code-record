src=$(wildcard *.c)
obj=$(patsubst %.c,%,$(src))

ALL:$(obj)
$(obj):%:%.c
	gcc $< -o $@

clean:
	-rm -rf $(obj)

.PHONY:ALL clean