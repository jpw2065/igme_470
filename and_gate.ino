/*
  AND Gate

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.




  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.




  created 2022
  by Jack Watson
*/

// The two input pins going into the arduino.
const int switchPinOne = 2;
const int switchPinTwo = 3;

// The two output pins going out of the arduino.
const int transistorPinOne = 13;
const int transistorPinTwo = 12;


void setup() {
  // Init the pins switch pins as INPUT.
  pinMode(switchPinOne, INPUT);
  pinMode(switchPinTwo, INPUT);

  // Init the transistor pins as OUTPUT
  pinMode(transistorPinOne, OUTPUT);
  pinMode(transistorPinTwo, OUTPUT);
}

void loop() {

  /**
   * Pipe the input pins directly into the output pins.\
   * This ofloads the logical functionality to that of the circuit. If we were to program
   * this functionality on the arduino itself you would see an if statement here.
   */
  digitalWrite(transistorPinOne, digitalRead(switchPinOne));
  digitalWrite(transistorPinTwo, digitalRead(switchPinTwo));
}
