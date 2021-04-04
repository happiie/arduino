 #include <PS2X_lib.h>  //for v1.6
#include <MotorControl.h>
//#include <SoftPWM.h>

PS2X ps2x; // create PS2 Controller Class

int error = 0; 
byte vibrate = 0;
int lf=5,lb=6,rf=8,rb=9,sp=0,count=0;                // lf same with lb and rf same with rb because only 1 pwm port to control the speed of both front and rear of left side tyres and vice versa
int a,b,c,d;
MotorControl mL(10,11,1,'H');
MotorControl mR(8,9,1,'H');

void setup(){
  // SoftPWMBegin();
  do{  
    error = ps2x.config_gamepad(4,6,5,7, false, true);  
    /*setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error 
     error == 0 "Found Controller, configured successful"
     error == 1 "No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips"
     error == 2 "Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips"
     error == 3 "Controller refusing to enter Pressures mode, may not support it. " 
     */
  }
  while(error==1||error==2);  
  sp=255;
  
}


void speedcontrol(){

 if(ps2x.Button(PSB_R1))
  {
    sp = 255;
  }
  else
  {
   sp = (190);
  }


 
  //delay(5);
}


void loop(){
  sp=255;
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
//if(ps2x.ButtonPressed(PSB_SELECT)) test();
  speedcontrol();
   if (ps2x.Button(PSB_R2))
  {
    
    mL.speed(sp);
    mR.speed(0);
  }
  else if (ps2x.Button(PSB_L2))
  {
    
    mL.speed(0);
    mR.speed(sp);
  }

else if (ps2x.Button(PSB_RED))
  {
  // sp/=2;   
    mL.speed(sp);
    mR.speed(-sp+20);
  }

  else if (ps2x.Button(PSB_PINK))
  {
  // sp/=2;

    mL.speed(-sp);
    mR.speed(sp-20);
  }
  
  
 else if (ps2x.Button(PSB_PAD_UP))
  {
    
    mL.speed(sp);
    mR.speed(sp-20);
  }

  else if (ps2x.Button(PSB_PAD_DOWN))
  {
    
    mL.speed(-sp);
    mR.speed(-sp+20);
  }


else
  {
   
    mL.speed(0);
    mR.speed(0);
  } 
  


  delay(5);
 
}

