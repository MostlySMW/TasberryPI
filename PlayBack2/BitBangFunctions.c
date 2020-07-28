/* This was my attempt at cleaning up the code by segmenting it into functions. Turns out the simple function calls kill the already tight window 
   to respond to the latch/clock lines.*/
   
void clk12() {				//Function used by the Latch segment to preemptively load the data lines with first clock pulse data. Could also just call checkClk1/checkClk2, but merging them into one function means less function calls.
	
	if(((C1[inputIndex]<<buttonIndex1)&0x8000) == 0 ) gpio[GPIO_GPSET0] = Data1Bit;	// Extracts relevant bits, and sets Data1 if necessary.
	else gpio[GPIO_GPCLR0] = Data1Bit;
	if(((C2[inputIndex]<<buttonIndex1)&0x8000) == 0) gpio[GPIO_GPSET0] = Data2Bit;	//Same as before, with Data 2 line
	else gpio[GPIO_GPCLR0] = Data2Bit;
	buttonIndex1++;																		//Inc. index for the next round through the function
	gpio[GPIO_GPEDS0] = Clk1Bit;
	
	if(((C3[inputIndex]<<buttonIndex2)&0x8000) == 0) gpio[GPIO_GPSET0] = Data3Bit;
	else   gpio[GPIO_GPCLR0] = Data3Bit;
	if(((C4[inputIndex]<<buttonIndex2)&0x8000) == 0) gpio[GPIO_GPSET0] = Data4Bit;
	else   gpio[GPIO_GPCLR0] = Data4Bit;
	buttonIndex2++;
	gpio[GPIO_GPEDS0] = Clk2Bit;
}

void checkClk1() {			//Name might be bad, this function is called once a rising edge on clk1 is detected. It does not check on its own, only handles the data1/2 lines.
	if(buttonIndex1 > 15) gpio[GPIO_GPCLR0] = Data1Bit | Data2Bit; 	// Sets data 1/2 if the clock pulsed more than 16 times. Maybe unnecessary, but is part of the protocol so I added it.
	
	else {	
		if((((C1[inputIndex]>>(15-buttonIndex1))&1) == 0)) gpio[GPIO_GPSET0] = Data1Bit;	// Extracts relevant bits, and sets Data1 if necessary.
		else gpio[GPIO_GPCLR0] = Data1Bit;
	
		if((((C2[inputIndex]>>(15-buttonIndex1))&1) == 0)) gpio[GPIO_GPSET0] = Data2Bit;	//Same as before, with Data 2 line
		else gpio[GPIO_GPCLR0] = Data2Bit;
		buttonIndex1++;																		//Inc. index for the next round through the function
	}
	gpio[GPIO_GPEDS0] = Clk1Bit;															//Clear the CLK1 interrupt.
}

void checkClk2() {														//Same as checkClk1, just for the 2nd controller port lines.
	if(buttonIndex2 > 15) gpio[GPIO_GPCLR0] = Data3Bit | Data4Bit;
	
	else {
		if((((C3[inputIndex]>>(15-buttonIndex2))&1) == 0)) gpio[GPIO_GPSET0] = Data3Bit;
		else   gpio[GPIO_GPCLR0] = Data3Bit;
	
		if((((C4[inputIndex]>>(15-buttonIndex2))&1) == 0)) gpio[GPIO_GPSET0] = Data4Bit;
		else   gpio[GPIO_GPCLR0] = Data4Bit;
		buttonIndex2++;
	}
	gpio[GPIO_GPEDS0] = Clk2Bit;
}

void checkLatch() {			//Same bad naming scheme, this function does not check on its own, but is called once a rising edge has ALREADY HAPPENED.	
		inputIndex++;							//Next frame
		currentLatchTimer = 0;					//Used for latch trains. Basically starting the timer for the frame.
		stopCounting = 0;						//Allows the function handling the latch trains to resume after a lag frame.
		currentLatchTrain++;					
		
		buttonIndex1 = 0;
		buttonIndex2 = 0;
		
		gpio[GPIO_GPEDS0] = LatchBit;			//Reset the triggered interrupt on the Latch line.
		
		checkClk1();							//Handle clocks 1/2 one edge ahead of time. Hacky way of getting a bit more time to output data.
		checkClk2();
}

void handleActiveLines() {
	/*Fastest way I could think to do this without involving loops. May not be the best.
	  Any of the lines with multiple checks may rarely or never be activated, but I thought 
	  it was best to include all the possibilities in the chance it happens*/
	switch(gpio[GPIO_GPEDS0] & (Clk1Bit | Clk2Bit | LatchBit)) 	{
		case 0x00:
			break;								//Do Nothing
		case Clk1Bit:							//CLK1
				checkClk1();
				break;
		case Clk2Bit:							//CLK2
				checkClk2();
				break;
		case Clk1Bit | Clk2Bit:					//CLK 1&2		Clock lines are the most time sensetive so those are checked first. 
				checkClk1();
				checkClk2();
				break;			
		case LatchBit: 							//Latch			
				checkLatch();
				break;
		case Clk1Bit | LatchBit:				//CLK1 & Latch
				checkLatch();
				checkClk1();
				break;
		case Clk2Bit | LatchBit:				//CLK2 & Latch
				checkLatch();
				checkClk2();
				break;
		case Clk1Bit | Clk2Bit | LatchBit:		//CLK 1&2 & Latch
				checkLatch();
				checkClk1();
				checkClk2();
				break;
	}
}