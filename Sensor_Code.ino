
/*
Function calls in this file


*/
bool Cliff_Sensor_Read(int pinNumber,int threshold){
  //reads analog signal from sensorPin
  return analogRead(pinNumber) < threshold;
}
void Sensor_Read(void){
  static int sensor_buffer_wr = 0;
  int sum = 0;
  axl1.read();
  axl2.read();
  SensorMeasurements[0][sensor_buffer_wr] = analogRead(CSL); //clif left  Max = 789, Min = 503
  SensorMeasurements[1][sensor_buffer_wr] = analogRead(CSR); //cliff right
  SensorMeasurements[2][sensor_buffer_wr] = analogRead(DSF); //forward  Max = 637, Min = 177
  SensorMeasurements[3][sensor_buffer_wr] = analogRead(DSTF); //top front Max = 650, Min = 43
  SensorMeasurements[4][sensor_buffer_wr] = analogRead(DSTB); //top back Max = 537, Min = 58
  SensorMeasurements[5][sensor_buffer_wr] = analogRead(DSBL); //back left Max = 735, Min = 53
  SensorMeasurements[6][sensor_buffer_wr] = analogRead(DSBR); //back right Max = 671, Min = 52
  SensorMeasurements[7][sensor_buffer_wr] = getSensorAngle(1);  //Accelerator bottomhalf
  SensorMeasurements[8][sensor_buffer_wr] = getSensorAngle(2);  //Accelerator tophalf
  SensorMeasurements[9][sensor_buffer_wr] = getHingeAngle();
  
  if(++sensor_buffer_wr >= SIZE_OF_BUFFER){
    sensor_buffer_wr = 0;
  }
  //buffer for measurements
  for(int i = 0; i < SENSOR_AMOUNT;i++){
    for(int j = 0;j < SIZE_OF_BUFFER;j++){
      sum+=SensorMeasurements[i][j];
      }
    BufferOut[i] = sum/SIZE_OF_BUFFER;
    sum = 0;
  }
}


int getHingeAngle(void){ //returns a number between 90 and 270
  return getSensorAngle(1)+getSensorAngle(2)+180;
}

int getSensorAngle(int AXLNumber){
  if(AXLNumber == 1){
    if(axl1.z < 0) return (axl1.y > 0) ? (axl1.y)/182 : (axl1.y)/182 ; //True True: 0->90 //True False: -90->0
    return (axl1.y > 0) ? 180-((axl1.y)/182) : (-(axl1.y)/182)-180 ; //False True: 90->180  //False False: -90->-180
  } else {
    if(axl2.z < 0) return (axl2.y > 0) ? (axl2.y)/182 : (axl2.y)/182 ; //True True: 0->90 //True False: -90->0
    return (axl2.y > 0) ? 180-((axl2.y)/182) : (-(axl2.y)/182)-180 ; //False True: 90->180  //False False: -90->-180
  }
}



int Normalize(int buffer, int max, int min){
  double sum;
  sum = buffer - min;
  //Serial.print(sum);Serial.print(", ");
  sum *=100;
  //Serial.print(sum);Serial.print(", ");
  sum /=(max-min);
  //Serial.print(sum);Serial.println(", ");
  return sum;
}
