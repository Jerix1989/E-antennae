/*
  CONFIGURATION:

  microcontroller:
  Arduino NANO
  
  timing definition:
  previous Δt*2 time, previous Δt time, current time
  t2              t1            t0

  sampling frequency: 200 hz
  A0 A1: senor signal#1 and sensor signal#2 correspond to pin A0 and pin A1 in the MCU, both are assigned as input pins and connected to sensor#1 and sensor#2
  A2 A3: spike signal SA1 and FA1 correspond to pin A2 and pin A3 in the MCU, both are assigned as output pins and connected to the dual gates of device#1
  A4 A5: spike signal SA2 and FA2 correspond to pin A4 and pin A5 in the MCU, both are assigned as output pins and connected to the dual gates of device#2
  SA1 FA1： SA spike and FA spike encoded from the first sensor signal (sensor#1)
  SA2 FA2： SA spike and FA spike encoded from the second sensor signal (sensor#2)
  
  bool VALUE: sensor signal is displayed or not
  bool SPIKE: spike signal is displayed or not
  
 */

#include <SPI.h>

const int SIZE = 160;
int pin_sensor1[SIZE] = 
{
451,  451 , 451 , 451 , 452 , 452 , 452 , 452 , 452 , 452 , 453 , 452 , 452 , 452 , 452 , 450 , 449 , 449 , 447 , 447 , 
448 , 446 , 445 , 445 , 445 , 444 , 443 , 443 , 443 , 442 , 441 , 441 , 441 , 440 , 439 , 438 , 439 , 438 , 437 , 437 , 
436 , 436 , 436 , 435 , 434 , 434 , 434 , 433 , 432 , 432 , 432 , 431 , 431 , 431 , 431 , 430 , 431 , 429 , 429 , 429 , 
428 , 428 , 427 , 428 , 427 , 427 , 427 , 426 , 425 , 426 , 425 , 424 , 424 , 424 , 423 , 423 , 423 , 423 , 422 , 423 , 
423 , 422 , 422 , 422 , 421 , 421 , 422 , 421 , 420 , 421 , 420 , 420 , 420 , 420 , 419 , 420 , 420 , 420 , 421 , 421 , 
421 , 423 , 422 , 423 , 423 , 424 , 424 , 425 , 425 , 425 , 425 , 425 , 426 , 426 , 427 , 427 , 427 , 427 , 428 , 428 , 
428 , 429 , 429 , 429 , 429 , 429 , 429 , 430 , 430 , 430 , 431 , 526 , 398 , 458 , 457 , 456 , 455 , 452 , 457 , 451 , 
451 , 450 , 450 , 449 , 448 , 448 , 447 , 446 , 446 , 446 , 444 , 444 , 445 , 443 , 442 , 442 , 443 , 441 , 441 , 441 
};

int pin_sensor2[SIZE] =
{
451,  451,  451,  450,  450,  452,  452,  452,  452,  451,  452,  451,  451,  451,  451,  451,  451,  450,  450,  451,  
452,  449,  449,  450,  450,  449,  449,  449,  448,  448,  448,  447,  446,  446,  445,  444,  445,  443,  443,  443,  
443,  442,  441,  441,  440,  440,  440,  439,  438,  439,  438,  437,  436,  437,  435,  435,  435,  434,  433,  434,  
433,  433,  432,  432,  432,  431,  431,  431,  430,  430,  429,  428,  429,  429,  428,  426,  427,  426,  426,  426,  
426,  425,  426,  425,  424,  424,  425,  423,  423,  423,  422,  422,  422,  422,  421,  421,  421,  420,  421,  421,  
420,  421,  421,  421,  422,  423,  423,  423,  424,  424,  424,  425,  425,  425,  427,  426,  426,  427,  428,  428,  
428,  428,  428,  428,  429,  429,  429,  430,  429,  429,  430,  429,  432,  429,  432,  431,  431,  532,  432,  455,  
456,  455,  454,  453,  451,  450,  449,  449,  449,  448,  447,  448,  448,  447,  447,  446,  446,  445,  445,  445  
};

const int SA1 = A2;
const int FA1 = A3;
const int SA2 = A4;
const int FA2 = A5;

const int pin_LED = 13; 

float time_read = 5; // dewelling time 5 ms, corresponding to sampling frequency of 200hz (this value can be set as 4)

int sensor1_t0 = 0; // current reading of the signal from sensor #1 (0-1023)
int sensor1_t1 = 0;
int sensor1_t2 = 0;
int sensor1_def = 450; //default value of the signal from sensor #1

int sensor2_t0 = 0; // current reading of the signal from sensor #2 (0-1023)
int sensor2_t1 = 0;
int sensor2_t2 = 0;
int sensor2_def = 450; //default value of the signal from sensor #2

int SA1_cnt = 0;
int FA1_cnt = 0;
int SA2_cnt = 0;
int FA2_cnt = 0;

bool SENSE = 0; // display sensor signal
bool SPIKE = 1; // display spike signal

int SA_th1 = 15; // FIRST threshold value for SA signal
int FA_th1 = 5; // FIRST threshold value for FA signal

int n = 3;


void setup() 
{
  pinMode(pin_LED, OUTPUT);
  pinMode(SA1, OUTPUT);
  pinMode(FA1, OUTPUT);
  pinMode(SA2, OUTPUT);
  pinMode(FA2, OUTPUT);
  digitalWrite(pin_LED, LOW);
  digitalWrite(SA1, LOW);
  digitalWrite(FA1, LOW);
  digitalWrite(SA2, LOW);
  digitalWrite(FA2, LOW);
  Serial.begin(250000); // Baud rate 250000
  delay(3000); // waiting time 3 sec

  
  
  sensor1_t2 = pin_sensor1[0];
  delay(time_read);
  sensor1_t1 = pin_sensor1[1];
  delay(time_read);
  sensor1_t0 = pin_sensor1[2];
  delay(time_read);

  sensor2_t2 = pin_sensor2[0];
  delay(time_read);
  sensor2_t1 = pin_sensor2[1];
  delay(time_read);
  sensor2_t0 = pin_sensor2[2];
  delay(time_read);
}


void loop()
{

  for( ; n < SIZE; n ++)
  {
      sensor1_t2 = sensor1_t1;
      sensor1_t1 = sensor1_t0;
      sensor1_t0 = pin_sensor1[n];
    
      sensor2_t2 = sensor2_t1;
      sensor2_t1 = sensor2_t0;
      sensor2_t0 = pin_sensor2[n];
    
      delay(time_read);  // delay time for controlling sampling and cycling
      
      if(SENSE == 1) // enable display sensor value
      {
        Serial.print("SENSOR1: ");
        Serial.print(sensor1_t0);  //print signal from sensor#1
         
        Serial.print("SENSOR2: ");
        Serial.print(sensor2_t0);  //print signal from sensor#2
      }
    
       
      if(SPIKE == 1) // enable display spike value
      {
        
        /**********SA1 coding************/
        if (SA1_cnt == 0)
        {
          if( abs(sensor1_t0 - sensor1_def) < SA_th1) // SA spike encoding: compare the sensor value at t0 and the default value
          {
            SA1_cnt = 1;
            Serial.print("SA1: 0  ");
            digitalWrite(SA1, LOW);
          }
          else
          {  
            SA1_cnt = 1;
            Serial.print("SA1: 5  ");
            digitalWrite(SA1, HIGH);
          }
        }
        else
        {
          SA1_cnt --;
          Serial.print("SA1: 0  ");
          digitalWrite(SA1, LOW);
        }
    
        /**********FA1 coding************/  
        if (FA1_cnt == 0)
        {
          if( abs(sensor1_t0 - sensor1_t2) < FA_th1) // FA spike encoding: compare the sensor value at t0 and t2
          {
            FA1_cnt = 1;
            Serial.print("FA1: 0  ");
            digitalWrite(FA1, LOW);
          }
          else
          {  
            FA1_cnt = 1;
            Serial.print("FA1: 5  ");
            digitalWrite(FA1, HIGH);
          }
        }
        else
        {
          FA1_cnt --;
          Serial.print("FA1: 0  ");
          digitalWrite(FA1, LOW);
        }   
    
        /**********SA2 coding************/
        if (SA2_cnt == 0)
        {
          if( abs(sensor2_t0 - sensor2_def) < SA_th1) // SA spike encoding: compare the sensor value at t0 and the default value
          {
            SA2_cnt = 1;
            Serial.print("SA2: 0  ");
            digitalWrite(SA2, LOW);
          }
          else
          {  
            SA2_cnt = 1;
            Serial.print("SA2: 5  ");
            digitalWrite(SA2, HIGH);
          }
        }
        else
        {
          SA2_cnt --;
          Serial.print("SA2: 0  ");
          digitalWrite(SA2, LOW);
        }
    
        /**********FA2 coding************/  
        if (FA2_cnt == 0)
        {
          if( abs(sensor2_t0 - sensor2_t2) < FA_th1) // FA spike encoding: compare the sensor value at t0 and t2
          {
            FA2_cnt = 1;
            Serial.print("FA2: 0  ");
            digitalWrite(FA2, LOW);
          }
          else
          {  
            FA2_cnt = 1;
            Serial.print("FA2: 5  ");
            digitalWrite(FA2, HIGH);
          }
        }
        else
        {
          FA2_cnt --;
          Serial.print("FA2: 0  ");
          digitalWrite(FA2, LOW);
        }     
    
      } // end of enable display sensor value
      
      Serial.println(" ");  // print control
  }
}
