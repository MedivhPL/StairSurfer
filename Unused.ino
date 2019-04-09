/*if(Ready){
    digitalWrite(LIGHT,HIGH);
  switch(Descend){
  
    // forward, hinge down
    case DRIVE_DOWN:{
    /*  while(digitalRead(){
        Move_forward(Speed_low);
      }
      
      
      
      Move_forward(Speed_Low);
      delay(200);
      MotorsOFF();
      HingeDown(Speed_Fast);
      delay(300);
      HingeOFF();
      Descend = CHECK_ONE;
      Serial.println("Going Down Case");
      break;
    }
    // check if sensors are triggered
    case SENSOR:{
      if(!(Cliff_Sensor_Read(CSL) && Cliff_Sensor_Read(CSR))){
        Descend = CHECK_ONE;
      }       
      else{
        Descend = REPEAT;
      }
      Serial.println("Sensor Case");
      break;
    }
    //if yes increment counter
    case CHECK_ONE:{
      Sensor_Trigger +=1;
      Serial.println("Check Case");
    }
    //if no repeat
    //sensors got triggered x times
    case REPEAT:{
      if(Sensor_Trigger > 3){
        Descend = HINGEUP;
        }
      else{
        Descend = DRIVE_DOWN;
        }
      Serial.println("Repeat Case");
      break;
    }
    // hinge up
    case HINGEUP:{
      HingeUp(Speed_Fast);
      Move_forward(Speed_Medium);
      delay(1900);
      Descend = END;
      Stop();
      Serial.println("Hinge Up Case");
      break;
    }
    case END:{
      Descend = DRIVE_DOWN;
      Sensor_Trigger = 0;
      Serial.println("End Case");
      break;
    }
  }
  /*/
