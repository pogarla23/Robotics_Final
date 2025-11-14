#include <Pixy2.h>
Pixy2 pixy;


// LED for right servo monito
const int FRAME_X_MAX = 316;
const int FRAME_Y_MAX = 208;
const int CENTER_X = 158;  
const int CENTER_TOL = 25; 
const int CLOSE_WIDTH = 100;



void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);  //right 
  pinMode(7, OUTPUT); //left 
  pixy.init();
}

void loop() {
  pixy.ccc.getBlocks();  // Get all detected color-connected components (blocks)

  if (pixy.ccc.numBlocks) {
    bool ballDetected = false;

    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      if (pixy.ccc.blocks[i].m_signature == 1) {
        ballDetected = true;

        int x = pixy.ccc.blocks[i].m_x;
        int y = pixy.ccc.blocks[i].m_y;
        int width = pixy.ccc.blocks[i].m_width;

        Serial.print("DETECTED -> ");
        Serial.print("X: ");
        Serial.print(x);
        
        Serial.print(" Y: ");
        Serial.print(y);

        Serial.print(", Width= ");
        Serial.println(width);

        if (x < (FRAME_X_MAX/2 - CENTER_TOL)) {
          Serial.println("Ball is LEFT");
           digitalWrite(5, HIGH); // Left LED on
           digitalWrite(7, LOW); 
        }
        else if (x > (FRAME_X_MAX/2 + CENTER_TOL))  {
          Serial.println("Ball is RIGHT");
          digitalWrite(7,HIGH);
          digitalWrite(5, LOW); 
        }
        else {
          Serial.println("Ball is CENTER");
          digitalWrite(7,HIGH);
          digitalWrite(5,HIGH); 
          
        }

        //if (width < CLOSE_WIDTH) {
        //  Serial.println("Ball is FAR");
        //} else {
          //Serial.println("Ball is CLOSE");
        //}
       // pixy.ccc.blocks[i].print();

        break; 
      }
    }

    if (!ballDetected) {
      Serial.println("No tennis ball found");
    }
  } else {
    Serial.println("No blocks detected");
    digitalWrite(7,LOW);
    digitalWrite(5,LOW); 
  }
  delay(200);
}



