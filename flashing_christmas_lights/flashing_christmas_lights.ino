#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define BUTTON 2

int r, g, b;
int fadeSpeed;
int mode;
int maxMode = 3;
volatile boolean changeMode;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonClick, RISING);
  
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  fadeSpeed = 10;
  changeMode = false;
  mode = 1;
}
 
 
void loop() {
  Serial.print("current mode ");
  Serial.println(mode);
  if (mode == 1) {
    fadeSpeed = 10;
    program1();
  }
  else if (mode == 2) {
    fadeSpeed = 4;
    program1();
  }
  else if (mode == 3) {
    program2();
  }
  else {
    mode = 1;
  }
  if (changeMode) {
    mode++;
    changeMode = false;
    Serial.print("-- switch mode to ");
    Serial.println(mode);
    analogWrite(REDPIN, 256);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 0);
    delay(1000);
    analogWrite(REDPIN, 0);
    analogWrite(BLUEPIN, 0);
    analogWrite(GREENPIN, 0);
  }
}

void buttonClick() {
  changeMode = true;
}

void program1() {
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    if (changeMode) {
      break;
    }
    analogWrite(REDPIN, r);
    delay(fadeSpeed);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    if (changeMode) {
      break;
    }
    analogWrite(BLUEPIN, b);
    delay(fadeSpeed);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    if (changeMode) {
      break;
    }
    analogWrite(GREENPIN, g);
    delay(fadeSpeed);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    if (changeMode) {
      break;
    }
    analogWrite(REDPIN, r);
    delay(fadeSpeed);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    if (changeMode) {
      break;
    }
    analogWrite(BLUEPIN, b);
    delay(fadeSpeed);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    if (changeMode) {
      break;
    }
    analogWrite(GREENPIN, g);
    delay(fadeSpeed);
  } 
}

void program2() {
  int color1 = random(257);
  Serial.print("\t1->");
  Serial.print(color1);
  int color2 = random(257);
  Serial.print("\t2->");
  Serial.println(color2);
  int color3 = random(257);
  Serial.print("\t3->");
  Serial.println(color3);
  for (int grow = 0; grow < 256; grow++) {
    if (changeMode) {
      break;
    }
    int current1 = map(grow, 0, color1, 0, 256);
    Serial.print("\t\t1->");
    Serial.println(current1);
    int current2 = map(grow, 0, color2, 0, 256);
    Serial.print("\t\t2->");
    Serial.println(current2);
    int current3 = map(grow, 0, color3, 0, 256);
    Serial.print("\t\t3->");
    Serial.println(current3);
    analogWrite(REDPIN, current1);
    analogWrite(BLUEPIN, current2);
    analogWrite(GREENPIN, current3);
    delay(10);
  }
}

