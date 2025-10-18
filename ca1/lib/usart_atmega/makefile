#C compiler
CC= avr-gcc
#Target microcontroller (default to atmega328p)
MMCU= atmega328p
#build Target of makefile (static library)
TARGET=$(LOCALOBJ)/libusart_atmega.a
#C compiler flags
CCFLAGS= -O2 -mmcu=$(MMCU) -I./include
#Linker Dependency Flags
LDFLAGS= -L$(LOCALOBJ) -lusart_atmega

#local directories
LOCALBIN=./bin
LOCALOBJ=./obj
LOCALDEP=./dep
LOCALSRC=./src
LOCALTESTS=./tests

#retrieve all source files
SRCS=$(wildcard $(LOCALSRC)/*.c)
TESTSRCS=$(wildcard $(LOCALTESTS)/*.c)
OBJS=$(SRCS:$(LOCALSRC)/%.c=$(LOCALOBJ)/%.o)
DEPS=$(SRCS:$(LOCALSRC)/%.c=%.d)
EXES=$(TESTSRCS:$(LOCALTESTS)/%.c=$(LOCALBIN)/%.exe)
ELFS=$(EXES:%.exe=%.elf)

#declare all and clean
.PHONY: all clean

all: $(TARGET) tests

clean:
	@echo "Running clean"
	-@rm -f $(LOCALBIN)/*.exe 2> /dev/null
	-@rm -f $(LOCALBIN)/*.elf 2> /dev/null
	-@rm -f $(LOCALOBJ)/*.o 2> /dev/null
	-@rm -f $(LOCALDEP)/*.d 2> /dev/null
	-@rm -f $(LOCALOBJ)/*.a 2> /dev/null

#generates test elf's from tests
tests: $(ELFS)

#include .d file rules
-include $(DEPS)

#static pattern rule to generate object files
$(LOCALOBJ)/%.o: $(LOCALSRC)/%.c
	$(CC) $(CCFLAGS) -c -MMD $< -o $@
	mv $(LOCALOBJ)/$(*F).d $(LOCALDEP)

#static pattern rule to generate exe from test source files
$(EXES): $(LOCALBIN)/%.exe: $(LOCALTESTS)/%.c
	$(CC) $(CCFLAGS) $< $(LDFLAGS) -o $@

#static pattern to generate elf files from exe
$(ELFS): $(LOCALBIN)/%.elf: $(LOCALBIN)/%.exe
	avr-objcopy -O ihex $< $@

#rule to generate static library from object files
$(TARGET): $(OBJS)
	ar rcs $@ $<
