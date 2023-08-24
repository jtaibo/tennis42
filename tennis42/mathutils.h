#pragma once

#define CLAMP(v) ((v>1.0)?1.0:((v<.0)?0:v))

struct Vec2i {
  int x;
  int y;
  void set(int x_, int y_)
  {
    x = x_;
    y = y_;
  }
};

struct Vec2f {
  float x;
  float y;
  void set(float x_, float y_)
  {
    x = x_;
    y = y_;
  }
};

