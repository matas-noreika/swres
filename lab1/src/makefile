#C compiler
CC= avr-gcc

MMCU= atmega328p

#C Compiler flags
CFLAGS= -O2 -mmcu=$(MMCU)
CPPFLAGS=-I../include -I../lib/usartLib/include
LDFLAGS=-Wl,-u,vfprintf -lm -lprintf_flt
TARGETS=lab1.hex
BUILDTARGETS=$(addprefix $(LOCALBIN)/, $(TARGETS))
PORT=
HEXFILE=

LOCALBIN= ../bin
LOCALOBJ= ../obj
LOCALDEP= ../dep

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
DEPS=$(SRCS:%.c=%.d)
LDOBJS=$(addprefix $(LOCALOBJ)/, $(OBJS))
LIBS=../lib/usartLib/lib/usart.o

.PHONY: all clean
.PRECIOUS:$(LOCALDEP)/%.d $(LOCALOBJ)/%.o

all:$(BUILDTARGETS)


clean:
	@-rm -f $(LOCALBIN)/*.exe 2> /dev/null
	@-rm -f $(LOCALBIN)/*.hex 2> /dev/null
	@-rm -f $(LOCALOBJ)/*.o 2> /dev/null
	@-rm -f $(LOCALDEP)/*.d 2> /dev/null

-include $(DEPS)

#static pattern rule to generate object file from 
$(LOCALOBJ)/%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@
	mv $(LOCALOBJ)/$(*F).d $(LOCALDEP)/$(*F).d

#static pattern rule to generate executable files from object files
$(LOCALBIN)/%.exe:$(LOCALOBJ)/%.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LIBS) $< -o $@

#static pattern rule to convert exe to hex file
$(LOCALBIN)/%.hex:$(LOCALBIN)/%.exe
	avr-objcopy -O ihex $< $@

