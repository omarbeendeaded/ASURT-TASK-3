#include <SPI.h>
#include <mcp2515.h>

#define POT A0
#define LED 12

struct can_frame msgT;
struct can_frame msgR;
MCP2515 mcp2515(10);

int potReading = 0;
int prevPotReading = 100;
bool LED_ON;

void setup() {
  // Initialize frame ID and Size
  msgT.can_id = 0x01;
  msgT.can_dlc = 1;

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mcp2515.readMessage(&msgR) == MCP2515::ERROR_OK) {
    LED_ON = msgR.data[0];
    digitalWrite(LED, LED_ON);
  }
 
  potReading = map(analogRead(POT), 0, 1023, 0, 180);

  if (prevPotReading != potReading) {
    msgT.data[0] = potReading;
    mcp2515.sendMessage(&msgT);
    prevPotReading = potReading;
  }
  
}
