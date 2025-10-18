# Introduction
The following C application is a frequency calculator using Input Capture on timer 1 of the atmega328p microcontroller. An interrupt service routine is set on the event of an input capture for which it reads the previous input capture value to obtain the period of the square wave input.
# Frequency calculations
The typical calculations for period T and frequency f are given by the following:

```math
T = {1 \over f} = f = {1 \over T}
```

Since our application depends on a system clock and our timer may as well have a clock divisor we need to adjust our expression. It then translates to the following:

```math
T = {1 \over {n \bullet F_{CPU}}}
```
