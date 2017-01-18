// Pins configuration:
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 3
#define BUTTON_PIN 2

// Constants:
#define MAX 255
#define MIN 1

// Global variables:
volatile boolean changeMode;
volatile boolean buttonPressed;
int mode;
int prev_red;
int prev_green;
int prev_blue;

void setup() {
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonClick, RISING); // allowing interraption by pressing button
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // set starting data
  changeMode = false;
  buttonPressed = false;
  mode = 1;
}
 
 
void loop() {
  switch (mode) {
    case 1:
      program1(12);
      break;
    case 2:
      program2(12);
      break;
    case 3:
      program3(12);
      break;
    case 4:
      program4(12);
      break;
    case 5:
      program5(12);
      break;
    default:
      mode = 1;
      break;
  }

  if (changeMode) {
    mode++;
    changeMode = false;
    blink(mode);
    prev_red = 1;
    prev_green = 1;
    prev_blue = 1;
    buttonPressed = false;
  }
}

void program1(int timeout) {
  growBright(RED_PIN, timeout); // from blue to violet
  fadeBright(BLUE_PIN, timeout); // from violet to red
  growBright(GREEN_PIN, timeout); // from red to yellow
  fadeBright(RED_PIN, timeout); // from yellow to green
  growBright(BLUE_PIN, timeout); // from green to teal
  fadeBright(GREEN_PIN, timeout); // from teal to blue
}

void program2(int timeout) {
  int red = getRandomBright();
  int green = getRandomBright();
  int blue = getRandomBright();
  slideBrights(red, green, blue, timeout);
  interruptibleDelay(timeout, 20);
}

void program3(int timeout) {
  int red = getRandomBright();
  int green = getRandomBright();
  int blue = getRandomBright();
  growBrights(red, green, blue, timeout);
  interruptibleDelay(timeout, 30);
  fadeBrights(red, green, blue, timeout);
  interruptibleDelay(timeout, 30);
}

void program4(int timeout) {
  int red = getRandomBright();
  int green = getRandomBright();
  int blue = getRandomBright();
  setBrights(red, green, blue);
  interruptibleDelay(timeout, 60);
  turnOffBrights();
  interruptibleDelay(timeout, 40);
}

void program5(int timeout) {
  int red = getRandomBright();
  int green = getRandomBright();
  int blue = getRandomBright();
  slideBrights(red, green, blue, timeout);
  interruptibleDelay(timeout, 60);
  slideBrights(0, 0, 0, timeout);
  interruptibleDelay(timeout, 80);
}

void buttonClick() {
  if (!buttonPressed) changeMode = true;
  buttonPressed = true;
}

void blink(int count) {
  turnOffBrights();
  delay(500);
  for(int cycle = 1; cycle < count; cycle ++) {
    setRed(MAX);
    delay(300);
    turnOffBrights();
    delay(300);
  }
}

void growBright(int pin, int timeout) {
  for (int grow = MIN; grow <= MAX; grow++) { 
    if (changeMode) {
      break;
    }
    setBright(pin, grow);
    delay(timeout);
  } 
}

void fadeBright(int pin, int timeout) {
  for (int bright = MAX; bright >= MIN; bright--) { 
    if (changeMode) {
      break;
    }
    setBright(pin, bright);
    delay(timeout);
  } 
}

void slideBrights(int red, int green, int blue, int timeout) {
  for (int slide = 0; slide <= 100; slide++) {
    if (changeMode) {
      break;
    }
    int redStep = map(slide, 0, 100, prev_red, red);
    int greenStep = map(slide, 0, 100, prev_green, green);
    int blueStep = map(slide, 0, 100, prev_blue, blue);
    setRed(redStep);
    setGreen(greenStep);
    setBlue(blueStep);
    delay(timeout);
  }
  prev_red = red;
  prev_green = green;
  prev_blue = blue;
}

void growBrights(int red, int green, int blue, int timeout) {
  for (int grow = MIN; grow <= MAX; grow++) {
    if (changeMode) {
      break;
    }
    int redStep = map(grow, MIN, MAX, MIN, red);
    int greenStep = map(grow, MIN, MAX, MIN, green);
    int blueStep = map(grow, MIN, MAX, MIN, blue);
    setRed(redStep);
    setGreen(greenStep);
    setBlue(blueStep);
    delay(timeout);
  }
}

void fadeBrights(int red, int green, int blue, int timeout) {
  for (int fade = MAX; fade >= MIN; fade--) {
    if (changeMode) {
      break;
    }
    int redStep = map(fade, MIN, MAX, MIN, red);
    int greenStep = map(fade, MIN, MAX, MIN, green);
    int blueStep = map(fade, MIN, MAX, MIN, blue);
    setRed(redStep);
    setGreen(greenStep);
    setBlue(blueStep);
    delay(timeout);
  }
}

void setRed(int bright) {
  setBright(RED_PIN, bright);
}

void setGreen(int bright) {
  setBright(GREEN_PIN, bright);
}

void setBlue(int bright) {
  setBright(BLUE_PIN, bright);
}

void setBright(int pin, int bright) {
  analogWrite(pin, bright);
}

void setBrights(int red, int green, int blue) {
  setRed(red);
  setGreen(green);
  setBlue(blue);
}

void turnOffBrights() {
  setBrights(0, 0, 0);
}

int getRandomBright() {
  int result = random(MIN, MAX);
  return result;
}

void interruptibleDelay(int timeout, int cycles) {
  int x = 0;
  do {
    if (changeMode) {
      break;
    }
    delay(timeout);
    x++;
  } while (x < cycles);
}
