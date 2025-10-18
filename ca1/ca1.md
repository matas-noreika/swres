# Introduction
The following C application is a frequency calculator using Input Capture on timer 1 of the atmega328p microcontroller. An interrupt service routine is set on the event of an input capture for which it reads the previous input capture value to obtain the period of the square wave input.
# Frequency calculations
The typical calculations for period T and frequency f are given by the following:

```math
T = {1 \over f}; f = {1 \over T}
```

Since our application depends on a system clock and our timer may as well have a clock divisor we need to adjust our expression. It then translates to the following:

```math
T = {tick \over {F_{CPU} \over n}}; f = { {F_{CPU} \over n} \over tick }

Where:

tick = timer tick count,
T = period,
f = frequency,
F_{CPU} = frequency of cpu clock,
n = timer clock division
```

# Design considerations
The clock division has an impact on the lowest possible period which you can measure which in turn affects frequency. If a lower clock division is used the possibility of our interrupt service routine out pacing our CPU frequency could lead to undesired affects.
# Observations
* When running ca1.hex which implements input capture the max out frequency was ~= 2KHz.
* When running ca1_int0.hex which implements int0 the max out frequency was ~= 28kHz.
