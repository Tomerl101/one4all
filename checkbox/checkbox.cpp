#include "checkbox.h"
#include <iostream>
#include <algorithm>

#define SPACE 32

COORD getCursorPosition();

checkbox::checkbox(short top, short left, std::string value)
    : TOP(top), LEFT(left), value(value), isFilled(false),
      color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      background(0) {}

void checkbox::toggle()
{
  isFilled = !isFilled;
  draw();
}

void checkbox::draw()
{
  COORD originalCursorPos = getCursorPosition();
  COORD coord = {LEFT, TOP};
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(handle, coord);
  SetConsoleTextAttribute(handle, color | (background << 4));

  //draw
  if (isFilled)
    std::cout << "* " + value << std::endl;
  else
    std::cout << "o " + value << std::endl;

  SetConsoleCursorPosition(handle, originalCursorPos);
}

//e.g {x:3, y:6}
COORD getCursorPosition()
{
  CONSOLE_SCREEN_BUFFER_INFO info;
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(handle, &info);
  return info.dwCursorPosition;
}