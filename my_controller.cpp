#include "my_controller.h"

void MyController::SetCmd(const String& cmd) {
  last_cmd = cur_cmd;
  cur_cmd = cmd;
  
  if (cmd == KEY_STOP) {
    Stop();
  } else {
    GetNewMoveState();
    GetLightingState();
    GetSoundState();
  }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
void MyController::GetNewMoveState() {
    if (cur_cmd == KEY_SPEED) {
      cur_speed += INC_SPEED;
      if (cur_speed > 255) {
        cur_speed = 255;
      }
    } else if (cur_cmd == KEY_MOVE_STOP) {
      is_active = false;
    }
    
    else if (cur_cmd == KEY_MOVE_D0) {
      dir = DIR_W;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D45) {
      dir = DIR_W_N;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D90) {
      dir = DIR_N;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D135) {
      dir = DIR_N_E;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D180) {
      dir = DIR_E;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D225) {
      dir = DIR_E_S;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D270) {
      dir = DIR_S;
      is_active = true;
    } else if (cur_cmd == KEY_MOVE_D315) {
      dir = DIR_S_W;
      is_active = true;
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
  dir = DIR_NULL;  
}

bool MyController::StartAction() {
  if (is_active && dir != last_dir) {  
    return true;
  } else {
    return false;
  }
}

void MyController::EndAction() {
  last_dir = dir;
}

    

