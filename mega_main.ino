#define relay_count 16
#define relay_1 47
#define relay_2 46
#define relay_3 45
#define relay_4 44
#define relay_5 43
#define relay_6 42
#define relay_7 41
#define relay_8 40
// -------------
#define relay_9 39
#define relay_10 38
#define relay_11 37
#define relay_12 36
#define relay_13 35
#define relay_14 34
#define relay_15 33
#define relay_16 32

int recived_relay_num = 0;
char msg[8] = "Iam Mega";

int relay[relay_count] = { relay_1, relay_2, relay_3, relay_4,
                           relay_5, relay_6, relay_7, relay_8,
                           relay_9, relay_10, relay_11, relay_12,
                           relay_13, relay_14, relay_15, relay_16 };

// Structure to hold the state of each relay
struct RelayState {
  int pin;
  unsigned long startTime;
  int duration;
  bool isOn;
};

RelayState relayStates[relay_count];

void setup() {
  for (int i = 0; i < relay_count; i++) {
    pinMode(relay[i], OUTPUT);
    digitalWrite(relay[i], HIGH);
    relayStates[i] = {relay[i], 0, 0, false};
  }

  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop() {
  // Check if there is any data available on Serial1
  if (Serial1.available()) {
    // Read the incoming data
    int receivedNumber = Serial1.parseInt();
    if (receivedNumber > 0 && receivedNumber <= relay_count) {
      // Call the function with the received number
      turn_on_for_period(relay[receivedNumber - 1], 2000); // Adjusted for zero-based indexing

      // Print the received number to the Serial Monitor for debugging
      Serial.println("Received: " + String(receivedNumber));
    }
  }

  // Update the state of the relays
  unsigned long currentMillis = millis();
  for (int i = 0; i < relay_count; i++) {
    if (relayStates[i].isOn && (currentMillis - relayStates[i].startTime >= relayStates[i].duration)) {
      digitalWrite(relayStates[i].pin, HIGH);
      relayStates[i].isOn = false;
      Serial.println("Relay " + String(i + 1) + " turned off"); // i + 1 for 1-based indexing in output
    }
  }
}

void turn_on_for_period(int pin, int ddelay) {
  for (int i = 0; i < relay_count; i++) {
    if (relayStates[i].pin == pin) {
      digitalWrite(pin, LOW);
      relayStates[i].startTime = millis();
      relayStates[i].duration = ddelay;
      relayStates[i].isOn = true;
      Serial.println("Relay " + String(i + 1) + " turned on for " + String(ddelay) + " ms");
      break;
    }
  }
}
