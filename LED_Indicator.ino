/*
   This code is aiming to design the LED indicator for UAV.

   Editor : Luke
   Date: 02/12/2016
   Ver:0.1

   Description:
   ThE LED device is comprised with three colors, Red,Green and Yellow.

   THe followings are the meanings for different combinations of LED.
   R,G,Y:Off      --> No Power supply for the boat
   R,G:Off  Y:On  --> Manual control by the remote control
   R,Y:Off  G:On  --> Autonomously control
   R,Y:Off  R:On  --> E-stop for protecting the boat from uncertain damage or danger

   The Arduino Relay shield V2.1 is used.
   Relay1 for the Red Led.
   Relay2 for the Green Led.
   Relay3 for the Yellow Led.

*/
# define EStop 3
# define ControlMode 4
//# define power_pin 10
byte RelayPin[4] = {2, 7, 8, 10};
//int  RelayState[4];
// D2 -> relay1;
// D7 -> relay2;
// D8 -> relay3;
int ModeState = LOW; // It initializes the mode with manual control.
int EStopState = LOW;// The EStop wont be active at initialization.




void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
  {
    pinMode(RelayPin[i], OUTPUT);
    digitalWrite(RelayPin[i], LOW); // Define the output for the LED digital pins and initialize them with Low condition.
  }
  pinMode(EStop, INPUT);
  pinMode(ControlMode, INPUT); // Define the input pin for the EStop and ControlMode.
  //pinMode(power_pin,OUTPUT)
  //digitalWrite(power_pin,LOW)



}

void loop() {

  EStopState = digitalRead(EStop);
  ModeState = digitalRead(ControlMode); //Read the input from the Estop and mode pins

  if (EStopState == HIGH)
  { digitalWrite(RelayPin[0], HIGH);
    delay(1000);
  }// If the Estop is on, then Red LED is on.

  else
  { if (ModeState == LOW)
    { digitalWrite(RelayPin[1], HIGH);
      delay(1000);
      Serial.println("No E-stop and it's manual control mode!");
    }// If the estop is off and mode pin is low then it's manual control mode, the yellow LED will be on.

    else {
      digitalWrite(RelayPin[2], HIGH);
      delay(1000);
    }  // Estop is off and Mode pin is high, then the autonomous mode is actived.
  }

}

