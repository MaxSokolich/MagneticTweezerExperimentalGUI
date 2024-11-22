

  //This is working without the need to open the serial monitor. However, I am not sure i am able to adjust 
//the pwm timers.
// action = [Bx, By, Bz, alpha, gamma, freq]
//potential issues
// - if  (myTransfer.available()) may cuz bugs because actions maybe empty or something
// - may need a better way to toggle the enable pin on all 6 drivers
// - there is no hard zero option as I got rid of typ
#include <AD9850.h>
#include "SerialTransfer.h"
SerialTransfer myTransfer;
float action[9]; //an array to store incoming data from python

#define PI 3.1415926535897932384626433832795

//actions
float I1;
float I2;
float I3;
float I4;




//other constants
float tim;
float t;







//Coil 1 : +Y Brown
const int Coil1_PWMR = 2;
const int Coil1_PWML = 3;
const int Coil1_ENR = 26; //26
const int Coil1_ENL = 27; //27                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            333

//Coil 2 : +X Purple
const int Coil2_PWMR = 4;
const int Coil2_PWML = 5;
const int Coil2_ENR = 24; //24
const int Coil2_ENL = 25; //25

//Coil 3 : -Y Green
const int Coil3_PWMR = 6;
const int Coil3_PWML = 7;
const int Coil3_ENR = 22;
const int Coil3_ENL = 23;

//Coil 4: -X Blue
const int Coil4_PWMR = 8;
const int Coil4_PWML = 9;
const int Coil4_ENR = 32;
const int Coil4_ENL = 33;

//Coil 5 : +Z  Yellow
const int Coil5_PWMR = 10;
const int Coil5_PWML = 11;
const int Coil5_ENR = 30;
const int Coil5_ENL = 31;

//Coil 6 : -Z Orange
const int Coil6_PWMR = 12;
const int Coil6_PWML = 13;
const int Coil6_ENR = 28;
const int Coil6_ENL = 29;


//AD9850 Acoustic Module
const int W_CLK_PIN = 34;
const int FQ_UD_PIN = 36;
const int DATA_PIN = 38;
const int RESET_PIN = 40;


  
void setup()
{
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
  DDS.calibrate(124999500);

  cli();
  TCCR0B = (TCCR0B & 0b11111000) | 0x02; //7.81250[kHz] pin 13,4
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; //31.37255 [kHz] pin 12,11
  TCCR2B = (TCCR2B & 0b11111000) | 0x01; //31.37255 [kHz] pin 10,9
  TCCR3B = (TCCR3B & 0b11111000) | 0x01; //31.37255 [kHz] pin 5,3,2
  TCCR4B = (TCCR4B & 0b11111000) | 0x01; //31.37255 [kHz] pin 8,7,6 
  sei();
  
  Serial.begin(115200);
  myTransfer.begin(Serial);


   //Coil1 Ouptut
  pinMode(Coil1_PWMR, OUTPUT);  
  pinMode(Coil1_PWML, OUTPUT);
  pinMode(Coil1_ENR, OUTPUT);  
  pinMode(Coil1_ENL, OUTPUT); 
  


  //Coil2 Output
  pinMode(Coil2_PWMR, OUTPUT);  
  pinMode(Coil2_PWML, OUTPUT);
  pinMode(Coil2_ENR, OUTPUT);  
  pinMode(Coil2_ENL, OUTPUT); 
  


  //Coil3 Output
  pinMode(Coil3_PWMR, OUTPUT);  
  pinMode(Coil3_PWML, OUTPUT);
  pinMode(Coil3_ENR, OUTPUT);  
  pinMode(Coil3_ENL, OUTPUT); 


  //Coil4 Output
  pinMode(Coil4_PWMR, OUTPUT);  
  pinMode(Coil4_PWML, OUTPUT);
  pinMode(Coil4_ENR, OUTPUT);  
  pinMode(Coil4_ENL, OUTPUT); 


  //Coil5 Output
  pinMode(Coil5_PWMR, OUTPUT);  
  pinMode(Coil5_PWML, OUTPUT);
  pinMode(Coil5_ENR, OUTPUT);  
  pinMode(Coil5_ENL, OUTPUT);
 

  //Coil6 Output
  pinMode(Coil6_PWMR, OUTPUT);  
  pinMode(Coil6_PWML, OUTPUT);
  pinMode(Coil6_ENR, OUTPUT);  
  pinMode(Coil6_ENL, OUTPUT);
  
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set1(float DC1){
  digitalWrite(Coil1_ENR,HIGH);
  digitalWrite(Coil1_ENL,HIGH);

  if (DC1 > 0){
    analogWrite(Coil1_PWMR,abs(DC1)*255);
    analogWrite(Coil1_PWML,0);
  }
  else if (DC1 < 0){
    analogWrite(Coil1_PWMR,0);
    analogWrite(Coil1_PWML,abs(DC1)*255);
  }
  else {
    analogWrite(Coil1_PWMR,0);
    analogWrite(Coil1_PWML,0);
    
  }



}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set2(float DC2){
  digitalWrite(Coil2_ENR,HIGH);
  digitalWrite(Coil2_ENL,HIGH);

  if (DC2 > 0){
    analogWrite(Coil2_PWMR,abs(DC2)*255);
    analogWrite(Coil2_PWML,0);
  }
  else if (DC2 < 0){
    analogWrite(Coil2_PWMR,0);
    analogWrite(Coil2_PWML,abs(DC2)*255);
  }
  else {
    analogWrite(Coil2_PWMR,0);
    analogWrite(Coil2_PWML,0);
    
  }
  

  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set3(float DC3){
  digitalWrite(Coil3_ENR,HIGH);
  digitalWrite(Coil3_ENL,HIGH);

  if (DC3 > 0){
    analogWrite(Coil3_PWMR,abs(DC3)*255);
    analogWrite(Coil3_PWML,0);
  }
  else if (DC3 < 0){
    analogWrite(Coil3_PWMR,0);
    analogWrite(Coil3_PWML,abs(DC3)*255);
  }
  else {
    analogWrite(Coil3_PWMR,0);
    analogWrite(Coil3_PWML,0);
    
  }

  

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set4(float DC4){
  digitalWrite(Coil4_ENR,HIGH);
  digitalWrite(Coil4_ENL,HIGH);

  if (DC4 > 0){
    analogWrite(Coil4_PWMR,abs(DC4)*255);
    analogWrite(Coil4_PWML,0);
  }
  else if (DC4 < 0){
    analogWrite(Coil4_PWMR,0);
    analogWrite(Coil4_PWML,abs(DC4)*255);
  }
  else {
    analogWrite(Coil4_PWMR,0);
    analogWrite(Coil4_PWML,0);
   
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set5(float DC5){
  digitalWrite(Coil5_ENR,HIGH);
  digitalWrite(Coil5_ENL,HIGH);

  if (DC5 > 0){
    analogWrite(Coil5_PWMR,abs(DC5)*255);
    analogWrite(Coil5_PWML,0);
  }
  else if (DC5 < 0){
    analogWrite(Coil5_PWMR,0);
    analogWrite(Coil5_PWML,abs(DC5)*255);
  }
  else {
    analogWrite(Coil5_PWMR,0);
    analogWrite(Coil5_PWML,0);
    
  }


 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set6(float DC6){
  digitalWrite(Coil6_ENR,HIGH);
  digitalWrite(Coil6_ENL,HIGH);

  if (DC6 > 0){
    analogWrite(Coil6_PWMR,abs(DC6)*255);
    analogWrite(Coil6_PWML,0);
  }
  else if (DC6 < 0){
    analogWrite(Coil6_PWMR,0);
    analogWrite(Coil6_PWML,abs(DC6)*255);
  }
  else {
    analogWrite(Coil6_PWMR,0);
    analogWrite(Coil6_PWML,0);

  }
  
 

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void loop()
{
    if  (myTransfer.available()){ // THIS IF STATEMENT MIGHT MESS UP EVERYTHING BELOW
      
              uint16_t message = 0;
              message = myTransfer.rxObj(action,message);               
    }

   
   //NEW LOGIC
    I1 = action[0];
    I2 = action[1];
    I3 = action[2];   
    I4 = action[3];

    

  
    set1(I1); // North (-1 < I1 < 1)
    set2(I2); // East (-1 < I2 < 1)
    set3(I3); //South (-1 < I3 < 1)
    set4(I4); //West (-1 < I4 < 1)
      
  
    }
  