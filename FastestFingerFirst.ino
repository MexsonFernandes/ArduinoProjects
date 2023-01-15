int buttonState[10];

void setup() {
  for(int i = 3; i < 13; i++)
    pinMode(i,INPUT);
  Serial.begin(9600);
}

void loop() {
    int i;
    for(i = 0; i < 10; i++){
        buttonState[i] = digitalRead(i + 3);
        if(buttonState[i] && i < 10) Serial.println(i + 1);
        else if(buttonState[i] && i == 9) Serial.println(i + 1);
    }

    if(Serial.available())
    {
        if(Serial.read() == 48)//48 ASCII code of 0
            Serial.println("I am Working fine!!!");
    }   
}
