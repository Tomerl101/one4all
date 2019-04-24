#include "textbox.h"
#include <iostream>
#include <algorithm>

#define SPACE 32

bool isValidChar(int character);
COORD getCursorPosition();

TextBox::TextBox(short width, short top, short left, std::string value)
    : WIDTH(width), TOP(top), LEFT(left), value(value), HAS_BORDER(true),
      color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      background(0) {}

void TextBox::onKeyboardPress(KEY_EVENT_RECORD &event)
{
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!event.bKeyDown)
    return;

  //add char to the textbox
  if (isValidChar(event.wVirtualKeyCode))
  {
    COORD cursorPos = getCursorPosition();
    auto cursorPosX = cursorPos.X - (LEFT + 1);
    cursorPos.X += 1;

    if (value.length() == (WIDTH - 1))
      return;

    value.insert(cursorPosX, 1, event.uChar.AsciiChar);
    draw();
    SetConsoleCursorPosition(handle, cursorPos);

    return;
  }

  //move cursor when pressing left or right
  if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT)
  {
    int textWidth = value.length();
    COORD cursorPos = getCursorPosition();

    if ((cursorPos.X > LEFT) && (cursorPos.X < WIDTH + LEFT + 1))
    {
      if (event.wVirtualKeyCode == VK_LEFT)
      {
        if (cursorPos.X == LEFT + 1)
          return;
        SetConsoleCursorPosition(handle, {cursorPos.X - 1, cursorPos.Y});
      }

      if (event.wVirtualKeyCode == VK_RIGHT)
      {
        if (cursorPos.X > value.length() + LEFT)
          return;

        if (cursorPos.X == WIDTH + LEFT)
          return;

        SetConsoleCursorPosition(handle, {cursorPos.X + 1, cursorPos.Y});
      }
    }
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

void TextBox::onMousePress(MOUSE_EVENT_RECORD &event)
{
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

  //if left mouse button pressed (if disable then even mouse move will be catched as event)
  if (event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
  {
    // std::cout << "X";
    COORD cursorPos = getCursorPosition();

    auto cursorPosX = cursorPos.X - (LEFT + 1);
    cursorPos.X += 1;

    if (value.length() == (WIDTH - 1))
      return;
    std::cout << (char)(int)cursorPos.Y;
    value.insert(cursorPosX, 1, 'x');
    draw();
    SetConsoleCursorPosition(handle, cursorPos);

    return;
  }
}

void TextBox::draw()
{
  COORD coord = {LEFT, TOP};
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(handle, coord);
  SetConsoleTextAttribute(handle, color | (background << 4));
  COORD originalCursorPos = getCursorPosition();

  //draw textbox border
  std::cout << (char)0xda;
  for (int i = 0; i < WIDTH; i++)
    std::cout << (char)0xc4;
  std::cout << (char)0xbf;

  SetConsoleCursorPosition(handle, {coord.X, coord.Y + 1});
  std::cout << (char)0xb3;

  for (int i = 0; i < WIDTH; i++)
    std::cout << (i <= value.length() ? value[i] : ' ');

  SetConsoleCursorPosition(handle, {LEFT + WIDTH + 1, TOP + 1});
  std::cout << (char)0xb3;

  SetConsoleCursorPosition(handle, {LEFT, TOP + 2});
  std::cout << (char)0xc0;
  for (int i = 0; i < WIDTH; i++)
    std::cout << (char)0xc4;
  std::cout << (char)0xd9;

  SetConsoleCursorPosition(handle, {LEFT + 1 + value.length(), TOP + 1});
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