#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(1);

  pinMode(4,OUTPUT);
  digitalWrite(4,0);
}

void loop() {
  digitalWrite(4,0);
  delay(95);
  while (mySwitch.available()) {

    Serial.print("433MHz: ");
    Serial.println( mySwitch.getReceivedValue() );
    mySwitch.resetAvailable();
  }
  
  digitalWrite(4,1);
  delay(95);
  while (mySwitch.available()) {

    Serial.print("315MHz: ");
    Serial.println( mySwitch.getReceivedValue() );
    mySwitch.resetAvailable();
  }
  
}
