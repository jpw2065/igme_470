/*
  AND Gate

  Turns on the LED when both of the switches writing data into the program are on.

  The circuit:
  - 2 swtiches connected to D2, and D3
  - 2 output pins D12, D13 connected to a 10k Ohm resistor which connects to the base leg of the transistor.

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
