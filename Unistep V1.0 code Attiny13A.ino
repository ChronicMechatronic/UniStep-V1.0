/*100% functional UniStep code for Attiny13A
Distributed under the GPL-3.0 V3 license
01/28/2024 by Chronic Mechatronic
With modifications suggested by Flo (change variables to uint8/16_t; add default case to switch statement)
and tested. (Attiny can be erased and reprogrammed in-situ)

Requires following voltage divider on PB3:
47K resistor from sensepin to ground, 47K resistor from sensepin to DIR input, generic diode from ENABLE input to sensepin (cathode connects to sensepin)
*/

#include <avr/io.h>
#include <avr/interrupt.h>

//input pins:
#define StepIn PB5
#define DirEnableIn PB3

volatile bool direction = 0;   //boolean for CW or CCW rotation
volatile uint8_t StepCount = 1;   // step counter variable
uint16_t DirEnval = 0;



void setup() {

  DDRB = DDRB | B00010111; //set PB3 and PB5 as inputs, the rest as outputs using direct port manipulation

  // Enable the pin change interrupt for PB0
  PCMSK |= _BV(PCINT5);
  GIMSK |= _BV(PCIE);
  
}





void loop() {
  
  DirEnval = analogRead(DirEnableIn);   //read analog input voltage for the combined direction/enable pin

  //set direction variable true or false depending on the voltage measured on the resistor divider. True = clockwise and false = anticlockwise
  if(DirEnval<256) {direction=false;}                         //direction of rotation is CCW if measured voltage under 1.25V
  else if(DirEnval>256 && DirEnval<600) {direction=true;}     //direction of rotation is CW if voltage between 1.25V and 2.93V

  while(analogRead(DirEnableIn)>600) {           //turn motor off while enable input is high
    PORTB = B00000000;
  }

    

  switch(StepCount) {               //Main step execution. Switches PB0 through PB4 via direct port manipulation depending on the current position in the halfstep sequence
    case 1:
    PORTB = B00000001;
    break;
    
    case 2:
    PORTB = B00000011;
    break;
    
    case 3:
    PORTB = B00000010;
    break;
    
    case 4:
    PORTB = B00000110;
    break;
    
    case 5:
    PORTB = B00000100;
    break;
    
    case 6:
    PORTB = B00010100;
    break;
    
    case 7:
    PORTB = B00010000;
    break;
    
    case 8:
    PORTB = B00010001;
    break;    
  
    default:
    PORTB = B00000000;    // turn off motor in case StepCount variable doesn't match expected value
    break;
  }



} //end of void loop



ISR (PCINT0_vect) {       //interrupt service routine: counts the step sequence up or down depending on the last known state of the direction pin

if(!digitalRead(StepIn)){ /*do nothing for interrupts triggered by a falling edge*/ }
else{

  if(direction){StepCount++;}       //advance step sequence if direction CW, lower count if CCW
  else {StepCount--;}
 

  if(StepCount>8) {StepCount=1;}          //reset step counter to keep count within the 8 designated halfsteps
  else if(StepCount<1) {StepCount=8;}   
}

}
