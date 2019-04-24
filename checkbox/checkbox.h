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
  void toggle();
  void draw();
};