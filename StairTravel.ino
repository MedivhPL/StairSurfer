// #define FIRSTPASS 0
// #define SECONDPASS 1
// #define TURNING_CCW1 2
// #define TURNING_CCW2 3
// #define DONE 4
// #define TURNING_CW 5

void Travel_Stairs(void){
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
	normalized[0] = Normalize(BufferOut[5],500 ,300 );
	normalized[1] = Normalize(BufferOut[6], 500,300 );
	normalized[2] = Normalize(BufferOut[3], 500,300 );
    normalized[3] = Normalize(BufferOut[4], 500,300 );
	switch(stair_pass){
		case FIRSTPASS:
		if(!Cliff_Sensor_Read(DSBL,DSBLT) && !Cliff_Sensor_Read(DSBR,DSBRT)){
			Serial.println("GOLEFT");
			Move_back(Speed_Medium);
			}
		error_distance = normalized[0];
		error_angle = normalized[0] - normalized[1];
		
		if(error_distance > 10)
		{
			Move_right(Speed_Low);
		}
		if(error_angle > 10)
		{
			Turn_ccw(Speed_Low);
		}
		if(error_angle < -10){
			Turn_cw(Speed_Low);
		}
		if(Cliff_Sensor_Read(DSBL,DSBLT) && Cliff_Sensor_Read(DSBR,DSBRT)){
			MotorsOFF();
			stair_pass = TURNING_CW;
			}
		break;
		case TURNING_CW: /////////////////////////////Turning
		Turn_cw(Speed_Medium);
		if(!Cliff_Sensor_Read(DSBR,DSBRT) && !Cliff_Sensor_Read(DSBL,DSBLT)){
			Serial.println("TURNING");
			stair_pass = SECONDPASS;
			}
		break;
		case TURNING_CCW2: /////////////////////Turning
		Turn_ccw(Speed_Medium);
		if(!Cliff_Sensor_Read(DSTB,DSTBT) && !Cliff_Sensor_Read(DSTF,DSTFT)){
			Serial.println("TURNING");
			stair_pass = DONE;
			}
		break;
		case TURNING_CCW1: //////////////////Turning
		Turn_ccw(Speed_Medium);
		if(!Cliff_Sensor_Read(DSTB,DSTBT) && !Cliff_Sensor_Read(DSTF,DSTFT)){
			Serial.println("TURNING");
			stair_pass = FIRSTPASS;
			
		case SECONDPASS:
		if(!Cliff_Sensor_Read(DSTB,DSTBT) && !Cliff_Sensor_Read(DSTF,DSTFT)){
			Serial.println("GORIGHT");
			Move_right(Speed_Medium);
			}
		error_distance = normalized[2];
		error_angle = normalized[2] - normalized[3];
		
		if(error_distance > 10)
		{
			Move_back(Speed_Low);
		}
		if(error_angle > 10)
		{
			Turn_ccw(Speed_Low);
		}
		if(error_angle < -10){
			Turn_cw(Speed_Low);
		}
		if(Cliff_Sensor_Read(DSBL,DSBLT) && Cliff_Sensor_Read(DSBR,DSBRT)){
			MotorsOFF();
			stair_pass = TURNING_CCW2;
			}
		break;
		case DONE:
		MotorsOFF();
		Cleaning = false;
		default: 
		break;
		}
		
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
  
}
