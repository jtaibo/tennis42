#include <Wire.h>//Include the Wire library to talk I2C

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0. 
//For devices with A0 pulled HIGH, use 0x61
#define MCP4725_ADDR1 0x60
#define MCP4725_ADDR2 0x61

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

Vec2f ballPos;
Vec2f ballSpeed;
float gravity;
Vec2i screenSize;
unsigned long lastTime;

/**
 * 
 */
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  
  ballPos.set(0., 1.);
  ballSpeed.set(1., 0.);
  gravity = -9.8;
  screenSize.set(4095, 4095); // Set screen size to DAC resolution (12-bit = 0-4095)
  lastTime = millis();
}

/**
 * 
 */
void setDACValue(int addr, int val)
{
  Wire.beginTransmission(addr);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(val >> 4);        // the 8 most significant bits...
  Wire.write((val & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
}

/**
 * 
 */
void setPosition(int x, int y)
{
  setDACValue(MCP4725_ADDR1, x);
  setDACValue(MCP4725_ADDR2, y);
}

void updatePhysics()
{
  unsigned long now = millis();
  float delta_t = (now - lastTime) / 1000.;
  lastTime = now;
  
  // Update ball position
  ballPos.x += ballSpeed.x * delta_t;
  ballPos.y += ballSpeed.y * delta_t;
  if ( ballSpeed.y < 0. && ballPos.y <= 0. ) {
    // Ground reached. Bounce!
    ballSpeed.y = -ballSpeed.y;
  }
  if ( ballSpeed.x > 0 && ballPos.x >= 1.0 ) {
    ballSpeed.x = -ballSpeed.x;
  }
  else if ( ballSpeed.x < 0 && ballPos.x <= 0.0 ) {
    ballSpeed.x = -ballSpeed.x;
  }
  ballSpeed.y += gravity * delta_t;
  // Draw ball in screen space
#define CLAMP(v) ((v>1.0)?1.0:((v<.0)?0:v))
  setPosition(CLAMP(ballPos.x)*screenSize.x, CLAMP(ballPos.y)*screenSize.y);
}

/**
 * 
 */
void loop()
{
  updatePhysics();
}
