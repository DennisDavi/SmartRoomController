/*
   Prodject: Smart Room Controller
   Description: mid-term project
   Aauthor: Dennis Davis
   Date: March 7, 2022
*/

//#include <TM1637.h>
#include<math.h>
#include<SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include<Adafruit_BME280.h>
#include<wemo.h>
#include<Ethernet.h>
#include<mac.h>
#include<hue.h>
int SCREEN_WIDTH = 128;
int SCREEN_HIGHT = 64;
int SCREEN_ADDRESS = 0x3c;
int OLED_RESET = 4;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme;
float tempC;
float tempF;
float pressPA;
float humidRH;
const char degree = 0xF8;
bool status;
int hexAddress = 0x76;
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
bool ledState=false;
int redled = 5;
int mic = 14;
int DBlevel;
int lastTime;
int currentTime;
int buzzer = 6;
bool buzzerState = false;
int theTime;
int wemoNum;
int HueColor;


void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.printf("SSD1306 allocation failed");
  }

  status = bme.begin(hexAddress);
  if (status == false) {
    Serial.printf("BME280 at address 0x%02X failed to start", hexAddress);
  }

  Ethernet.begin(mac);
  wemoNum=1;
  switchON(wemoNum);

  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(button1, INPUT);
  digitalWrite(sensor, OUTPUT);
  pinMode(sensorPin, OUTPUT);
  //  tm1637.init();
  //  tm1637(BRIGHT_TYPICAL);
  pinMode(led, OUTPUT);
  pinMode(redled, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(redled, LOW);
  pinMode(mic, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  testdrawstyles();
  tempC = bme.readTemperature();
  pressPA = bme.readPressure();
  humidRH = bme.readHumidity();

  tempF = tempC * (9.0 / 5.0) + 32.2;

  currentTime = millis();

  //if ((currentTime - lastTime) > 3000) {
  DBlevel = analogRead(mic);
  Serial.printf("DBlevel:%i\n", DBlevel);
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
    ledState=true;
    digitalWrite(led, HIGH);
  } else {
    ledState=false;
    digitalWrite(led, LOW);
  }


}

void testdrawstyles(void) {
  currentTime = millis();
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.printf("Temp:%0.1f%c\nwater sensor:%i\nhumid:%0.2f", tempF, degree, water, humidRH);
  display.display();


  if (humidRH > 45 && tempF >81 && ledState == true) {
    digitalWrite(redled, HIGH);
    if (buzzerState) {
      digitalWrite(buzzerState, true);
    } else {
      digitalWrite(redled, LOW);
      digitalWrite(buzzerState, false);
    }
    if ((currentTime - lastTime) > theTime) {
      buzzerState = !buzzerState;
      if (buzzerState) {
        digitalWrite(buzzer, HIGH);
        theTime = 35;
      } else {
        digitalWrite(buzzer, LOW);
        theTime = 2000;
      }
      lastTime = millis();
    }

  }
  if(humidRH > 55 && ledState == true){
    switchON(wemoNum);
  }else{
    switchOFF(wemoNum);
  }

  HueColor =map(tempF, 45, 100, 45000, 0);

  if(ledState == true){
    setHue(2,true,HueColor,255,255);
  }else{
    setHue(2,false,0,0,0);
  }



}
