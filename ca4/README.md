# Introduction
The goals of CA4 are to continue on with the concept of a nuclear reactor that has been explored in previous CA exercises.

# Hardware
* MCU -> atmega328p
* LED -> connected on PB5
* push button -> connected on INT0 (PD2)

# Software
* [usart_atmega](https://github.com/matas-noreika/usart_atmega) -> my personal library developed for developing with usart on avr atmega range
* [freeRTOS](https://www.freertos.org/) -> version used is a ported version for the atmega328p

# Disclaimer
The makefile assumes libs/ to be located above the current project directories. Make also assumes each library directory contains a makefile to generate a static library.
