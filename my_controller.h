#ifndef  MY_CRONTALLER_H_
#define  MY_CRONTALLER_H_
#include <Arduino.h>

const char CMD_END = '\n';
#define KEY_STOP "stop" //停止
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
#define INIT_SPEED 100
#define INC_SPEED 20 //加速度

//方向状态：中、左、右状态机
#define DIR_MID 90

class MyController
{
  public:
    MyController():cur_speed(0), last_speed(0),
      pos(DIR_MID), last_pos(DIR_MID),
      is_lighting(false),last_lighting(false),
      is_sound(false), last_sound(false), last_cmd(""), cur_cmd(""){}

    void SetCmd(const String& cmd);
    
    void GetNewMoveState();
    void GetNewDirState();
    void GetLightingState();
    void GetSoundState();

    void Stop();
    
  public:
    String last_cmd;
    String cur_cmd;
    
    int cur_speed;
    int last_speed;    
    int pos;
    unsigned long last_pos;
    
    //灯光控制
    bool is_lighting;
    bool last_lighting;
    
    //声音控制
    bool is_sound;
    bool last_sound;
};

#endif
