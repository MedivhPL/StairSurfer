#define SIZE_OF_BUFFER 10

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
	SensorMeasurements[0][sensor_buffer_wr] = analogRead(CSL); //clif left
	SensorMeasurements[1][sensor_buffer_wr] = analogRead(CSR); //cliff right
	SensorMeasurements[2][sensor_buffer_wr] = analogRead(DSF); //forward
	SensorMeasurements[3][sensor_buffer_wr] = analogRead(DSTF); //top front
	SensorMeasurements[4][sensor_buffer_wr] = analogRead(DSTB); //top back
	SensorMeasurements[5][sensor_buffer_wr] = analogRead(DSBL); //back left
	SensorMeasurements[6][sensor_buffer_wr] = analogRead(DSBR); //back right
	
	if(++sensor_buffer_wr >= SIZE_OF_BUFFER){
		sensor_buffer_wr = 0;
	}
	//buffer for measurements
	for(int i = 0; i < 7;i++){
		for(int j = 0;j < SIZE_OF_BUFFER;j++){
			sum+=SensorMeasurements[i][j];
			}
		BufferOut[i] = sum/SIZE_OF_BUFFER;
		sum = 0;
	}
}
int Angle_Mapper(char axis){
	//map -35k to 35k to -180.00 to 180.00
	//return map(axis,-35k,35k,-180,180);
	return 1;
}

int Angle_Calculator( void){
	//get XYZ map from TOP
	//get XYZ map from BOT
	//(BOT - TOP) + 180
	// return that ^
	return 1;
	
}
int Normalize(int buffer, int max, int min){
	return (buffer - min)*100/(max - min);
	
}
