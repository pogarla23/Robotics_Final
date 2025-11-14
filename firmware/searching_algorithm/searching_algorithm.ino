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




#include <Servo.h>
#include <Pixy2.h>

// Servos
Servo servoLeft;
Servo servoRight;
Servo servoBack;

// Pixy2
Pixy2 pixy;

// Pin for signal (you had this)
const int SIG_PIN = 7;

// Pixy center (horizontal)
const int CENTER_X = 158;

// Memory / tracking
int lastX = -1;
unsigned long lastSeen = 0;

void setup() {
  Serial.begin(115200);
  pixy.init();

  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);

  servoLeft.attach(12);
  servoRight.attach(13);
  servoBack.attach(11);
}

void loop() {

  // Grab blocks
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks > 0) {
    // *** BALL SEEN ***
    int x = pixy.ccc.blocks[0].m_x;
    lastX = x;
    lastSeen = millis();

    int error = x - CENTER_X;

    if (abs(error) < 20) {
      // centered → move forward
      Serial.println("FORWARD");
      forward(0);
    }
    else if (error > 0) {
      Serial.println("TURN RIGHT");
      rotate_right(0);
    }
    else {
      Serial.println("TURN LEFT");
      rotate_left(0);
    }
  } 
  else {
    // *** BALL NOT SEEN ***
    search();
  }
}

//////////////////////////////////////////////////////
//                SEARCHING ALGORITHM
//////////////////////////////////////////////////////

void search() {
  unsigned long lostTime = millis() - lastSeen;

  if (lostTime < 1200) {
    // Short-term memory search (predict direction)
    if (lastX == -1) {
      spin_search();  // no memory yet, do general scan
      return;
    }

    if (lastX < CENTER_X - 30) {
      Serial.println("SEARCH LEFT (memory)");
      rotate_left(0);
    } 
    else if (lastX > CENTER_X + 30) {
      Serial.println("SEARCH RIGHT (memory)");
      rotate_right(0);
    } 
    else {
      Serial.println("SEARCH FORWARD (memory)");
      forward(0);
    }
  } 
  else {
    // Ball completely lost → wide-area spin search
    Serial.println("SPIN SEARCH");
    spin_search();
  }
}

void spin_search() {
  // Slowly rotate until Pixy sees ball again
  rotate_left(0);
}

//////////////////////////////////////////////////////
//                MOVEMENT FUNCTIONS
//////////////////////////////////////////////////////

void rotate_right(int time){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
}

void rotate_left(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
}

void forward(int time){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  servoBack.writeMicroseconds(1700);
}

void backward(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  servoBack.writeMicroseconds(1300);
}

void stop(int time){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  servoBack.writeMicroseconds(1500);
}




