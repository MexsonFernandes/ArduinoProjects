#define m11 12    // rear motor
#define m12 11
#define m21 10    // front motor
#define m22 8

#include <Servo.h> 

Servo test;  // create servo object to control a servo   GUN 
Servo myservo2;  // create servo object to control a servo   TRIG

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position
int pos3 = 0;    // variable to store the servo position

//int hasObstacle = LOW;  // HIGH MEANS NO OBSTACLE
//int obstaclePin = 3;  // This is our input pin
int trigPin = 3;    //Trig - green Jumper
int echoPin = 4;    //Echo - yellow Jumper
long duration, cm;

char str[2],i;

void forward()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
  // motor1.run(FORWARD);  // 
   //motor2.run(FORWARD);  // BOT MOVE FORWARD
}

void backward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH);
   //motor1.run(BACKWARD);  // 
   //motor2.run(BACKWARD);  // BOT MOVE BACKWARD
 
}

void left()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   delay(100);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
   
  // motor1.run(BACKWARD);  // 
   //motor2.run(FORWARD);  // BOT MOVE LEFT
}

void right()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   delay(100);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH);
   
   //motor1.run(FORWARD);  // 
   //motor2.run(BACKWARD);  // BOT MOVE RIGHT
}

void Stop()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, LOW);
   
   //motor1.run(RELEASE);  // 
   //motor2.run(RELEASE);  // BOT STOPS
   //motor3.run(RELEASE);
   //motor4.run(RELEASE);
}
void gunservo()
   {

   /*motor3.run(FORWARD);     //cleaner clock wise
   delay(2000);
   motor3.run(BACKWARD);   //cleaner anti-clock wise
   delay(2000);*/
//   for(pos1 = 0; pos1 <= 120; pos1 += 1)  // goes from 0 degrees to 180 degrees 
//  {                                      // in steps of 1 degree 
//    myservo1.write(pos1);               // tell servo to go to position in variable 'pos' 
//    delay(50);                         // waits 15ms for the servo to reach the position 
//  } 
//  for(pos1 = 120; pos1 >=0; pos1-=1)  // goes from 180 degrees to 0 degrees 
//  {                                
//    myservo1.write(pos1);            // tell servo to go to position in variable 'pos' 
//    delay(50);                      // waits 15ms for the servo to reach the position 
//  }

   }

void trigservo()
   {


   for(pos2 = 0; pos2 <= 130; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 130; pos2 >=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
   
}

void setup() 
{
  test.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(6);  // attaches the servo on pin 6 to the servo object

  //pinMode(obstaclePin, INPUT);
  
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void motorControl()
{
   while(Serial.available())
  {
    char ch=Serial.read();
    str[i++]=ch;
    
    if(str[i-1]=='1')
    {
     Serial.println("forward");
     forward();
     i=0;
    }

    else if(str[i-1]=='2')
    {
     Serial.println("left");
     left();
     i=0;
    }

    else if(str[i-1]=='3')
    {
      Serial.println("right");
      right();
      i=0;
    }
    
    else if(str[i-1]=='4')
    {
      Serial.println("backward");
      backward();
      i=0;
    }

    else if(str[i-1]=='5')
    {
      Serial.println("Stop");
      Stop();
      i=0;
    }
    else if(str[i-1]=='6')
    {
      Serial.println("trigservo");
      trigservo();
      i=0;
    }

    else if(str[i-1]=='7')
    {
      Serial.println("gunservo");
      gunservo();
      i=0;
    }

    delay(100);
  }    
}
long distanceSensor()
{
    digitalWrite(trigPin,HIGH);
  _delay_ms(500);
  digitalWrite(trigPin, LOW);
  
  duration=pulseIn(echoPin,HIGH); 
  //distance=(duration/2)/29.1; 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
  return cm;
}

long distance;
void loop() 
{
   for(pos3 = 0; pos3 <= 120; pos3 += 7) // goes from 0 degrees to 180 degrees 
  {      
    distance = distanceSensor();
    if(distance>=50 || distance == 0)//move motor when there is no obstacle
    {
      test.write(pos3);              // tell servo to go to position in variable 'pos' 
      motorControl();
    }
    else
    {
       Stop();
       trigservo();
      delay(15); 
    }
  } 
  for(pos3 = 120; pos3 >=0; pos3-=7)     // goes from 180 degrees to 0 degrees 
  {                       
     distance = distanceSensor();         
    if(distance>=50 || distance == 0)
    {
      test.write(pos3);              // tell servo to go to position in variable 'pos' 
      motorControl();
    }
    else
    {
       Stop();
       trigservo();
       delay(15); 

    }
  } 
 
  }
