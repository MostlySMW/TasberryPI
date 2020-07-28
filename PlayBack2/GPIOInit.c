void initializeGPIO() {
	int outputPins[] = {DataPin1,DataPin2,DataPin3, DataPin4};
	
	gpio = (unsigned long*)GPIO_BASE;

	for(int i=0; i<4; i++) {
		gpio[GPIO_GPFSEL0] |=(((outputPins[i]/10) == 0) << (outputPins[i]%10)*3);	//Set pins declared in outputPins as outputs.
		gpio[GPIO_GPFSEL1] |=(((outputPins[i]/10) == 1) << (outputPins[i]%10)*3);
		gpio[GPIO_GPFSEL2] |=(((outputPins[i]/10) == 2) << (outputPins[i]%10)*3);
	}

	/* Rising Edge detection for Latch line. Also rising Edge for CLK lines 1&2, a hacky way to get more time to output data*/
	gpio[GPIO_GPAREN0]   = LatchBit | Clk1Bit | Clk2Bit;
	//gpio[GPIO_GPAFEN0]   = (1 << Clk1Bit) | (1 << Clk2Bit);						/* OLD - Falling edge detection for CLK lines 1&2. This is the appropriate way to do it. */
}