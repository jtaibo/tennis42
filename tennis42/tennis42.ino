#include "display.h"
#include "mathutils.h"

Display display;

Vec2f ballPos;
Vec2f ballSpeed;
float gravity;
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
  lastTime = millis();
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
  display.setNormalizedPosition(ballPos.x, ballPos.y);
}

/**
 * 
 */
void loop()
{
  updatePhysics();
}
