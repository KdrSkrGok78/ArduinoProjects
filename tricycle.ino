#include <Servo.h>
#include <SoftwareSerial.h>
char state;
int speed = 255;
const int pinTwo = 6;  // in3(ileri glb)
const int pinOne = 5; // in1
Servo frontServo;
SoftwareSerial BTSerial(2,3);

void setup() {
  frontServo.attach(9);  // Servo PWM pin 10
  frontServo.write(90);   // Başlangıçta tekerleği düz konuma getir
  pinMode(pinTwo, OUTPUT);
  pinMode(pinOne, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600); 
}

void loop() {
    if (BTSerial.available() > 0) {
    state = BTSerial.read();
    Serial.print("Received from BT: "); // Kontrol için Serial Monitor'e yaz
    Serial.println(state);
  }
  
  switch(state) {
    case 'F': // İleri
      frontServo.write(90);
      analogWrite(pinTwo, 150);
      analogWrite(pinOne, 0);
      break;
      
    case 'G': // İleri sol
      frontServo.write(45); 
      analogWrite(pinTwo, 150); 
      analogWrite(pinOne, 0);
      break;
      
    case 'I': // İleri sağ
      frontServo.write(135); 
      analogWrite(pinTwo, 150);  
      analogWrite(pinOne, 0);
      break;
      
    case 'B': // Geri
      frontServo.write(90);
      analogWrite(pinOne, 150);
      analogWrite(pinTwo, 0);
      break;
      
    case 'H': // Geri sol
      frontServo.write(45);  
      analogWrite(pinOne, 150); 
      analogWrite(pinTwo, 0);
      break;
      
    case 'J': // Geri sağ
      frontServo.write(135); 
      analogWrite(pinOne, 150); 
      analogWrite(pinTwo, 0);
      break;
      
    case 'S': // Dur
      frontServo.write(90);
      analogWrite(pinTwo, 0);
      analogWrite(pinOne, 0);
      break;
  }
}
