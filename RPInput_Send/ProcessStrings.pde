String extensions[] = {"_1.txt","_2.txt","_3.txt","_4.txt","_Latches.txt"};

int[][] LoadAndExtractInputs(String Filename) {
  String InputStrings[][] = new String[5][];
  int inputs[][] = new int[5][];
  
  for(int i=0; i<extensions.length;i++){
    InputStrings[i] = loadStrings(Filename + extensions[i]);
  }
  
  for(int i=0; i<inputs.length; i++) {
    if(InputStrings[i] == null) continue;
    inputs[i] = new int[InputStrings[i].length];
    totalInputs += inputs[i].length;
  }
  
  for(int i=0; i<inputs.length; i++) {
    if(inputs[i] == null  || inputs[i].length == 0) continue;
    for(int j=0; j<inputs[i].length; j++) inputs[i][j] = processLine(InputStrings[i][j]);
  }
  return inputs;
}

int processLine(String S) {
  //println(unhex(trim(S.split("x")[1].split(",")[0])));
 return unhex(trim(S.split("x")[1].split(",")[0]));
}
