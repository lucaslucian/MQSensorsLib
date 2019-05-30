/*
  MQUnifiedsensor Library - calibrating an MQ2 to MQ9

  Demonstrates the use a MQ2 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez
 
  Added example
  modified 27 May 2019
  by Miguel Califa 

  Added LCD
  modified 26 May 2019
  by Miguel Califa 

  Changed sample frecuency
  modified 28 May 2019
  by Ghiordy contreras, Miguel Califa 

  Added voltaje to log
  modified 29 May 2019
  by Miguel Califa 
  
 This example code is in the public domain.

*/

//Include the library
#include <MQUnifiedsensor.h>
//And lcd library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Definitions
#define pin2 A2 //Analog input 2 of your arduino
#define pin3 A3 //Analog input 3 of your arduino
#define pin4 A4 //Analog input 4 of your arduino
#define pin5 A5 //Analog input 5 of your arduino
#define pin6 A6 //Analog input 6 of your arduino
#define pin7 A7 //Analog input 7 of your arduino
#define pin8 A8 //Analog input 8 of your arduino
#define pin9 A9 //Analog input 9 of your arduino

#define timeDelay 500
//Declare Sensor

MQUnifiedsensor MQ2(pin2, 2);
MQUnifiedsensor MQ3(pin3, 3);
MQUnifiedsensor MQ4(pin4, 4);
MQUnifiedsensor MQ5(pin5, 5);
MQUnifiedsensor MQ6(pin6, 6);
MQUnifiedsensor MQ7(pin7, 7);
MQUnifiedsensor MQ8(pin8, 8);
MQUnifiedsensor MQ9(pin9, 9);

unsigned long contador = 0;
unsigned long time = millis();

void setup() {
  //Init serial port
  Serial.begin(115200);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  //Welcome message
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MQ2 to MQ9");
  lcd.setCursor(0,1);
  lcd.print("   Calibrating");
  //init the sensor
  
  MQ2.inicializar(); 
  MQ3.inicializar(); 
  MQ4.inicializar(); 
  MQ5.inicializar(); 
  MQ6.inicializar(); 
  MQ7.inicializar(); 
  MQ8.inicializar(); 
  MQ9.inicializar();

  MQ2.setVoltResolution(5);
  MQ3.setVoltResolution(5);
  MQ4.setVoltResolution(5);
  MQ5.setVoltResolution(5);
  MQ6.setVoltResolution(5);
  MQ7.setVoltResolution(5);
  MQ8.setVoltResolution(5);
  MQ9.setVoltResolution(5);
  
  //Print in serial monitor
  Serial.println("MQ2 to MQ9 - Calibracion");
  Serial.println("Note - Make sure you are in a clean room and the sensor has pre-heated almost 4 hours");
  Serial.println("Autonumeric, MQ2(R0), MQ3(R0), MQ4(R0), MQ5(R0), MQ6(R0), MQ7(R0)");
  //Wait one second to continue
  delay(timeDelay/10);
}

void loop() {
  //Read the sensor
  int lecture2 =  MQ2.calibrate();
  int lecture3 =  MQ3.calibrate();
  int lecture4 =  MQ4.calibrate();
  int lecture5 =  MQ5.calibrate();
  int lecture6 =  MQ6.calibrate();
  int lecture7 =  MQ7.calibrate();
  int lecture8 =  MQ8.calibrate();
  int lecture9 =  MQ9.calibrate();

  
  //Print in serial monitor
  char out[40];
  snprintf(out, 30, "%d,%d,%d,%d,%d,%d,%d,%d", contador, lecture2, lecture3, lecture4, lecture5, lecture6, lecture7, lecture8, lecture9);
  Serial.println(out);
  
  //Print in LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("**CALIBRATING***");
  lcd.setCursor(0,1);
  lcd.print("Time: " + String((millis() - time)/60000) + "min");
  //Increment counter
  contador++;
  //Wait to measure next sample
  delay(timeDelay/4);
}