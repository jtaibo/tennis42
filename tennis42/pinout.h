#pragma once

#define PLAYER1_POT A0
#define PLAYER1_BUTTON 7
#define PLAYER2_POT A1
#define PLAYER2_BUTTON 8

// WARNING: DACs are using I2C bus: Arduino Uno pins A4 and A5

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0. 
//For devices with A0 pulled HIGH, use 0x61
#define MCP4725_ADDR1 0x60
#define MCP4725_ADDR2 0x61
