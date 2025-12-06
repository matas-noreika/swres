# Introduction
The aim of the lab is to implement the challenge exercise found at [introduction to rtos](https://www.youtube.com/watch?v=pHJ3lxOoWeI&list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz&index=8&t=588s) at the end of the video.
# Software overview
The software is composed of two tasks A & B.

Task A is acting as a serial interface to the program. Its role is to echo back any strings/characters written by the user. If delay xxx is written the task will communicate the xxx time to task B. xxx is given in miliseconds.

Task B is tasked with controlling the frequency of the blink speed. It will await information from task A to give the target period per blink. Once the LED has blinked a total of 100 times it will write to task A indicating 100 blinks occurred.

<div align="center">

![CA5 software overview](./docs/ca5.png)

</div>

# GCC linker optimisations used
-ffunction-sections
-fdata-sections
Place each function or data item into its own section in the output file if the target supports arbitrary sections. The name of the function or the name of the data item determines the section’s name in the output file.

Use these options on systems where the linker can perform optimizations to improve locality of reference in the instruction space. Most systems using the ELF object format have linkers with such optimizations. On AIX, the linker rearranges sections (CSECTs) based on the call graph. The performance impact varies.

Together with a linker garbage collection (linker --gc-sections option) these options may lead to smaller statically-linked executables (after stripping).

On ELF/DWARF systems these options do not degenerate the quality of the debug information. There could be issues with other object files/debug info formats.

Only use these options when there are significant benefits from doing so. When you specify these options, the assembler and linker create larger object and executable files and are also slower. These options affect code generation. They prevent optimizations by the compiler and assembler using relative locations inside a translation unit since the locations are unknown until link time. An example of such an optimization is relaxing calls to short call instructions.
