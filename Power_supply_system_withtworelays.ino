/*
 * Project:Power Supply Switch System for Kayak
 * Version:1.1.0
 * Editor:Luke
 * 
 * Goal:
 * This coding is aiming to imporve the battery switch system for the new Autonomous Kayak 
 * project, where now the battery can power both motors in case of failing to return the 
 * boat when one of the battery is switched off. This idea is figured out by Renye,which can 
 * make better use of batteries power.
 * 
 * Configuration:
 * Pin 8 and 9 are used to detect the voltages of both batteries separately.
 * Pin 5 and 6 are configured as switch signals for the two relays separately.
 * For example:
 * When Pin8 detects the voltage of battery one which is used to power thruster left,
 * when the voltage is lower than some predetermined value, the relay one will be switched 
 * to bettery Two, in that case the second battery will power both thrusters. 
  
 * Default condition:
 * Relay one NC is working for battery one, NO for battery two.
 * Relay two NC is working for battery two, NO for battery one.
 * 
*/

# define BatteryOne_voltage A0
# define BatteryTwo_voltage A1
# define RelayOne_switch 5
# define RelayTwo_switch 6 //Define the different pins' numbers

const int R1 = 200;
const int R2 = 100; // Define the resistors' values

int voltage_one;
int voltage_two;
double voltage_low_limit = 11.6;

void setup() {
Serial.begin(9600);//Communicate with serial on computer.
if(!Serial){;}
pinMode(BatteryOne_voltage,INPUT);
pinMode(BatteryTwo_voltage,INPUT);
pinMode(RelayOne_switch,OUTPUT);
pinMode(RelayTwo_switch,OUTPUT);//Identify the inputs and outputs.
digitalWrite(RelayOne_switch,LOW);
digitalWrite(RelayTwo_switch,LOW);//Initialize the conditions for two relays.

}

void loop() {
voltage_one = battery_voltage(analogRead(BatteryOne_voltage),R1,R2);
voltage_two = battery_voltage(analogRead(BatteryTwo_voltage),R1,R2);

if (voltage_one <= voltage_low_limit){
  if(voltage_two > voltage_low_limit){
    digitalWrite(RelayOne_switch,HIGH);
    Serial.println("Battery two is working for both thrusters.");}
  else if(voltage_two <= voltage_low_limit) {
    Serial.println("There should be an E-stop!");}
  
  }
else if(voltage_one > voltage_low_limit){
  if (voltage_two <= voltage_low_limit){
    digitalWrite(RelayTwo_switch,HIGH);
    Serial.println("Battery one is working for both thrusters.");}
  else{Serial.println("Both batteries are working separately!");
       digitalWrite(RelayOne_switch,LOW);
       digitalWrite(RelayTwo_switch,LOW);}
  }
delay(1000);

}

double battery_voltage(int ACDin, int m, int n){
  double v_battery = (ACDin*5.0/1023.0)*(1+double(R1/R2));
  return v_battery;
  }
