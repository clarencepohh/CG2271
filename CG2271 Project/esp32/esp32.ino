#include "BluetoothSerial.h"

#define RXD2 16
#define TXD2 17
BluetoothSerial SerialBT;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  SerialBT.begin("zeus ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialBT.available()) {
    int command = SerialBT.read();
    Serial.print("i got: ");
    Serial.println(command);
    Serial2.write(command);
  }
}
