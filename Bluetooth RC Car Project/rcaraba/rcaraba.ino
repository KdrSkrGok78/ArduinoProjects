  #include "NewPing.h" // Ultrasonik sensör için gerekli kütüphane
  const int motorA2  = 11;  // L298N'in IN1 Girişi
  const int motorB1  = 9; // L298N'in IN2 Girişi
  const int motorA1  = 12;  // L298N'in IN3 Girişi
  const int motorB2  = 10;  // L298N'in IN4 Girişi
  const int echoPin = 5; // Ultrasonik sensörün echo pin girişi
  const int trigPin = 6; // Ultrasonik sensörün trigger pin girişi
  int i=0; //Döngüler için atanan rastgele bir değişken
  int j=0; //Döngüler için atanan rastgele bir değişken
  int state; //Bluetooth cihazından gelecek sinyalin değişkeni
  int vSpeed=255;     // Standart Hız, 0-255 arası bir değer alabilir
  NewPing sonar(trigPin, echoPin, 200);
  float duration , distance ;
void setup() {
    // Pinlerimizi belirleyelim
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);   
    pinMode(echoPin,INPUT);
    pinMode(trigPin,OUTPUT); 
    // 9600 baud hızında bir seri port açalım
    Serial.begin(9600);
}
 
void loop() {
 
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
    //Mesafe sensöründen gelen mesafe değerini distance adlı mesafe değişkenine atadık "geri yönünde" belli mesafeye ulaşınca
    //aracın geriye gitmesini önleyecek dahili park sensörü yapmış olduk tek kodda kütüphaneyi kurmadan çalışmayacaktır.
     distance = sonar.ping_cm();
     
  //Gelen veri 'F' ise araba ileri gider.
    if (state == 'F') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
    }
  //Gelen veri 'G' ise araba ileri sol(çapraz) gider.
    else if (state == 'G') {
      analogWrite(motorA1,vSpeed ); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);    analogWrite(motorB2, 0); 
    }
  //Gelen veri 'I' ise araba ileri sağ(çapraz) gider.
    else if (state == 'I') {
        analogWrite(motorA1, 100); analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);      analogWrite(motorB2, 0); 
    }
  //Gelen veri 'B' ise araba geri gider.
    else if (state == 'B' && distance > 20) {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, vSpeed); 
    }
  //Gelen veri 'H' ise araba geri sol(çapraz) gider
    else if (state == 'H' && distance > 20) {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); analogWrite(motorB2, vSpeed); 
    }
  //Gelen veri 'J' ise araba geri sağ(çapraz) gider
    else if (state == 'J' && distance > 20) {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 100); 
    }
  //Gelen veri 'L' ise araba sola gider.
    else if (state == 'L') {
      analogWrite(motorA1, vSpeed);   analogWrite(motorA2, 150); 
        analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
    }
  //Gelen veri 'R' ise araba sağa gider
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, vSpeed);   analogWrite(motorB2, 150);     
    }
  
  //Gelen veri 'S' ise arabayı durdur.
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }  
}
