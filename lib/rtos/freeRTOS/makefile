
SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)

all: makeLib

makeLib: $(OBJS)
	ar rcs libfreeRTOS.a $(OBJS)

clean:
	rm -f *.o 2> /dev/null
	rm -f *.exe 2> /dev/null
	rm -f *.hex 2> /dev/null
	rm -f *.a 2> /dev/null

%.o: %.c
	avr-gcc -mmcu=atmega328p -O2 -D F_CPU=1000000UL -ffunction-sections -Wl,--gc-sections -c $< -o $@
