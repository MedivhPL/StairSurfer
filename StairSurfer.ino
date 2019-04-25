//Motor values
//Motor 1 (front right)
#define M1PWM 4
#define M1P1 26
#define M1P2 27
//Motor 2 (front left)
#define M2PWM 5
#define M2P1 28
#define M2P2 29
//Motor 3 (back left)
#define M3PWM 3
#define M3P1 24
#define M3P2 25
//Motor 4 (back right)
#define M4PWM 2
#define M4P1 22
#define M4P2 23
//Hinge Motor
#define HMPWM 6
#define HMP1 30
#define HMP2 31
//Motor 5 (top back)
#define	M5PWM 7
#define M5P1 32
#define M5P2 33
//Brush roll
#define BMPWM 8
#define BMP1 34
#define BMP2 35
//Vacuum Motor
#define VMPWM 9
#define VMP1 36
#define VMP2 37
// Misc
#define GOUP 46
#define GODOWN 47
#define LIGHT 13

//Cases for "Descend"
#define CHECK_ONE 3 
#define DRIVE_DOWN 1
#define END 0
#define HINGEUP 5
#define REPEAT 4
#define SENSOR 2

//Sensor values
#define CSL A0 //(C)liff (S)ensor (L)eft
#define CSLT 700 //(C)liff (S)ensor (L)eft (T)reshold
#define CSR A1 //(C)liff (S)ensor (R)ight
#define CSRT 820//(C)liff (S)ensor (R)ight (T)reshold
#define DSF A2 //(D)istance (S)ensor (F)ront
#define DSFT 700 //Threshold
#define DSTF A4 //(D)istance (S)ensor (T)op (F)ront
#define DSTFT 300 //Threshold
#define DSTB A3 //(D)istance (S)ensor (T)op (B)ack
#define DSTBT 300 //Threshold
#define DSBR A6 //(D)istance (S)ensor (B)ackhalf (R)ight
#define DSBRT 500 //Threshold
#define DSBL A5 //(D)istance (S)ensor (B)ackhalf (L)eft
#define DSBLT 300 //Threshold
#define AXTX 1350 //(AX)ccelerometer (T)op Ma(x)
#define AXTN -1350 //(AX)ccelerometer (T)op Mi(n)
#define AXBX 1300 //(AX)ccelerometer (B)ottom Ma(x)
#define AXBN -1350 //(AX)ccelerometer (B)ottom Mi(n)
// Macros for travelling
#define FIRSTPASS 0
#define SECONDPASS 1
#define TURNING_CW 2
#define TURNING_CW1 5
#define TURNING_CCW 3
#define DONE 4
// Macros for alligning
#define ALIGNED 0
#define ADJUST_DIR 1
#define HINGE 2
//Macros for hinge movement
#define DOWN 0
#define GOFORWARD 1
#define CHECK_SENSORS 2
#define HINGE_DOWN_ONCE 3
#define UP 4
#define CHECK_STEPS 5
#define STOP 6
//Macros for main
#define CHECK1 1
#define CHECK2 2
#define CLEANING 3
#define DESCEND 4

#define SENSOR_AMOUNT 10
#define SIZE_OF_BUFFER 10

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3DH axl1 = Adafruit_LIS3DH();
Adafruit_LIS3DH axl2 = Adafruit_LIS3DH();

bool Ready = false;
bool Cleaning = false;
bool Descend = false;

int hinge_step = 0;
int align = 0;
int Sensor_Trigger = 0;
int travel_step = 0;

int Speed_Low = 150;
int Speed_Medium = 205;
int Speed_Fast = 250; 

int SensorMeasurements[SENSOR_AMOUNT][SIZE_OF_BUFFER];
int BufferOut[SENSOR_AMOUNT];
int stair_pass;
char incomingByte;
int angletemp = 270;


void setup() {
//Motor 1
	pinMode(M1P1, OUTPUT);
	pinMode(M1P2, OUTPUT);
	pinMode(M1PWM, OUTPUT);
//Motor 2
	pinMode(M2P1, OUTPUT);
	pinMode(M2P2, OUTPUT);
	pinMode(M2PWM, OUTPUT);
//Motor 3
	pinMode(M3P1, OUTPUT);
	pinMode(M3P2, OUTPUT);
	pinMode(M3PWM, OUTPUT);
//Motor 4
	pinMode(M4P1, OUTPUT);
	pinMode(M4P2, OUTPUT);
	pinMode(M4PWM, OUTPUT);
//Hinge motor
	pinMode(HMP1, OUTPUT);
	pinMode(HMP2, OUTPUT);
	pinMode(HMPWM, OUTPUT);
//Motor 5
	pinMode(M5P1, OUTPUT);
	pinMode(M5P2, OUTPUT);
	pinMode(M5PWM, OUTPUT);
//Brushroll motor
	pinMode(BMP1 ,OUTPUT);
	pinMode(BMP2,OUTPUT);
	pinMode(BMPWM,OUTPUT);
//Vacuum motore
	pinMode(VMP1, OUTPUT);
	pinMode(VMP2, OUTPUT);
	pinMode(VMPWM, OUTPUT);
// other
	pinMode(GOUP, INPUT);
	pinMode(GODOWN, INPUT_PULLUP);
	pinMode(LIGHT,OUTPUT);
	Serial.begin(115200);
	delay(20);
	Serial.println("A1xell Setup");
	AXLSetup();
	delay(20);
	Serial.println("End of Setup");
	for(int i = 0; i < SIZE_OF_BUFFER;i++) Sensor_Read();
  }

void loop() {
	// put your main code here, to run repeatedly:
	//Motors_Test();
	if(digitalRead(GOUP)){
		// Ready =true;
		travel_step = CHECK2;
		hinge_step = DOWN;
		stair_pass = TURNING_CW;
		// Test_Forward(200);
		// Motors_Test();
		// Move_back(Speed_Medium);
		// Hinge(-Speed_Medium);
		 delay(500);
		// Stop();
		Serial.println("Start");
		}
		
	if(!digitalRead(GODOWN)){
		// Motor1(-Speed_Low);
		// Motor2(Speed_Low);
		// Motor3(-Speed_Low);
		// Motor4(-Speed_Low);
		//Test_Backward(200);
		//HingeDown(Speed_Low);
		hingeToAngle(270,200);
		delay(100);
		Stop();
		Serial.println("End");
		}
	

	//Drive to the edge and check for cliff.
	switch(travel_step){
		case CHECK1:
		if(checkCliff()){
			travel_step = DESCEND;
			hinge_step = DOWN;
		}
		break;
		case DESCEND:
		if(hinging()){
			travel_step = CHECK2;
		}
		break;
		case CHECK2:
		if(checkCliff()){
			travel_step = CLEANING;
			stair_pass = TURNING_CW;
		}
		break;
		case CLEANING:
		if(Travel_Stairs()){
			travel_step = CHECK1;
			Stop();
		}
		break;
		default: break;
	}

// if (Serial.available()) {
    // // read the incoming byte:
    // incomingByte = Serial.read();
	// if(incomingByte == 'u'){if(!(angletemp >= 275)) angletemp+=5;}
	// if(incomingByte == 'i'){if(!(angletemp <= 150))angletemp-=5;}
// }
	Sensor_Read();
	delay(20);
	// hingeToAngle(angletemp);
// static int max = 0,min = 10000,value;
	int normalized[4];
	normalized[0] = Normalize(BufferOut[5],735,53);
	normalized[1] = Normalize(BufferOut[6],671,52);
	normalized[2] = Normalize(BufferOut[3],650,100);
    normalized[3] = Normalize(BufferOut[4],537,270);
	// Serial.print("Normalized BackLeft = ");Serial.print(normalized[0]);
	// Serial.print(" Normalized BackRight = ");Serial.println(normalized[1]);
	Serial.print(" Normalized TopFront = ");Serial.print(normalized[2]);
	Serial.print(" Normalized TopBack = ");Serial.println(normalized[3]);
	// angle = getHingeAngle();
	// Serial.print("Angle wanted = ");Serial.print(angletemp);
	// Serial.print("Buffer BackLeft = ");Serial.print(BufferOut[5]);
	// Serial.print(" Buffer BackRight = ");Serial.print(BufferOut[6]);
	// Serial.print(" Buffer TopFront = ");Serial.print(BufferOut[3]);
	// Serial.print(" Buffer TopBack = ");Serial.print(BufferOut[4]); 
	// Serial.print(" Buffer Front = ");Serial.println(BufferOut[2]); 

	// Serial.print(", Angle1 = ");Serial.print(BufferOut[7]); 
	// Serial.print(", Angle2 = ");Serial.print(BufferOut[8]);
	// Serial.print(", Angle Total = ");Serial.println(BufferOut[9]);
}
void Stop(void){
	HingeOFF();	
	MotorsOFF();
	travel_step = 0;
	digitalWrite(LIGHT,LOW);
}


void Test_Forward(int speed)
{
	analogWrite(M1PWM,speed);
	digitalWrite(M1P1,HIGH);
	digitalWrite(M1P2,LOW);
}	
void Test_Backward(int speed)
{
	analogWrite(HMPWM,speed);
	digitalWrite(HMP1,LOW);
	digitalWrite(HMP2,HIGH);
}	
