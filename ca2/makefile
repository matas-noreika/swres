#C Compiler
CC= avr-gcc
#target microcontroller
MMCU= atmega328p
#C Compiler Flags
CCFLAGS= -mmcu=$(MMCU) -O2 -I./include

#Local directories
LOCALBIN=./bin
LOCALOBJ=./obj
LOCALSRC=./src

#target Files
SRCS=$(wildcard $(SRCS)/*.c)
OBJS=$(SRCS:$(LOCALSRC)/%.c=$(LOCALOBJ)/%.o)
EXES=$(SRCS:$(LOCALSRC)/%.c=$(LOCALBIN)/%.exe)
HEXS=$(EXES:%.exe=%.hex)

.PHONY: all clean

all: $(LOCALBIN)/ca2.hex

clean:
	-@rm -f $(LOCALBIN)/*.exe 2> /dev/null
	-@rm -f $(LOCALBIN)/*.hex 2> /dev/null
	-@rm -f $(LOCALOBJ)/*.o 2> /dev/null

# .c -> .o
$(LOCALOBJ)/%.o: $(LOCALSRC)/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

# .o -> .exe
$(LOCALBIN)/%.exe: $(LOCALOBJ)/%.o
	$(CC) $(CCFLAGS) $< -o $@

# .exe -> .hex
$(LOCALBIN)/%.hex: $(LOCALBIN)/%.exe
	avr-objcopy -O ihex $< $@
