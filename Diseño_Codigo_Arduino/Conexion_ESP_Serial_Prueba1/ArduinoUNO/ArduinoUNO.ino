#include <SoftwareSerial.h>
SoftwareSerial s(A2,A3);

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  s.println("Begin");
}

void loop() {
  if(Serial.available())
  {
    char val = Serial.read();
    /*
    Serial.print("Received: ");
    Serial.println(val);
    */
    s.print("Received: ");
    s.println(val);
    if (val == '0')
    {
      digitalWrite(A0, LOW);
    }
    if (val == '1')
    {
      digitalWrite(A0, HIGH);
    }
  }
}
