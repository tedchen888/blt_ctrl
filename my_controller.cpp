#include "my_controller.h"

void MyController::SetCmd(const String& cmd) {
  last_cmd = cur_cmd;
  cur_cmd = cmd;
  
  GetNewMoveState();
  GetNewDirState();
  GetLightingState();
  GetSoundState();
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
void MyController::GetNewMoveState() {
    if (cur_cmd == KEY_FORWARD) {
      cur_move_state = ((cur_move_state == MOVE_BACK) ? MOVE_STOP : MOVE_FORWARD);
        //Serial.println("forward");
    } else if (cur_cmd == KEY_BACK) {
      cur_move_state = ((cur_move_state == MOVE_FORWARD) ? MOVE_STOP : MOVE_BACK);
        //Serial.println("back");
    } else if (cur_cmd == KEY_STOP) {
      cur_move_state = MOVE_STOP;
        //Serial.println("stop");
    } else if (cur_cmd == KEY_MOVE_STOP) { //松开按键后停止运动
      cur_move_state = MOVE_STOP;   
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
  cur_move_state = MOVE_STOP;
  pos = DIR_MID;  
}

