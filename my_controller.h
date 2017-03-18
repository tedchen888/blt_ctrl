#ifndef  MY_CRONTALLER_H_
#define  MY_CRONTALLER_H_
#include <Arduino.h>

const char CMD_END = '\n';
#define KEY_STOP "stop" //停止
#define KEY_MOVE "move"
#define KEY_MOVE_STOP "move0"
#define KEY_MOVE_D0 "d0"
#define KEY_MOVE_D45 "d45"
#define KEY_MOVE_D90 "d90"
#define KEY_MOVE_D135 "d135"
#define KEY_MOVE_D180 "d180"
#define KEY_MOVE_D225 "d225"
#define KEY_MOVE_D270 "d270"
#define KEY_MOVE_D315 "d315"
#define KEY_SPEED "speed"
#define KEY_LIGHT "light"  //on1
#define KEY_SOUND "sound"  //on2

//运动状态：停、前、后状态机
#define INIT_SPEED 255
#define INC_SPEED 20 //加速度

//方向状态：中、左、右状态机
#define POS_LEFT 20
#define POS_MID 90
#define MOVE_FORWARD 1
#define MOVE_BACK 2
#define MOVE_STOP 3
#define DIR_NULL 0  //初始
#define DIR_W 1  //西
#define DIR_W_N 2 //西北
#define DIR_N 3   //北
#define DIR_N_E 4 //东北
#define DIR_E 5   //东
#define DIR_E_S 6  //东南
#define DIR_S 7 //南
#define DIR_S_W 8 //西南

//方向对应的运动状态
struct TDirMovingState{
  int pos;//舵机角度
  int moving; //1前进、2后退、0停止
};

class MyController
{
  public:
    MyController():moving(MOVE_STOP),last_moving(MOVE_STOP),
      cur_speed(INIT_SPEED), servo_pos(POS_MID), last_servo_pos(POS_MID),
      is_lighting(false),last_lighting(false),
      is_sound(false), last_sound(false), 
      last_cmd(""), cur_cmd(""){}

    void SetCmd(const String& cmd);    
    void UpdateMoveState();
    void UpdateLightingState();
    void UpdateSoundState();
    void Stop();
  public:    
    String last_cmd;
    String cur_cmd;

    int moving;
    int last_moving;
    int cur_speed;

    int servo_pos;
    int last_servo_pos;
    
    //灯光控制
    bool is_lighting;
    bool last_lighting;
    
    //声音控制
    bool is_sound;
    bool last_sound;
};

#endif
