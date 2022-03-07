/*
   Prodject: Smart Room Controller
   Description: mid-term project 
   Aauthor: Dennis Davis
   Date: March 7, 2022
*/

int water=0;
const int button1= 22;
const int sensor=23;
bool buttonState;
int oldButton;
int pushButton;


void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(sensor, OUTPUT);

}

void loop() {
//  water=analogRead(sensor);
//  Serial.printf("%i\n",water);
  buttonState=digitalRead(button1);
  Serial.printf("%i\n",buttonState);
  

}
