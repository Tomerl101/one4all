#include <string>
#include <windows.h>

class checkbox
{
public:
  const short TOP;
  const short LEFT;
  const WORD color;
  const WORD background;
  bool isFilled;
  std::string value;

  checkbox(short top, short left, std::string value);
  void onKeyboardPress(KEY_EVENT_RECORD &);
  void onMousePress(MOUSE_EVENT_RECORD &);
  void draw();

private:
  void putChar();
  //void removeChar();
  //void moveCursor();
};