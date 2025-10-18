#C Compiler
CC= avr-gcc
MMCU= atmega328p
#C Compiler flags
CCFLAGS= -mmcu=$(MMCU) -O2 -I./include $(LIBDINCS)
#Linker Dependency flags
LDFLAGS= $(LDDIRS) $(LDLIBS)

#Local Directories
LOCALSRC=./src
LOCALOBJ=./obj
LOCALDEP=./dep
LOCALLIB=./lib
LOCALBIN=./bin

#Retrieve build targets
SRCS=$(wildcard $(LOCALSRC)/*.c)
OBJS=$(SRCS:$(LOCALSRC)/%.c=$(LOCALOBJ)/%.o)
DEPS=$(SRCS:$(LOCALSRC)/%.c=$(LOCALDEP)/%.d)
EXES=$(SRCS:$(LOCALSRC)/%.c=$(LOCALBIN)/%.exe)
ELFS=$(SRCS:$(LOCALSRC)/%.c=$(LOCALBIN)/%.elf)

LIBDIRS=$(wildcard $(LOCALLIB)/*)
LDDIRS=$(LIBDIRS:%=-L%/obj)
LIBDINCS=$(LIBDIRS:%=-I%/include)
LIBS=$(LIBDIRS:$(LOCALLIB)/%=%)
LDLIBS=$(LIBS:%=-l%)

.PHONY: all clean buildLibs

all: buildLibs $(ELFS)

clean:
	-@rm -f $(LOCALBIN)/*.exe 2> /dev/null
	-@rm -f $(LOCALBIN)/*.elf 2> /dev/null
	-@rm -f $(LOCALDEP)/*.d 2> /dev/null
	-@rm -f $(LOCALOBJ)/*.o 2> /dev/null

buildLibs:
	for lib in $(LIBDIRS); do \
		$(MAKE) -C$$lib; \
	done;

#static pattern rule to generate object files from source files
$(LOCALOBJ)/%.o: $(LOCALSRC)/%.c
	$(CC) $(CCFLAGS) -c -MMD $< -o $@
	mv $(LOCALOBJ)/$(*F).d $(LOCALDEP)

#static pattern rule to generate executable files from object file
$(LOCALBIN)/%.exe: $(LOCALOBJ)/%.o
	$(CC) $(CCFLAGS) $< $(LDFLAGS) -o $@

#static pattern rule to generate elf files from executable file
$(LOCALBIN)/%.elf: $(LOCALBIN)/%.exe
	avr-objcopy -O ihex $< $@

