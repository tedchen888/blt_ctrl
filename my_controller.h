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
#define INIT_SPEED 100
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
    MyController():dir(DIR_NULL),last_dir(DIR_NULL),
      cur_speed(0),is_active(false),
      is_lighting(false),last_lighting(false),
      is_sound(false), last_sound(false), 
      last_cmd(""), cur_cmd(""){

      //初始化8种方向与状态的关系
      dir2state[DIR_NULL].pos = POS_MID;
      dir2state[DIR_NULL].moving = MOVE_STOP;
      
      dir2state[DIR_W].pos = 20;
      dir2state[DIR_W].moving = MOVE_FORWARD;
      dir2state[DIR_W_N].pos = 45;
      dir2state[DIR_W_N].moving = MOVE_FORWARD;
      dir2state[DIR_N].pos = 90;
      dir2state[DIR_N].moving = MOVE_FORWARD;
      dir2state[DIR_N_E].pos = 135;
      dir2state[DIR_N_E].moving = MOVE_FORWARD;
      dir2state[DIR_E].pos = 160;
      dir2state[DIR_E].moving = MOVE_FORWARD;
      dir2state[DIR_E_S].pos = 135;
      dir2state[DIR_E_S].moving = MOVE_BACK;
      dir2state[DIR_S].pos = 90;
      dir2state[DIR_S].moving = MOVE_BACK;
      dir2state[DIR_S_W].pos = 45;
      dir2state[DIR_S_W].moving = MOVE_BACK;      
    }

    void SetCmd(const String& cmd);
    
    void GetNewMoveState();
    void GetLightingState();
    void GetSoundState();

    bool StartAction();
    void EndAction();

    bool IsForward() {
      return (dir2state[dir].moving == MOVE_FORWARD);
    }
    bool IsBack() {
      return (dir2state[dir].moving == MOVE_BACK);
    }
    int GetSpeed() {
      return cur_speed;
    }
    int GetPos() {
      return (dir2state[dir].pos);
    }
    const TDirMovingState& CurState() const {
      return dir2state[dir];
    }

    void Stop();
    
  public:
    TDirMovingState dir2state[8];
    
    String last_cmd;
    String cur_cmd;

    bool is_active;
    int dir;
    int last_dir;
    int cur_speed;
    
    //灯光控制
    bool is_lighting;
    bool last_lighting;
    
    //声音控制
    bool is_sound;
    bool last_sound;
};

#endif
