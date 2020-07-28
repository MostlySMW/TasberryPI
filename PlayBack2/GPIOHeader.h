#define LatchPin 6			//You can change any of the pins here to match the pins you have connected on the rpi
#define Clk1Pin 5
#define Clk2Pin 12		
#define DataPin1 13
#define DataPin2 19		
#define DataPin3 16		
#define DataPin4 20

#define LatchBit (1 << LatchPin)
#define Clk1Bit (1 << Clk1Pin)
#define Clk2Bit (1 << Clk2Pin)
#define Data1Bit (1 << DataPin1)
#define Data2Bit (1 << DataPin2)
#define Data3Bit (1 << DataPin3)
#define Data4Bit (1 << DataPin4)
