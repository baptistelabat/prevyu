/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogOutPin = 3; // Analog output pin that the LED is attached to
const int analogInPin = A0;
const int pumpPin = 4;
const int ledPin = 13;
long dropCounter;
float delayValue = 0.0;
int sensorValue;
String inputString = "";         // A string to hold incoming data
boolean stringComplete = false;  // Whether the string is complete
int outputValue = 0;
float receivedValue = 0.0;
boolean levelWasDown = true;
boolean levelIsDown = true;
boolean freeze = false;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
    pinMode(pumpPin, OUTPUT); 
    pinMode(analogOutPin, OUTPUT); 
}

void serialEvent() {
  inputString="";
  Serial.flush();
  while (Serial.available()) {
    // Get the new byte:
    char inChar = (char)Serial.read();
    // Add it to the inputString:
    inputString += inChar;
    // If the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }  
      char c[50];
      inputString.toCharArray(c, 50);
      receivedValue = StrToFloat(inputString); 
}
float StrToFloat(String str){
  char carray[str.length() + 1]; // Determine the size of the array
  str.toCharArray(carray, sizeof(carray)); // Put str into an array
  return atof(carray);
}

void loop() {    

  // print the results to the serial monitor:
        

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  sensorValue = analogRead(analogInPin);
  Serial.print("Sensor: ");
  Serial.println(sensorValue);
  levelIsDown = sensorValue>250;
  
  if (dropCounter>150) //This should normaly never happen
  {
    if (levelIsDown)
    { //Too many drops without sensor activation: sensor is not working, stop everything!
      freeze = true;
    }
    else
    { //The sensor was reset, restart normaly
      freeze = false;
    }
  }
  
  if (!levelIsDown) //It is time to activate the pump
  {
    
    if (levelWasDown) //normal case, the level was previously low
    { 
      //Active the pump for a few seconds (if not freezed)
      if (!freeze)
      {
        digitalWrite(pumpPin, HIGH);
        Serial.println("High");
        delay(5000);
        dropCounter = 0; //Reset the drop counter
      }
    }
    else
    {//We have just pumped, but the sensor value is not changing
    //which either means the sensor or the pump are not properly working: stop everything!
      freeze = true;
      digitalWrite(pumpPin, LOW);
    }
  }
  else
  {
    if (!levelWasDown) // The level was previously up, the sensor is working
    {
      freeze = false;
    }
    digitalWrite(pumpPin, LOW);
  }
  levelWasDown = (sensorValue>250);

  // change the analog out value:
  analogWrite(analogOutPin, int(receivedValue));
  Serial.println(int(receivedValue));
  if (receivedValue < 1)
  {
      Serial.println("No rain");
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(analogOutPin, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);               // wait for a second
  }
  else
   {
     if (receivedValue < 10)
     {
       delayValue = map(int(receivedValue), 1, 10, 20000, 10000);
     }   
     else
     {
       if (receivedValue < 60)
       {
         delayValue = map(int(receivedValue), 10, 60, 10000, 2000);
       }
       else
       {
         if (receivedValue >=255)
         {
           delayValue = 0;
         }
         else
         {
           delayValue = map(int(receivedValue), 60, 255, 2000, 0);
         }
       }
          
     }
       Serial.print("Delay: ");
       Serial.println(delayValue);
       digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
       digitalWrite(analogOutPin, LOW);    // turn the LED off by making the voltage LOW
       delay(delayValue);         // wait for a second
       digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
       if (!freeze) //only if not problem
       {
         digitalWrite(analogOutPin, HIGH);   // turn the flow on (HIGH is the voltage level)
         dropCounter++;
       }
       delay(900);               // wait for a second
       
   }
}
