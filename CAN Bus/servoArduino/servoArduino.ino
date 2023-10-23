#include <SPI.h>
#include <mcp2515.h>
#include <Servo.h>

#define BUTTON 5
#define SERVO 9

struct can_frame msgT;
struct can_frame msgR;
MCP2515 mcp2515(10);

Servo myservo;
int position = 0;

bool prevState = false;
bool state = false;


void setup() {
  // Initialize frame ID and Size
  msgT.can_id = 0x00;
  msgT.can_dlc = 1;

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  myservo.attach(SERVO);
  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (mcp2515.readMessage(&msgR) == MCP2515::ERROR_OK) {
    position = msgR.data[0];
    myservo.write(position);
  }

  state = digitalRead(BUTTON);

  if (state != prevState) {
    msgT.data[0] = !state;
    mcp2515.sendMessage(&msgT);
    prevState = state;
  }
}
