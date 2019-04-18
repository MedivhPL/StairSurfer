#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

void AXLSetup(void){
  Serial.println("End of Setup");
  if(!axl1.begin(0x18)){
  Serial.println("Could not start front AXL");
  }
  if(!axl2.begin(0x19)){
  Serial.println("Could not start back AXL");
  }
  axl1.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!
  axl2.setRange(LIS3DH_RANGE_16_G);
  Serial.println("AXL SETUP COMPLETE");

}
