/*
  [include/Sosage/Utils/enum.h]
  All enums in namespace Sosage.

  ===========================================================================

  This file is part of SOSAGE, released under the MIT License.
  Copyright (c) 2019-present Simon Giraudot

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.

  ===========================================================================

  Author(s): Simon Giraudot <sosage@ptilouk.net>
*/

#ifndef SOSAGE_UTILS_ENUM_H
#define SOSAGE_UTILS_ENUM_H

namespace Sosage
{

enum Status
{
  IDLE,
  CUTSCENE,
  PAUSED,
  LOCKED,
  ACTION_CHOICE,
  INVENTORY_ACTION_CHOICE,
  DIALOG_CHOICE,
  OBJECT_CHOICE,
  IN_INVENTORY,
  IN_MENU,
  IN_WINDOW,
  IN_CODE
};

enum Orientation
{
  COLINEAR,
  CLOCKWISE,
  COUNTERCLOCKWISE
};

enum Button_orientation
{
  UP,
  RIGHT_BUTTON,
  DOWN,
  LEFT_BUTTON,

  UPPER,
  UP_RIGHT,
  DOWN_RIGHT,
  DOWNER,
  DOWN_LEFT,
  UP_LEFT,

  LEFTER,
  RIGHTER,
  LEFT_UP,
  RIGHT_UP,
  LEFT_DOWN,
  RIGHT_DOWN
};


enum Collision_type
{
  PIXEL_PERFECT,
  BOX,
  UNCLICKABLE
};

enum Input_mode
{
  MOUSE,
  TOUCHSCREEN,
  GAMEPAD
};

enum Event_type
{
  EMPTY,
  UNUSED,

  WINDOW,

  MOUSE_DOWN,
  MOUSE_MOVE,
  MOUSE_UP,

  TOUCH_DOWN,
  TOUCH_MOVE,
  TOUCH_UP,

  KEY_DOWN,
  KEY_UP,

  NEW_GAMEPAD,
  GAMEPAD_CHANGED,
  DELETE_GAMEPAD,

  BUTTON_DOWN,
  BUTTON_UP,
  STICK_MOVE
};

enum Event_value
{
  NONE,

  // Window
  EXIT,
  RESIZED,
  BACKGROUND,
  FOREGROUND,

  // Cursor
  LEFT,
  RIGHT,

  // Keys
  ALT,
  CTRL,
  SHIFT,
  TAB,
  ANDROID_BACK,
  ENTER,
  ESCAPE,
  SPACE,
  UP_ARROW,
  LEFT_ARROW,
  RIGHT_ARROW,
  DOWN_ARROW,

  // Controller
  NORTH,
  WEST,
  EAST,
  SOUTH,
  LEFT_SHOULDER,
  RIGHT_SHOULDER,
  START,
  SELECT,

  A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
  F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,

  NUMBER_OF_EVENT_VALUES
};

enum Fast_access_component
{
  CAMERA__POSITION,
  CAMERA__ZOOM,
  CURSOR__POSITION,
  CLOCK__SAVED_TIME,
  CLOCK__DISCOUNTED_TIME,
  CLOCK__TIME,
  CLOCK__LATEST_ACTIVE,
  GAME__DEBUG,
  GAME__STATUS,
  GAME__LOCALE,
  GAME__CURRENT_LOCAL,
  LOADING_SPIN__IMAGE,
  LOADING_SPIN__POSITION,
  INTERFACE__INPUT_MODE,
  STICK__DIRECTION,

  NUMBER_OF_KEYS
};

enum Split_direction
{
  NO_SPLIT,
  BUTTON,
  VERTICALLY,
  HORIZONTALLY
};

}

#endif //  SOSAGE_UTILS_ENUM_H
