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
#define INTMAX 500
void hingeToAngle(int angle, int max_speed){
	static int error, error_previous, kp, kd, c_out;
	static double ki,integral;
	//Serial.println(angle);
	if (angle > 270) angle = 270;
	if (angle < 150) angle = 150;
	
	error = angle - BufferOut[9];
	kp = 5 * error;
	kd = 5 * (error - error_previous);
	integral += (error + error_previous)/2;
	// Serial.print("int = ");Serial.print(integral);

	ki = .3 * (integral);
	c_out = kp + kd + ki;
	if (c_out <= 40 && c_out >= -40) c_out = 0;
	if (c_out > max_speed) c_out = max_speed;
	if (c_out < -max_speed) c_out = -max_speed;
	Hinge(c_out);
	if(integral > INTMAX)integral = INTMAX;
	if(integral < -INTMAX)integral = -INTMAX;
	// Serial.print("kp = ");Serial.print(kp);
	// Serial.print("kd = ");Serial.print(kd);
	// Serial.print("ki = ");Serial.print(ki);
	// Serial.print("int = ");Serial.print(integral);
	// Serial.print("er_pr = ");Serial.println(error_previous);
	Serial.print("cout = ");Serial.print(c_out);
	Serial.print(", Angle = ");Serial.println(BufferOut[9]);	
	
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
				Move_back(Speed_Fast);
				Serial.println("Going Back");
			}
			if(!Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				Turn_cw(Speed_Fast);	 //left forward
				Serial.println("Turning Left");
			}
			else if(Cliff_Sensor_Read(CSL,CSLT) && !Cliff_Sensor_Read(CSR,CSRT)){
				Turn_ccw(Speed_Fast); //right forward
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
bool hinging(void){
	switch(hinge_step){
		case DOWN:
			Serial.println("Hinge Down");
			hingeToAngle(160,Speed_Medium);
			Move_forward(Speed_Medium);
			Motor5(Speed_Medium);
			hinge_step=CHECK_SENSORS;
			Serial.println("Sensors check");
			break;
		case CHECK_SENSORS:
			hingeToAngle(BufferOut[9] - 10,Speed_Fast);
			if(Cliff_Sensor_Read(DSF,DSFT) || BufferOut[9] <= 160){
				hingeToAngle(BufferOut[9] - 10,Speed_Fast);
				hinge_step=UP;
				Hinge(0);
				Motor5(-Speed_Low);
				MotorsOFF();
				Serial.println("Hinge Up");
			}
			break;
			
		case UP:
			// Motor5(Speed_Low);
			delay(1000);
			Move_forward(Speed_Low);
			Motor1(Speed_Medium);
			Motor2(-Speed_Medium);
			hinge_step = CHECK_STEPS;
			Serial.println("Steps");
			break;
			
		case CHECK_STEPS:
			if(BufferOut[7] > 5){
				hingeToAngle(BufferOut[9] + 3,Speed_Low);
			}
			else{
				if(BufferOut[9] > 265 && BufferOut[9] < 275){
				hinge_step=STOP;
				}
				else{
				MotorsOFF();
				hingeToAngle(270,Speed_Low);
				}
			}
			break;
		case STOP:
			Serial.println("STOP");
			HingeOFF();
			MotorsOFF();
			hinge_step=STOP;
			return true;
			break;
	}
	return false;
}
			
			
