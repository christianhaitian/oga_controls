/* Copyright (c) 2021
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
#
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
#
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA
#
* Authored by: Kris Henriksen <krishenriksen.work@gmail.com>
#
* AnberPorts-Joystick
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <linux/input.h>
#include <linux/uinput.h>

#include <libevdev-1.0/libevdev/libevdev.h>
#include <libevdev-1.0/libevdev/libevdev-uinput.h>

#include "parser.h"

struct libevdev* dev_joypad;
int fd_ev_joypad;
int rc_joypad;
struct input_event ev_joypad;

static int uinp_fd = -1;
struct uinput_user_dev uidev;

int debug = 0;
char quit_command[100];

// Define variables to be used for key codes
int back_key;
int start_key;
int a_key;
int b_key;
int x_key;
int y_key;
int up_key;
int down_key;
int left_key;
int right_key;
int l1_key;
int l2_key;
int l3_key;
int r1_key;
int r2_key;
int r3_key;
int deadzone_y;
int deadzone_x;

short back = KEY_ESC;
short start = KEY_ENTER;
short a = KEY_ENTER;
short b = KEY_ENTER;
short x = KEY_RIGHTALT;
short y = KEY_RIGHTALT;
short l1 = KEY_RIGHTALT;
short l2 = KEY_RIGHTALT;
short l3 = KEY_RIGHTALT;
short r1 = KEY_RIGHTALT;
short r2 = KEY_RIGHTALT;
short r3 = KEY_RIGHTALT;
short up = KEY_UP;
short down = KEY_DOWN;
short left = KEY_LEFT;
short right = KEY_RIGHT;
short left_analog_up = KEY_RIGHTALT;
short left_analog_down = KEY_RIGHTALT;
short left_analog_left = KEY_RIGHTALT;
short left_analog_right = KEY_RIGHTALT;
short right_analog_up = KEY_RIGHTALT;
short right_analog_down = KEY_RIGHTALT;
short right_analog_left = KEY_RIGHTALT;
short right_analog_right = KEY_RIGHTALT;

int left_analog_x = 0;
int left_analog_y = 0;
int right_analog_x = 0;
int right_analog_y = 0;

int left_analog_mouse = 0;
int right_analog_mouse = 0;

int hold = 0;

void emit(int type, int code, int val) {
   struct input_event ev;

   ev.type = type;
   ev.code = code;
   ev.value = val;
   ev.time.tv_sec = 0;
   ev.time.tv_usec = 0;

   write(uinp_fd, &ev, sizeof(ev));
}

void handle_event_rg552(int type, int code, int value) {
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
				system(quit_command);
				system("sleep 0.2");
                exit (0);
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
			hold = 1;
			emit(EV_KEY, r3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r3_key && value == 0) {
			hold = 0;
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
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			else if (code == 3) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_X, (value/64));
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
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			else if (code == 0) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
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

void handle_event_chi(int type, int code, int value) {
	if (type == 1) {
		if (code == back_key && value == 1) {
			emit(EV_KEY, back, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == back_key && value == 0) {
			emit(EV_KEY, back, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == start_key && value == 1) {
			if (hold == 1) {
				system(quit_command);
				system("sleep 0.2");
                exit (0);
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
			hold = 1;
			emit(EV_KEY, l3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == l3_key && value == 0) {
			hold = 0;
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
			hold = 1;
			emit(EV_KEY, r3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r3_key && value == 0) {
			hold = 0;
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
			if (code == 3) { // up/down
				if (value > deadzone_y) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			else if (code == 4) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
		}
		else {
			if (code == 3) { // up/down
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
			
			if (code == 4) { // left/right
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
			if (code == 0) { // up/down
				if (value > deadzone_y) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_Y, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			else if (code == 1) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value < deadzone_x) {
					emit(EV_REL, REL_X, (value/64));
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
		}
		else {	
			if (code == 0) { // left analog y axis
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
             if (code == 1) { // left analogue x axis
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
				system(quit_command);
				system("sleep 0.2");
                exit (0);
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

void handle_event_ogx(int type, int code, int value) {
	if (type == 1) {
		if (code == back_key && value == 1) {
			emit(EV_KEY, back, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == back_key && value == 0) {
			emit(EV_KEY, back, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == start_key && value == 1) {
			if (hold == 1) {
				system(quit_command);
				system("sleep 0.2");
                exit (0);
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
			hold = 1;
			emit(EV_KEY, l3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == l3_key && value == 0) {
			hold = 0;
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
			hold = 1;
			emit(EV_KEY, r3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r3_key && value == 0) {
			hold = 0;
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

void handle_event_rk2020(int type, int code, int value) {
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
				system(quit_command);
				system("sleep 0.2");
                exit (0);
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
		// mouse movement, left analog
		if (left_analog_mouse) {
			if (code == 3) { // up/down
				if (value > deadzone_y) {
					emit(EV_REL, REL_Y, -1);
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value > 0 && value < deadzone_x) {
					emit(EV_REL, REL_Y, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			else if (code == 2) { // left/right
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

void handle_event_anbernic(int type, int code, int value) {
	if (type == 1) {
		if (code == back_key && value == 1) {
			hold = 0;

			emit(EV_KEY, back, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == back_key && value == 0) {
			hold = 0;
			emit(EV_KEY, back, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == back_key && value == 2) {
			hold = 1;
		}

		if (code == start_key && value == 1) {
			if (hold == 1) {
				system(quit_command);
				system("sleep 0.2");
                exit (0);
			}

			emit(EV_KEY, start, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == start_key && value == 0) {
			emit(EV_KEY, start, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == a_key && (value == 1 || value == 2)) {
			emit(EV_KEY, a, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == a_key && value == 0) {
			emit(EV_KEY, a, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == b_key && (value == 1 || value == 2)) {
			emit(EV_KEY, b, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == b_key && value == 0) {
			emit(EV_KEY, b, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == x_key && (value == 1 || value == 2)) {
			emit(EV_KEY, x, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == x_key && value == 0) {
			emit(EV_KEY, x, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == y_key && (value == 1 || value == 2)) {
			emit(EV_KEY, y, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == y_key && value == 0) {
			emit(EV_KEY, y, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == l1_key && (value == 1 || value == 2)) {
			emit(EV_KEY, l1, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == l1_key && value == 0) {
			emit(EV_KEY, l1, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}		

		if (code == l2_key && (value == 1 || value == 2)) {
			emit(EV_KEY, l2, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == l2_key && value == 0) {
			emit(EV_KEY, l2, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == l3_key && (value == 1 || value == 2)) {
			emit(EV_KEY, l3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == l3_key && value == 0) {
			emit(EV_KEY, l3, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}

		if (code == r1_key && (value == 1 || value == 2)) {
			emit(EV_KEY, r1, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r1_key && value == 0) {
			emit(EV_KEY, r1, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}		

		if (code == r2_key && (value == 1 || value == 2)) {
			emit(EV_KEY, r2, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r2_key && value == 0) {
			emit(EV_KEY, r2, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}		

		if (code == r3_key && (value == 1 || value == 2)) {
			emit(EV_KEY, r3, 1);
			emit(EV_SYN, SYN_REPORT, 0);
		}
		else if (code == r3_key && value == 0) {
			emit(EV_KEY, r3, 0);
			emit(EV_SYN, SYN_REPORT, 0);
		}
	}

	// d-pad
	if (type == 3) {
		if (code == up_key && value == -1) {
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

		if (code == left_key && value == -1) {
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
		// mouse movement, left analog
		if (right_analog_mouse) {
			if (code == 5) { // up/down
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

				if (value >= 0 && value < deadzone_x) {
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
			else if (code == 4) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, 1);
					emit(EV_SYN, SYN_REPORT, 0);
                    			left_analog_x = 2;
				}
				else {
                       			if (left_analog_y > 0 || left_analog_x > 0) {
    						emit(EV_REL, REL_X, 0);
					        emit(EV_SYN, SYN_REPORT, 0);
                               			left_analog_x = left_analog_x - 1;
                       			}
				}

				if (value >= 0 && value < deadzone_x) {
					emit(EV_REL, REL_X, -1);
					emit(EV_SYN, SYN_REPORT, 0);
                    			left_analog_x = 2;
				}
				else {
                       			if (left_analog_y > 0 || left_analog_x > 0) {
    						emit(EV_REL, REL_X, 0);
					        emit(EV_SYN, SYN_REPORT, 0);
                               			left_analog_x = left_analog_x - 1;
                       			}
				}
			}
		}
		else {
			if (code == 5) { // up/down
				if (value > deadzone_y) {
					emit(EV_KEY, right_analog_down, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, right_analog_down, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value >= 0 && value < deadzone_x) {
					emit(EV_KEY, right_analog_up, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, right_analog_up, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			
			if (code == 4) { // left/right
				if (value > deadzone_y) {
					emit(EV_KEY, right_analog_right, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, right_analog_right, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value >= 0 && value < deadzone_x) {
					emit(EV_KEY, right_analog_left, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, right_analog_left, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
		}

		// mouse movement, left analog
		if (left_analog_mouse) {
			if (code == 3) { // up/down
				if (value > deadzone_y) {
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

				if (value > 0 && value < deadzone_x) {
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
			}
			else if (code == 2) { // left/right
				if (value > deadzone_y) {
					emit(EV_REL, REL_X, -1);
					emit(EV_SYN, SYN_REPORT, 0);
                    			left_analog_x = 2;
				}
				else {
                       			if (left_analog_y > 0 || left_analog_x > 0) {
    						emit(EV_REL, REL_X, 0);
					        emit(EV_SYN, SYN_REPORT, 0);
                               			left_analog_x = left_analog_x - 1;
                       			}
				}

				if (value > 0 && value < deadzone_x) {
					emit(EV_REL, REL_X, 1);
					emit(EV_SYN, SYN_REPORT, 0);
                    			left_analog_x = 2;
				}
				else {
                       			if (left_analog_y > 0 || left_analog_x > 0) {
    						emit(EV_REL, REL_X, 0);
					        emit(EV_SYN, SYN_REPORT, 0);
                               			left_analog_x = left_analog_x - 1;
                       			}
				}
			}
		}
		else {	
			if (code == 3) { // w/s
				if (value > deadzone_y) {
					emit(EV_KEY, left_analog_up, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, left_analog_up, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}

				if (value >= 0 && value < deadzone_x) {
					emit(EV_KEY, left_analog_down, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, left_analog_down, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
			
			if (code == 2) { // a/d
				if (value > deadzone_y) {
					emit(EV_KEY, left_analog_left, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, left_analog_left, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				
				if (value >= 0 && value < deadzone_x) {
					emit(EV_KEY, left_analog_right, 1);
					emit(EV_SYN, SYN_REPORT, 0);
				}
				else {
					emit(EV_KEY, left_analog_right, 0);
					emit(EV_SYN, SYN_REPORT, 0);
				}
			}
		}
	}
}

// convert ASCII chars to key codes
short char_to_keycode(char str[]) {
	short keycode;

	// arrow keys
	if (strcmp(str, "up") == 0) keycode = KEY_UP;
	else if (strcmp(str, "down") == 0) keycode = KEY_DOWN;
	else if (strcmp(str, "left") == 0) keycode = KEY_LEFT;
	else if (strcmp(str, "right") == 0) keycode = KEY_RIGHT;

	// special keys
	else if (strcmp(str, "mouse_left") == 0) keycode = BTN_LEFT;
	else if (strcmp(str, "mouse_right") == 0) keycode = BTN_RIGHT;
	else if (strcmp(str, "space") == 0) keycode = KEY_SPACE;
	else if (strcmp(str, "esc") == 0) keycode = KEY_ESC;
	else if (strcmp(str, "end") == 0) keycode = KEY_END;
	else if (strcmp(str, "home") == 0) keycode = KEY_HOME;
	else if (strcmp(str, "shift") == 0) keycode = KEY_LEFTSHIFT;
	else if (strcmp(str, "leftshift") == 0) keycode = KEY_LEFTSHIFT;
	else if (strcmp(str, "rightshift") == 0) keycode = KEY_RIGHTSHIFT;
	else if (strcmp(str, "ctrl") == 0) keycode = KEY_LEFTCTRL;
	else if (strcmp(str, "leftctrl") == 0) keycode = KEY_LEFTCTRL;
	else if (strcmp(str, "rightctrl") == 0) keycode = KEY_RIGHTCTRL;
	else if (strcmp(str, "alt") == 0) keycode = KEY_LEFTALT;
	else if (strcmp(str, "leftalt") == 0) keycode = KEY_LEFTALT;
	else if (strcmp(str, "rightalt") == 0) keycode = KEY_RIGHTALT;
	else if (strcmp(str, "backspace") == 0) keycode = KEY_BACKSPACE;
	else if (strcmp(str, "enter") == 0) keycode = KEY_ENTER;
	else if (strcmp(str, "pageup") == 0) keycode = KEY_PAGEUP;
	else if (strcmp(str, "pagedown") == 0) keycode = KEY_PAGEDOWN;
	else if (strcmp(str, "insert") == 0) keycode = KEY_INSERT;
	else if (strcmp(str, "delete") == 0) keycode = KEY_DELETE;
	else if (strcmp(str, "capslock") == 0) keycode = KEY_CAPSLOCK;
	else if (strcmp(str, "tab") == 0) keycode = KEY_TAB;

	// normal keyboard
	else if (strcmp(str, "a") == 0) keycode = KEY_A;
	else if (strcmp(str, "b") == 0) keycode = KEY_B;
	else if (strcmp(str, "c") == 0) keycode = KEY_C;
	else if (strcmp(str, "d") == 0) keycode = KEY_D;
	else if (strcmp(str, "e") == 0) keycode = KEY_E;
	else if (strcmp(str, "f") == 0) keycode = KEY_F;
	else if (strcmp(str, "g") == 0) keycode = KEY_G;
	else if (strcmp(str, "h") == 0) keycode = KEY_H;
	else if (strcmp(str, "i") == 0) keycode = KEY_I;
	else if (strcmp(str, "j") == 0) keycode = KEY_J;
	else if (strcmp(str, "k") == 0) keycode = KEY_K;
	else if (strcmp(str, "l") == 0) keycode = KEY_L;
	else if (strcmp(str, "m") == 0) keycode = KEY_M;
	else if (strcmp(str, "n") == 0) keycode = KEY_N;
	else if (strcmp(str, "o") == 0) keycode = KEY_O;
	else if (strcmp(str, "p") == 0) keycode = KEY_P;
	else if (strcmp(str, "q") == 0) keycode = KEY_Q;
	else if (strcmp(str, "r") == 0) keycode = KEY_R;
	else if (strcmp(str, "s") == 0) keycode = KEY_S;
	else if (strcmp(str, "t") == 0) keycode = KEY_T;
	else if (strcmp(str, "u") == 0) keycode = KEY_U;
	else if (strcmp(str, "v") == 0) keycode = KEY_V;
	else if (strcmp(str, "w") == 0) keycode = KEY_W;
	else if (strcmp(str, "x") == 0) keycode = KEY_X;
	else if (strcmp(str, "y") == 0) keycode = KEY_Y;
	else if (strcmp(str, "z") == 0) keycode = KEY_Z;

	else if (strcmp(str, "1") == 0) keycode = KEY_1;
	else if (strcmp(str, "2") == 0) keycode = KEY_2;
	else if (strcmp(str, "3") == 0) keycode = KEY_3;
	else if (strcmp(str, "4") == 0) keycode = KEY_4;
	else if (strcmp(str, "5") == 0) keycode = KEY_5;
	else if (strcmp(str, "6") == 0) keycode = KEY_6;
	else if (strcmp(str, "7") == 0) keycode = KEY_7;
	else if (strcmp(str, "8") == 0) keycode = KEY_8;
	else if (strcmp(str, "9") == 0) keycode = KEY_9;
	else if (strcmp(str, "0") == 0) keycode = KEY_0;

	else if (strcmp(str, "f1") == 0) keycode = KEY_F1;
	else if (strcmp(str, "f2") == 0) keycode = KEY_F2;
	else if (strcmp(str, "f3") == 0) keycode = KEY_F3;
	else if (strcmp(str, "f4") == 0) keycode = KEY_F4;
	else if (strcmp(str, "f5") == 0) keycode = KEY_F5;
	else if (strcmp(str, "f6") == 0) keycode = KEY_F6;
	else if (strcmp(str, "f7") == 0) keycode = KEY_F7;
	else if (strcmp(str, "f8") == 0) keycode = KEY_F8;
	else if (strcmp(str, "f9") == 0) keycode = KEY_F9;
	else if (strcmp(str, "f10") == 0) keycode = KEY_F10;	

	else if (strcmp(str, "@") == 0) keycode = KEY_2; // with SHIFT
	else if (strcmp(str, "#") == 0) keycode = KEY_3; // with SHIFT
	//else if (strcmp(str, "€") == 0) keycode = KEY_5; // with ALTGR; not ASCII
	else if (strcmp(str, "%") == 0) keycode = KEY_5; // with SHIFT
	else if (strcmp(str, "&") == 0) keycode = KEY_7; // with SHIFT
	else if (strcmp(str, "*") == 0) keycode = KEY_8; // with SHIFT; alternative is KEY_KPASTERISK
	else if (strcmp(str, "-") == 0) keycode = KEY_MINUS; // alternative is KEY_KPMINUS
	else if (strcmp(str, "+") == 0) keycode = KEY_EQUAL; // with SHIFT; alternative is KEY_KPPLUS
	else if (strcmp(str, "(") == 0) keycode = KEY_9; // with SHIFT
	else if (strcmp(str, ")") == 0) keycode = KEY_0; // with SHIFT

	else if (strcmp(str, "!") == 0) keycode = KEY_1; // with SHIFT
	else if (strcmp(str, "\"") == 0) keycode = KEY_APOSTROPHE; // with SHIFT, dead key
	else if (strcmp(str, "\'") == 0) keycode = KEY_APOSTROPHE; // dead key
	else if (strcmp(str, ":") == 0) keycode = KEY_SEMICOLON; // with SHIFT
	else if (strcmp(str, ";") == 0) keycode = KEY_SEMICOLON;
	else if (strcmp(str, "/") == 0) keycode = KEY_SLASH;
	else if (strcmp(str, "?") == 0) keycode = KEY_SLASH; // with SHIFT
	else if (strcmp(str, ".") == 0) keycode = KEY_DOT;
	else if (strcmp(str, ",") == 0) keycode = KEY_COMMA;

	// special chars
	else if (strcmp(str, "~") == 0) keycode = KEY_GRAVE; // with SHIFT, dead key
	else if (strcmp(str, "`") == 0) keycode = KEY_GRAVE; // dead key
	else if (strcmp(str, "|") == 0) keycode = KEY_BACKSLASH; // with SHIFT
	else if (strcmp(str, "{") == 0) keycode = KEY_LEFTBRACE; // with SHIFT
	else if (strcmp(str, "}") == 0) keycode = KEY_RIGHTBRACE; // with SHIFT
	else if (strcmp(str, "$") == 0) keycode = KEY_4; // with SHIFT
	else if (strcmp(str, "^") == 0) keycode = KEY_6; // with SHIFT, dead key
	else if (strcmp(str, "_") == 0) keycode = KEY_MINUS; // with SHIFT
	else if (strcmp(str, "=") == 0) keycode = KEY_EQUAL;
	else if (strcmp(str, "[") == 0) keycode = KEY_LEFTBRACE;
	else if (strcmp(str, "]") == 0) keycode = KEY_RIGHTBRACE;
	else if (strcmp(str, "\\") == 0) keycode = KEY_BACKSLASH;
	else if (strcmp(str, "<") == 0) keycode = KEY_COMMA; // with SHIFT
	else if (strcmp(str, ">") == 0) keycode = KEY_DOT; // with SHIFT

	return keycode;
}

int main(int argc, char* argv[]) {
  char inputstr[100];
  
	// command line arguments
	if (argc == 3) {
      strcpy(quit_command, "kill -9 $(pgrep ");
	  strcat(quit_command, argv[1]);
	  strcat(quit_command, " ) && pkill ogage");

    if (strcmp(argv[2], "anbernic") == 0) {
      back_key = 311;
      start_key = 310;
      a_key = 304;
      b_key = 305;
      x_key = 306;
      y_key = 307;
      up_key = 17;
      down_key = 17;
      left_key = 16;
      right_key = 16;
      l1_key = 308;
      l2_key = 314;
      l3_key = 312;
      r1_key = 309;
      r2_key = 315;
      r3_key = 313;
      deadzone_y = 2100;
      deadzone_x = 1900;
      strcpy(inputstr, "/dev/input/by-path/platform-ff300000.usb-usb-0:1.2:1.0-event-joystick");
    }
	else if (strcmp(argv[2], "oga") == 0) {
      back_key = 704;
      start_key = 709;
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
      l3_key = 705; /*minus key*/
      r1_key = 311;
      r2_key = 313;
      r3_key = 708; /*plus key*/
      deadzone_y = 300;
      deadzone_x = -300;
      strcpy(inputstr, "/dev/input/by-path/platform-odroidgo2-joypad-event-joystick");
	}
	else if (strcmp(argv[2], "rk2020") == 0) {
      back_key = 704;
      start_key = 709;
      a_key = 305;
      b_key = 304;
      x_key = 307;
      y_key = 308;
      up_key = 544;
      down_key = 545;
      left_key = 546;
      right_key = 547;
      l1_key = 310;
      l2_key = 706;
      r1_key = 311;
      r2_key = 707;
      deadzone_y = 300;
      deadzone_x = -300;
      strcpy(inputstr, "/dev/input/by-path/platform-odroidgo2-joypad-event-joystick");
	}
    else if (strcmp(argv[2], "ogs") == 0) {
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
    else if (strcmp(argv[2], "chi") == 0) {
      back_key = 314;
      start_key = 315;
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
      l3_key = 704; /*1 key*/
      r1_key = 311;
      r2_key = 313;
      r3_key = 705; /*2 key*/
      deadzone_y = 300;
      deadzone_x = -300;
      strcpy(inputstr, "/dev/input/by-path/platform-gameforce-gamepad-event-joystick");
    }
    else if (strcmp(argv[2], "rg552") == 0) {
      back_key = 314;
      start_key = 315;    
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
      l3_key = 317; 
      r1_key = 311;
      r2_key = 313;
      r3_key = 318; 
      deadzone_y = 300;
      deadzone_x = -300;
      strcpy(inputstr, "/dev/input/by-path/platform-singleadc-joypad-event-joystick");
    }
    else {
      printf("Error launching, unrecognised parameters\n");
  		exit(0);
		}
  }
  else {
    printf("Error launching, missing required parameters\n");
		exit(0);
	}

	uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (uinp_fd < 0) {
		printf("Unable to open /dev/uinput\n");
		return -1;
	}

	// Intialize the uInput device to NULL
	memset(&uidev, 0, sizeof(uidev));

	strncpy(uidev.name, "AnberPorts Joystick", UINPUT_MAX_NAME_SIZE);
	uidev.id.version = 1;
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor = 0x1234; /* sample vendor */
	uidev.id.product = 0x5678; /* sample product */

	for (int i = 0; i < 256; i++) {
		ioctl(uinp_fd, UI_SET_KEYBIT, i);
	}

	// Keys or Buttons
	ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);

	/* enable mouse button left and relative events */
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_LEFT);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_RIGHT);

	ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);
	ioctl(uinp_fd, UI_SET_RELBIT, REL_X);
	ioctl(uinp_fd, UI_SET_RELBIT, REL_Y);

	// Create input device into input sub-system
	write(uinp_fd, &uidev, sizeof(uidev));

	if (ioctl(uinp_fd, UI_DEV_CREATE)) {
		printf("Unable to create UINPUT device.");
		return -1;
	}

	// parse oga_controls_settings.txt if available
	config_option_t co;
    if ((co = read_config_file("oga_controls_settings.txt")) != NULL) {
	    while(1) {
	    	if (strcmp(co->key, "back") == 0) {
	    		back = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "start") == 0) {
	    		start = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "a") == 0) {
	    		a = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "b") == 0) {
	    		b = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "x") == 0) {
	    		x = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "y") == 0) {
	    		y = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "l1") == 0) {
	    		l1 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "l2") == 0) {
	    		l2 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "l3") == 0) {
	    		l3 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "r1") == 0) {
	    		r1 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "r2") == 0) {
	    		r2 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "r3") == 0) {
	    		r3 = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "up") == 0) {
	    		up = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "down") == 0) {
	    		down = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "left") == 0) {
	    		left = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "right") == 0) {
	    		right = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "left_analog_up") == 0) {
	    		if (strcmp(co->value, "mouse_movement_up") == 0) {
	    			left_analog_mouse = 1;
	    		}
	    		else {
	    			left_analog_up = char_to_keycode(co->value);
	    		}
	    	}
	    	else if (strcmp(co->key, "left_analog_down") == 0) {
	    		left_analog_down = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "left_analog_left") == 0) {
	    		left_analog_left = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "left_analog_right") == 0) {
	    		left_analog_right = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "right_analog_up") == 0) {
	    		if (strcmp(co->value, "mouse_movement_up") == 0) {
	    			right_analog_mouse = 1;
	    		}
	    		else {
	    			right_analog_up = char_to_keycode(co->value);
	    		}
	    	}
	    	else if (strcmp(co->key, "right_analog_down") == 0) {
	    		right_analog_down = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "right_analog_left") == 0) {
	    		right_analog_left = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "right_analog_right") == 0) {
	    		right_analog_right = char_to_keycode(co->value);
	    	}
	    	else if (strcmp(co->key, "deadzone_y") == 0) {
	    		deadzone_y = atoi(co->value);
	    	}
	    	else if (strcmp(co->key, "deadzone_x") == 0) {
	    		deadzone_x = atoi(co->value);
	    	}

	        if (co->prev != NULL) {
	            co = co->prev;
	        } else {
	            break;
	        }
	    }
    }

	fd_ev_joypad = open(inputstr, O_RDONLY|O_NONBLOCK);
	rc_joypad = libevdev_new_from_fd(fd_ev_joypad, &dev_joypad);

	do {
		rc_joypad = libevdev_next_event(dev_joypad, LIBEVDEV_READ_FLAG_NORMAL, &ev_joypad);

		if (rc_joypad == LIBEVDEV_READ_STATUS_SUCCESS) {
           if (strcmp(argv[2], "anbernic") == 0) {
              handle_event_anbernic(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
           else if (strcmp(argv[2], "rk2020") == 0) {
              handle_event_rk2020(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
           else if (strcmp(argv[2], "chi") == 0) {
              handle_event_chi(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
           else if (strcmp(argv[2], "ogs") == 0) {
              handle_event_ogs(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
           else if (strcmp(argv[2], "rg552") == 0) {
              handle_event_rg552(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
           else {
              handle_event_ogx(ev_joypad.type, ev_joypad.code, ev_joypad.value);
           }
		}

		usleep(100);
	} while (rc_joypad == LIBEVDEV_READ_STATUS_SYNC || rc_joypad == LIBEVDEV_READ_STATUS_SUCCESS || rc_joypad == -EAGAIN);

	libevdev_free(dev_joypad);
	close(fd_ev_joypad);

	/*
	* Give userspace some time to read the events before we destroy the
	* device with UI_DEV_DESTROY.
	*/
	sleep(1);

	/* Clean up */
	ioctl(uinp_fd, UI_DEV_DESTROY);
	close(uinp_fd);

	return 0;
}
