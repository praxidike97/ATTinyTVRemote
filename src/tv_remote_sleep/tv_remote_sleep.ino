#include <IRremote.hpp>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

long current_time = 0;
int debounce_delay = 200;
long last_button_press = 0;

int pin_vol_up = 0;
int pin_vol_down = 1;
int pin_power = 2;

ISR(PCINT0_vect) {
  if (digitalRead(pin_vol_up) == LOW){
     IrSender.sendNEC(0x9867F20D, 32);
  }
  
  if (digitalRead(pin_vol_down) == LOW){
     IrSender.sendNEC(0x9867B04F, 32);
  }
  
  if (digitalRead(pin_power) == LOW){
     IrSender.sendNEC(0x98676A95, 32);
  }

  _delay_ms(200);
}


void setup() {
   // put your setup code here, to run once:
   //Serial.begin(115200);

   pinMode(pin_vol_up, INPUT_PULLUP);
   pinMode(pin_vol_down, INPUT_PULLUP);
   pinMode(pin_power, INPUT_PULLUP);

   //pinMode(2, INPUT_PULLUP);
   
   IrSender.begin(3);

   ADCSRA = 0; // ADC disabled
   GIMSK = 0b00010000;  // General Interrupt Mask Register, / Bit 5 – PCIE: Pin Change Interrupt Enable / When the PCIE bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt is enabled. Any change on any enabled PCINT[5:0] pin will cause an interrupt. The corresponding interrupt of Pin Change Interrupt Request is executed from the PCI Interrupt Vector. PCINT[5:0] pins are enabled individually by the PCMSK0 Register. / see https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
   PCMSK0 = 0b00000111; 
}

void loop() {
   sleep_enable();
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
   sleep_cpu(); 
}
