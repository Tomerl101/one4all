#include "textbox.h"
#include <iostream>

HANDLE handle;
DWORD fdwSaveOldMode;
VOID ErrorExit(LPSTR);

int main(int argc, char const *argv[])
{

  DWORD cNumRead, fdwMode, i;
  INPUT_RECORD ir;
  DWORD count;
  // Get the standard input handle.
  handle = GetStdHandle(STD_INPUT_HANDLE);
  if (handle == INVALID_HANDLE_VALUE)
    ErrorExit("GetStdHandle");

  // Save the current input mode, to be restored on exit.
  if (!GetConsoleMode(handle, &fdwSaveOldMode))
    ErrorExit("GetConsoleMode");

  // Enable the window and mouse input events.
  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
  SetConsoleMode(handle, fdwMode);
  // ErrorExit("SetConsoleMode");

  TextBox tb(8, 0, 4, "hello");
  tb.draw();

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
      if (ir.EventType == KEY_EVENT)
      {
        // std::cout << "1";
        tb.onKeyboardPress(ir.Event.KeyEvent);
      }
      if (ir.EventType == MOUSE_EVENT)
      {
        tb.onMousePress(ir.Event.MouseEvent);
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
