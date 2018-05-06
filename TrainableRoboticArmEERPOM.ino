
#include <Servo.h>
#include <EEPROM.h>

#define CALIB_MAX 512
#define CALIB_MIN 100
#define SAMPLE_DELAY 500 // in ms, 50ms seems good

uint8_t recordButtonPin = 6;
uint8_t playButtonPin = 7;
uint8_t flashButton = 4;

int number_of_reading = 0;
//servo motor pin definition
uint8_t servoPin = 3;
uint8_t servoPin1 = 9;
uint8_t servoPin2 = 10;
//uint8_t servoPin3 = 11;
//uint8_t servoPin4 = 12;
//uint8_t servoPin5 = 2;

//feedback pin definition
uint8_t feedbackPin = A0;
uint8_t analogPin1 = A1;
uint8_t analogPin2 = A2;
//uint8_t analogPin3 = A3;
//uint8_t analogPin4 = A4;

uint8_t ledPin = 2;

Servo myServo1, myServo2, myServo3, myServo4, myServo5, myServo6; 
//base at servo1
//gripper at servo5
  
void setup() {
  Serial.begin(9600);
  pinMode(recordButtonPin, INPUT);
  digitalWrite(recordButtonPin, HIGH);
  pinMode(playButtonPin, INPUT);
  pinMode(flashButton, INPUT);
  digitalWrite(flashButton, HIGH);
  digitalWrite(playButtonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  Serial.println("Servo Record-Play started...(Prashant Sharma's Robotic Arm)");
  myServo1.write(0);
  delay(500);
  myServo2.write(0);
  delay(500);
  myServo3.write(0);
  delay(500);
  myServo4.write(0);
  delay(500);
  myServo5.write(0);
  delay(500);
  myServo6.write(0);
  delay(500);
}

void loop() {
  //flash memory
  if (! digitalRead(flashButton)) {
    uint16_t address = 0;
    delay(10);
    while (! digitalRead(recordButtonPin));
    delay(20);
    Serial.println("Flashing memory...");
    while(address<=512){
      EEPROM.write(address, 90);
      address++;
     }
     Serial.println("Done flashing memory...");
  }
  
  //start recording when record button is pressed
 if (! digitalRead(recordButtonPin)) {
   delay(10);
   // wait for button to be released
   while (! digitalRead(recordButtonPin));
   delay(20);
   // OK released!
   recordServo(servoPin, feedbackPin, recordButtonPin);
 }

 //start playing when play button is pressed
  if (! digitalRead(playButtonPin)) {
   delay(10);
   // wait for button to be released
   while (! digitalRead(playButtonPin));
   delay(20);
   // OK released!
   playServo(servoPin, playButtonPin);
 }
}
uint8_t y;//compute angle for extra motor 
void playServo(uint8_t servoPin, uint8_t buttonPin) {
  uint16_t addr = 0;
  Serial.println("Playing");

  myServo1.attach(servoPin);
  myServo2.attach(servoPin1);
  myServo3.attach(servoPin2);

  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
//  myServo4.attach(servoPin3);
//  myServo5.attach(servoPin4);
//  myServo6.attach(servoPin5);
  while (digitalRead(buttonPin)) { 
    if(number_of_reading == addr)
      break;   
    uint8_t x = writeServo(addr);
    if (x== -1)
    break;
    myServo1.write(x);
    delay(SAMPLE_DELAY);
    addr++;
    x = writeServo(addr);
    if (x== -1)
    break;
    //y = 180-x;
    myServo2.write(x);
    //myServo3.write(y);
    delay(SAMPLE_DELAY);
    addr++;
    x = writeServo(addr);
    if (x== -1)
    break;
    myServo3.write(x);
    delay(SAMPLE_DELAY);
    addr++;
//    x = writeServo(addr);
//    if (x== -1)
//    break;
//    myServo5.write(x);
//    delay(SAMPLE_DELAY);
//    addr++;
//    x = writeServo(addr);
//    if (x== -1)
//    break;
//    myServo6.write(x);
//    delay(SAMPLE_DELAY);
//    addr++;
    if (addr == 512) break;
  }
  Serial.println("Done");
  myServo1.detach();
  myServo2.detach();
  myServo3.detach();
  myServo4.detach();
//  myServo5.detach();
//  myServo6.detach();
  delay(250);  
}

uint8_t writeServo(uint16_t addr)
{
  uint8_t x = EEPROM.read(addr);
    Serial.print("Reading data : "); Serial.print(x);
    //if (x == 255) return -1;
    // map to 0-180 degrees
    x = map(x, 0, 254, 0, 180);
    Serial.print(" -> "); Serial.println(x);
    if (addr==0) delay(1000); //to set motor to inital position
    return x;
}

void recordServo(uint8_t servoPin, uint8_t analogPin, uint8_t buttonPin) {
  uint16_t addr = 0;
  number_of_reading =0;
  Serial.println("Recording");
  digitalWrite(ledPin, HIGH);
    
  pinMode(analogPin, INPUT); 
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
//  pinMode(analogPin3, INPUT);
//  pinMode(analogPin4, INPUT);
  
  while (digitalRead(buttonPin)) {

     //do this for one motor
     uint16_t a = analogRead(analogPin); 
     recordServoWrite(a, addr, 1);
     addr++;
     delay(SAMPLE_DELAY);
     uint16_t b = analogRead(analogPin1);
     recordServoWrite(b, addr, 2);
     addr++;
     delay(SAMPLE_DELAY);
     uint16_t c = analogRead(analogPin2);
     recordServoWrite(c, addr, 3);
     addr++;
     delay(SAMPLE_DELAY);
//     uint16_t d = analogRead(analogPin3);
//     recordServoWrite(d, addr, 4);
//     addr++;
//     delay(SAMPLE_DELAY);
//     uint16_t e = analogRead(analogPin4);
//     recordServoWrite(e, addr, 5);
//     addr++;
//     delay(SAMPLE_DELAY);
     
     if (addr == 512) break;
     delay(SAMPLE_DELAY);
  }
  if (addr != 512) EEPROM.write(addr, 255);

  digitalWrite(ledPin, LOW);

  Serial.println("Done");
  number_of_reading = addr;
  delay(250);
}
void recordServoWrite(uint16_t a, uint16_t addr, int motor)
{
     Serial.print("Read analog from motor " + String(motor) +" : "); 
     Serial.print(a);
     if (a < CALIB_MIN) a = CALIB_MIN;
     if (a > CALIB_MAX) a = CALIB_MAX;
     a = map(a, CALIB_MIN, CALIB_MAX, 0, 254);
     //a = map(a, 0, 1023, 0, 254);
     Serial.print(" -> "); Serial.println(a);
     EEPROM.write(addr, a);
}

