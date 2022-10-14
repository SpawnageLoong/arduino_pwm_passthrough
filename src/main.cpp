#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile int onOff12 = 0;
static volatile int onOff13 = 0;

void setup() {
  // External Interrupt Control Register A (EICRA)
  // A rising edge on INT0 and INT1 generates an interrupt request
  EICRA |= 0b00001111;

  // External Interrupt Mask Register (EIMSK)
  // Enable both external interrupt pins
  EIMSK |= 0b00000011;

  // Port B Data Direction Register (DDRB)
  // Set pins PB4 (Arduino Pin 12) and PB5 (Arduino Pin 13) to OUTPUT
  DDRB |= 0b00110000;

  // Enable interrupts
  sei();

  //Serial.begin(9600);
}

// Interrupt Service Routine (ISR) for INT0
ISR(INT0_vect){
  // Toggle the state of the flag
  onOff12 = 1-onOff12;
  //Serial.print(onOff12);

  // Set PB4 based on flag, change interrupt pin behaviour
  if(onOff12==0){
    PORTB &= 0b11101111;
    EICRA |= 0b00000011;
  }
  else{
    PORTB |= 0b00010000;
    EICRA &= 0b00000010;
  }
}

// Interrupt Service Routine (ISR) for INT1
ISR(INT1_vect){
  // Toggle the state of the flag
  onOff13 = 1-onOff12;

  // Set PB5 based on flag
  if(onOff13==0){
    PORTB &= 0b11011111;
  }
  else{
    PORTB |= 0b00100000;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}