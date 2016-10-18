
#include <SmartLight.h>
#define RED_PIN 8
#define YELLOW_PIN 7
#define GREEN_PIN 13
#define OFF_PIN 1000

const static int car_in_pin = 2;
const static int car_enable_pin = 4;

SmartLight light;

void setup() {
  pinMode(car_in_pin, INPUT);
  pinMode(car_enable_pin, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(car_enable_pin, HIGH);
}



void loop()
{
  byte v = digitalRead(car_in_pin);
  //movement
  if (v == LOW){
      light.detectCar();
  }
  light.loop_check();

}

