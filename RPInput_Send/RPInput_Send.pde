// Example by Tom Igoe  
import processing.serial.*; 
volatile Serial myPort;    // The serial port
int inputArr[][];
float progress = 0;
int totalInputs;
void setup() {
  size(400, 200);
  inputArr = LoadAndExtractInputs("Inputs");
  //printArray(Serial.list());                           //Uncomment to see a list of all COMs
  myPort = new Serial(this, Serial.list()[2], 1008064); 
  thread("sendAllData");
  background(255,0,0);
} 

void draw() { 
  background(255,0,0);
  fill(0,255,0);
  rect(0,0,width*progress,height);
} 

void keyPressed() {
  myPort.write(1);    //Inform the system it can start playback.
  exit();
}
