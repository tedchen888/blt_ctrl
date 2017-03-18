#include <Servo.h>
#include "my_controller.h"

Servo myservo; //舵机
MyController controller;

#define PIN_MOVE_L1 2  //前后控制2，3直流电机脚
#define PIN_MOVE_L2 3
#define PIN_MOVE_R1 4
#define PIN_MOVE_R2 5
#define PIN_DIRECT 6     //前后控制舵机
#define PIN_LIGHT 7
#define PIN_SOUND 8


void setup() 
{
  pinMode(PIN_MOVE_L1, OUTPUT);
  pinMode(PIN_MOVE_L2, OUTPUT);
  pinMode(PIN_MOVE_R1, OUTPUT);
  pinMode(PIN_MOVE_R2, OUTPUT);
  //pinMode(PIN_DIRECT, OUTPUT);
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_SOUND, OUTPUT);  
  
  // 如果是HC-05，請改成38400，独立供电要使用Serial1
  Serial.begin(9600);
  myservo.attach(PIN_DIRECT);  
 }

void action() {
    //unsigned long now = millis();
    
    //moving
<<<<<<< HEAD
    if (controller.moving != controller.last_moving) {          
        if (controller.moving == MOVE_FORWARD) {
=======
    if (controller.StartAction()) {          
        if (controller.IsForward()) {
>>>>>>> origin/master
            digitalWrite(PIN_MOVE_L1, LOW);
            analogWrite(PIN_MOVE_L2, controller.GetSpeed());
            digitalWrite(PIN_MOVE_R1, LOW);
<<<<<<< HEAD
            analogWrite(PIN_MOVE_R2, controller.cur_speed);
        } else if (controller.moving == MOVE_BACK) {
            digitalWrite(PIN_MOVE_L2, LOW);
            analogWrite(PIN_MOVE_L1, controller.cur_speed);
            digitalWrite(PIN_MOVE_R2, LOW);
            analogWrite(PIN_MOVE_R1, controller.cur_speed);
=======
            analogWrite(PIN_MOVE_R2, controller.GetSpeed());
        } else if (controller.IsBack()) {
            digitalWrite(PIN_MOVE_L2, LOW);
            analogWrite(PIN_MOVE_L1, -controller.GetSpeed());
            digitalWrite(PIN_MOVE_R2, LOW);
            analogWrite(PIN_MOVE_R1, -controller.GetSpeed());
>>>>>>> origin/master
        } else {
            digitalWrite(PIN_MOVE_L1, LOW);
            digitalWrite(PIN_MOVE_L2, LOW);
            digitalWrite(PIN_MOVE_R1, LOW);
            digitalWrite(PIN_MOVE_R2, LOW);
        }
<<<<<<< HEAD
        controller.last_moving = controller.moving;
=======
        //转向
        myservo.write(controller.GetPos()); 
        //更新状态  
        controller.EndAction();     
>>>>>>> origin/master
    }

    //转向
    if (controller.last_servo_pos != controller.servo_pos) {
      myservo.write(controller.servo_pos); 
      controller.last_servo_pos = controller.servo_pos;
    }   
    
    //lighting
    if (controller.is_lighting != controller.last_lighting) {
        digitalWrite(PIN_LIGHT, controller.is_lighting);
        controller.last_lighting = controller.is_lighting;
    }
    //sound
    if (controller.is_sound != controller.last_sound) {
        digitalWrite(PIN_SOUND, controller.is_sound);
        controller.last_sound = controller.is_sound;
    }
}

String cur_cmd; //存储接收命令
void loop() 
{
  while(Serial.available()) {
    char c = Serial.read();
    
    if (CMD_END == c) { //收到完整命令
      controller.SetCmd(cur_cmd);
      cur_cmd = "";
    } else {
      cur_cmd += c;
    }    
  }
    //根据命令动作
  action();  
}


