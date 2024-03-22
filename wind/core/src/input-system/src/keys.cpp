#include "input-system/keys.h"
#include "utils/includes.h"

namespace wind {

#define isEqual(keyAction)  \
  if (action == #keyAction) \
    return keyAction;

KEY_ACTIONS mapStringToKeyAction(std::string action) {
  isEqual(KEY_ACTIONS::RELEASED);
  isEqual(KEY_ACTIONS::PRESSED);
  isEqual(KEY_ACTIONS::HELD);
  isEqual(KEY_ACTIONS::RELEASED);

  return KEY_ACTIONS::RELEASED;
};

KEYCODES mapStringToKeycode(std::string action) {
  isEqual(KEYCODES::KEY_SPACE);
  isEqual(KEYCODES::KEY_APOSTROPHE);
  isEqual(KEYCODES::KEY_COMMA);
  isEqual(KEYCODES::KEY_MINUS);
  isEqual(KEYCODES::KEY_PERIOD);
  isEqual(KEYCODES::KEY_SLASH);
  isEqual(KEYCODES::KEY_0);
  isEqual(KEYCODES::KEY_1);
  isEqual(KEYCODES::KEY_2);
  isEqual(KEYCODES::KEY_3);
  isEqual(KEYCODES::KEY_4);
  isEqual(KEYCODES::KEY_5);
  isEqual(KEYCODES::KEY_6);
  isEqual(KEYCODES::KEY_7);
  isEqual(KEYCODES::KEY_8);
  isEqual(KEYCODES::KEY_9);
  isEqual(KEYCODES::KEY_SEMICOLON);
  isEqual(KEYCODES::KEY_EQUAL);
  isEqual(KEYCODES::KEY_A);
  isEqual(KEYCODES::KEY_B);
  isEqual(KEYCODES::KEY_C);
  isEqual(KEYCODES::KEY_D);
  isEqual(KEYCODES::KEY_E);
  isEqual(KEYCODES::KEY_F);
  isEqual(KEYCODES::KEY_G);
  isEqual(KEYCODES::KEY_H);
  isEqual(KEYCODES::KEY_I);
  isEqual(KEYCODES::KEY_J);
  isEqual(KEYCODES::KEY_K);
  isEqual(KEYCODES::KEY_L);
  isEqual(KEYCODES::KEY_M);
  isEqual(KEYCODES::KEY_N);
  isEqual(KEYCODES::KEY_O);
  isEqual(KEYCODES::KEY_P);
  isEqual(KEYCODES::KEY_Q);
  isEqual(KEYCODES::KEY_R);
  isEqual(KEYCODES::KEY_S);
  isEqual(KEYCODES::KEY_T);
  isEqual(KEYCODES::KEY_U);
  isEqual(KEYCODES::KEY_V);
  isEqual(KEYCODES::KEY_W);
  isEqual(KEYCODES::KEY_X);
  isEqual(KEYCODES::KEY_Y);
  isEqual(KEYCODES::KEY_Z);
  isEqual(KEYCODES::KEY_LEFT_BRACKET);
  isEqual(KEYCODES::KEY_BACKSLASH);
  isEqual(KEYCODES::KEY_RIGHT_BRACKET);
  isEqual(KEYCODES::KEY_GRAVE_ACCENT);
  isEqual(KEYCODES::KEY_WORLD_1);
  isEqual(KEYCODES::KEY_WORLD_2);
  isEqual(KEYCODES::KEY_ESCAPE);
  isEqual(KEYCODES::KEY_ENTER);
  isEqual(KEYCODES::KEY_TAB);
  isEqual(KEYCODES::KEY_BACKSPACE);
  isEqual(KEYCODES::KEY_INSERT);
  isEqual(KEYCODES::KEY_DELETE);
  isEqual(KEYCODES::KEY_RIGHT);
  isEqual(KEYCODES::KEY_LEFT);
  isEqual(KEYCODES::KEY_DOWN);
  isEqual(KEYCODES::KEY_UP);
  isEqual(KEYCODES::KEY_PAGE_UP);
  isEqual(KEYCODES::KEY_PAGE_DOWN);
  isEqual(KEYCODES::KEY_HOME);
  isEqual(KEYCODES::KEY_END);
  isEqual(KEYCODES::KEY_CAPS_LOCK);
  isEqual(KEYCODES::KEY_SCROLL_LOCK);
  isEqual(KEYCODES::KEY_NUM_LOCK);
  isEqual(KEYCODES::KEY_PRINT_SCREEN);
  isEqual(KEYCODES::KEY_PAUSE);
  isEqual(KEYCODES::KEY_F1);
  isEqual(KEYCODES::KEY_F2);
  isEqual(KEYCODES::KEY_F3);
  isEqual(KEYCODES::KEY_F4);
  isEqual(KEYCODES::KEY_F5);
  isEqual(KEYCODES::KEY_F6);
  isEqual(KEYCODES::KEY_F7);
  isEqual(KEYCODES::KEY_F8);
  isEqual(KEYCODES::KEY_F9);
  isEqual(KEYCODES::KEY_F10);
  isEqual(KEYCODES::KEY_F11);
  isEqual(KEYCODES::KEY_F12);
  isEqual(KEYCODES::KEY_F13);
  isEqual(KEYCODES::KEY_F14);
  isEqual(KEYCODES::KEY_F15);
  isEqual(KEYCODES::KEY_F16);
  isEqual(KEYCODES::KEY_F17);
  isEqual(KEYCODES::KEY_F18);
  isEqual(KEYCODES::KEY_F19);
  isEqual(KEYCODES::KEY_F20);
  isEqual(KEYCODES::KEY_F21);
  isEqual(KEYCODES::KEY_F22);
  isEqual(KEYCODES::KEY_F23);
  isEqual(KEYCODES::KEY_F24);
  isEqual(KEYCODES::KEY_F25);
  isEqual(KEYCODES::KEY_KP_0);
  isEqual(KEYCODES::KEY_KP_1);
  isEqual(KEYCODES::KEY_KP_2);
  isEqual(KEYCODES::KEY_KP_3);
  isEqual(KEYCODES::KEY_KP_4);
  isEqual(KEYCODES::KEY_KP_5);
  isEqual(KEYCODES::KEY_KP_6);
  isEqual(KEYCODES::KEY_KP_7);
  isEqual(KEYCODES::KEY_KP_8);
  isEqual(KEYCODES::KEY_KP_9);
  isEqual(KEYCODES::KEY_KP_DECIMAL);
  isEqual(KEYCODES::KEY_KP_DIVIDE);
  isEqual(KEYCODES::KEY_KP_MULTIPLY);
  isEqual(KEYCODES::KEY_KP_SUBTRACT);
  isEqual(KEYCODES::KEY_KP_ADD);
  isEqual(KEYCODES::KEY_KP_ENTER);
  isEqual(KEYCODES::KEY_KP_EQUAL);
  isEqual(KEYCODES::KEY_LEFT_SHIFT);
  isEqual(KEYCODES::KEY_LEFT_CONTROL);
  isEqual(KEYCODES::KEY_LEFT_ALT);
  isEqual(KEYCODES::KEY_LEFT_SUPER);
  isEqual(KEYCODES::KEY_RIGHT_SHIFT);
  isEqual(KEYCODES::KEY_RIGHT_CONTROL);
  isEqual(KEYCODES::KEY_RIGHT_ALT);
  isEqual(KEYCODES::KEY_RIGHT_SUPER);
  isEqual(KEYCODES::KEY_MENU);
  isEqual(KEYCODES::KEY_LAST);
  isEqual(KEYCODES::MOUSE_BUTTON_1);
  isEqual(KEYCODES::MOUSE_BUTTON_2);
  isEqual(KEYCODES::MOUSE_BUTTON_3);
  isEqual(KEYCODES::MOUSE_BUTTON_4);
  isEqual(KEYCODES::MOUSE_BUTTON_5);
  isEqual(KEYCODES::MOUSE_BUTTON_6);
  isEqual(KEYCODES::MOUSE_BUTTON_7);
  isEqual(KEYCODES::MOUSE_BUTTON_8);
  isEqual(KEYCODES::MOUSE_BUTTON_LAST);
  isEqual(KEYCODES::MOUSE_BUTTON_LEFT);
  isEqual(KEYCODES::MOUSE_BUTTON_RIGHT);
  isEqual(KEYCODES::MOUSE_BUTTON_MIDDLE);
  isEqual(KEYCODES::JOYSTICK_1);
  isEqual(KEYCODES::JOYSTICK_2);
  isEqual(KEYCODES::JOYSTICK_3);
  isEqual(KEYCODES::JOYSTICK_4);
  isEqual(KEYCODES::JOYSTICK_5);
  isEqual(KEYCODES::JOYSTICK_6);
  isEqual(KEYCODES::JOYSTICK_7);
  isEqual(KEYCODES::JOYSTICK_8);
  isEqual(KEYCODES::JOYSTICK_9);
  isEqual(KEYCODES::JOYSTICK_10);
  isEqual(KEYCODES::JOYSTICK_11);
  isEqual(KEYCODES::JOYSTICK_12);
  isEqual(KEYCODES::JOYSTICK_13);
  isEqual(KEYCODES::JOYSTICK_14);
  isEqual(KEYCODES::JOYSTICK_15);
  isEqual(KEYCODES::JOYSTICK_16);
  isEqual(KEYCODES::JOYSTICK_LAST);
  isEqual(KEYCODES::GAMEPAD_BUTTON_A);
  isEqual(KEYCODES::GAMEPAD_BUTTON_B);
  isEqual(KEYCODES::GAMEPAD_BUTTON_X);
  isEqual(KEYCODES::GAMEPAD_BUTTON_Y);
  isEqual(KEYCODES::GAMEPAD_BUTTON_LEFT_BUMPER);
  isEqual(KEYCODES::GAMEPAD_BUTTON_RIGHT_BUMPER);
  isEqual(KEYCODES::GAMEPAD_BUTTON_BACK);
  isEqual(KEYCODES::GAMEPAD_BUTTON_START);
  isEqual(KEYCODES::GAMEPAD_BUTTON_GUIDE);
  isEqual(KEYCODES::GAMEPAD_BUTTON_LEFT_THUMB);
  isEqual(KEYCODES::GAMEPAD_BUTTON_RIGHT_THUMB);
  isEqual(KEYCODES::GAMEPAD_BUTTON_DPAD_UP);
  isEqual(KEYCODES::GAMEPAD_BUTTON_DPAD_RIGHT);
  isEqual(KEYCODES::GAMEPAD_BUTTON_DPAD_DOWN);
  isEqual(KEYCODES::GAMEPAD_BUTTON_DPAD_LEFT);
  isEqual(KEYCODES::GAMEPAD_BUTTON_LAST);
  isEqual(KEYCODES::GAMEPAD_BUTTON_CROSS);
  isEqual(KEYCODES::GAMEPAD_BUTTON_CIRCLE);
  isEqual(KEYCODES::GAMEPAD_BUTTON_SQUARE);
  isEqual(KEYCODES::GAMEPAD_BUTTON_TRIANGLE);
  isEqual(KEYCODES::GAMEPAD_AXIS_LEFT_X);
  isEqual(KEYCODES::GAMEPAD_AXIS_LEFT_Y);
  isEqual(KEYCODES::GAMEPAD_AXIS_RIGHT_X);
  isEqual(KEYCODES::GAMEPAD_AXIS_RIGHT_Y);
  isEqual(KEYCODES::GAMEPAD_AXIS_LEFT_TRIGGER);
  isEqual(KEYCODES::GAMEPAD_AXIS_RIGHT_TRIGGER);
  isEqual(KEYCODES::GAMEPAD_AXIS_LAST);
  isEqual(KEYCODES::MOUSE_MOVE);
  isEqual(KEYCODES::MOUSE_SCROLL_DOWN);
  isEqual(KEYCODES::MOUSE_SCROLL_UP);
  isEqual(KEYCODES::MOUSE_SCROLL);
  isEqual(KEYCODES::ALL_KEYBOARD_KEYS);
  isEqual(KEYCODES::ALL_MOUSE_KEYS);
  isEqual(KEYCODES::ALL_MOUSE_EVENTS);
  isEqual(KEYCODES::ALL_EVENTS);
  isEqual(KEYCODES::ALL_KEYBOARD_CHARS);

  return KEYCODES::KEY_UNKNOWN;
}

#undef isEqual

KEY_ACTIONS mapGlfwActionToKeyAction(int action) {
  switch (action) {
  case GLFW_RELEASE:
    return KEY_ACTIONS::RELEASED;
  case GLFW_PRESS:
    return KEY_ACTIONS::PRESSED;
  case GLFW_REPEAT:
    return KEY_ACTIONS::HELD;
  default:
    return KEY_ACTIONS::RELEASED;
  }
};

Key mapGlfwMouseCodeToKey(int glfwKey, int action) {
  switch (glfwKey) {
  case GLFW_MOUSE_BUTTON_1:
    return Key{KEYCODES::MOUSE_BUTTON_1, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_2:
    return Key{KEYCODES::MOUSE_BUTTON_2, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_3:
    return Key{KEYCODES::MOUSE_BUTTON_3, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_4:
    return Key{KEYCODES::MOUSE_BUTTON_4, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_5:
    return Key{KEYCODES::MOUSE_BUTTON_5, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_6:
    return Key{KEYCODES::MOUSE_BUTTON_6, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_7:
    return Key{KEYCODES::MOUSE_BUTTON_7, mapGlfwActionToKeyAction(action)};
  case GLFW_MOUSE_BUTTON_8:
    return Key{KEYCODES::MOUSE_BUTTON_8, mapGlfwActionToKeyAction(action)};
  default:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  }
}

Key mapGlfwJoystickCodeToKey(int glfwKey, int action) {
  switch (glfwKey) {
  case GLFW_JOYSTICK_1:
    return Key{KEYCODES::JOYSTICK_1, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_2:
    return Key{KEYCODES::JOYSTICK_2, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_3:
    return Key{KEYCODES::JOYSTICK_3, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_4:
    return Key{KEYCODES::JOYSTICK_4, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_5:
    return Key{KEYCODES::JOYSTICK_5, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_6:
    return Key{KEYCODES::JOYSTICK_6, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_7:
    return Key{KEYCODES::JOYSTICK_7, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_8:
    return Key{KEYCODES::JOYSTICK_8, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_9:
    return Key{KEYCODES::JOYSTICK_9, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_10:
    return Key{KEYCODES::JOYSTICK_10, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_11:
    return Key{KEYCODES::JOYSTICK_11, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_12:
    return Key{KEYCODES::JOYSTICK_12, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_13:
    return Key{KEYCODES::JOYSTICK_13, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_14:
    return Key{KEYCODES::JOYSTICK_14, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_15:
    return Key{KEYCODES::JOYSTICK_15, mapGlfwActionToKeyAction(action)};
  case GLFW_JOYSTICK_16:
    return Key{KEYCODES::JOYSTICK_16, mapGlfwActionToKeyAction(action)};
  default:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  }
}

Key mapGlfwGamepadButtonCodeToKey(int glfwKey, int action) {
  switch (glfwKey) {
  case GLFW_GAMEPAD_BUTTON_A:
    return Key{KEYCODES::GAMEPAD_BUTTON_A, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_B:
    return Key{KEYCODES::GAMEPAD_BUTTON_B, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_X:
    return Key{KEYCODES::GAMEPAD_BUTTON_X, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_Y:
    return Key{KEYCODES::GAMEPAD_BUTTON_Y, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:
    return Key{KEYCODES::GAMEPAD_BUTTON_LEFT_BUMPER, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:
    return Key{KEYCODES::GAMEPAD_BUTTON_RIGHT_BUMPER, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_BACK:
    return Key{KEYCODES::GAMEPAD_BUTTON_BACK, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_START:
    return Key{KEYCODES::GAMEPAD_BUTTON_START, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_GUIDE:
    return Key{KEYCODES::GAMEPAD_BUTTON_GUIDE, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:
    return Key{KEYCODES::GAMEPAD_BUTTON_LEFT_THUMB, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:
    return Key{KEYCODES::GAMEPAD_BUTTON_RIGHT_THUMB, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_DPAD_UP:
    return Key{KEYCODES::GAMEPAD_BUTTON_DPAD_UP, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:
    return Key{KEYCODES::GAMEPAD_BUTTON_DPAD_RIGHT, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:
    return Key{KEYCODES::GAMEPAD_BUTTON_DPAD_DOWN, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:
    return Key{KEYCODES::GAMEPAD_BUTTON_DPAD_LEFT, mapGlfwActionToKeyAction(action)};
  default:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  }
}

Key mapGlfwGamepadAxisCodeToKey(int glfwKey, int action) {
  switch (glfwKey) {
  case GLFW_GAMEPAD_AXIS_LEFT_X:
    return Key{KEYCODES::GAMEPAD_AXIS_LEFT_X, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_AXIS_LEFT_Y:
    return Key{KEYCODES::GAMEPAD_AXIS_LEFT_Y, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_AXIS_RIGHT_X:
    return Key{KEYCODES::GAMEPAD_AXIS_RIGHT_X, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_AXIS_RIGHT_Y:
    return Key{KEYCODES::GAMEPAD_AXIS_RIGHT_Y, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:
    return Key{KEYCODES::GAMEPAD_AXIS_LEFT_TRIGGER, mapGlfwActionToKeyAction(action)};
  case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:
    return Key{KEYCODES::GAMEPAD_AXIS_RIGHT_TRIGGER, mapGlfwActionToKeyAction(action)};
  default:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  }
}

Key mapGlfwKeyboardCodeToKey(int glfwKey, int action) {
  switch (glfwKey) {
  case GLFW_KEY_UNKNOWN:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_SPACE:
    return Key{KEYCODES::KEY_SPACE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_APOSTROPHE:
    return Key{KEYCODES::KEY_APOSTROPHE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_COMMA:
    return Key{KEYCODES::KEY_COMMA, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_MINUS:
    return Key{KEYCODES::KEY_MINUS, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_PERIOD:
    return Key{KEYCODES::KEY_PERIOD, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_SLASH:
    return Key{KEYCODES::KEY_SLASH, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_0:
    return Key{KEYCODES::KEY_0, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_1:
    return Key{KEYCODES::KEY_1, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_2:
    return Key{KEYCODES::KEY_2, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_3:
    return Key{KEYCODES::KEY_3, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_4:
    return Key{KEYCODES::KEY_4, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_5:
    return Key{KEYCODES::KEY_5, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_6:
    return Key{KEYCODES::KEY_6, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_7:
    return Key{KEYCODES::KEY_7, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_8:
    return Key{KEYCODES::KEY_8, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_9:
    return Key{KEYCODES::KEY_9, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_SEMICOLON:
    return Key{KEYCODES::KEY_SEMICOLON, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_EQUAL:
    return Key{KEYCODES::KEY_EQUAL, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_A:
    return Key{KEYCODES::KEY_A, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_B:
    return Key{KEYCODES::KEY_B, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_C:
    return Key{KEYCODES::KEY_C, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_D:
    return Key{KEYCODES::KEY_D, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_E:
    return Key{KEYCODES::KEY_E, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F:
    return Key{KEYCODES::KEY_F, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_G:
    return Key{KEYCODES::KEY_G, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_H:
    return Key{KEYCODES::KEY_H, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_I:
    return Key{KEYCODES::KEY_I, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_J:
    return Key{KEYCODES::KEY_J, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_K:
    return Key{KEYCODES::KEY_K, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_L:
    return Key{KEYCODES::KEY_L, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_M:
    return Key{KEYCODES::KEY_M, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_N:
    return Key{KEYCODES::KEY_N, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_O:
    return Key{KEYCODES::KEY_O, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_P:
    return Key{KEYCODES::KEY_P, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_Q:
    return Key{KEYCODES::KEY_Q, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_R:
    return Key{KEYCODES::KEY_R, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_S:
    return Key{KEYCODES::KEY_S, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_T:
    return Key{KEYCODES::KEY_T, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_U:
    return Key{KEYCODES::KEY_U, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_V:
    return Key{KEYCODES::KEY_V, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_W:
    return Key{KEYCODES::KEY_W, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_X:
    return Key{KEYCODES::KEY_X, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_Y:
    return Key{KEYCODES::KEY_Y, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_Z:
    return Key{KEYCODES::KEY_Z, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT_BRACKET:
    return Key{KEYCODES::KEY_LEFT_BRACKET, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_BACKSLASH:
    return Key{KEYCODES::KEY_BACKSLASH, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT_BRACKET:
    return Key{KEYCODES::KEY_RIGHT_BRACKET, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_GRAVE_ACCENT:
    return Key{KEYCODES::KEY_GRAVE_ACCENT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_WORLD_1:
    return Key{KEYCODES::KEY_WORLD_1, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_WORLD_2:
    return Key{KEYCODES::KEY_WORLD_2, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_ESCAPE:
    return Key{KEYCODES::KEY_ESCAPE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_ENTER:
    return Key{KEYCODES::KEY_ENTER, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_TAB:
    return Key{KEYCODES::KEY_TAB, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_BACKSPACE:
    return Key{KEYCODES::KEY_BACKSPACE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_INSERT:
    return Key{KEYCODES::KEY_INSERT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_DELETE:
    return Key{KEYCODES::KEY_DELETE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT:
    return Key{KEYCODES::KEY_RIGHT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT:
    return Key{KEYCODES::KEY_LEFT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_DOWN:
    return Key{KEYCODES::KEY_DOWN, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_UP:
    return Key{KEYCODES::KEY_UP, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_PAGE_UP:
    return Key{KEYCODES::KEY_PAGE_UP, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_PAGE_DOWN:
    return Key{KEYCODES::KEY_PAGE_DOWN, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_HOME:
    return Key{KEYCODES::KEY_HOME, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_END:
    return Key{KEYCODES::KEY_END, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_CAPS_LOCK:
    return Key{KEYCODES::KEY_CAPS_LOCK, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_SCROLL_LOCK:
    return Key{KEYCODES::KEY_SCROLL_LOCK, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_NUM_LOCK:
    return Key{KEYCODES::KEY_NUM_LOCK, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_PRINT_SCREEN:
    return Key{KEYCODES::KEY_PRINT_SCREEN, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_PAUSE:
    return Key{KEYCODES::KEY_PAUSE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F1:
    return Key{KEYCODES::KEY_F1, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F2:
    return Key{KEYCODES::KEY_F2, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F3:
    return Key{KEYCODES::KEY_F3, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F4:
    return Key{KEYCODES::KEY_F4, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F5:
    return Key{KEYCODES::KEY_F5, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F6:
    return Key{KEYCODES::KEY_F6, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F7:
    return Key{KEYCODES::KEY_F7, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F8:
    return Key{KEYCODES::KEY_F8, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F9:
    return Key{KEYCODES::KEY_F9, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F10:
    return Key{KEYCODES::KEY_F10, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F11:
    return Key{KEYCODES::KEY_F11, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F12:
    return Key{KEYCODES::KEY_F12, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F13:
    return Key{KEYCODES::KEY_F13, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F14:
    return Key{KEYCODES::KEY_F14, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F15:
    return Key{KEYCODES::KEY_F15, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F16:
    return Key{KEYCODES::KEY_F16, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F17:
    return Key{KEYCODES::KEY_F17, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F18:
    return Key{KEYCODES::KEY_F18, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F19:
    return Key{KEYCODES::KEY_F19, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F20:
    return Key{KEYCODES::KEY_F20, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F21:
    return Key{KEYCODES::KEY_F21, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F22:
    return Key{KEYCODES::KEY_F22, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F23:
    return Key{KEYCODES::KEY_F23, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F24:
    return Key{KEYCODES::KEY_F24, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_F25:
    return Key{KEYCODES::KEY_F25, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_0:
    return Key{KEYCODES::KEY_KP_0, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_1:
    return Key{KEYCODES::KEY_KP_1, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_2:
    return Key{KEYCODES::KEY_KP_2, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_3:
    return Key{KEYCODES::KEY_KP_3, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_4:
    return Key{KEYCODES::KEY_KP_4, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_5:
    return Key{KEYCODES::KEY_KP_5, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_6:
    return Key{KEYCODES::KEY_KP_6, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_7:
    return Key{KEYCODES::KEY_KP_7, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_8:
    return Key{KEYCODES::KEY_KP_8, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_9:
    return Key{KEYCODES::KEY_KP_9, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_DECIMAL:
    return Key{KEYCODES::KEY_KP_DECIMAL, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_DIVIDE:
    return Key{KEYCODES::KEY_KP_DIVIDE, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_MULTIPLY:
    return Key{KEYCODES::KEY_KP_MULTIPLY, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_SUBTRACT:
    return Key{KEYCODES::KEY_KP_SUBTRACT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_ADD:
    return Key{KEYCODES::KEY_KP_ADD, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_ENTER:
    return Key{KEYCODES::KEY_KP_ENTER, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_KP_EQUAL:
    return Key{KEYCODES::KEY_KP_EQUAL, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT_SHIFT:
    return Key{KEYCODES::KEY_LEFT_SHIFT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT_CONTROL:
    return Key{KEYCODES::KEY_LEFT_CONTROL, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT_ALT:
    return Key{KEYCODES::KEY_LEFT_ALT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_LEFT_SUPER:
    return Key{KEYCODES::KEY_LEFT_SUPER, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT_SHIFT:
    return Key{KEYCODES::KEY_RIGHT_SHIFT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT_CONTROL:
    return Key{KEYCODES::KEY_RIGHT_CONTROL, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT_ALT:
    return Key{KEYCODES::KEY_RIGHT_ALT, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_RIGHT_SUPER:
    return Key{KEYCODES::KEY_RIGHT_SUPER, mapGlfwActionToKeyAction(action)};
  case GLFW_KEY_MENU:
    return Key{KEYCODES::KEY_MENU, mapGlfwActionToKeyAction(action)};
  default:
    return Key{KEYCODES::KEY_UNKNOWN, mapGlfwActionToKeyAction(action)};
  }
}
} // namespace wind
