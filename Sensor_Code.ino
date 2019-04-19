
/*
Function calls in this file
Cliff_Sensor_Read(int, int)
Sensor_Read()
int getSensorAngle()
int getHingeAngle
int Normalize
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
int getSensorAngle(int AXLNumber){

	int angle = 13;
	int angle2 = 13;
	int anglea = 13;
	if(AXLNumber == 1){	
		if(axl1.z < 0){
			if(axl1.y < 0){ //--
				angle = (axl1.y)/(AXBX/90);
				angle2 = -90+(axl1.z)/(AXBN/90);
				anglea = (angle+angle2)/2;
				return anglea;        
			}
			else { //+-
				angle = (-axl1.y)/(AXBN/90);
				angle2 = 90-(axl1.z)/(AXBN/90);
				anglea = (angle+angle2)/2;
				return anglea;
			}
		} 
		else {
			if(axl1.y < 0){ //-+
				angle = -180-(axl1.y)/(AXBX/90);
				angle2 = -90-(axl1.z)/(AXBX/90);
				anglea = (angle+angle2)/2;
				return anglea;
			
			} 
			else { //++
				angle = 180+(axl1.y)/(AXBN/90);
				angle2 = 90+(axl1.z)/(AXBX/90);
				anglea = (angle+angle2)/2;
				return anglea;
			}
		}
	}
		else {
		  
			if(axl2.z < 0){
				if(axl2.y < 0){ //--
					angle = (axl2.y)/(AXTX/90);
					angle2 = -90+(axl2.z)/(AXTN/90);
					anglea = (angle+angle2)/2;
					return anglea;
				}
				else { //+-
					angle = (-axl2.y)/(AXTN/90);
					angle2 = 90-(axl2.z)/(AXTN/90);
					anglea = (angle+angle2)/2;
					return anglea;
				}		
			}
		
		else {
			if(axl2.y < 0){ //-+
				angle = -180-(axl2.y)/(AXTX/90);
				angle2 = -90-(axl2.z)/(AXTX/90);
				anglea = (angle+angle2)/2;
				return anglea;
			} 
			else { //++
				angle = 180+(axl2.y)/(AXTN/90);
				angle2 = 90+(axl2.z)/(AXTX/90);
				anglea = (angle+angle2)/2;
				return anglea;
			}
		}
	}
}

int getHingeAngle(void){ //returns a number

	int angle = 180+(BufferOut[8]-BufferOut[7]);

	// Serial.print(axl2.y);
	// Serial.print("  ,  ");
	// Serial.print(axl2.z);
	// Serial.print(getSensorAngle(1));
	// Serial.print("  ,  ");
	// Serial.print(getSensorAngle(2));
	// Serial.print("  ,  ");
	// Serial.println(angle);
	return angle;
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
