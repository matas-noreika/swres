#C Compiler
CC=avr-gcc
#Target microcontroller unit
MMCU=atmega328p
#C Compiler Flags
CCFLAGS=-O2 -D F_CPU=1000000UL -mmcu=$(MMCU) $(INC_DIRS)
#Include directories
INC_DIRS=-I../lib/usart_atmega/include -I../lib/rtos/freeRTOS -ffunction-sections
#C Linker Flags
CLFLAGS=-lusart_atmega -lfreeRTOS -Wl,--gc-sections
CLFLAGS += -L../lib/usart_atmega/obj -L../lib/rtos/freeRTOS

#retrieve all source files from src directory
SRCS=$(wildcard ./src/*.c)
OBJS=$(SRCS:./src/%.c=./obj/%.o)
EXES=$(SRCS:./src/%.c=./bin/%.exe)
HEXS=$(EXES:%.exe=%.hex)

.PHONY: all clean

#general rule to build target files
all: clean makeLibs $(HEXS)

#creates static libraries to link
makeLibs:
	make -C ../lib/usart_atmega
	make -C ../lib/rtos/freeRTOS


clean:
	@rm -f bin/* 2> /dev/null
	@rm -f obj/* 2> /dev/null
	make -C ../lib/rtos/freeRTOS clean
	make -C ../lib/usart_atmega clean

./obj/%.o: ./src/%.c
	$(CC) -o $@ $(CCFLAGS) $< -c

./bin/%.exe: ./obj/%.o
	$(CC) -o $@ $(CCFLAGS) $< $(CLFLAGS)

./bin/%.hex: ./bin/%.exe
	avr-objcopy -O ihex $< $@

