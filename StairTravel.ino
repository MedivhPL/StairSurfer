// #define FIRSTPASS 0
// #define SECONDPASS 1
// #define TURNING_CCW1 2
// #define TURNING_CCW2 3
// #define DONE 4
// #define TURNING_CW 5
bool distance_Check(int buffer, int threshold){
	return buffer < threshold;
}
bool Travel_Stairs(void){
	int DSTF_THRESHOLD = 300;
	int DSTB_THRESHOLD = 300;
	int DSBL_THRESHOLD = 200;
	int DSBR_THRESHOLD = 300;
	bool lined_up = false;
	int error_distance,error_angle;
	static int previous_error=0;
	int normalized[4];
  
	//turn on vacuum
	//move to wall
    //drive left
	//loop until sensor(s) sees wall
	
	//next
	MotorsOFF();
	//line up with wall
    //pass both sensor reading tests
    //
	normalized[0] = Normalize(BufferOut[5],735,53);
	normalized[1] = Normalize(BufferOut[6],671,52);
	normalized[2] = Normalize(BufferOut[3],650,100);
    normalized[3] = Normalize(BufferOut[4],537,270);
	switch(stair_pass){
		
		case FIRSTPASS:
		if(!distance_Check(BufferOut[5],DSBLT) || !distance_Check(BufferOut[6],DSBRT)){
			Serial.println("GOBACK");
			Move_back(Speed_Medium);
			}
		error_distance = normalized[0]; //top back
		error_angle = normalized[1]; //top front
		
		if(error_distance > 45)
		{
			Serial.println("GOLEFT");
			Motor2(-Speed_Fast);
			Motor4(-Speed_Fast);
			// Move_left(Speed_Medium);
		}
		if(error_distance >70){
			Move_left(Speed_Medium);
		}
		if(error_angle < 20){
			Serial.println("TURNLEFT");
			Move_back(Speed_Medium);
			Motor1(-Speed_Fast);
			Motor4(-Speed_Fast);
			//Turn_cw(Speed_Medium);
		}
		else if(error_angle > 45){
			Serial.println("TURNRIGHT");
			Motor2(-Speed_Fast);	
			Motor3(-Speed_Fast);
			//Turn_ccw(Speed_Medium);
		}
		if(distance_Check(BufferOut[5],DSBLT) && distance_Check(BufferOut[6],DSBRT)){
			MotorsOFF();
			stair_pass = TURNING_CCW;
			}
		break;
		
		case TURNING_CW: /////////////////////////////Turning
		Turn_cw(Speed_Medium);
		if(distance_Check(BufferOut[2],DSFT)||(!distance_Check(BufferOut[0],CSLT) && !distance_Check(BufferOut[1],CSRT))){
			Serial.println("TURNING");
			stair_pass = TURNING_CW1;
		}
		break;
		
		case TURNING_CW1: /////////////////////////////Turning
		Move_forward(Speed_Medium);
		if(distance_Check(BufferOut[2],DSFT)){
			Serial.println("TURNING");
			stair_pass = FIRSTPASS;
		}
		break;
		
		case TURNING_CCW: /////////////////////Turning
		Turn_ccw(Speed_Medium);
		if(!distance_Check(BufferOut[0],CSLT) && !distance_Check(BufferOut[1],CSRT)){
			Serial.println("TURNING");
			stair_pass = SECONDPASS;
			}
		break;
		
		case SECONDPASS:
		if(!distance_Check(BufferOut[4],DSTBT) || !distance_Check(BufferOut[3],DSTFT)){
			Serial.println("GORIGHT");
			Move_left(Speed_Medium);
			}
		error_distance = normalized[2];
		error_angle = normalized[2] - normalized[3];
		
		if(error_distance > 40)
		{
			Motor2(-Speed_Fast);
			Motor4(-Speed_Fast);
			Motor3(Speed_Low);
			// Move_back(Speed_Low);
		}
		if(error_distance>50){
			Move_back(Speed_Medium);
		}
		if(error_angle<-30){
			Turn_cw(Speed_Medium);
		}
		else if(error_angle > 10)
		{
			Motor3(Speed_Fast);
			Motor4(-Speed_Fast);
			//Turn_ccw(Speed_Low);
		}
		else if(error_angle < -10)
		{
			Motor2(-Speed_Fast);
			Motor4(-Speed_Low);
			//Turn_cw(Speed_Low);
		}
		if(distance_Check(BufferOut[4],DSTBT) && distance_Check(BufferOut[3],DSTFT)){
			MotorsOFF();
			stair_pass = DONE;
			}
		break;
		
		case DONE:
		MotorsOFF();
		return true;
		default: 
		break;
		}
		return false;
}
	
	// while(!lined_up){
      // //parrellelize
      // if(analogRead(DSTF) > analogRead(DSTB)){
        // Turn_ccw(Speed_Medium);
        // while(analogRead(DSTF) > analogRead(DSTB)){Serial.println("turn ccw");}
        // MotorsOFF();
      // }
      // if(analogRead(DSTF) < analogRead(DSTB)-50){
        // Turn_cw(Speed_Medium);
        // while(analogRead(DSTF) < analogRead(DSTB)){Serial.println("turn cw");}
        // MotorsOFF();
      // }


      // //move closer to wall
      // if(analogRead(DSTF) < (analogRead(DSTB)+50) && analogRead(DSTF) > (analogRead(DSTB)-50)){
        // if(analogRead(DSTB) > DSTF_THRESHOLD){
          // Move_left(Speed_Medium);
          // while(analogRead(DSTB) > DSTF_THRESHOLD){Serial.println("go left closer");}
          // MotorsOFF();
        // }
        // lined_up =true;
        // Serial.println("readu");
      // }
    // }
    
  //turn on spinner
  
  //follow wall to next wall
    // //drive back
    // Move_back(Speed_Medium);
    // //loop until rear sensors detect wall
    // while(analogRead(DSBL) > DSBL_THRESHOLD || analogRead(DSBR) > DSBR_THRESHOLD){Serial.println("follow back");}
    // //next state
    // MotorsOFF();
    // Serial.println("done");
    
  //turn
    //turn CCW
    //loop until front sensor sees wall
  //line up with wall
  //follow wall to next wall
    //drive back
    //loop until rear sensors detect wall
  //turn
  //follow wall to cliff (back sensors)
  //turn 180
  
