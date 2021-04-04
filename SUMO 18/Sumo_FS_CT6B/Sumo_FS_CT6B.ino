#include <MotorControl.h>
int channel1 = 6;
int channel2 = 4;

int C1 ; // forward & backward
int C2 ; // left & right

MotorControl ML(10,11,1,'H');
MotorControl MR(8,9,1,'H');
int MLSmax=255;
int MRSmax=255;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600); // Sets the baud rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
 C1 = (pulseIn (channel1, HIGH)); // Checks the value of channel1
  Serial.print (C1); //Prints the channels value on the serial monitor
  Serial.print ("    ");
  
  C2 = (pulseIn (channel2, HIGH)); // Checks the value of channel1
  Serial.print (C2);
  Serial.println ("    ");

  if (C1 >1700){
  ML.speed(MLSmax);
  MR.speed(MRSmax);
 Serial.print ("F");
 }
  else if (C1 <1300){
  ML.speed(-MLSmax);
  MR.speed(-MRSmax);
  Serial.print ("B");
  }

  else if (C2 >1700){
  ML.speed(-100);
  MR.speed(150);
  Serial.print ("R");
  }
  else if (C2 <1400){
  ML.speed(100);
  MR.speed(-150);
  Serial.print ("L");
  }

}
