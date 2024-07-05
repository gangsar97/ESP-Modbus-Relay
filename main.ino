#include <SoftwareSerial.h>
#include <ModbusRTU.h>

//definisi software serial

#define RX_pin 14
#define TX_pin 12
#define BAUD_RATE 9600
#define PARITY SWSERIAL_8N1

//definisi Pin NodeMCU

#define Relay_1 5
#define Relay_2 4
#define Relay_3 0
#define Relay_4 2

// definisi modbus address data

#define SLAVE_ID 1
#define Relay1_address 1
#define Relay2_address 2
#define Relay3_address 3
#define Relay4_address 4

SoftwareSerial swSerial(RX_pin, TX_pin);
ModbusRTU modbus;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);
  pinMode(Relay_3, OUTPUT);
  pinMode(Relay_4, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  swSerial.begin(BAUD_RATE, PARITY);
  modbus.begin(&swSerial);
  modbus.slave(SLAVE_ID);
  modbus.addCoil(Relay1_address);
  modbus.addCoil(Relay2_address);
  modbus.addCoil(Relay3_address);
  modbus.addCoil(Relay4_address);
}

void loop() {
  modbus.task();
  
  digitalWrite(Relay_1, modbus.Coil(Relay1_address));
  digitalWrite(Relay_2, modbus.Coil(Relay2_address));
  digitalWrite(Relay_3, modbus.Coil(Relay3_address));
  digitalWrite(Relay_4, modbus.Coil(Relay4_address));
 
  delay(100);
}
