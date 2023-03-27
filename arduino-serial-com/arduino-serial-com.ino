/*
Peripherals:
 - Potentiometer
 - Push-button switch
 - Buzzer
*/

const int POTEN_PIN = A5;
const int BTN_A_PIN = 2;
const int BTN_B_PIN = 3;
const int PIEZO_BUZZ_PIN = 6;

bool btnStateA = false;
bool previousStateA = false;

bool btnStateB = false;
bool previousStateB = false;

int potentiometerValue = 0;
int previousPotenValue = potentiometerValue;
int threshold = 5;


void setup() {
  pinMode(POTEN_PIN, INPUT);
  pinMode(BTN_A_PIN, INPUT);
  pinMode(BTN_B_PIN, INPUT);
  pinMode(PIEZO_BUZZ_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    receivingData();
  } else {
    sendingData();
  }
  delay(10);
}

void sendingData() {

  potentiometerValue = analogRead(POTEN_PIN);
  btnStateA = digitalRead(BTN_A_PIN);
  btnStateB = digitalRead(BTN_B_PIN);

  //if (previousPotenValue != potentiometerValue) {
  if (potentiometerValue > previousPotenValue + threshold || potentiometerValue < previousPotenValue - threshold) {
    sendSerialMessage('O', 'O', potentiometerValue);
    previousPotenValue = potentiometerValue;
  }

  if (btnStateA && !previousStateA) {  //Pressed!
    sendSerialMessage('W', '0', potentiometerValue);
    tone(PIEZO_BUZZ_PIN, 800);
    delay(50);
    noTone(PIEZO_BUZZ_PIN);
    previousStateA = true;
  } else if (!btnStateA && previousStateA) {  //Released!
    sendSerialMessage('O', 'O', potentiometerValue);
    previousStateA = false;
  }

  if (btnStateB && !previousStateB) {  //Pressed!
    sendSerialMessage('O', 'S', potentiometerValue);
    tone(PIEZO_BUZZ_PIN, 800);
    delay(50);
    noTone(PIEZO_BUZZ_PIN);
    previousStateB = true;
  } else if (!btnStateB && previousStateB) {  //Released!
    sendSerialMessage('O', 'O', potentiometerValue);
    previousStateB = false;
  }

  delay(100);
}


void receivingData() {

  char inByte = Serial.read();

  switch (inByte) {
    case 'P':
      tone(PIEZO_BUZZ_PIN, 500);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 1500);
      delay(400);
      noTone(PIEZO_BUZZ_PIN);
      break;
    case 'N':
      tone(PIEZO_BUZZ_PIN, 300);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 250);
      delay(200);
      noTone(PIEZO_BUZZ_PIN);
      break;
    case 'I':
      tone(PIEZO_BUZZ_PIN, 440);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 494);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 523);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 587);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 659);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 698);
      delay(100);
      tone(PIEZO_BUZZ_PIN, 784);
      delay(100);
      noTone(PIEZO_BUZZ_PIN);
      break;
  }
  Serial.flush();
}

void sendSerialMessage(char keyA, char keyB, int potenValue) {
  Serial.print(keyA);
  Serial.print(' ');
  Serial.print(keyB);
  Serial.print(' ');
  Serial.print(potenValue);
  Serial.print(' ');
  Serial.println();
}