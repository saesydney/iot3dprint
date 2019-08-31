const int TxPin = 6;
int incomingText = 0;  

#include <SoftwareSerial.h>
SoftwareSerial myLCD= SoftwareSerial(255, TxPin);
//Serial.begin(9600)
void setup() {

pinMode(TxPin, OUTPUT);
digitalWrite(TxPin, HIGH);

myLCD.begin(9600);
delay(100);
myLCD.write(12);                             
myLCD.write(17);                
delay(5);                           
}

void loop()                    
{

   if (Serial.available() > 0) {
            incomingText= Serial.read();
            Serial.println(incomingText);
            myLCD.print(incomingText);
            delay(5000);
    }
}

//incomingText= Serial.read();
            //delay(1000);
            //Serial.print(incomingText, DEC);
            //delay(1000);
            //mySerial.print(incomingText);
