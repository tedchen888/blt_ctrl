#include "my_controller.h"

void MyController::SetCmd(const String& cmd) {
  last_cmd = cur_cmd;
  cur_cmd = cmd;
  
  if (cmd == KEY_STOP) {
    Stop();
  } else {
<<<<<<< HEAD
    UpdateMoveState();
    UpdateLightingState();
    UpdateSoundState();
=======
    GetNewMoveState();
    GetLightingState();
    GetSoundState();
>>>>>>> origin/master
  }
}

//根据当前运动状态、上次按键、本次按键、按键间隔得到下一步运动状态
//如果是反方向的先停下来
<<<<<<< HEAD
void MyController::UpdateMoveState() {
=======
void MyController::GetNewMoveState() {
>>>>>>> origin/master
    if (cur_cmd == KEY_SPEED) {
      cur_speed += INC_SPEED;
      if (cur_speed > 255) {
        cur_speed = 255;
      }
    } else if (cur_cmd == KEY_MOVE_STOP) {
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
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
  cur_speed = 0;
<<<<<<< HEAD
  moving = MOVE_STOP;  
  servo_pos = POS_MID;
}

=======
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
>>>>>>> origin/master

    

