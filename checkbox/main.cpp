#include "checkbox.h"
#include <iostream>
#define SPACE 32

HANDLE handle;
DWORD fdwSaveOldMode;
VOID ErrorExit(LPSTR);
COORD getCursorPosition();

int main(int argc, char const *argv[])
{

  DWORD cNumRead, fdwMode, i;
  INPUT_RECORD ir;
  DWORD count;
  // Get the standard input handle.
  handle = GetStdHandle(STD_INPUT_HANDLE);
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

  if (handle == INVALID_HANDLE_VALUE)
    ErrorExit("GetStdHandle");

  // Save the current input mode, to be restored on exit.
  if (!GetConsoleMode(handle, &fdwSaveOldMode))
    ErrorExit("GetConsoleMode");

  // Enable the window and mouse input events.
  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
  SetConsoleMode(handle, fdwMode);
  // ErrorExit("SetConsoleMode");

  checkbox tb1(2, 2, "eat");
  checkbox tb2(6, 2, "work");
  checkbox tb3(10, 2, "sdsdsd");
  tb1.draw();
  tb2.draw();
  tb3.draw();

  SetConsoleCursorPosition(output, {2, 2});

  while (1)
  {

    if (!ReadConsoleInput(
            handle,  // input buffer handle
            &ir,     // buffer to read into
            1,       // size of read buffer
            &count)) // number of records read
      ErrorExit("ReadConsoleInput");

    // ReadConsoleInput(handle, &ir, 1, &count);
    if (count)
    {
      if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
      {
        COORD cursorPos = getCursorPosition();
        switch (ir.Event.KeyEvent.wVirtualKeyCode)
        {
        case VK_SPACE:

          break;
        case VK_DOWN:
          if (cursorPos.Y == 10)
            break;
          SetConsoleCursorPosition(output, {cursorPos.X, cursorPos.Y + 4});
          break;
        case VK_UP:
          if (cursorPos.Y == 2)
            break;
          SetConsoleCursorPosition(output, {cursorPos.X, cursorPos.Y - 4});
          break;
        }
        tb1.onKeyboardPress(ir.Event.KeyEvent);
      }
      if (ir.EventType == MOUSE_EVENT)
      {
        tb1.onMousePress(ir.Event.MouseEvent);
      }
    }
  }

  SetConsoleMode(handle, fdwSaveOldMode);
  return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
  fprintf(stderr, "%s\n", lpszMessage);

  // Restore input mode on exit.
  SetConsoleMode(handle, fdwSaveOldMode);

  ExitProcess(0);
}

// COORD getCursorPosition()
// {
//   CONSOLE_SCREEN_BUFFER_INFO info;
//   auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
//   GetConsoleScreenBufferInfo(handle, &info);
//   return info.dwCursorPosition;
// }