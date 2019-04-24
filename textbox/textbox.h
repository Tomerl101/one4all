#include <string>
#include <windows.h>

class TextBox
{
public:
  const short WIDTH;
  const short TOP;
  const short LEFT;
  const bool HAS_BORDER;
  const WORD color;
  const WORD background;

  std::string value;
  TextBox(short width, short top, short left, std::string value);
  void onKeyboardPress(KEY_EVENT_RECORD &);
  void onMousePress(MOUSE_EVENT_RECORD &);
  void draw();

private:
  void putChar();
  //void removeChar();
  //void moveCursor();
};