#include <Ultrasonic.h>

// Mótor A
int pwmA = 3;
int Ai1 = 5;
int Ai2 = 4;

// Mótor B
int pwmB = 6;
int Bi1 = 7;
int Bi2 = 8;

unsigned long lastLightSwap = millis();
bool isRed = false;

Ultrasonic ultrasonic(12, 13);

void setup() {
 Serial.begin(9600);
  
  // Mótor pinnar
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(Ai1, OUTPUT);
  pinMode(Ai2, OUTPUT);
  pinMode(Bi1, OUTPUT);
  pinMode(Bi2, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);


  randomSeed(analogRead(0));

}

void loop() {
  int dist = ultrasonic.read();
  Serial.println();

  if(dist > 50){
    afram(127);

    blikk();
  }else{
    stoppa();
    delay(200);
    if (random(2) == 0){
      right(90);
    }else{
      left(90);
    }
  }
}


void afram(int hradi) {
  // Set Motor A forward
  digitalWrite(Ai1, HIGH);
  digitalWrite(Bi1, LOW);

  // Set Motor B forward
  digitalWrite(Ai2, LOW);
  digitalWrite(Bi2, HIGH);

  // Set the motor speeds
  analogWrite(pwmA, hradi);
  analogWrite(pwmB, hradi);

}

void stoppa() {
    digitalWrite(Ai1, LOW);
    digitalWrite(Ai2, LOW);

    digitalWrite(Bi1, LOW);
    digitalWrite(Bi2, LOW);

    analogWrite(pwmA, 0);
    analogWrite(pwmB, 0);
}

void bakka(int hradi) { 
    digitalWrite(Ai1, LOW);
    digitalWrite(Bi1, HIGH);

    digitalWrite(Ai2, HIGH);
    digitalWrite(Bi2, LOW);

    analogWrite(pwmA, hradi);
    analogWrite(pwmB, hradi);
}

void right(int deg) {
    digitalWrite(Ai1, LOW);
    digitalWrite(Ai2, HIGH);

    digitalWrite(Bi1, LOW);
    digitalWrite(Bi2, HIGH);

    analogWrite(pwmB, 100);
    analogWrite(pwmA, 100);

    delay(deg * 6.666);

    stoppa();
}

void left(int deg) {
    digitalWrite(Ai1, HIGH);
    digitalWrite(Ai2, LOW);

    digitalWrite(Bi1, HIGH);
    digitalWrite(Bi2, LOW);

    analogWrite(pwmB, 100);
    analogWrite(pwmA, 100);

    delay(deg * 6.666);

    stoppa();
}

void blikk(){
  if(lastLightSwap+500
   < millis()){
    isRed = !isRed;
    lastLightSwap = millis();
  }

  if(isRed){
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }else{
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
}