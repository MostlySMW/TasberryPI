long inputIndex = -1;			//Index into input array.
unsigned char buttonIndex1 = 0;					//Port 1 Controller Index (0-15)
unsigned char buttonIndex2 = 0;					//Port 2 Controller Index (0-15)

int latchTrainsIndex = 0;		//Index into latch train array	
long currentLatchTimer = 0;		//Simple timer to check if a lag frame has occured. Incremented each time through main()
int currentLatchTrain = 0;		//Counter for current latch train
int stopCounting = 1;			//Stops trains from being checked until playback has actually started

/* const int C1[] = { 
	#include "Inputs.txt"		// Port 1, Controller 1 Inputs
};

const int C2[] = {
	#include "Inputs1.txt"		// Port 1, Controller 2 Inputs
};

const int C3[] = {
	#include "Inputs2.txt"		// Port 2, Controller 1 Inputs	
};

const int C4[] = {
	#include "Inputs3.txt"		// Port 2, Controller 2 Inputs
};

const int LatchTrains[] = {
	#include "Latches.txt"
}; */

unsigned int *C1, *C2, *C3, *C4, *LatchTrains;