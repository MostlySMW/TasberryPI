void latchTrainInit() {
	latchTrainsIndex = 0;
	currentLatchTimer = 0;
	stopCounting = 1;
	currentLatchTrain = 0;
}

void handleLatchTrains() {
 		currentLatchTimer++;
		if(currentLatchTimer > 45000 && !stopCounting) {				//45000 "Magic Number* was found be seeing the average number of times the currentLatchTimer was incremented in main.
			int diff = LatchTrains[latchTrainsIndex] - currentLatchTrain;
			inputIndex += diff;
			latchTrainsIndex++;
			currentLatchTrain = 0;
			stopCounting = 1;
		} 
}