//searching algorithm

#include <Servo.h>
#include <Pixy2.h>

Servo servoLeft;
Servo servoRight;
Servo servoBack;
Pixy2 pixy; 

const int SIG_PIN = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  servoLeft.attach(12);
  servoRight.attach(13);
  servoBack.attach(11);
  //leds?
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(SIG_PIN, OUTPUT);
}

void search(){
  //

}

void clockwise_circle(int time){
   for (int i = 0; i < 5; i++){
        rotate_right(2000);
    }
}

void counter_clockwise_circle(int time){
  for (int i = 0; i < 5; i++){
      rotate_left(2000);
  }
}

void rotate_right(int time){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
}
void rotate_left(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
}
void forward(int time ){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  servoBack.writeMicroseconds(1700); // idk??
  
}
void backward(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  servoBack.writeMicroseconds(1300);  //idk
}
void stop(int time){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  servoBack.writeMicroseconds(1500);
}






