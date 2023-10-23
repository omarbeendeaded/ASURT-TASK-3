#include <SoftwareSerial.h>

#define RX 2
#define TX 3
#define LED 12
#define POT A0

int potReading = 0;
int prevPotReading = 100;
bool LED_ON;

SoftwareSerial mySerial(RX, TX);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    LED_ON = mySerial.read();
    digitalWrite(LED, LED_ON);
  }
 
  potReading = map(analogRead(POT), 0, 1023, 0, 180);

  if (prevPotReading != potReading) {
    mySerial.write(potReading);
    prevPotReading = potReading;
  }
  
}
