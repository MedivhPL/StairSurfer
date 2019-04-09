/*
Function calls in this file 
Move_back(int )
Move_forward(int )
Move_left(int )
Move_right(int )
Turn_ccw(int )
Turn_cw(int )
HingeDown(int)
HingeUp(int)
MotorsOFF()
HingeOFF(int)
*/
void Motors_Test(void)
{
	Move_back(200);
	delay(1000);
	Move_forward(200);
	delay(1000);
	Move_left(200);
	delay(1000);
	Move_right(200);
	delay(1000);
	Turn_ccw(200);
	delay(1000);
	Turn_cw(200);
	delay(1000);
}
void Hinge_Test(void){
	HingeDown(200);
	delay(1000);
	HingeUp(200);
	delay(1000);
}
void Move_left(int speed){
	//Move motor 1 CCW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,LOW);
	digitalWrite(M1P2,HIGH);
	//Move motor 2 CCW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,HIGH);
	digitalWrite(M2P2,LOW);
	//Move motor 3 CW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,LOW);
	digitalWrite(M3P2,HIGH);
	//Move motor 4 CW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,LOW);
	digitalWrite(M4P2,HIGH);
	}
void Move_right(int speed){
	//Move motor 1 CW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,HIGH);
	digitalWrite(M1P2,LOW);
	//Move motor 2 CW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,LOW);
	digitalWrite(M2P2,HIGH);
	//Move motor 3 CCW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,HIGH); 
	digitalWrite(M3P2,LOW);
	//Move motor 4 CCW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,HIGH);
	digitalWrite(M4P2,LOW);
	}
void Move_forward(int speed){
	//Move motor 1 CW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,HIGH);
	digitalWrite(M1P2,LOW);
	//Move motor 2 CCW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,LOW);
	digitalWrite(M2P2,HIGH);
	//Move motor 3 CCW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,HIGH)  ;
	digitalWrite(M3P2,LOW);
	//Move motor 4 CW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,HIGH);
	digitalWrite(M4P2,LOW);
	}
void Move_back(int speed){
	//Move motor 1 CCW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,LOW);
	digitalWrite(M1P2,HIGH);
	//Move motor 2 CW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,HIGH);
	digitalWrite(M2P2,LOW);
	//Move motor 3 CCW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,LOW); 
	digitalWrite(M3P2,HIGH);
	//Move motor 4 CW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,LOW);
	digitalWrite(M4P2,HIGH);
	}
void Turn_cw(int speed){
	//Move motor 1 CW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,HIGH);
	digitalWrite(M1P2,LOW);
	//Move motor 2 CW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,HIGH);
	digitalWrite(M2P2,LOW);
	//Move motor 3 CW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,LOW);
	digitalWrite(M3P2,HIGH);
	//Move motor 4 CW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,HIGH);
	digitalWrite(M4P2,LOW);
	}
void Turn_ccw(int speed){
	//Move motor 1 CCW 
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,LOW);
	digitalWrite(M1P2,HIGH);
	//Move motor 2 CCW 
	analogWrite(M2PWM,speed);
	digitalWrite(M2P1,LOW);
	digitalWrite(M2P2,HIGH);
	//Move motor 3 CCW
	analogWrite(M3PWM,speed);
	digitalWrite(M3P1,HIGH); 
	digitalWrite(M3P2,LOW);
	//Move motor 4 CCW 
	analogWrite(M4PWM,speed);
	digitalWrite(M4P1,LOW);
	digitalWrite(M4P2,HIGH);
	}
void HingeUp(int speed){
	analogWrite(HMPWM,speed);
	digitalWrite(HMP1,HIGH);
	digitalWrite(HMP2,LOW);
	}
void HingeDown(int speed){
	//Move hinge motor clockwise
	analogWrite(HMPWM,speed);
	digitalWrite(HMP1,LOW);
	digitalWrite(HMP2,HIGH);
	}
void HingeOFF(void){
	//Move hinge motor counter-clockwise
	analogWrite(HMPWM,0);
	digitalWrite(HMP1,LOW);
	digitalWrite(HMP2,LOW);
	}
void MotorsOFF(void){
	//Stop motor 1
	analogWrite(M1PWM,0);
	digitalWrite(M1P1,LOW);
	digitalWrite(M1P2,LOW);
	//Stop motor 2  
	analogWrite(M2PWM,0);
	digitalWrite(M2P1,LOW);
	digitalWrite(M2P2,LOW);
	//Stop motor 3 
	analogWrite(M3PWM,0);
	digitalWrite(M3P1,LOW); 
	digitalWrite(M3P2,LOW);
	//Stop motor 4  
	analogWrite(M4PWM,0);
	digitalWrite(M4P1,LOW);
	digitalWrite(M4P2,LOW);
	}
void Break(void){
	//Move motor 1 CCW
	analogWrite(M1PWM,200);
	digitalWrite(M1P1,LOW);
	digitalWrite(M1P2,HIGH);
	//Move motor 2 CW 
	analogWrite(M2PWM,200);
	digitalWrite(M2P1,LOW);
	digitalWrite(M2P2,HIGH);
	//Stop motor 3
	analogWrite(M3PWM,0);
	digitalWrite(M3P1,LOW); 
	digitalWrite(M3P2,LOW);
	//Stop motor 4  
	analogWrite(M4PWM,0);
	digitalWrite(M4P1,LOW);
	digitalWrite(M4P2,LOW);
	delay(100);
	}
