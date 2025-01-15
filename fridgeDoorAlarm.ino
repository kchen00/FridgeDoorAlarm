const int button = 2;     // Input pin for the button
const int led = 3;        // Output pin for the LED
const int buzzerPin = 4;  // Output pin for the buzzer

unsigned long doorOpenStartTime = 0;      // To track when the doorOpened became HIGH
const unsigned long openDuration = 120000;  // 2 minutes in milliseconds
bool isTimerRunning = false;              // Flag to track if the timer is running

void setup() {
  pinMode(button, INPUT_PULLUP);  // Set button pin as input with pull-up
  pinMode(led, OUTPUT);           // Set LED pin as output
  pinMode(buzzerPin, OUTPUT);     // Set buzzer pin as output
  reset();                        // Initialize outputs
}

void loop() {
  int doorOpened = digitalRead(button);  // Read the button state

  // by default INPUT_PULLUP is high, so if the button is not pressed, the pin is in high
  if (doorOpened == HIGH) {  // Door is opened
    if (!isTimerRunning) {
      doorOpenStartTime = millis();  // Start the timer
      isTimerRunning = true;
    }

    // Check if the door has been opened for 2 minutes
    if (millis() - doorOpenStartTime >= openDuration) {
      alertUser();
    }
  } else {                   // Door is closed or not HIGH
    isTimerRunning = false;  // Reset the timer
    doorOpenStartTime = 0;   // Clear the start time
    reset();
  }
}

void alertUser() {
  // alert user by blink led and making sound with buzzer
  digitalWrite(led, HIGH);    // Turn the LED on
  tone(buzzerPin, 120, 500);  // Activate the buzzer
  delay(120);                 // Wait for 120 ms
  reset();                    // Reset LED and buzzer after delay
  delay(120);                 // wait for 120ms
}

void reset() {
  digitalWrite(led, LOW);     // Turn the LED off
  noTone(buzzerPin);          // Turn the buzzer off
}
