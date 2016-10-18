#include "SmartLight.h"



void SensorMovement::movementReaction()
{
    unsigned long tmp_time = millis();
    // this car  has already been taken into account
    if (tmp_time - last_time <  ONE_CAR_TIME)
        return;
    _quantity++;
    last_time = tmp_time;   
}


void SmartLight::next_state()
{
    color tmp = state;
    switch (tmp) {
        case OFF: {
            state = GREEN;
            break;
        }
        case YELLOW:
        {
            if (previous_state == GREEN)
              state = RED;
            else
              state = GREEN;
            break;
        }
        default:
        {
            state = YELLOW;
            break;
        }
      }
      previous_state = tmp;
      state_time = millis();
}


void SmartLight::unwork()
{
  unsigned long tmp_time = millis();
  if (car_detection.quantity() == 0 && people_detection.quantity() == 0 &&
     (tmp_time - state_time > MIN_STATE_TIME)){
      next_state();
  }
}


void SmartLight::init(int green_pin_c, int yellow_pin_c, int red_pin_c,
                      int green_pin_p = 0, int yellow_pin_p = 0, int red_pin_p = 0)
{
   green_pin_car = green_pin_c;
   yellow_pin_car= yellow_pin_c;
   red_pin_car = red_pin_c;
   green_pin_people = green_pin_p;
   yellow_pin_people = yellow_pin_p;
   red_pin_people = red_pin_p;
   car_detection.init();
   people_detection.init();
}

bool SmartLight::loop_check()
{
   if (car_detection.quantity() > 0){
       color tmp = state;
       switch(tmp){
           case GREEN:
           {
               if (millis() - state_time > MIN_STATE_TIME)
               {
                   car_detection.quantityDecrease();
                   state_time = millis();
               }
               break;
           }
           case RED:
           { 
               digitalWrite(red_pin_car, LOW);
               digitalWrite(yellow_pin_car, HIGH);
	       state = YELLOW;
               state_time = millis();
               break;
           }
           case YELLOW: 
           {
               if (millis() - state_time > MIN_STATE_TIME)
               {
                   digitalWrite(yellow_pin_car, LOW);
                   digitalWrite(green_pin_car, HIGH);
		   state = GREEN;
                   state_time = millis();
               }
               break;
           }
       }
       return true;
   }
   unwork();
   return false;
}
