// // Macros for alligning
// #define ALIGNED 0
// #define ADJUST_DIR 1
// #define HINGE 2
// //Macros for hinge movement
// #define DOWN 0
// #define GOFORWARD 1
// #define CHECK_SENSORS 2
// #define HINGE_DOWN_ONCE 3
// #define UP 4
// #define CHECK_STEPS 5
// #define STOP 6
void hingeToAngle(int angle){
	static int error, error_previous, kp, kd, ki,c_out;
	static int integral;
	//Serial.println(angle);
	if (angle > 270) angle = 270;
	if (angle < 150) angle = 150;
	
	error = angle - BufferOut[9];
	kp = 5 * error;
	kd = 5 * (error - error_previous);
	integral += (error + error_previous)/2;
	// Serial.print("int = ");Serial.print(integral);

	ki = .1 * (integral);
	c_out = kp + kd + ki;
	if (c_out <= 60 && c_out >= -60) c_out = 0;
	if (c_out > 120) c_out = 120;
	if (c_out < -120) c_out = -120;
	Hinge(c_out);
	if(integral > 500)integral = 500;
	if(integral < -500)integral = -500;
	// Serial.print("kp = ");Serial.print(kp);
	// Serial.print("kd = ");Serial.print(kd);
	// Serial.print("ki = ");Serial.print(ki);
	// Serial.print("int = ");Serial.print(integral);
	// Serial.print("er_pr = ");Serial.println(error_previous);

	
	error_previous = error;
}

bool checkCliff(void){
	switch(align){
		case ALIGNED:
			if(Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				Serial.println("Finished");
				MotorsOFF();
				Ready = false;
				align = DONE;
				hinge_step = DOWN;
				return true;
			}
			else{
				align = ADJUST_DIR;
				return false;
			break;
		}
		case ADJUST_DIR:{
			if(!Cliff_Sensor_Read(CSL,CSLT) && !Cliff_Sensor_Read(CSR,CSRT)){
				Move_back(Speed_Medium);
				Serial.println("Going Back");
			}
			if(!Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				Turn_cw(Speed_Low);	 //left forward
				Serial.println("Turning Left");
			}
			else if(Cliff_Sensor_Read(CSL,CSLT) && !Cliff_Sensor_Read(CSR,CSRT)){
				Turn_ccw(Speed_Low); //right forward
				Serial.println("Turning Right");
			}
			if(Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				Serial.println("Finished");
				MotorsOFF();
				Ready = false;
				align = DONE;
				hinge_step = DOWN;
				return true;
			}			
			break;
		}
		default: align = ALIGNED; break;
	}
	return false;
}
void hinging(void){
	switch(hinge_step){
		case DOWN:
			Serial.println("Hinge Down");
			hingeToAngle(160);
			Move_forward(Speed_Medium);
			Motor5(Speed_Medium);
			hinge_step=CHECK_SENSORS;
			Serial.println("Sensors check");
			break;
		case CHECK_SENSORS:
			hingeToAngle(BufferOut[9] - 3);
			if(Cliff_Sensor_Read(DSF,DSFT)){
				hinge_step=UP;
				Hinge(0);
				Motor5(-Speed_Low);
				Serial.println("Hinge Up");
			}
			break;
			
		case UP:
			Move_forward(Speed_Low);
			hinge_step = CHECK_STEPS;
			Serial.println("Steps");
			break;
			
		case CHECK_STEPS:
			if(BufferOut[7] > 5){
				hingeToAngle(BufferOut[9] + 3);
			}
			else{
				hinge_step=STOP;
			}
			break;
		case STOP:
			Serial.println("STOP");
			HingeOFF();
			MotorsOFF();
			//Stop();
			hinge_step=STOP;
			break;
	}
}
			
			
