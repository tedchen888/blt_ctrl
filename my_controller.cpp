#include "my_controller.h"

void MyController::SetCmd(const String& cmd) {
  last_cmd = cur_cmd;
  cur_cmd = cmd;
  
  if (cmd == KEY_STOP) {
    Stop();
  } else {
    UpdateMoveState();
    UpdateLightingState();
    UpdateSoundState();
  }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
void MyController::UpdateMoveState() {
    if (cur_cmd == KEY_SPEED) {
      cur_speed += INC_SPEED;
      if (cur_speed > 255) {
        cur_speed = 255;
      }
    } else if (cur_cmd == KEY_MOVE_STOP) {
      moving = MOVE_STOP;
    }
    //方向
    else if (cur_cmd == KEY_MOVE_D0) {
      servo_pos = 45;
      moving = MOVE_FORWARD;
    } else if (cur_cmd == KEY_MOVE_D45) {
      servo_pos = 65;
      moving = MOVE_FORWARD;
    } else if (cur_cmd == KEY_MOVE_D90) {
      servo_pos = 90;
      moving = MOVE_FORWARD;
    } else if (cur_cmd == KEY_MOVE_D135) {
      servo_pos = 115;
      moving = MOVE_FORWARD;
    } else if (cur_cmd == KEY_MOVE_D180) {
      servo_pos = 135;
      moving = MOVE_FORWARD;
    } else if (cur_cmd == KEY_MOVE_D225) {
      servo_pos = 115;
      moving = MOVE_BACK;
    } else if (cur_cmd == KEY_MOVE_D270) {
      servo_pos = 90;
      moving = MOVE_BACK;
    } else if (cur_cmd == KEY_MOVE_D315) {
      servo_pos = 65;
      moving = MOVE_BACK;
    }    
}

void MyController::UpdateLightingState() {
    if (cur_cmd == KEY_LIGHT) {
        is_lighting = is_lighting ? LOW : HIGH;
    }
}

void MyController::UpdateSoundState() {
    if (cur_cmd == KEY_SOUND) {
        is_sound = is_sound ? LOW : HIGH;
    }
}

void MyController::Stop() {
  moving = MOVE_STOP;  
  servo_pos = POS_MID;
}

