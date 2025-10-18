#C compiler
CC= avr-gcc
#Target microcontroller
MMCU= atmega328p
#C compiler flags
CCFLAGS= -O2 -mmcu=$(MMCU) -I../include

#local directories
LOCALBIN=../bin
LOCALOBJ=../obj
LOCALDEP=../dep

#retrieve all source files
SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=$(LOCALOBJ)/%.o)
DEPS=$(SRCS:%.c=%.d)
EXES=$(SRCS:%.c=$(LOCALBIN)/%.exe)
ELFS=$(SRCS:%.c=$(LOCALBIN)/%.elf)

#declare all and clean
.PHONY: all clean buildlib

#retain all object files generated
.PRECIOUS: $(LOCALBIN)/%.elf $(LOCALBIN)/%.exe 

all: $(ELFS)

clean:
	@echo "Running clean"
	-@rm -f $(LOCALBIN)/*.exe 2> /dev/null
	-@rm -f $(LOCALOBJ)/*.o 2> /dev/null
	-@rm -f $(LOCALDEP)/*.d 2> /dev/null
	-@rm -f $(LOCALBIN)/*.elf 2> /dev/null

#include .d file rules
-include $(DEPS)

#builds required libraries
buildlib:
	$(MAKE) -C ../src

#static pattern rule to generate object files
$(OBJS): $(LOCALOBJ)/%.o: %.c
	$(CC) $(CCFLAGS) -c -MMD $< -o $@
	mv $(LOCALOBJ)/$(*F).d $(LOCALDEP)/$(*F).d

#static pattern rule to generate exe files
$(EXES): $(LOCALBIN)/%.exe: $(LOCALOBJ)/%.o buildlib
	$(CC) $(CCFLAGS) $< $(LOCALOBJ)/usart.o -o $@

#static pattern rule to generate elf files
$(ELFS): $(LOCALBIN)/%.elf: $(LOCALBIN)/%.exe
	avr-objcopy $< -O ihex $@
