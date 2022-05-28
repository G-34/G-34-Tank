#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <Servo.h>
#define LASER 11 //  Pin10
#define SERVO_TOWER 9 //  Pin9
#define SERVO_MUZZLE 10//  Pin11
#define MOTOR_LEFT 4 // Pin4
#define MOTOR_RIGHT 3 //  Pin3



char data;
int val_tower, val_muzzle;
int t;
int i;
int SPEED;

//SoftwareSerial bluetoothserial( , );

AF_DCMotor motor_left(MOTOR_LEFT); // left motor
AF_DCMotor motor_right(MOTOR_RIGHT); // right motor

Servo servo_tower;
Servo servo_muzzle; // variables of type Servo


void setup() 
{  
  Serial.begin(9600); 
  //bluetoothSerial.begin(9600);
  
  pinMode(LASER, OUTPUT); //  Pin10 

  servo_tower.attach(SERVO_TOWER);   
  servo_muzzle.attach(SERVO_MUZZLE);
  servo_tower.write(90);    // starting position
  servo_muzzle.write(90);   // starting position
  val_tower=90;
  val_muzzle=90;
  t=5; // povoroti na 5 gradusov
}

void loop() 
{
  //if (bluetoothSerial.available())
  if (Serial.available())
  {
    //data = (bluetoothSerial.read()); 
    data = (Serial.read());
    if (data == '0') // stop
    {
      motor_left.run(RELEASE);
      motor_right.run(RELEASE);
    }
    if (data == '9')
    {
      digitalWrite(LASER, HIGH);
      delay(1500);
      digitalWrite(LASER, LOW);     
    }
    
    if (data == 'R') // RIGHT
    {
      motor_right.run(BACKWARD);
      motor_left.run(FORWARD);
    }
    
    if (data == 'L') // LEFT
    {
      motor_right.run(FORWARD);
      //motor_left.setSpeed(SPEED);
      motor_left.run(BACKWARD);
      //motor_right.setSpeed(SPEED);
    }
    
    if (data == 'F') // FORWARD
    {
      motor_left.run(FORWARD);
      //motor_left.setSpeed(SPEED);
      motor_right.run(FORWARD);
      //motor_right.setSpeed(SPEED);
    }
    
    if (data == 'B') // BACK
    {
      //motor_left.setSpeed(SPEED);
      motor_left.run(BACKWARD);
      //motor_right.setSpeed(SPEED);
      motor_right.run(BACKWARD);

    }
    
    if ((data == 'l')&&((val_tower-t)<=180)&&((val_tower-t)>=0)) // servo_tower left
    {
      val_tower-=t;
      servo_tower.write(val_tower); 
      //delay(15);    
    }
    
    if ((data == 'r')&&((val_tower+t)<=180)&&((val_tower+t)>=0)) // servo_tower right
    {
      val_tower+=t;
      servo_tower.write(val_tower);
      //delay(15);    
    }
    
    if ((data == 'u')&&((val_muzzle+t)<=90)&&((val_muzzle+t)>=0)) // servo_muzzle up
    {
      val_muzzle+=t;
      servo_muzzle.write(val_muzzle);
      //delay(15);
    }
    
    if ((data == 'd')&&((val_muzzle-t)<=90)&&((val_muzzle-t)>=0)) // servo_muzzle down
    {
      val_muzzle-=t;
      servo_muzzle.write(val_muzzle);
      //delay(15);
    }
    if (data == '1') // first speed
    {
      SPEED = 150;
      motor_left.setSpeed(SPEED);
      motor_right.setSpeed(SPEED);
    }
    if (data == '2') // second speed
    {
      SPEED = 200;
      motor_left.setSpeed(SPEED);
      motor_right.setSpeed(SPEED);
    }
    if (data == '3') // third speed
    {
      SPEED = 255;
      motor_left.setSpeed(SPEED);
      motor_right.setSpeed(SPEED);
    }
    
    
  }

}
