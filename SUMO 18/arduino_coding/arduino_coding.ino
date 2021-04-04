#include <SoftwareSerial.h>
#include <MotorControl.h>

const int echoPin = 13;
const int trigPin = 12;

int D1 = 2;
int D2 = 4;
int a, b;

MotorControl motorL(6, 3, 0, 'H');
MotorControl motorR(11, 10, 0, 'H');

void setup()
{
  pinMode(D1, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(D2, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600);

  pinMode(7, OUTPUT); 
  digitalWrite(7, HIGH);
}

long duration;
double distance_cm;
const int forward_spd = 200;
const int reverse_spd = -150;

void loop()
{
  ReadSensors();
  if (a > 420 && b < 350) {
    reverse();
    delay(1000);
  }
  else if (a < 420 && b > 350) {
    forward();
  }
  
}



// functions
void forward()
{
  motorR.speed(forward_spd);
  motorL.speed(forward_spd);
}

void reverse()
{
  motorR.speed(reverse_spd);
  motorL.speed(0);
}

void brake()
{
  motorR.speed(0);
  motorL.speed(0);
}


void ReadSensors() // IR / ultrasonic sensors
{
  digitalWrite(D1, HIGH); // Turn on LED
  delayMicroseconds(500);
  a = analogRead(A1);
  digitalWrite(D2, HIGH);
  delayMicroseconds(500);
  b = analogRead(A2);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  digitalWrite(echoPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_cm = duration * 0.034 / 2;
 // Serial.print(distance_cm);
 // Serial.println("cm ");
  //Serial.println(a);
  //Serial.println(b);
}
