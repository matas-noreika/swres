# Introduction
The goal of the CA is to showcase the race condition using a debugger. In this CA we are using an AVR Dragon In-Circuit debugger to step through the program.
# Possible issues
It was found that avr-gdb tool does not re-flash program removing software breakpoints from flash memory. It is suggested to re-flash the application between debugging sessions.
