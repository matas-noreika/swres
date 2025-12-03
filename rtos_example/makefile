#C Compiler
CC=avr-gcc

#Target Microcontroller
MMCU=atmega328p

#Target build source
TARGET=

#Debug flag
DEBUG=

#C Compiler Flags
CCFLAGS=-I./include -O2 -mmcu=$(MMCU)

#Local directories
LOCALSRC=./src
LOCALBIN=./bin
LOCALOBJ=./obj

#Lib management (assumes a file structure with lib folder contain folders with lib_name/obj/lib_name.a and a makefile to generate the lib_name.a)

#All source file and output references
SRCS:=$(wildcard $(LOCALSRC)/*.c)
OBJS:=$(SRCS:$(LOCALSRC)/%.c=$(LOCALOBJ)/%.o)
EXES:=$(SRCS:$(LOCALSRC)/%.c=$(LOCALBIN)/%.exe)
HEXS:=$(EXES:%.exe=%.hex)

#Generic default all rule to describe options
all:
	@echo "Available options:"
	@echo "clean - cleans all build files"
	@echo "build - generate target and test programs"

#Generic clean rule to remove all build files
clean:
	-@rm -f $(LOCALOBJ)/*.o 2> /dev/null
	-@rm -f $(LOCALBIN)/*.exe 2> /dev/null
	-@rm -f $(LOCALBIN)/*.hex 2> /dev/null

#Generic build rule to make all files including tests if applicable
build:


