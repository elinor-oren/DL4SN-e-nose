#include "DFRobot_MICS.h"

#define CALIBRATION_TIME   1  // Default calibration time is three minutes

// When using I2C communication, use the following program to construct an object by DFRobot_MICS_I2C

// I2C slave addresses for DFRobot_MICS_I2C:
// ADDRESS_0: 0x75  // I2C device address
// ADDRESS_1: 0x76
// ADDRESS_2: 0x77
// ADDRESS_3: 0x78  // Used in this setup

#define Mics_I2C_ADDRESS ADDRESS_0
DFRobot_MICS_I2C mics(&Wire, 0x75);

void setup() 
{
  Serial.begin(115200);
  while(!Serial);  // Wait for the serial port to connect
  while(!mics.begin()){
    Serial.println("NO Devices !");
    delay(1000);
  } 
  Serial.println("Device connected successfully !");

  // Get the power mode of the sensor
  uint8_t mode = mics.getPowerState();
  if(mode == SLEEP_MODE){
    mics.wakeUpMode();
    Serial.println("Wake up sensor success!");
  }else{
    Serial.println("The sensor is in wake up mode");
  }

  // Preheating the sensor, do not touch the sensor probe during this time
  while(!mics.warmUpTime(CALIBRATION_TIME)){
    Serial.println("Warming up...");
    delay(1000);
  }
}

void loop() 
{
  // Read and print each gas concentration
  float ch4 = mics.getGasData(CH4);
  Serial.print("Methane CH4: ");
  Serial.print(ch4);
  Serial.println(" PPM");

  float c2h5oh = mics.getGasData(C2H5OH);
  Serial.print("Ethanol C2H5OH: ");
  Serial.print(c2h5oh);
  Serial.println(" PPM");

  float h2 = mics.getGasData(H2);
  Serial.print("Hydrogen H2: ");
  Serial.print(h2);
  Serial.println(" PPM");

  float nh3 = mics.getGasData(NH3);
  Serial.print("Ammonia NH3: ");
  Serial.print(nh3);
  Serial.println(" PPM");

  float co = mics.getGasData(CO);
  Serial.print("Carbon Monoxide CO: ");
  Serial.print(co);
  Serial.println(" PPM");

  float no2 = mics.getGasData(NO2);
  Serial.print("Nitrogen Dioxide NO2: ");
  Serial.print(no2);
  Serial.println(" PPM");
  
  delay(1000);  // Delay for a second before the next read
}
