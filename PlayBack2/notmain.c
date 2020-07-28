#include "GlobalVars.h"
#include "RPIHeader.h"
#include "UARTHeader.h"
#include "Pins.h"
#include "BitBangFunctions.c"
#include "InputLoad.c"
#include "GPIOInit.c"
#include "LatchTrains.c"

int notmain(void)
{
	uart_init();
	loadInputs();
	initializeGPIO();		/*Initialize GPIO pins for correct input / output / edge detection. */
	//latchTrainInit();		
	
    while(1)
    {

		//handleLatchTrains();
		if((gpio[GPIO_GPEDS0] & Clk1Bit) == Clk1Bit) {
			if(((C1[inputIndex]<<buttonIndex1)&0x8000) == 0 ) gpio[GPIO_GPSET0] = Data1Bit;	// Extracts relevant bits, and sets Data1 if necessary.
			else gpio[GPIO_GPCLR0] = Data1Bit;
			
			if(((C2[inputIndex]<<buttonIndex1)&0x8000) == 0) gpio[GPIO_GPSET0] = Data2Bit;	//Same as before, with Data 2 line
			else gpio[GPIO_GPCLR0] = Data2Bit;
			buttonIndex1++;																		//Inc. index for the next round through the function
			gpio[GPIO_GPEDS0] = Clk1Bit;
		}
		
		if((gpio[GPIO_GPEDS0] & Clk2Bit) == Clk2Bit) {
			if(((C3[inputIndex]<<buttonIndex2)&0x8000) == 0) gpio[GPIO_GPSET0] = Data3Bit;
			else   gpio[GPIO_GPCLR0] = Data3Bit;
			
			if(((C4[inputIndex]<<buttonIndex2)&0x8000) == 0) gpio[GPIO_GPSET0] = Data4Bit;
			else   gpio[GPIO_GPCLR0] = Data4Bit;
			buttonIndex2++;
			gpio[GPIO_GPEDS0] = Clk2Bit;
		}
		
		if((gpio[GPIO_GPEDS0] & LatchBit) == LatchBit) {
			inputIndex++;							//Next frame
			currentLatchTimer = 0;					//Used for latch trains. Basically starting the timer for the frame.
			stopCounting = 0;						//Allows the function handling the latch trains to resume after a lag frame.
			currentLatchTrain++;					
			
			buttonIndex1 = 0;
			buttonIndex2 = 0;
			
			gpio[GPIO_GPEDS0] = LatchBit;			//Reset the triggered interrupt on the Latch line.
			clk12();

		}
    }
	
	while(1){};
}

// Substantial portions of this code were taken from https://github.com/dwelch67/raspberrypi-zero/blob/master
// As such I am leaving in the copyright and permission notice below:
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.