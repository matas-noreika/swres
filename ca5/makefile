#C Compiler
CC=avr-gcc
#Target MCU
MMCU=atmega328p
#CPU Frequency
F_CPU=1000000UL
#C Compiler Flags
CCFLAGS=-mmcu=$(MMCU) -O2 -DF_CPU=$(F_CPU) $(INC_DIR_PATHS)
#C Linker Flags
CLFLAGS=-ffunction-sections -Wl,--gc-sections $(L_LIB_PATHS) $(L_LIBS)

#Paths to header files to include
INC_DIR_PATHS=-I../lib/usart_atmega/include/ -I../lib/rtos/freeRTOS/

#Paths to library directories
LIB_DIR_PATHS=../lib/rtos/freeRTOS/ ../lib/usart_atmega/
#Linker lib directories paths
L_LIB_PATHS=-L../lib/rtos/freeRTOS/ -L../lib/usart_atmega/obj/
#libraries to link with linker
L_LIBS=-lfreeRTOS -lusart_atmega

#retrieve all source files
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)
ELFS=$(SRCS:src/%.c=bin/%.elf)
HEXS=$(ELFS:%.elf=%.hex)

.PHONY: all clean

all: clean makeLibs $(HEXS)

clean:
	for lib in $(LIB_DIR_PATHS); do \
		$(MAKE) -C $$lib clean; \
	done
	-rm -f bin/* 2> /dev/null
	-rm -f obj/* 2> /dev/null

makeLibs: $(LIB_DIR_PATHS)
	for lib in $(LIB_DIR_PATHS); do \
		$(MAKE) -C $$lib; \
	done

obj/%.o: src/%.c
	$(CC) $(CCFLAGS) -c $< $(CLFLAGS) -o $@

bin/%.elf: obj/%.o
	$(CC) $(CCFLAGS) $< $(CLFLAGS) -o $@

bin/%.hex: bin/%.elf
	avr-objcopy -O ihex $< $@
