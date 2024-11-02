void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for the serial connection to be established
  }
  
  String data = "{1256,432,1256,432,410,1278,1256,432,1256,432,412,1276,410,1278,412,1278,1256,432,410,1278,412,1278,410,8034,1256,432,1254,434,410,1278,1256,432,1254,434,408,1278,410,1278,412,1276,1256,432,412,1278,410,1278,410,8012,1278,432,1256,434,410,1276,1254,434,1254,434,412,1276,412,1276,410,1278,1256,432,410,1278,412,1278,410,8034,1256,432,1256,432,410,1278,1256,432,1258,432,412,1276,412,1276,412,1278,1254,434,408,1280}";

  // Remove the curly braces from the string
  data = data.substring(1, data.length() - 1);
  // Split the string by comma and space

  
  int values[512]; // Assuming a maximum of 100 elements
    for (int i = 0; i < 512; i++) {
    values[i] = 0;
  }
  int count = 0;

  
  int index = 0;
  while (index < data.length()) {
    int commaIndex = data.indexOf(',', index);
    if (commaIndex == -1) {
      commaIndex = data.length();
    }
    String token = data.substring(index, commaIndex);
    int value = token.toInt();
    
    values[count] = value;
    count++;

    index = commaIndex + 1;
  }
  
Serial.println();
  // Display the new array
  for (int i = 0; i < 512; i++) {
    Serial.print(values[i]);
    Serial.print(",");
  }
  
 Serial.println();
Serial.print("the index is");
Serial.println(index);
 Serial.println();
Serial.print("the count is");
Serial.println(count);

}

void loop() {
  // Your code here
}
