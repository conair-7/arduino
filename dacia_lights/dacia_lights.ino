double lights;
double lightsHigh;
double blinker;
double blinkerLR;
double fogLight;
double revLight;

long interval = 500;
long previousMillis = 0;
int ledState = LOW; 
const int SHORT_PRESS_TIME = 500; // 500 milliseconds

int lastStateLH = LOW;  // the previous state from the input pin
unsigned long pressedTimeLH  = 0;
unsigned long releasedTimeLH = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

void loop() {
  lights = pulseIn(A0, HIGH);
  fogLight = pulseIn(A1, HIGH);
  blinker = pulseIn(A2, HIGH);
  blinkerLR = pulseIn(A3, HIGH);
  lightsHigh = pulseIn(A4, HIGH);
  revLight = pulseIn(A5, HIGH);

unsigned long currentMillis = millis();

/*Serial.print(lights);
Serial.print("\t");
Serial.print(fogLight);
Serial.print("\t");
Serial.print(blinker);
Serial.print("\t");
Serial.print(blinkerLR);
Serial.print("\t");
Serial.print(lightsHigh);
Serial.print("\t");
Serial.print(revLight);
Serial.println("");*/

// ŚWIATŁA
if (lights < 1300) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);  
}
else if (lights >= 1300 && lights < 1700) {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
}
else if (lights >= 1700 && lights < 2000) {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}

// AWARYJNE
if (blinker >= 1500) {
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
  }
    digitalWrite(4, ledState);
    digitalWrite(5, ledState);
}
else {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

// KIERUNKOWSKAZY
if (blinkerLR >= 1600) {
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
  }
    digitalWrite(4, ledState);
    digitalWrite(5, LOW);

}
else if (blinkerLR < 1400) {
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
  }
    digitalWrite(4, LOW);
    digitalWrite(5, ledState);
}

// ŚWIATŁA DŁUGIE

if(lastStateLH < 1300 && lightsHigh > 1300) {       // button is pressed
    pressedTimeLH = millis();
    if (lightsHigh > 1300)
        digitalWrite(6, HIGH);
      else
        digitalWrite(6, LOW);
}
else if(lastStateLH > 1300 && lightsHigh < 1300) { // button is released
    releasedTimeLH = millis();

    long pressDurationLH = releasedTimeLH - pressedTimeLH;

    if( pressDurationLH < SHORT_PRESS_TIME ) {
      if (digitalRead(6) == LOW)
        digitalWrite(6, HIGH);
      else
        digitalWrite(6, LOW);
      }
    else
        digitalWrite(6, HIGH);
}

lastStateLH = lightsHigh;
    

// WSTECZNY
if(revLight > 1300)
    digitalWrite(7, HIGH);
else
  digitalWrite(7, LOW);

}
