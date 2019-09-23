# Compsys303 Assignment 2
This assignment involves designing a pacemaker controller on a Altera(DE2-115) FPGA 
with two modes. 

## Run instructions
* Connect FPGA to PC using blaster and UART via RS232 cable
* Open Quartus Prime Programmer and click on Add File to add the cs303.sof for programming the nios processor
* Open nios2 build tools for eclipse. Click on File -> New -> Nios II application for BSP and from Template. Select nios2_system.sopcinfo, 
  select cpu, name project and select Hello World from template.
* Add a new C source and header file in Nios II.
* Copy-paste the code from paceMaker.c into hello_world.c and rename the file to paceMaker.c
* Change Makefile C_SRC hello_world.c to paceMaker.c
* Follow above steps for pacemakerFSM.h and pacemakerFSM.c(No changes to be made for pacemake.FSM.h in makeFile)

Alternatively one can:
* In project explorer, right click -> import -> Nios II Software Build Tools Project -> Import Nios II Software Build Tools Project
  Choose Assignment1, tick on clean project when importing and repeat process for Assignment1_bsp

## Note
include <fcnt1.h>. Statement for mode2 exists in paceMaker.c. 

### Mode 1(SW0 is low)
Buttons 0 and 1 are used to provide VSense and ASense signals. If a VSense or ASense is not provided within the timing constraints,
the pacemaker provides a VPace or APace. Green Led 0 and 1 turn high for VPace and APace respectively.

### Mode 2(SW0 is high)
Run pacemaker.exe to open virtual heart. One can test pacemaker against three diseases.

