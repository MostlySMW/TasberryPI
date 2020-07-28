# TasberryPI
Using various revisions of the raspberry pi as a replay device for SNES/NES TASes
Compile using [this](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) toolchain

Steps for playback:
  1.) Set up pins in pins.h to match the pins you are using in your setup. The pins numbering is using the BCM numbering, NOT the physical or wiringpi numbering scheme. Use [this](https://pinout.xyz/#) diagram to help find your pins.
  2.) Compile
  3.) Add kernal.img onto sd card along with bootcode.bin and start.elf.
  4.) insert into the pi.
  
  On the computer side:
    1.) Run RPInput_send, with the files Input_1.txt/Input_2.txt/Input_3.txt/Input_4.txt/Input_Latches.txt in the same folder.(If you only have a 1-controller TAS with no latchTrain    file, only include Input_1.txt)
    2.) Run the program, plug in the PI, and wait until the loading is complete.
    3.) When the loading is done, hold reset on the snes, press any key (program will let the pi know it can start), and release reset. The pi should begin playback.
