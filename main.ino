String inputString = "";  // A string to hold incoming data
bool inputComplete = false;  // Whether the string is complete

void setup() {
  // Initialize Serial (PC communication) at 9600 baud rate
  Serial.begin(9600);

  // Initialize Serial2 (communication with Arduino Mega) at 115200 baud rate
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // RX2 (GPIO16), TX2 (GPIO17)

  // Reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // If a complete input string has been received from the Serial Monitor:
  if (inputComplete) {
    // Convert the string to an integer
    int numberToSend = inputString.toInt();
    
    // Send the number to the Arduino Mega
    Serial2.println(numberToSend);
    
    // Print the sent number to the Serial Monitor for debugging
    Serial.println("Sent: " + String(numberToSend));
    
    // Clear the string and reset the flag
    inputString = "";
    inputComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // Get the new byte:
    char inChar = (char)Serial.read();
    // Add it to the inputString:
    inputString += inChar;
    // If the incoming character is a newline, set the flag:
    if (inChar == '\n') {
      inputComplete = true;
    }
  }
}
