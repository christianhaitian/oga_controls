
#ifndef MAIN_HEADER
#define MAIN_HEADER

typedef void (*function_type)(int, int, int);
static function_type handleEventFunction;

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
short a = KEY_V;
short b = KEY_C;
short x = KEY_X;
short y = KEY_A;
short l1 = KEY_B;
short l2 = KEY_R;
short l3 = BTN_LEFT;
short r1 = KEY_D;
short r2 = KEY_S;
short r3 = BTN_RIGHT;
short up = KEY_UP;
short down = KEY_DOWN;
short left = KEY_LEFT;
short right = KEY_RIGHT;
short left_analog_up = KEY_UP;
short left_analog_down = KEY_DOWN;
short left_analog_left = KEY_LEFT;
short left_analog_right = KEY_RIGHT;
short right_analog_up = KEY_UP;
short right_analog_down = KEY_DOWN;
short right_analog_left = KEY_LEFT;
short right_analog_right = KEY_RIGHT;

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


void handleKillApplication() {
  system(quit_command);
  system("sleep 0.2");
  exit (0);
}

#endif /* !MAIN_HEADER */
