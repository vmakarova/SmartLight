#include "Arduino.h"


enum color {OFF, RED, YELLOW, GREEN};

class SensorMovement
{
    int _quantity = 0;
    unsigned long last_time = millis();
    
public:
    const static unsigned long  ONE_CAR_TIME = 1000;
    void init(){};
    void movementReaction();
    void quantityDecrease() {_quantity--;}
    int quantity(){return _quantity;}
};


class SmartLight {
    SensorMovement car_detection;
    SensorMovement people_detection;
    int green_pin_car, yellow_pin_car, red_pin_car;
    int green_pin_people, yellow_pin_people, red_pin_people;
    color previous_state = OFF;
    color state = OFF;
    unsigned long state_time = millis();
    const static unsigned long MIN_STATE_TIME = 1000;
    
    void next_state();
    //stable state: flashing yellow or standart light
    void unwork();
public:
    void init(int green_pin_c, int yellow_pin_c, int red_pin_c,
              int green_pin_p, int yellow_pin_p, int red_pin_p);
    
    virtual void detectCar(){ car_detection.movementReaction(); }
    virtual void detectPeople(){}
    virtual bool loop_check();
};
