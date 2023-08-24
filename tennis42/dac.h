#pragma once
#include <Wire.h> //Include the Wire library to talk I2C

#define MCP4725_CMD_WRITEDAC 0x40    ///< Writes data to the DAC
#define MCP4725_CMD_WRITEDACEEPROM 0x60 ///< Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

/**
 *  Wire should be initialized to use this class (just call Wire.begin() in setup() function)
 */
class DAC {

public:

  DAC(int addr) :
    _addr(addr)
  {}

  setValue(int val)
  {
    Wire.beginTransmission(_addr);
    Wire.write(MCP4725_CMD_WRITEDAC); // cmd to update the DAC
    Wire.write(val >> 4);        // the 8 most significant bits...
    Wire.write((val & 15) << 4); // the 4 least significant bits...
    Wire.endTransmission();
  }

private:
  int _addr;
};
