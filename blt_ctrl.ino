#include <Servo.h>
/*
有两点是要注意的
1：给hc05供电要接3.3v
2：波特率的设置   Serial.begin(38400);
*/
Servo myservo; //舵机
int pos = 90;    // 舵机角度位置

#define PIN_MOVE_L1 5  //前后控制2，3直流电机脚
#define PIN_MOVE_L2 6
#define PIN_MOVE_R1 10
#define PIN_MOVE_R2 11
#define PIN_DIRECT 3     //前后控制舵机
#define PIN_LIGHT 7
#define PIN_SOUND 8

#define KEY_STOP "stop" //按下0停止

#define KEY_LIGHT "light"  //on1
#define KEY_SOUND "sound"  //on2
#define KEY_FORWARD "up" //前 on5
#define KEY_LEFT "left" //左 on7
#define KEY_BACK "down" //后on8
#define KEY_RIGHT "right" //右on9
#define KEY_SPEED "speed"
#define KEY_SOUND "sound"
#define KEY_RELEASE "release" //松开按键

//运动状态：停、前、后状态机
#define MOVE_STOP 0
#define MOVE_FORWARD 1
#define MOVE_BACK 2
char cur_move_state = MOVE_STOP; 
unsigned long last_move_state = MOVE_STOP;
int cur_speed = 0;
int last_speed = 0;

//方向状态：中、左、右状态机
#define DIR_MID 90
unsigned long last_pos = 0;

//灯光控制
bool is_lighting = false;
unsigned long last_light_time = 0;

//声音控制
bool is_sound = false;
unsigned long last_sound_time = 0;

void setup() {
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

int on = 0;
unsigned long last = millis();

//根据状态机停止上一次动作
void stop_last() {
  cur_move_state = MOVE_STOP;
  pos = DIR_MID;  
  cur_speed = 0;
}

void action() {
    unsigned long now = millis();
    
    //moving
    if (cur_move_state != last_move_state) { //每次改变移动方向需要间隔1毫秒    
      //digitalWrite(PIN_EN1, HIGH);
      //digitalWrite(PIN_EN2, HIGH);
        if (cur_move_state == MOVE_FORWARD) {
            digitalWrite(PIN_MOVE_L1, LOW);
            digitalWrite(PIN_MOVE_L2, HIGH);
            digitalWrite(PIN_MOVE_R1, LOW);
            digitalWrite(PIN_MOVE_R2, HIGH);
        } else if (cur_move_state == MOVE_BACK) {
            digitalWrite(PIN_MOVE_L2, LOW);
            digitalWrite(PIN_MOVE_L1, HIGH);
            digitalWrite(PIN_MOVE_R2, LOW);
            digitalWrite(PIN_MOVE_R1, HIGH);
        } else {
            digitalWrite(PIN_MOVE_L1, LOW);
            digitalWrite(PIN_MOVE_L2, LOW);
            digitalWrite(PIN_MOVE_R1, LOW);
            digitalWrite(PIN_MOVE_R2, LOW);
        }
        last_move_state = cur_move_state;
    }

  if (cur_speed != last_speed) {
    //analogWrite(PIN_EN1, cur_speed);
    //analogWrite(PIN_EN2, cur_speed);
    last_speed = cur_speed;
  }
    
    //direction
    if (pos != last_pos) {  //每次改变转向需要间隔10毫秒    
        /*if (cur_dir_state == DIR_LEFT) {
            //转向角度每次加5
            pos = (pos > 175) ? 180 : (pos + 5);
        } else if (cur_dir_state == DIR_RIGHT) {
            //转向角度每次减少
            pos = (pos < 5) ? 0 : (pos - 5);
        } else {
            pos = 90;
        }*/
        //Serial.println(pos, DEC);
        myservo.write(pos);
        last_pos = pos;
    }
    
    //lighting
    if (now - last_light_time > 10) {
        digitalWrite(PIN_LIGHT, is_lighting);
        last_light_time = now;
    }
    //sound
    if (now - last_sound_time > 10) {
        digitalWrite(PIN_SOUND, is_sound);
        last_sound_time = now;
    }
}

//存储接收命令
String cur_cmd;
String last_cmd;

void loop() {
  while(Serial.available()) {
    char c = Serial.read();
    if ('\n'== c) { //命令结束
      if (cur_cmd == KEY_STOP) { //停止按钮
        stop_last();
      } else {
          GetNewMoveState();
          GetNewDirState();
          GetLightingState();
          GetSoundState();
      }    
      last_cmd = cur_cmd;
      cur_cmd = "";
    } else {
      cur_cmd += c;
    }    
  }
    //根据命令动作
  action();  
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
void GetNewMoveState() {
    if (cur_cmd == KEY_FORWARD) {
      cur_move_state = ((cur_move_state == MOVE_BACK) ? MOVE_STOP : MOVE_FORWARD);
        //Serial.println("forward");
    } else if (cur_cmd == KEY_BACK) {
      cur_move_state = ((cur_move_state == MOVE_FORWARD) ? MOVE_STOP : MOVE_BACK);
        //Serial.println("back");
    } else if (cur_cmd == KEY_STOP) {
      cur_move_state = MOVE_STOP;
        //Serial.println("stop");
    } else if (cur_cmd == KEY_RELEASE  //松开按键后停止运动
    && (last_cmd == KEY_FORWARD || last_cmd == KEY_BACK) ) {
      cur_move_state = MOVE_STOP;
    } else if (cur_cmd == KEY_SPEED) {
      cur_speed = (cur_speed > 220) ? 250 : (cur_speed + 50);      
    }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步方向状态
//按一次键转一次
void GetNewDirState() {
    /*
    if (cur_cmd == KEY_LEFT) {
        cur_dir_state = DIR_LEFT;
    } else if (cur_cmd == KEY_RIGHT) {
        cur_dir_state = DIR_RIGHT;
    } else if (cur_cmd == KEY_FORWARD || cur_cmd == KEY_BACK) { //按下前进和后退时需要转到正前方
        cur_dir_state = DIR_MID;
    } */
    if (cur_cmd == KEY_RIGHT) {
        pos = (pos > 120) ? 140 : (pos + 20);
    } else if (cur_cmd == KEY_LEFT) {
        pos = (pos < 60) ? 40 : (pos - 20);
    } else if (cur_cmd == KEY_FORWARD || cur_cmd == KEY_BACK) { //按下前进和后退时需要转到正前方
        //pos = 90;
    }     
}

void GetLightingState() {
    if (cur_cmd == KEY_LIGHT) {
        is_lighting = is_lighting ? LOW : HIGH;
    }
}

void GetSoundState() {
    if (cur_cmd == KEY_SOUND) {
        is_sound = is_sound ? LOW : HIGH;
    }
}

