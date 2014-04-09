// Actuators
const int redLED = 9;
const int yellowLED = 10;
const int greenLED = 11;

// Sensors
const int cds = A0;
const int tact = 7;

const int interval = 30000;
const int mode = 3;

int currentLED = redLED;
int sensorValue = 0;
int outputValue = 0;

unsigned long curTimer;
unsigned long prevTimer = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);     
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);   
//  pinMode(cds, INPUT);
//  pinMode(tact, INPUT);
  
  turnLightWithSignal(currentLED);
}

// the loop routine runs over and over again forever:
void loop() {      
  switch (mode) {
    case 0: 
      trafficLight();
      break;
    case 1:
      greenLight();
      break;
    case 2:
      moodLight();
      break;
    case 3:
      emergencyLight();
      break;
    default:
      break;
  }
}

void emergencyLight() {
  int time = 100;
  
  for ( int i = 0; i < 10; i++ ) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(time);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    delay(time);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    delay(time);
  }
  
  for ( int j = 0; j < 10; j++ ) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(time);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(time);
  }
}

void moodLight() {
  for ( int i = 0; i < 255; i++ ) {
    analogWrite(redLED, i);
    analogWrite(yellowLED, i);
    analogWrite(greenLED, i);
    delay(10);
  }
  
  for ( int j = 255; j > 0; j-- ) {
    analogWrite(redLED, j);
    analogWrite(yellowLED, j);    
    analogWrite(greenLED, j);
    delay(10);
  }
}

void trafficLight() {
  digitalWrite(redLED, HIGH);
  
  curTimer = millis();
  unsigned long difference = (unsigned long)(curTimer - prevTimer);

  if ( difference >= interval || digitalRead(tact) == HIGH ) {
    greenSignal();
  }
}

void turnLightWithSignal (int currentLED) { 
  switch ( currentLED ) {
    case redLED: 
      analogWrite(redLED, outputValue);
      analogWrite(yellowLED, 0);
      analogWrite(greenLED, 0);
      break;
    case yellowLED:
      analogWrite(redLED, 0);
      analogWrite(yellowLED, outputValue);
      analogWrite(greenLED, 0);
      break;
    case greenLED:
      analogWrite(redLED, 0);
      analogWrite(yellowLED, 0);
      analogWrite(greenLED, outputValue);
      break;
    default:
      break;    
  }
}

void greenLight() {
  if ( digitalRead(tact) == HIGH ) {
    switch (currentLED) {
      case redLED: 
        currentLED++;
        break; 
      case yellowLED:
        currentLED++;
        break;
      case greenLED:
        currentLED = redLED;
        break;
      default:
        currentLED++;
        break;
    }
   
    turnLightWithSignal(currentLED);
    delay(200);
  }
  
  sensorValue = analogRead(cds);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(outputValue);
  turnLightWithSignal(currentLED);
}

void greenSignal() {  
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, LOW);
  delay(1000);
  
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  delay(5000);
  
  for ( int i = 0; i < 5; i++ ) {
    digitalWrite(greenLED, LOW);
    delay(750);
    digitalWrite(greenLED, HIGH);
    delay(750);
  }
  
  digitalWrite(greenLED, LOW);
  prevTimer = millis();
}
