
#ifndef OGS_HEADER
#define OGS_HEADER

void handle_event_ogs(int type, int code, int value) {
  if (type == 1) {
    if (code == back_key && value == 1) {
      hold = 1;
      emit(EV_KEY, back, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == back_key && value == 0) {
      hold = 0;
      emit(EV_KEY, back, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

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

    if (code == a_key && value == 1) {
      emit(EV_KEY, a, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == a_key && value == 0) {
      emit(EV_KEY, a, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == b_key && value == 1) {
      emit(EV_KEY, b, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == b_key && value == 0) {
      emit(EV_KEY, b, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == x_key && value == 1) {
      emit(EV_KEY, x, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == x_key && value == 0) {
      emit(EV_KEY, x, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == y_key && value == 1) {
      emit(EV_KEY, y, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == y_key && value == 0) {
      emit(EV_KEY, y, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == l1_key && value == 1) {
      emit(EV_KEY, l1, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l1_key && value == 0) {
      emit(EV_KEY, l1, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == l2_key && value == 1) {
      emit(EV_KEY, l2, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l2_key && value == 0) {
      emit(EV_KEY, l2, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == l3_key && value == 1) {
      emit(EV_KEY, l3, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == l3_key && value == 0) {
      emit(EV_KEY, l3, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == r1_key && value == 1) {
      emit(EV_KEY, r1, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r1_key && value == 0) {
      emit(EV_KEY, r1, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == r2_key && value == 1) {
      emit(EV_KEY, r2, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r2_key && value == 0) {
      emit(EV_KEY, r2, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == r3_key && value == 1) {
      emit(EV_KEY, r3, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == r3_key && value == 0) {
      emit(EV_KEY, r3, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    //dpad
    if (code == up_key && value == 1) {
      emit(EV_KEY, up, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == up_key && value == 0) {
      emit(EV_KEY, up, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == down_key && value == 1) {
      emit(EV_KEY, down, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == down_key && value == 0) {
      emit(EV_KEY, down, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

    if (code == left_key && value == 1) {
      emit(EV_KEY, left, 1);
      emit(EV_SYN, SYN_REPORT, 0);
    }
    else if (code == left_key && value == 0) {
      emit(EV_KEY, left, 0);
      emit(EV_SYN, SYN_REPORT, 0);
    }

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
          emit(EV_REL, REL_Y, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_y = 2;
        }
        else {
          if (left_analog_y > 0 || left_analog_x > 0) {
            emit(EV_REL, REL_Y, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_y = left_analog_y - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_REL, REL_Y, -1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_y = 2;
        }
        else {
          if (left_analog_y > 0 || left_analog_x > 0) {
            emit(EV_REL, REL_Y, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_y = left_analog_y - 1;
          }
        }
      }
      if (code == 0) { // left analog x axis
        if (value > deadzone_y) {
          emit(EV_REL, REL_X, 1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_x = 2;
        }
        else {
          if (left_analog_x > 0 || left_analog_y > 0) {
            emit(EV_REL, REL_X, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_x = left_analog_x - 1;
          }
        }
        if (value < deadzone_x) {
          emit(EV_REL, REL_X, -1);
          emit(EV_SYN, SYN_REPORT, 0);
          left_analog_x = 2;
        }
        else {
          if (left_analog_x > 0 || left_analog_y > 0) {
            emit(EV_REL, REL_X, 0);
            emit(EV_SYN, SYN_REPORT, 0);
            left_analog_x = left_analog_x - 1;
          }
        }
      }
    }
    else {
      if (code == 1) { // left analog y axis
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
      if (code == 0) { // left analog x axis
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

void config_ogs(char *inputstr)
{
#ifdef DEBUG
  printf("OGA Contols - Configuring 'OGS' device\n");
#endif
  handleEventFunction = &handle_event_ogs;
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
  l2_key = 312;
  l3_key = 707;
  r1_key = 311;
  r2_key = 313;
  r3_key = 708;
  deadzone_y = 300;
  deadzone_x = -300;
  strcpy(inputstr, "/dev/input/by-path/platform-odroidgo3-joypad-event-joystick");
}

#endif /* !OGS_HEADER */
