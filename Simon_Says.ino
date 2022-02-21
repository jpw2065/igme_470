
/**
 * Simon Says
 * 
 * A simon says game played out on the arduino using multiple different input/output pins. The game will play until the player looses a turn.
 * 
 * @author Jack Watson <jpw2065@g.rit.edu>
 * @date 2-21-2022
 */

// Led pins should be ordered from left to right from the players view
int ledPins[4] = {2, 3, 4, 5};
int buttonSensor = A7;

// Game memory declarations.
enum State { STARTING, SIMON_SAYS, RESPONSE, LOST};

unsigned char simonSays[256];
unsigned char roundInput[256];
unsigned int roundNumber;
unsigned int guessNumber;

State gameState;

/**
 * Setup the game 
 */
void setup() {
  // Set the pin states
  for(int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buttonSensor, INPUT);

  gameState = STARTING;  
}

/**
 * Loop through the game state.
 */
void loop() {
  
  // Use a State Machine to dictate the state of the game.
  switch(gameState) {
     case STARTING:
        initialize();
        displayStartingSequence();
        gameState = SIMON_SAYS;
      break;
     case SIMON_SAYS:
        newRound();
        displaySimonSaysSequence();
        gameState = RESPONSE;
      break;
     case RESPONSE:
        if(userIsPressingButton()) {
          makeGuess();
          displayUserInput();
          gameState = endCondition();
          delay(1000);
        }
      break;
     case LOST:
     default:
      displayEndingSequence();
      gameState = STARTING;
      break;
  }
}


/**
 * ---- Game Logic ----
 */

/**
 * Initialize the initial game state.
 */
void initialize() {
  roundNumber = 0;
  guessNumber = 0;
}
 
/**
 * Move to the next round in the game
 */
void newRound() {  
  roundNumber++;
  guessNumber = 0;
}

/**
 * Determine the end condition for the game.
 */
State endCondition() {
  for(int i = 0; i < guessNumber; i++) {
    if(simonSays[i] != roundInput[i]) {
      return LOST;
    }
  }
  if(guessNumber == roundNumber) {
    return SIMON_SAYS;
  }
  return RESPONSE;
}

/**
 * Make a guess against simon
 */
int makeGuess() {
    int button = determineUserInput();
    roundInput[guessNumber] = button;
    guessNumber++;
    return button;
}

/**
 * ---- Input Logic ----
 */

/**
 * Determine the user input bassed on the analog signal.
 * 
 * @param int The analog signal we are reading in from the sensor.
 * 
 * We will need some sort of debounce right here.
 */
int determineUserInput() {
  delay(10); // Delay to get a more accurate guess.
  int analogSignal = getAnalogInput();
  if( analogSignal > 1000){ return 0; }
  if( analogSignal > 700){ return 1; }
  if( analogSignal > 500){ return 2; }
  return 3;
}

/**
 * Determine if the user is pressing a button.
 * 
 * @param int The analog signal we are reading in from the sensor.
 */
bool userIsPressingButton() {
  return getAnalogInput() > 300;
}

/**
 * 
 * Get the analog data coming into the arduino
 * 
 * @param int Read from the pin that loads in data.
 */
int getAnalogInput() {
  return analogRead(buttonSensor);
}

/**
 * --- Presentation Logic ---
 */

/**
 * Display the starting sequence of the data.
 */
void displayStartingSequence() {
  for(int i = 0; i < 8; i++) {
    // This equation allows us to count backwards once we hit 4 (prevents two loops - totally unecessary)
    digitalWrite(ledPins[(i / 4) * 7 + i * (1 - (i / 4) * 2)], HIGH);
    delay(1000);
    setStateOnAllLeds(LOW);
  }
}

/**
 * Write out the ending sequence to the data line.
 */
void displayEndingSequence() {
  for(int i = 0; i < 4; i++) {
    setStateOnAllLeds(HIGH);
    delay(500);
    setStateOnAllLeds(LOW);
    delay(500);
  }  
}

/**
 * Write out the simon says sequence to the corresponding LEDs
 * 
 * @todo Move the RNG out of here. I am mixing game logic and output (presentation) code.
 */
void displaySimonSaysSequence() {
  simonSays[roundNumber - 1] = random(0, 4);
  for(int i = 0; i < roundNumber; i++) {
     int pinOut = ledPins[simonSays[i]];
     digitalWrite(pinOut, HIGH);
     delay(500); 
     digitalWrite(pinOut, LOW);
     delay(500);
  }
}

/**
 * Write out the user input to the correct LED.
 */
void displayUserInput() {
  int lastButtonInput = roundInput[guessNumber - 1];
  digitalWrite(ledPins[lastButtonInput], HIGH);
  delay(500);
  digitalWrite(ledPins[lastButtonInput], LOW);
}

/**
 * Utility function to write the state on all of the LEDs
 * 
 * @param state The voltage you want to write out to the LEDs.
 */
void setStateOnAllLeds(int state) {
  for(int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], state);
  }
}
