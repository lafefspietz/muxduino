
/*
*test code for building 16 bit switch controller for muxduino
*
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

// Which pin on the Arduino is connected to the NeoPixels?

#define PIN 5 // UNO

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // 
//there are 16

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

#define output1 17//this set of 4 pins{17,16,15,14} are reversed from what the silk screen says
#define output2 16
#define output3 15
#define output4 14
#define output5 4
#define output6 3
#define output7 2
#define output8 1

int inputbits[8] = {0,0,0,0,0,0,0,0};
int outputbits[8] = {0,0,0,0,0,0,0,0};

int buttonlevels[8] = {1023,823,665,536,424,321,220,114};


int inputbuttons = 0;// variable which reads out the analog input from the button ladder
int outputbuttons = 0;// variable which reads out the analog input from the button ladder
int inputbuttonsprev = 0;
int outputbuttonsprev = 0;

int delta = 20;//the acceptable difference between an analog value and an expected button state value
int mode = 1;//modes are 1,2,3,4,5,6 which are pixel 5,4,3,2,1, and 0 respectively, mode 0 is off, mode -1 is color cycle with all switches off
int cycle = 0;//variable for cycling colors as test pattern with switch off

int switchstate = 0;
String inString = "";  // string to hold input

void setup() {
    Serial.begin(9600);//set the baud rate to 9600 baud.

    //Set all bits to digital output mode:

    pinMode(input1,OUTPUT);
    pinMode(input2,OUTPUT);
    pinMode(input3,OUTPUT);
    pinMode(input4,OUTPUT);
    pinMode(input5,OUTPUT);
    pinMode(input6,OUTPUT);
    pinMode(input7,OUTPUT);
    pinMode(input8,OUTPUT);

    pinMode(output1,OUTPUT);
    pinMode(output2,OUTPUT);
    pinMode(output3,OUTPUT);
    pinMode(output4,OUTPUT);
    pinMode(output5,OUTPUT);
    pinMode(output6,OUTPUT);
    pinMode(output7,OUTPUT);
    pinMode(output8,OUTPUT);

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
  
inputbuttons = analogRead(A5);//read the analog voltage from the button ladder
outputbuttons = analogRead(A4);//read the analog voltage from the button ladder

if(inputbuttonsprev == 0){

  if(inputbuttons > buttonlevels[0] - delta){
    delay(1);
    inputbuttons = analogRead(A5);
    if(inputbuttons > buttonlevels[0] - delta){
        inputbits[0] = !inputbits[0];
    }
  }
  if(inputbuttons > buttonlevels[1] - delta && inputbuttons < buttonlevels[1] + delta){
    delay(1);
    inputbuttons = analogRead(A5);
    if(inputbuttons > buttonlevels[1] - delta && inputbuttons < buttonlevels[1] + delta){
        inputbits[1] = !inputbits[1];
    }
  }
  if(inputbuttons > buttonlevels[2] - delta && inputbuttons < buttonlevels[2] + delta){
     delay(1);
     inputbuttons = analogRead(A5);
    if(inputbuttons > buttonlevels[2] - delta && inputbuttons < buttonlevels[2] + delta){
        inputbits[2] = !inputbits[2];
    }
  }

  if(inputbuttons > buttonlevels[3] - delta && inputbuttons < buttonlevels[3] + delta){
     delay(1);
     inputbuttons = analogRead(A5);

    if(inputbuttons > buttonlevels[3] - delta && inputbuttons < buttonlevels[3] + delta){
        inputbits[3] = !inputbits[3];
    }
  }

  if(inputbuttons > buttonlevels[4] - delta && inputbuttons < buttonlevels[4] + delta){
     delay(1);
     inputbuttons = analogRead(A5);

    if(inputbuttons > buttonlevels[4] - delta && inputbuttons < buttonlevels[4] + delta){
        inputbits[4] = !inputbits[4];
    }
  }

  if(inputbuttons > buttonlevels[5] - delta && inputbuttons < buttonlevels[5] + delta){
     delay(1);
     inputbuttons = analogRead(A5);

    if(inputbuttons > buttonlevels[5] - delta && inputbuttons < buttonlevels[5] + delta){
        inputbits[5] = !inputbits[5];
    }
  }

  if(inputbuttons > buttonlevels[6] - delta && inputbuttons < buttonlevels[6] + delta){
     delay(1);
     inputbuttons = analogRead(A5);

    if(inputbuttons > buttonlevels[6] - delta && inputbuttons < buttonlevels[6] + delta){
        inputbits[6] = !inputbits[6];
    }
  }

  if(inputbuttons > buttonlevels[7] - delta && inputbuttons < buttonlevels[7] + delta){
     delay(1);
     inputbuttons = analogRead(A5);
    if(inputbuttons > buttonlevels[7] - delta && inputbuttons < buttonlevels[7] + delta){
        inputbits[7] = !inputbits[7];
    }
  }
}

if(outputbuttonsprev == 0){
  if(outputbuttons > buttonlevels[0] - delta){
    delay(1);
    outputbuttons = analogRead(A4);
    if(outputbuttons > buttonlevels[0] - delta){
        outputbits[0] = !outputbits[0];
    }
  }
  if(outputbuttons > buttonlevels[1] - delta && outputbuttons < buttonlevels[1] + delta){
    delay(1);
    outputbuttons = analogRead(A4);
    if(outputbuttons > buttonlevels[1] - delta && outputbuttons < buttonlevels[1] + delta){
        outputbits[1] = !outputbits[1];
    }
  }
  if(outputbuttons > buttonlevels[2] - delta && outputbuttons < buttonlevels[2] + delta){
     delay(1);
     outputbuttons = analogRead(A4);
    if(outputbuttons > buttonlevels[2] - delta && outputbuttons < buttonlevels[2] + delta){
        outputbits[2] = !outputbits[2];
    }
  }

  if(outputbuttons > buttonlevels[3] - delta && outputbuttons < buttonlevels[3] + delta){
     delay(1);
     outputbuttons = analogRead(A4);

    if(outputbuttons > buttonlevels[3] - delta && outputbuttons < buttonlevels[3] + delta){
        outputbits[3] = !outputbits[3];
    }
  }

  if(outputbuttons > buttonlevels[4] - delta && outputbuttons < buttonlevels[4] + delta){
     delay(1);
     outputbuttons = analogRead(A4);

    if(outputbuttons > buttonlevels[4] - delta && outputbuttons < buttonlevels[4] + delta){
        outputbits[4] = !outputbits[4];
    }
  }

  if(outputbuttons > buttonlevels[5] - delta && outputbuttons < buttonlevels[5] + delta){
     delay(1);
     outputbuttons = analogRead(A4);

    if(outputbuttons > buttonlevels[5] - delta && outputbuttons < buttonlevels[5] + delta){
        outputbits[5] = !outputbits[5];
    }
  }

  if(outputbuttons > buttonlevels[6] - delta && outputbuttons < buttonlevels[6] + delta){
     delay(1);
     outputbuttons = analogRead(A4);

    if(outputbuttons > buttonlevels[6] - delta && outputbuttons < buttonlevels[6] + delta){
        outputbits[6] = !outputbits[6];
    }
  }

  if(outputbuttons > buttonlevels[7] - delta && outputbuttons < buttonlevels[7] + delta){
     delay(1);
     outputbuttons = analogRead(A4);
    if(outputbuttons > buttonlevels[7] - delta && outputbuttons < buttonlevels[7] + delta){
        outputbits[7] = !outputbits[7];
    }
  }
}

inputbuttonsprev = inputbuttons;
outputbuttonsprev = outputbuttons;


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
      //Serial.println(inString);

     // Serial.println("INPUTS:");
      for(int index = 0;index < 8;index++){
        inputbits[index] = (switchstate>>(15-index))&1;       
      }
      for(int index = 0;index < 8;index++){
       // Serial.print(String(inputbits[index]));
      }
     // Serial.println();
     // Serial.println("OUTPUTS:");
      for(int index = 0;index < 8;index++){
        outputbits[index] = (switchstate>>(7 - index))&1;       
      }
      for(int index = 0;index <8;index++){
       // Serial.print(String(outputbits[index]));
      }

//      Serial.println((switchstate>>3)&1);
     // Serial.println();
      // clear the string for new input:
      inString = "";
    }
  }

  for(int index = 0;index < 8;index++){
      if(inputbits[7 - index] == 1){
          pixels.setPixelColor(index, pixels.Color(255, 0, 0));    
      } 
      else{
          pixels.setPixelColor(index, pixels.Color(0, 0, 0));    
      }   
  }
  for(int index = 0;index < 8;index++){
      if(outputbits[7 - index] == 1){
          pixels.setPixelColor(index +8, pixels.Color(0, 0, 255));    
      } 
      else{
          pixels.setPixelColor(index + 8, pixels.Color(0, 0, 0));    
      }   
  }
  pixels.show();   // Send the updated pixel colors to the hardware.

    digitalWrite(input1,inputbits[0]);
    digitalWrite(input2,inputbits[1]);
    digitalWrite(input3,inputbits[2]);
    digitalWrite(input4,inputbits[3]);
    digitalWrite(input5,inputbits[4]);
    digitalWrite(input6,inputbits[5]);
    digitalWrite(input7,inputbits[6]);
    digitalWrite(input8,inputbits[7]);
    digitalWrite(output1,outputbits[0]);
    digitalWrite(output2,outputbits[1]);
    digitalWrite(output3,outputbits[2]);
    digitalWrite(output4,outputbits[3]);
    digitalWrite(output5,outputbits[4]);
    digitalWrite(output6,outputbits[5]);
    digitalWrite(output7,outputbits[6]);
    digitalWrite(output8,outputbits[7]);

  delay(1); // Pause before next pass through loop

 
}
