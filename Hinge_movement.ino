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

int hinge_step = 0;
int descending = 0;

bool checkCliff(void){
	switch(descending){
		case ALIGNED:
			if(Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				//descending = HINGE;
				Serial.println("Stopped");
				MotorsOFF();
				return true;
			}
			else{
				descending = ADJUST_DIR;
				return false;
			break;
		}
		case ADJUST_DIR:{
			if(!Cliff_Sensor_Read(CSL,CSLT) && Cliff_Sensor_Read(CSR,CSRT)){
				Turn_cw(Speed_Low);  //left forward
				Serial.println("Turning Left");
			}
			else if(Cliff_Sensor_Read(CSL,CSLT) && !Cliff_Sensor_Read(CSR,CSRT)){
				Turn_ccw(Speed_Low); //right forward
				Serial.println("Turning Right");
			}
			else if(!Cliff_Sensor_Read(CSL,CSLT) && !Cliff_Sensor_Read(CSR,CSRT)){
				Move_back(Speed_Low);
				Serial.println("Going Back");
			}
			else{
				MotorsOFF();
				stair_pass = TURNING_CCW1;
				Ready = false;
				return true;//descending = HINGE;
			}			
			break;
		}
		case HINGE:{
			Serial.println("HINGING");
			hinging();
			if(hinge_step=STOP){
				hinge_step=DOWN;
				descending=ALIGNED;
			}
			else
				descending=HINGE;
				break;
		}
	}
	return false;
}
void hinging(void){
	switch(hinge_step){
		case DOWN:{
			Serial.println("HingeDown");
			//HingeDown(Speed_Low);
			delay(200);
			HingeOFF();
			hinge_step=GOFORWARD;
			break;
			}
		case GOFORWARD:{
			Serial.println("GOFORWARD");
			//Move_forward(Speed_Low);
			delay(200);
			MotorsOFF();
			hinge_step=CHECK_SENSORS;
			break;
			}
		case CHECK_SENSORS:{
			Serial.println("Sensors check");
			if(analogRead(DSBL)>600 || analogRead(DSBR)>600){
				hinge_step=HINGE_DOWN_ONCE;
			}
			else
				hinge_step=DOWN;
			break;
			}
		case HINGE_DOWN_ONCE:{
			Serial.println("Once more down");
			//HingeDown(Speed_Low);
			delay(200);
			HingeOFF();
			//move_forward(Speed_Low);
			delay(200);
			MotorsOFF();
			hinge_step=UP;
			break;
			}
		case UP:{
			Serial.println("HingeUp");
			//HingeUp(Speed_Low);
			delay(200);
			HingeOFF();
			hinge_step=CHECK_STEPS;
			break;
			}
		case CHECK_STEPS:{
			Serial.println("Steps");
			if(analogRead(DSBL)>600 || analogRead(DSBR)>600){
				hinge_step=STOP;
			}
			else
				hinge_step=UP;
			break;
			}
		case STOP:{
			Serial.println("STOP");
			HingeOFF();
			MotorsOFF();
			hinge_step=STOP;
			break;
			}
	}
}
			
			
