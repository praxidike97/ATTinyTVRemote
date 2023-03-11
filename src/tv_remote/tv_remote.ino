#include <IRremote.hpp>

long current_time = 0;
int debounce_delay = 200;
long last_button_press = 0;

int pin_vol_up = 0;
int pin_vol_down = 1;
int pin_power = 2;

void setup() {
   // put your setup code here, to run once:
   //Serial.begin(115200);

   pinMode(pin_vol_up, INPUT_PULLUP);
   pinMode(pin_vol_down, INPUT_PULLUP);
   pinMode(pin_power, INPUT_PULLUP);

   //pinMode(2, INPUT_PULLUP);
   
   IrSender.begin(3);
}

void loop() {
   current_time = millis();

   if (digitalRead(pin_power) == LOW and current_time - debounce_delay > last_button_press){
      IrSender.sendNEC(0x98676A95, 32);
      last_button_press = current_time;
   }

   if (digitalRead(pin_vol_up) == LOW and current_time - debounce_delay > last_button_press){
      IrSender.sendNEC(0x9867F20D, 32);
      last_button_press = current_time;
   }

   if (digitalRead(pin_vol_down) == LOW and current_time - debounce_delay > last_button_press){
      IrSender.sendNEC(0x9867B04F, 32);
      last_button_press = current_time;
   }
  
}
