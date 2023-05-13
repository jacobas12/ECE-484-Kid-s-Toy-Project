#include <SPI.h>  //the communication interface with the modem
#include "RF24.h" //the library which helps us to control the radio modem

//define the data pins
int joyX = A1;
int joyY = A2;

//define variable values
int dataX;
int dataY;

int data[2];

RF24 radio(10,9); //10 and 9 are a digital pin numbers to which signals CE and CSN are connected
const byte address[6] = "00001";
                                      
//const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino


void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem
  //radio.openWritingPipe(pipe); 
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();       //sets the address of the receiver to which the program will send data
}

void loop(){
  //Send signal data
  dataX = analogRead(joyX);
  dataY = analogRead(joyY);
  
  data[0] = dataX;
  data[1] = dataY;

  Serial.print("Data X:"); Serial.println(dataX);
  Serial.print("Data Y:"); Serial.println(dataY);
  radio.write(data, sizeof(data));
  Serial.println(data[0]);
  delay(500);
}