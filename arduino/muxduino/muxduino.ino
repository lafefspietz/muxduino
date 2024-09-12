
/*
*test code for building 16 bit switch controller for muxduino
*
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// It is very important to change this based on if you have a Mega or UNO, since the A5 pin maps to different digital output pins
// A5 maps to 19 on the UNO and 59 on the Mega  

//#define PIN 59 // MEGA 
#define PIN 6 // UNO

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // 
//there are 6

// When setting up the NeoPixel library, we tell it how many pixels,  
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


//define bit numbers on the Cryoelec controller and map them to Arduino pins

#define input1 13
#define input2 12
#define input3 11
#define input4 10
#define input5 9
#define input6 8
#define input7 7
#define input8 6

#define output1 14
#define output2 15
#define output3 16
#define output4 17
#define output5 4
#define output6 3
#define output7 2
#define output8 1

int inputbits[8] = {0,0,0,0,0,0,0,0};
int outputbits[8] = {0,0,0,0,0,0,0,0};

int analog = 0;// variable which reads out the analog input from the button ladder
int delta = 20;//the acceptable difference between an analog value and an expected button state value
int mode = 1;//modes are 1,2,3,4,5,6 which are pixel 5,4,3,2,1, and 0 respectively, mode 0 is off, mode -1 is color cycle with all switches off
int cycle = 0;//variable for cycling colors as test pattern with switch off

int switchstate = 0;
String inString = "";  // string to hold input

void setup() {
    Serial.begin(9600);//set the baud rate to 9600 baud.

    //Set all bits to digital output mode:

/*
    pinMode(input1,OUTPUT);
    pinMode(input2,OUTPUT);
    pinMode(input3,OUTPUT);
    pinMode(input4,OUTPUT);
    pinMode(input5,OUTPUT);
    pinMode(input6,OUTPUT);
    pinMode(input7,OUTPUT);
    pinMode(input8,OUTPUT);

    pinMode(ouput1,OUTPUT);
    pinMode(ouput2,OUTPUT);
    pinMode(ouput3,OUTPUT);
    pinMode(ouput4,OUTPUT);
    pinMode(ouput5,OUTPUT);
    pinMode(ouput6,OUTPUT);
    pinMode(ouput7,OUTPUT);
    pinMode(ouput8,OUTPUT);

    //set all pins low to start off with
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);
    digitalWrite(input3,LOW);
    digitalWrite(input4,LOW);
    digitalWrite(input5,LOW);
    digitalWrite(input6,LOW);
    digitalWrite(input7,LOW);
    digitalWrite(input8,LOW);
    digitalWrite(output1,LOW);
    digitalWrite(output2,LOW);
    digitalWrite(output3,LOW);
    digitalWrite(output4,LOW);
    digitalWrite(output5,LOW);
    digitalWrite(output6,LOW);
    digitalWrite(output7,LOW);
    digitalWrite(output8,LOW);
  */

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}





void loop() {


  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  
  // compare the analog value to all of the various button state values.  
  // This is a probe to see which node on a many-stage voltage divider
  //  is connected to the analog pin, which tests which button is pressed.
  // We check again after a milisecond to make sure the button state 
  // is stable and is not part of a transient signal.

/*
  analog = analogRead(A4);//read the analog voltage from the button ladder

  if(analog > 1024 - delta){
    delay(1);
    analog = analogRead(A4);
    if(analog > 1023 - delta){
       mode = 1;      
    }
  }
  if(analog > 784 - delta && analog < 784 + delta){
    delay(5);
    analog = analogRead(A4);
    if(analog > 784 - delta && analog < 784 + delta){
         mode = 2; 
    }
  }
  if(analog > 596 - delta && analog < 596 + delta){
     delay(5);
     analog = analogRead(A4);

    if(analog > 596 - delta && analog < 596 + delta){
      mode = 3;    
    }
  }

  if(analog > 437 - delta && analog < 437 + delta){
     delay(1);
     analog = analogRead(A4);

    if(analog > 437 - delta && analog < 437 + delta){
      mode = 4;    
    }
  }

  if(analog > 290 - delta && analog < 290 + delta){
     delay(1);
     analog = analogRead(A4);

    if(analog > 290 - delta && analog < 290 + delta){
      mode = 5;    
    }
  }

  if(analog > 158 - delta && analog < 158 + delta){
     delay(1);
     analog = analogRead(A4);

    if(analog > 158 - delta && analog < 158 + delta){
      mode = 6;    
    }
  }

  if(analog > 188 - delta && analog < 188 + delta){
     analog = analogRead(A4);
     mode = -1;    
  }
*/
//switchstate = 0;
 while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      switchstate = inString.toInt();
      Serial.println(inString);

      Serial.println("INPUTS:");
      for(int index = 0;index < 8;index++){
        inputbits[index] = (switchstate>>(15-index))&1;       
      }
      for(int index = 0;index < 8;index++){
        Serial.print(String(inputbits[index]));
      }
      Serial.println();
      Serial.println("OUTPUTS:");
      for(int index = 0;index < 8;index++){
        outputbits[index] = (switchstate>>(7 - index))&1;       
      }
      for(int index = 0;index <8;index++){
        Serial.print(String(outputbits[index]));
      }

//      Serial.println((switchstate>>3)&1);
      Serial.println();
      // clear the string for new input:
      inString = "";
    }
  }
  for(int index = 0;index < 8;index++){
      if(inputbits[7 - index] == 1){
          pixels.setPixelColor(index + 8, pixels.Color(255, 0, 0));    
      } 
      else{
          pixels.setPixelColor(index + 8, pixels.Color(0, 0, 0));    
      }   
  }
  for(int index = 0;index < 8;index++){
      if(outputbits[7 - index] == 1){
          pixels.setPixelColor(index, pixels.Color(0, 0, 255));    
      } 
      else{
          pixels.setPixelColor(index, pixels.Color(0, 0, 0));    
      }   
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(1); // Pause before next pass through loop

 
}
