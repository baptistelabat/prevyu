/*
  Prevyu source code
  Prevyu is a project by Charly
  Prevyu is an object connected to the cloud.
  Prevyu get the rain forecast (with a raspberry), and relate it to the frequency
  of drops of water in oil.
  https://github.com/baptistelabat/prevyu/
 
 The circuit:
  - a water level sensor http://composants.e44.com/capteurs/capteurs-niveau-d-eau/capteur-niveau-eau-normalement-ouvert-SCR4.html is linking 0V to analog pin A0 (with a 10kohm pull up resistor to 5V)
  - an electromechanical relay commanding a 12V pump is connected to digital output pin 4 (and to ground and 5V)
  - an electromechanical relay commanding an 220V electrovanne is connected to pin 3 (and to ground and 5V)
 
 Program by Baptiste LABAT, 2013
 
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int valvePin = 3; // Analog output pin that the LED is attached to
const int analogInPin = A0;
const int pumpPin = 4;
const int ledPin = 13;

long dropCounter; // A counter of the number of drops since the last pumping action
float delayValue = 0.0; // The delay between two drops
int sensorValue; // The value of the water level sensor (0-1023)
String inputString = "";         // A string to hold incoming data
boolean stringComplete = false;  // Whether the string is complete
int outputValue = 0;
float receivedValue = 0.0;
int sensorMax = 1024;

boolean waterLevelWasUp = true;
boolean waterLevelIsUp = true;
boolean freeze = false;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
    pinMode(pumpPin, OUTPUT); 
    pinMode(valvePin, OUTPUT); 
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
  Serial.print("dropCounter: ");
  Serial.println(dropCounter);
  managePump();
  makeADrop();
}

void managePump() {
  sensorValue = analogRead(analogInPin);
  Serial.print("Sensor: ");
  Serial.println(sensorValue);
  
  waterLevelIsUp = sensorValue>sensorMax/2;
  
  if (dropCounter>150) //This should normaly never happen, the sensor should start the pump before
  {
    if (waterLevelIsUp)
    { //Too many drops without sensor activation: sensor is not working, stop everything!
      freeze = true;
    }
    else
    { //The sensor was reset, restart normaly
      freeze = false;
    }
  }
  
  if (!waterLevelIsUp) //Not enough water, it is time to activate the pump
  {
    
    if (waterLevelWasUp) //normal case, the level was previously up
    { 
      //Active the pump for a few seconds (if not freezed)
      if (!freeze)
      {
        digitalWrite(pumpPin, HIGH);
        Serial.println("Pumping");
        delay(1000);
        digitalWrite(pumpPin, LOW);
        Serial.println("Stop pumping");
        delay(2000);
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
    if (!waterLevelWasUp) // The level was previously up, the sensor is working
    {
      freeze = false;
    }
    digitalWrite(pumpPin, LOW);
  }
  waterLevelWasUp = waterLevelIsUp;
}

void makeADrop() {
  /* Map the drop frequency to the precipitation (0-0.4inch/hr normalised to 0-255)*/
  Serial.println(int(receivedValue));
  if (receivedValue < 1)
  {
      Serial.println("No rain");
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(valvePin, LOW);    // turn the LED off by making the voltage LOW
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
       digitalWrite(valvePin, LOW);    // turn the valve off by making the voltage LOW
       delay(delayValue);         // wait for a second
       digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
       if (!freeze) //only if no problem
       {
         digitalWrite(valvePin, HIGH);   // turn the flow on (HIGH is the voltage level)
         dropCounter++;
       }
       delay(1100);               // wait for a second
       
       digitalWrite(ledPin, LOW);
       digitalWrite(valvePin, LOW); 
       
   }
}
