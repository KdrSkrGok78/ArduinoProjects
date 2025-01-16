#include <Servo.h>
#include <SoftwareSerial.h>
char state; //araca gelecek komutlar bu değişkene atanacak
int speed = 255; //motorların maks hızı olacak şekilde ayalarlandı 0-255 arası değerler verilebilir.
const int pinTwo = 6;  // in3 (output 1-2 için In1-3 ; output 3-4 için In2-4)
const int pinOne = 5; // in1
Servo frontServo; //servo motoru tanımladık
SoftwareSerial BTSerial(2,3); // 2-> RX , 3->TX ; arduinoya ters bağlanacak

void setup() {
  frontServo.attach(9);  // Servo PWM pin 9
  frontServo.write(90);   // Başlangıçta tekerleği düz konuma getir
  pinMode(pinTwo, OUTPUT);
  pinMode(pinOne, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);// BT modülü HC-06 9600 baud rate kabul ediyor bu yüzden bu hız seçildi
}

void loop() {
    if (BTSerial.available() > 0) {
    state = BTSerial.read();//alınan komutu yaz
    Serial.print("Received from BT: "); 
    Serial.println(state);// Kontrol için Serial Monitor'e yaz
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
