#include "my_controller.h"

void MyController::SetCmd(const String& cmd) {
  last_cmd = cur_cmd;
  cur_cmd = cmd;
  
  if (cmd == KEY_STOP) {
    Stop();
  } else {
    GetNewMoveState();
    GetNewDirState();
    GetLightingState();
    GetSoundState();
  }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
void MyController::GetNewMoveState() {
    if (cur_cmd == KEY_FORWARD) {
      if (cur_speed < 0) {
        cur_speed = 0;
      } else if (cur_speed == 0) {
        cur_speed = INIT_SPEED;
      }
    } else if (cur_cmd == KEY_BACK) {
      if (cur_speed > 0) {
        cur_speed = 0;
      } else if (cur_speed == 0) {
        cur_speed = -INIT_SPEED;
      }
    } else if (cur_cmd == KEY_STOP) {
      cur_speed = 0;
    } else if (cur_cmd == KEY_SPEED) {
      if (cur_speed > 0) {
        cur_speed += INC_SPEED;
      } else if (cur_speed < 0) {
        cur_speed -= INC_SPEED;
      }
    }

    if (cur_speed > 255) {
      cur_speed = 255;
    } else (cur_speed < -255) {
      cur_speed = -255;
    }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步方向状态
//按一次键转一次
void MyController::GetNewDirState() {
    /*
    if (cur_cmd == KEY_LEFT) {
        cur_dir_state = DIR_LEFT;
    } else if (cur_cmd == KEY_RIGHT) {
        cur_dir_state = DIR_RIGHT;
    } else if (cur_cmd == KEY_FORWARD || cur_cmd == KEY_BACK) { //按下前进和后退时需要转到正前方
        cur_dir_state = DIR_MID;
    } */
    if (cur_cmd == KEY_RIGHT) {
        pos = (pos > 120) ? 140 : (pos + 10);
    } else if (cur_cmd == KEY_LEFT) {
        pos = (pos < 60) ? 40 : (pos - 10);
    } else if (cur_cmd == KEY_FORWARD || cur_cmd == KEY_BACK) { //按下前进和后退时需要转到正前方
        //pos = 90;
    }     
}

void MyController::GetLightingState() {
    if (cur_cmd == KEY_LIGHT) {
        is_lighting = is_lighting ? LOW : HIGH;
    }
}

void MyController::GetSoundState() {
    if (cur_cmd == KEY_SOUND) {
        is_sound = is_sound ? LOW : HIGH;
    }
}

void MyController::Stop() {
  cur_speed = 0;
  pos = DIR_MID;  
}

