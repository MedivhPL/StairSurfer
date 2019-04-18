/*///Motor values
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
#define CSL A0//(C)liff (S)ensor (L)eft
#define CSLT 700//(C)liff (S)ensor (L)eft (T)reshold
#define CSR A1 //(C)liff (S)ensor (R)ight
#define CSRT 820//(C)liff (S)ensor (R)ight (T)reshold
#define DSF A2//(D)istance (S)ensor (F)ront
#define DSFT 300 //Threshold
#define DSTF A4//(D)istance (S)ensor (T)op (F)ront
#define DSTFT 300 //Threshold
#define DSTB A3//(D)istance (S)ensor (T)op (B)ack
#define DSTBT 300 //Threshold
#define DSBR A6//(D)istance (S)ensor (B)ackhalf (R)ight
#define DSBRT 400 //Threshold
#define DSBL A5//(D)istance (S)ensor (B)ackhalf (L)eft
#define DSBLT 200 //Threshold
#define AXT 1//(AX)ccelerometer (T)op
#define AXB 1//(AX)ccelerometer (B)ottom

// Macros for travelling
#define FIRSTPASS 0
#define SECONDPASS 1
#define TURNING_CCW1 2
#define TURNING_CCW2 3
#define DONE 4
#define TURNING_CW 5
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

bool Ready = false;
bool Cleaning = false;
int Descend = 0;
int Sensor_Trigger = 0;
int Speed_Low = 125;
int Speed_Medium = 175;
int Speed_Fast = 250; 
int SensorMeasurements[7];
