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

#include "main.h"
#include "parser.h"
#include "devices/rg552.h"
#include "devices/chi.h"
#include "devices/ogs.h"
#include "devices/ogx.h"
#include "devices/rk2020.h"
#include "devices/anbernic.h"
#include "devices/rgb10_max.h"

#include <stdbool.h>

#ifdef TESTING_LAG
#include <sys/time.h>
#endif

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

bool startsWith(const char* _string, const char* _start) {
  return (strstr(_string, _start) - _string) == 0;
}

bool endsWith(const char* _string, const char*_end) {
  int blen = strlen(_string);
  int slen = strlen(_end);
  return (blen >= slen) && (0 == strcmp(_string + blen - slen, _end));
}

void configDevice(const char* device, char *inputstr) {

    if (strcmp(device, "anbernic") == 0) {
      config_anbernic(inputstr);
    }
    else if (strcmp(device, "oga") == 0) {
      config_ogx(inputstr);
    }
    else if (strcmp(device, "rk2020") == 0) {
      config_rk2020(inputstr);
    }
    else if (strcmp(device, "ogs") == 0) {
      config_ogs(inputstr);
    }
    else if (strcmp(device, "chi") == 0) {
      config_chi(inputstr);
    }
    else if (strcmp(device, "rg552") == 0) {
      config_rg552(inputstr);
    }
    else if (startsWith(device, "rgb10max") && endsWith(device, "top")) {
      config_rgb10max_top(inputstr);
    }
    else if (startsWith(device, "rgb10max") && endsWith(device, "native")) {
      config_rgb10max_native(inputstr);
    }
    else {
      printf("Error launching, unrecognised parameters\n");
      exit(0);
    }
}

int main(int argc, char* argv[]) {

#ifdef DEBUG
  printf("OGA Contols - Configuration - device: %s, App To Kill: %s\n", argv[2], argv[1]);
#endif

  char inputstr[100];

  // command line arguments
  if (argc == 3) {
    strcpy(quit_command, "kill -9 $(pgrep ");
    strcat(quit_command, argv[1]);
    strcat(quit_command, " )");

    configDevice(argv[2], &inputstr[0]);
  }
  else {
    printf("Error launching, missing required parameters\n");
    exit(0);
  }

#ifdef DEBUG
  printf("OGA Contols - Input device: %s\n", inputstr);
#endif

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

#ifdef TESTING_LAG
    struct timeval st, et;
    gettimeofday(&st,NULL);
    bool is_valid_event = (ev_joypad.type == 1);
#endif

    if (rc_joypad == LIBEVDEV_READ_STATUS_SUCCESS) {
      handleEventFunction(ev_joypad.type, ev_joypad.code, ev_joypad.value);
    }

#ifdef TESTING_LAG
    if (is_valid_event) {
      gettimeofday(&et,NULL);
      int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
      printf("OGA Contols - Event elapsed time: %d microseconds\n", elapsed);
    }
#endif
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
