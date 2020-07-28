unsigned long getUART32() {		//Read UART 4 times and return 32bit long. Little Endian
	unsigned long returnedLong = 0;
	for(int i=0; i<4; i++) {
		returnedLong |= (uart_recv()&0xFF)<<(i*8);
	}
	return returnedLong;
}

unsigned int getUART16() {		//Read UART 2 times and return 16 bit int. Little Endian
	unsigned int returnedInt = 0;
	for(int i=0; i<2; i++) {
		returnedInt |= (uart_getHex()&0xFF)<<(i*8);
	}
	return returnedInt;
} 

void unpackSettings(unsigned int settings, unsigned int *unpacked) {	//Unpacks 1 byte received from UART into an array of the settings
	for(int i=0; i<5; i++) unpacked[i] = (settings>>i)&1;
}

void handleArrLengths(unsigned int *enabledSettings, unsigned long *arrLengths) {	//Receives 32 bit number representing the length of the arrays for each of the enabled settings.
	for(int i=0; i<5; i++) {
	if(enabledSettings[i] == 0) continue;
		arrLengths[i] = getUART32();
	}
	/* this is wonky but since we are doing baremetal, it works. The toolchain had no "malloc" function to reserve space for the input arrays,
	   so we can make do by just writing to unused ram, far enough away from the program memory. It will stay there, untouched, since there is no
	   os that can mess it up or do garbage collection of some kind.*/
	C1 = (unsigned int*)0x9000;
	C2 = (unsigned int*)(C1+arrLengths[0]*2) + 1;
	C3 = (unsigned int*)(C2+arrLengths[1]*2) + 1;
	C4 = (unsigned int*)(C3+arrLengths[2]*2) + 1;
	LatchTrains = (unsigned int*)(C4+arrLengths[3]*2)+1;
}

void handleInputLoad(unsigned int *Settings, unsigned long* Lengths) {	//Fills input arrays according to the active settings 1 16bit int at a time.
	unsigned int* DataArrays[] = {C1,C2,C3,C4,LatchTrains};
	for(int i=0; i<5; i++) {
		if(Settings[i] == 0) continue;
		unsigned int* activeArr = DataArrays[i];
		for(unsigned long j=0; j<Lengths[i]; j++) {
			activeArr[j] = getUART16();
		}
	}
}

void loadInputs() {								//Manager for the above functions.
	unsigned int enabledSettings[5];
	unsigned long arrLengths[5];
	uart_send(1);									//Notifies the other system that it is ready to receive settings/lengths/inputs.
	unpackSettings(uart_recv(), enabledSettings);
	handleArrLengths(enabledSettings, arrLengths);
	handleInputLoad(enabledSettings, arrLengths);
	uart_recv();
	
	PUT32(AUX_ENABLES,0);					//Disable interrupts that are no longer needed.
	PUT32(AUX_MU_CNTL_REG,0);
}