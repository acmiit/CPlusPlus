OUT:=main
SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
CC:=gcc
$(OUT):$(OBJS)
	$(CC) $^ -o $@
%.o:%.c 
	$(CC) -c $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) &(OBJS) %(OUT)
rebuild:clean main