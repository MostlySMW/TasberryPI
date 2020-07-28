void sendAllData() {
  while(myPort.available() == 0);
  sendSettings();
  sendArrLengths();
  sendInputs();
}

void sendSettings() {
  int settings = 0;
  for (int i=0; i<inputArr.length; i++) {
    if (inputArr[i] != null) settings |= (1<<i);
  }
  myPort.write(settings);
}

void sendArrLengths() {
  for (int i=0; i<inputArr.length; i++) {
    if (inputArr[i] == null) continue;
    for (int j=0; j<4; j++) {
      myPort.write(((inputArr[i].length>>(j*8))&0xFF));
    }
  }
}

int currentNumInputs;
void sendInputs() {
  for (int i=0; i<inputArr.length; i++) {
    if (inputArr[i] == null) continue;
    for (int j = 0; j < inputArr[i].length; j++) {

      myPort.write(inputArr[i][j]&0xFF);
      myPort.write(inputArr[i][j]>>8);
      currentNumInputs++;
      progress = (float)currentNumInputs/totalInputs;
    }
  }
}
