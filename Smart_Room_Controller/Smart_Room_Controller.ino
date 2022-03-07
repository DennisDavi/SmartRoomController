/*
   Prodject: Smart Room Controller
   Description: mid-term project 
   Aauthor: Dennis Davis
   Date: March 7, 2022
*/

int water=0;
const int button1= 22;
int sensor=23;
int sensorPin=21;
bool buttonState;
int oldButton;
int pushButton;
int onOff;


void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  digitalWrite(sensor, OUTPUT);
  pinMode(sensorPin,OUTPUT);

}

void loop() {
  
  water=analogRead(sensor);
  Serial.printf("%i\n",water);
  buttonState=digitalRead(button1);
  if (buttonState!=oldButton){
    if(buttonState==true){
      onOff=!onOff;
    }else{
      oldButton=buttonState;
    }
  }
  //Serial.printf("%i\n",buttonState);
  Serial.printf("onOff:%i\n",onOff);

  if(onOff==true){
    digitalWrite(sensorPin,HIGH);
  }else{
    digitalWrite(sensorPin,LOW);
  }

}
