#include "checkbox.h"
#include <iostream>
#include <algorithm>

#define SPACE 32

bool isValidChar(int character);
COORD getCursorPosition();

checkbox::checkbox(short top, short left, std::string value)
    : TOP(top), LEFT(left), value(value), isFilled(false),
      color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      background(0) {}

void checkbox::onKeyboardPress(KEY_EVENT_RECORD &event)
{
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!event.bKeyDown)
    return;

  //add char to the textbox
  if (event.wVirtualKeyCode == SPACE)
  {
    isFilled = !isFilled;
    draw();

    return;
  }

  //move cursor when pressing left or right
  if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT)
  {
    int textWidth = value.length();
    COORD cursorPos = getCursorPosition();
  }
  //delete char from textbox
  if (event.wVirtualKeyCode == VK_BACK)
  {
    COORD cursorPos = getCursorPosition();
    auto cursorPosX = cursorPos.X - (LEFT + 1);
    cursorPos.X -= 1;

    if (value.length() == 0)
    {
      return;
    }

    if (cursorPosX == 0)
    {
      return;
    }

    value.erase(cursorPosX - 1, 1);
    draw();
    SetConsoleCursorPosition(handle, cursorPos);
  }
}

void checkbox::onMousePress(MOUSE_EVENT_RECORD &event)
{
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

  //if left mouse button pressed (if disable then even mouse move will be catched as event)
  if (event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
  {
    // std::cout << "X";
    COORD cursorPos = getCursorPosition();

    auto cursorPosX = cursorPos.X - (LEFT + 1);
    cursorPos.X += 1;

    std::cout << (char)(int)cursorPos.Y;
    value.insert(cursorPosX, 1, 'x');
    draw();
    SetConsoleCursorPosition(handle, cursorPos);

    return;
  }
}

void checkbox::draw()
{
  COORD coord = {LEFT, TOP};
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(handle, coord);
  SetConsoleTextAttribute(handle, color | (background << 4));
  COORD originalCursorPos = getCursorPosition();

  //draw
  if (isFilled)
    std::cout << "* " + value << std::endl;
  else
    std::cout << "o " + value << std::endl;

  SetConsoleCursorPosition(handle, originalCursorPos);
}

bool isValidChar(int character)
{
  if ((character >= 0x30) && (character <= 0x5a))
  {
    return true;
  }

  if (character == SPACE)
  {
    return true;
  }

  return false;
}

//e.g {x:3, y:6}
COORD getCursorPosition()
{
  CONSOLE_SCREEN_BUFFER_INFO info;
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(handle, &info);
  return info.dwCursorPosition;
}