
#ifndef RGB10_MAX_HEADER
#define RGB10_MAX_HEADER

void handle_event_rgb10max(int type, int code, int value) {
  if (type == 1) {
    //Back Key
    if (code == back_key && value == 1) {
      emit(EV_KEY, back, 1);
      emit(EV_SYN, SYN_REPORT, 0);
      hold = 1;
    }
    else if (code == back_key && value == 0) {
      emit(EV_KEY, back, 0);
      emit(EV_SYN, SYN_REPORT, 0);
      hold = 0;
    }
    //Start Key
    if (code == start_key && value == 1) {
      if (hold == 1) {
        handleKillApplication();
      }
      emit(EV_KEY, start, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == start_key && value == 0) {
      emit(EV_KEY, start, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //A Key
    if (code == a_key && value == 1) {
      emit(EV_KEY, a, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == a_key && value == 0) {
      emit(EV_KEY, a, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //B Key
    if (code == b_key && value == 1) {
      emit(EV_KEY, b, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == b_key && value == 0) {
      emit(EV_KEY, b, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //X Key
    if (code == x_key && value == 1) {
      emit(EV_KEY, x, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == x_key && value == 0) {
      emit(EV_KEY, x, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //Y Key
    if (code == y_key && value == 1) {
      emit(EV_KEY, y, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == y_key && value == 0) {
      emit(EV_KEY, y, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //L1 Key
    if (code == l1_key && value == 1) {
      emit(EV_KEY, l1, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l1_key && value == 0) {
      emit(EV_KEY, l1, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //L2 Key
    if (code == l2_key && value == 1) {
      emit(EV_KEY, l2, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l2_key && value == 0) {
      emit(EV_KEY, l2, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //L3 Key
    if (code == l3_key && value == 1) {
      emit(EV_KEY, l3, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l3_key && value == 0) {
      emit(EV_KEY, l3, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //R1 Key
    if (code == r1_key && value == 1) {
      emit(EV_KEY, r1, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r1_key && value == 0) {
      emit(EV_KEY, r1, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //R2 Key
    if (code == r2_key && value == 1) {
      emit(EV_KEY, r2, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r2_key && value == 0) {
      emit(EV_KEY, r2, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //R3 Key
    if (code == r3_key && value == 1) {
      emit(EV_KEY, r3, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r3_key && value == 0) {
      emit(EV_KEY, r3, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //D-Pad Up
    if (code == up_key && value == 1) {
      emit(EV_KEY, up, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == up_key && value == 0) {
      emit(EV_KEY, up, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //D-pad Down
    if (code == down_key && value == 1) {
      emit(EV_KEY, down, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == down_key && value == 0) {
      emit(EV_KEY, down, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //D-Pad Left
    if (code == left_key && value == 1) {
      emit(EV_KEY, left, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == left_key && value == 0) {
      emit(EV_KEY, left, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    //D-Pad Right
    if (code == right_key && value == 1) {
      emit(EV_KEY, right, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == right_key && value == 0) {
      emit(EV_KEY, right, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

  }
  // analog
  if (type == 3) {
    // mouse movement, right analog
    if (right_analog_mouse) {
      if (code == 4) { // up/down
        if (value > deadzone_y) {
          emit(EV_REL, REL_Y, -1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
        if (value < deadzone_x) {
          emit(EV_REL, REL_Y, 1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
      }
      else if (code == 3) { // left/right
        if (value > deadzone_y) {
          emit(EV_REL, REL_X, -1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
        if (value < deadzone_x) {
          emit(EV_REL, REL_X, 1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
      }
    }
    else {
      if (code == 4) { // up/down
        if (value > deadzone_y) {
          emit(EV_KEY, right_analog_down, 1);
          emit(EV_SYN, SYN_REPORT, 0);
                right_analog_y = 2;
        }
        else {
          if (right_analog_y > 0 || right_analog_x > 0) {
            emit(EV_KEY, right_analog_down, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            right_analog_y = right_analog_y - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_KEY, right_analog_up, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          right_analog_y = 2;
        }
        else {
          if (right_analog_y > 0 || right_analog_x > 0) {
            emit(EV_KEY, right_analog_up, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            right_analog_y = right_analog_y - 1;
          }
        }
      }
      if (code == 3) { // left/right
        if (value > deadzone_y) {
          emit(EV_KEY, right_analog_right, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          right_analog_x = 2;
        }
        else {
          if (right_analog_x > 0 || right_analog_y > 0) {
            emit(EV_KEY, right_analog_right, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            right_analog_x = right_analog_x - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_KEY, right_analog_left, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          right_analog_x = 2;
        }
        else {
          if (right_analog_x > 0 || right_analog_y > 0) {
            emit(EV_KEY, right_analog_left, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            right_analog_x = right_analog_x - 1;
          }
        }
      }
    }
    // mouse movement, left analog
    if (left_analog_mouse) {
      if (code == 1) { // up/down
        if (value > deadzone_y) {
          emit(EV_REL, REL_Y, -1);
          emit(EV_SYN, SYN_REPORT, 0);
        }

        if (value > 0 && value < deadzone_x) {
          emit(EV_REL, REL_Y, 1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
      }
      else if (code == 0) { // left/right
        if (value > deadzone_y) {
          emit(EV_REL, REL_X, -1);
          emit(EV_SYN, SYN_REPORT, 0);
        }

        if (value > 0 && value < deadzone_x) {
          emit(EV_REL, REL_X, 1);
          emit(EV_SYN, SYN_REPORT, 0);
        }
      }
    }
    else {
      if (code == 1) { // left analogue y axis
        if (value > deadzone_y) {
          emit(EV_KEY, left_analog_down, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_y = 2;
        }
        else {
          if (left_analog_y > 0 || left_analog_x > 0) {
            emit(EV_KEY, left_analog_down, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_y = left_analog_y - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_KEY, left_analog_up, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_y = 2;
        }
        else {
          if (left_analog_y > 0 || left_analog_x > 0) {
            emit(EV_KEY, left_analog_up, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_y = left_analog_y - 1;
          }
        }
      }
      if (code == 0) { // left analogue x axis
        if (value > deadzone_y) {
          emit(EV_KEY, left_analog_right, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_x = 2;
        }
        else {
          if (left_analog_x > 0 || left_analog_y > 0) {
            emit(EV_KEY, left_analog_right, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_x = left_analog_x - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_KEY, left_analog_left, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_x = 2;
        }
        else {
          if (left_analog_x > 0 || left_analog_y > 0) {
            emit(EV_KEY, left_analog_left, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_x = left_analog_x - 1;
          }
        }
      }
    }
  }
}

void config_rgb10max_top(char *inputstr)
{
#ifdef DEBUG
	printf("OGA Contols - Configuring 'RGB10 MAX/MAX2 Top' device\n");
#endif
	handleEventFunction = &handle_event_rgb10max;
	back_key = 704;
	start_key = 705;
	a_key = 305;
	b_key = 304;
	x_key = 307;
	y_key = 308;
	up_key = 544;
	down_key = 545;
	left_key = 546;
	right_key = 547;
	l1_key = 310;
	r1_key = 311;
	l2_key = 312;
	r2_key = 313;
	l3_key = 708;
	r3_key = 709;
	deadzone_y = 400;
	deadzone_x = -400;
	strcpy(inputstr, "/dev/input/by-path/platform-odroidgo3-joypad-event-joystick");
}

void config_rgb10max_native(char *inputstr)
{
#ifdef DEBUG
	printf("OGA Contols - Configuring 'RGB10 MAX/MAX2 Native' device\n");
#endif
	handleEventFunction = &handle_event_rgb10max;
	back_key = 706;
	start_key = 707;
	a_key = 305;
	b_key = 304;
	x_key = 307;
	y_key = 308;
	up_key = 544;
	down_key = 545;
	left_key = 546;
	right_key = 547;
	l1_key = 310;
	r1_key = 311;
	l2_key = 312;
	r2_key = 313;
	l3_key = 708;
	r3_key = 709;
	deadzone_y = 400;
	deadzone_x = -400;
	strcpy(inputstr, "/dev/input/by-path/platform-odroidgo3-joypad-event-joystick");
}

#endif /* !RGB10_MAX_HEADER */
