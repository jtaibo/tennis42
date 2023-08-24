#pragma once
#include "dac.h"
#include "pinout.h"
#include "mathutils.h"

class Display {
public:

  Display() :
    _dacX(MCP4725_ADDR1),
    _dacY(MCP4725_ADDR2)
  {
    _screenSize.set(4095, 4095); // Set screen size to DAC resolution (12-bit = 0-4095)
  }

  void setNormalizedPosition(float x, float y)
  {
    setPosition(CLAMP(x)*_screenSize.x, CLAMP(y)*_screenSize.y);
  }

private:

  DAC _dacX;
  DAC _dacY;

  Vec2i _screenSize;

  setPosition(int x, int y)
  {
    _dacX.setValue(x);
    _dacY.setValue(y);
  }

};
