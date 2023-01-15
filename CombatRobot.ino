#define m11 12    // rear motor
#define m12 11
#define m21 10    // front motor
#define m22 8

#include <Servo.h> 

Servo test;      // create servo object to control a servo   GUN 
Servo myservo2;  // create servo object to control a servo   TRIG
Servo myservo3;  // create servo object to control a servo   Camera

int pos1 = 0, pos2 = 0, pos3 = 0;    // variable to store the servo position

int hasObstacle = LOW;  // HIGH MEANS NO OBSTACLE
int obstaclePin = 3;  // This is our input pin

char str[2], i;

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

void stop()
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
   delay(2000);
   for(pos1 = 0; pos1 <= 120; pos1 += 1)  // goes from 0 degrees to 180 degrees 
   {                                      // in steps of 1 degree 
   myservo1.write(pos1);               // tell servo to go to position in variable 'pos' 
   delay(50);                         // waits 15ms for the servo to reach the position 
   } 
   for(pos1 = 120; pos1 >=0; pos1-=1)  // goes from 180 degrees to 0 degrees 
   {                                
   myservo1.write(pos1);            // tell servo to go to position in variable 'pos' 
   delay(50);                      // waits 15ms for the servo to reach the position 
 }*/
}

void trigservo()
   {
   for(pos2 = 0; pos2 <= 35; pos2 += 1) // goes from 0 degrees to 180 degrees 
   {                                    // in steps of 1 degree 
      myservo2.write(pos2);             // tell servo to go to position in variable 'pos' 
      delay(15);                        // waits 15ms for the servo to reach the position 
  } 
  for(pos2 = 35; pos2 >=0; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
   myservo2.write(pos2);                // tell servo to go to position in variable 'pos' 
   delay(15);                           // waits 15ms for the servo to reach the position 
  } 
   
}

void camservo()
 {
   for(pos3 = 0; pos3 <= 160; pos3 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos' 
    delay(1);                       // waits 15ms for the servo to reach the position 
  } 
   for(pos3 = 160; pos3 >=0; pos3-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo3.write(pos3);              // tell servo to go to position in variable 'pos' 
    delay(1);                       // waits 15ms for the servo to reach the position 
  } 
   
  // motor4.run(FORWARD);     //PUMP on clock wise
   }

void setup() 
{
  test.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(6);  // attaches the servo on pin 6 to the servo object
  myservo3.attach(5);  // attaches the servo on pin 5 to the servo object

  pinMode(obstaclePin, INPUT);

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  Serial.begin(9600);
}

void motorControl()
{
    if(Serial.available())
    {
        char serialCommand = Serial.read();
        char newLn = Serial.read();

        Serial.print("Command ");
        Serial.print(serialCommand);
        Serial.print(" received, going ");
        
        switch(serialCommand)
        {
            case '1':
                Serial.println("forward");
                forward();
            break;
            case '2':
                Serial.println("left");
                left();
            break;
            case '3': 
                Serial.println("right");
                right();
            break;
            case '4': 
                Serial.println("backward");
                backward();
            break;
            case '5': 
                Serial.println("Stop");
                stop();
            break;
            case '6': 
                Serial.println("trigservo");
                trigservo();
            break;
            case '7': 
                Serial.println("gunservo");
                gunservo();
            break;
            case '8': 
                Serial.println("camservo");
                camservo();
            break;
        }
        delay(100);     
    }
}

void loop() 
{
    int posIt = 1;
    for(pos3 = 0; pos3 > -1; pos3 += posIt) // goes from 0 degrees to 180 degrees 
    {                   
        hasObstacle = digitalRead(obstaclePin);// in steps of 1 degree 
        if(hasObstacle)
        {
            char buff[4];
            itoa(pos3, buff, 10);
            Serial.print("Obstacle detected! Angle is: ");
            Serial.print(buff);
            Serial.println(" deg");
        }
        if(digitalRead(obstaclePin) == LOW)
        {
            test.write(pos3);              // tell servo to go to position in variable 'pos' 
            delay(50);                       // waits 15ms for the servo to reach the position 
            motorControl();
        }
        else
        {
            stop();
            trigservo();
        }
        if(pos3 == 120) posIt = -1;
    } 
}
