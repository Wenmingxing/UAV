/*
 * This example is to test the Arduino Uno Relay Shield.
 * 
 * Editor: Luke
 * Date:01/12/2016
 * Ver:0.1
 * 
 # Hardware
   1.Arduino UNO
   2.Relay Shield
   3.Power Supply:7~12v
 
 */

byte relayPin[4]={2,7,8,10}; //D2->Relay1,D7->Relay2
                             //D8->Relay3,D10->Relay4
char input = 0;

int state;

void setup() {
  
for(int i =0;i<4;i++) pinMode(relayPin[i],OUTPUT);
Serial.begin(57600);
delay(100);
Serial.println("Press 1-4 to control the state of the relay");
Serial.println("Waiting for input:");
for(int i=0;i<4;i++) digitalWrite(relayPin[i],LOW);  

}

void loop() {
if(Serial.available())
{
  input = Serial.read();
  
  if(input != -1)
  {
    switch(input)
    { 
      case '1':
        Serial.println("Relay1");
        state = !state;
        digitalWrite(relayPin[0],state);
        break;
      case '2':
        Serial.println("Relay2");
        state = !state;
        digitalWrite(relayPin[1],state);
        break;
      case '3':
        Serial.println("Relay3");
        state = !state;
        digitalWrite(relayPin[2],state);
        break;
      case '4':
        Serial.println("Relay4");
        state = !state;
        digitalWrite(relayPin[3],state);
        break;
        
      default: 
        if(input != '\r' && input != '\n')
         Serial.println("Invalid Entry!");
         break;
      }
         
   }
 } 

}
