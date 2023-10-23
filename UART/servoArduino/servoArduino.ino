#include <SoftwareSerial.h>
#include <Servo.h>

#define RX 2
#define TX 3
#define BUTTON 5
#define SERVO 9

Servo myservo;
int position = 0;
bool prevState = false;
bool state = true;

SoftwareSerial mySerial(RX, TX);

void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO);
  pinMode(BUTTON, INPUT_PULLUP);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    position = mySerial.read();
  }

  myservo.write(position);


  state = digitalRead(BUTTON);

  if (state != prevState) {
    mySerial.write(!state);
    prevState = state;
  }
}
