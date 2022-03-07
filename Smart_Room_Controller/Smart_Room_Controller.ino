/*
   Prodject: Smart Room Controller
   Description: mid-term project
   Aauthor: Dennis Davis
   Date: March 7, 2022
*/

//#include <TM1637.h>
#include<math.h>
int water = 0;
const int button1 = 22;
int sensor = 23;
int sensorPin = 21;
bool buttonState;
int oldButton;
int pushButton;
int onOff;
//int clk = 20;
//int dio = 19;
//TM1637 tm1637(clk,dio);
int led = 3;
int mic = 14;
int DBlevel;
int lastTime;
int currentTime;


void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  digitalWrite(sensor, OUTPUT);
  pinMode(sensorPin, OUTPUT);
  //  tm1637.init();
  //  tm1637(BRIGHT_TYPICAL);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(mic, INPUT);
}

void loop() {

  currentTime=millis();
  
  //if ((currentTime - lastTime) > 3000) {
    DBlevel = analogRead(mic);
    Serial.printf("%i\n", DBlevel);
    //lastTime = millis();
  //}


  water = analogRead(sensor);
  //Serial.printf("%i\n", water);
  buttonState = digitalRead(button1);
  if (buttonState != oldButton) {
    if (buttonState == true) {
      onOff = !onOff;
    } else {
      oldButton = buttonState;
    }
  }
//  Serial.printf("%i\n", buttonState);
//  Serial.printf("onOff:%i\n", onOff);

  if (onOff == true) {
    digitalWrite(sensorPin, HIGH);
  } else {
    digitalWrite(sensorPin, LOW);
  }
  analogRead(water);
  if (water > 100) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

}
