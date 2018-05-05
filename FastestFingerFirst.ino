const int buttonPin1 = 2;
const int buttonPin2 = 3;
int buttonState[10];
int timerStatus = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(3,INPUT);//pushButton 1
  pinMode(4,INPUT);//pushButton 2
  pinMode(5,INPUT);//pushButton 3
  pinMode(6,INPUT);//pushButton 4
  pinMode(7,INPUT);//pushButton 5
  pinMode(8,INPUT);//pushButton 6
  pinMode(9,INPUT);//pushButton 7
  pinMode(10,INPUT);//pushButton 8
  pinMode(11,INPUT);//pushButton 9
  pinMode(12,INPUT);//pushButton 10
    
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState[0] = digitalRead(3);
  buttonState[1] = digitalRead(4);
  buttonState[2] = digitalRead(5);
  buttonState[3] = digitalRead(6);
  buttonState[4] = digitalRead(7);
  buttonState[5] = digitalRead(8);
  buttonState[6] = digitalRead(9);
  buttonState[7] = digitalRead(10);
  buttonState[8] = digitalRead(11);
  buttonState[9] = digitalRead(12);

  if(Serial.available())
    {
        if(Serial.read() == 48)//48 ASCII code of 0
          Serial.println("I am Working fine!!!");
    }
 if(buttonState[0] == HIGH)
    Serial.println(1);
 if(buttonState[1] == HIGH)
    Serial.println(2);
 if(buttonState[2] == HIGH)
    Serial.println(3);
 if(buttonState[3] == HIGH)
    Serial.println(4);
 if(buttonState[4] == HIGH)
    Serial.println(5);
 if(buttonState[5] == HIGH)
    Serial.println(6);
 if(buttonState[6] == HIGH)
    Serial.println(7);
 if(buttonState[7] == HIGH)
    Serial.println(8); 
 if(buttonState[8] == HIGH)
    Serial.println(9);
 if(buttonState[9] == HIGH)
    Serial.println(0);
    

}
