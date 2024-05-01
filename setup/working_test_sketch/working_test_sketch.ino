/*!
TinyML via Edge Impulse
MIT License
MiCS-4514 gas sensor https://www.dfrobot.com/product-2417.html
*/

#include "DFRobot_MICS.h"
#include <SPI.h>
#include <Wire.h>

#define CALIBRATION_TIME   1   

#define Mics_I2C_ADDRESS ADDRESS_0
DFRobot_MICS_I2C mics(&Wire, 0x75);

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 32  
#define OLED_RESET     -1  
#define SCREEN_ADDRESS 0x3C  
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define ADC_PIN   A0
#define POWER_PIN 10

int measuresNumber=4;
int measuresCounter=0;
int measuresTimeFrame=1000; 
float defaultMin=50000;
int printReadings=0;
int timeStamp=0;
int timeStampIncrement=10;
int myCounter=0;

String line1="";
String line2="";
String line3="";

float coSum     = 0;
float ch4Sum     = 0;
float c2H5OHSum  = 0;
float h2Sum      = 0;
float nh3Sum     = 0;
float no2Sum     = 0;

float coMin     = defaultMin;
float ch4Min     = defaultMin;
float c2H5OHMin  = defaultMin;
float h2Min      = defaultMin;
float nh3Min     = defaultMin;
float no2Min     = defaultMin;

float coMax     = 0;
float ch4Max     = 0;
float c2H5OHMax  = 0;
float h2Max      = 0;
float nh3Max     = 0;
float no2Max     = 0;

float coAvg     = 0;
float ch4Avg     = 0;
float c2H5OHAvg  = 0;
float h2Avg      = 0;
float nh3Avg     = 0;
float no2Avg     = 0;

//void printScreen(){

void setup() 
{

  // wait for serial
  Serial.begin(115200);
  //while(!Serial);
    
  while(!mics.begin()){
    Serial.println("No gas sensor detected");
    delay(1000);
  } Serial.println("Gas sensor connected");


  uint8_t mode = mics.getPowerState();
  
  if(mode == SLEEP_MODE){
    mics.wakeUpMode();
    Serial.println("Wake up sensor success");
  }else{
    Serial.println("The sensor is waking up");
  }

   line1="Calibrating";
   line2="sensor...";
   line3="";
   
   while(!mics.warmUpTime(CALIBRATION_TIME)){
    Serial.println("Warming up");
    delay(1000);
  }
  
}

void loop() 
{

  
  if (measuresCounter==measuresNumber){
    
    // reached limit, make calculations
    
    measuresCounter=0;
    myCounter++;

    // average
    coAvg    =coSum/measuresNumber;
    ch4Avg    =ch4Sum/measuresNumber;
    c2H5OHAvg =c2H5OHSum/measuresNumber;
    h2Avg     =h2Sum/measuresNumber;
    nh3Avg    =nh3Sum/measuresNumber;
    no2Avg    =no2Sum/measuresNumber;
    line1="Series #"+String(myCounter);
    line2=String(coAvg)+"-"+String(c2H5OHAvg);
    line3=String(h2Avg)+"-"+String(nh3Avg);

    /*
    Serial.println("---------------------------- Average ");
    Serial.print("Carbon Monox: ");
    Serial.print(co2Avg,1);

    Serial.print(" Methane: ");
    Serial.print(ch4Avg,1);
  
    Serial.print(" Ethanol: ");
    Serial.print(c2H5OHAvg,1);

    Serial.print(" Hydrogen: ");
    Serial.print(h2Avg,1);

    Serial.print(" Amonia: ");
    Serial.print(nh3Avg,1);

    Serial.print(" Nitrogen Diox: ");
    Serial.print(no2Avg,1);
    */

    // normalize min

    if (coMin==defaultMin) {coMin=0;};
    if (ch4Min==defaultMin) {ch4Min=0;};
    if (c2H5OHMin==defaultMin) {c2H5OHMin=0;};
    if (h2Min==defaultMin) {h2Min=0;};
    if (nh3Min==defaultMin) {nh3Min=0;};
    if (no2Min==defaultMin) {no2Min=0;};
    
    // print csv 

    Serial.println("");

    Serial.print(timeStamp);
    Serial.print(",");
    
    Serial.print(coAvg);
    Serial.print(",");
    Serial.print(ch4Avg);
    Serial.print(",");
    Serial.print(c2H5OHAvg);
    Serial.print(",");
    Serial.print(h2Avg);
    Serial.print(",");
    Serial.print(nh3Avg);
    Serial.print(",");
    Serial.print(no2Avg);    

    Serial.print(",");
    Serial.print(coMin);
    Serial.print(",");
    Serial.print(ch4Min);
    Serial.print(",");
    Serial.print(c2H5OHMin);
    Serial.print(",");
    Serial.print(h2Min);
    Serial.print(",");
    Serial.print(nh3Min);
    Serial.print(",");
    Serial.print(no2Min);  

    Serial.print(",");
    Serial.print(coMax);
    Serial.print(",");
    Serial.print(ch4Max);
    Serial.print(",");
    Serial.print(c2H5OHMax);
    Serial.print(",");
    Serial.print(h2Max);
    Serial.print(",");
    Serial.print(nh3Max);
    Serial.print(",");
    Serial.print(no2Max);  

    delay(2000);

     // reset counters
     coSum      = 0;
     ch4Sum     = 0;
     c2H5OHSum  = 0;
     h2Sum      = 0;
     nh3Sum     = 0;
     no2Sum     = 0;
         
     coMin      = defaultMin;
     ch4Min     = defaultMin;
     c2H5OHMin  = defaultMin;
     h2Min      = defaultMin;
     nh3Min     = defaultMin;
     no2Min     = defaultMin;
    
     coMax      = 0;
     ch4Max     = 0;
     c2H5OHMax  = 0;
     h2Max      = 0;
     nh3Max     = 0;
     no2Max     = 0;

     timeStamp=timeStamp+timeStampIncrement;
     delay(measuresTimeFrame);

  }
  else
  {
    
    // increase sample counter
    measuresCounter++;

    // gets data from sensor
    float codata     = mics.getGasData(CO);
    float ch4data     = mics.getGasData(CH4);
    float c2H5OHdata  = mics.getGasData(C2H5OH);
    float h2data      = mics.getGasData(H2);
    float nh3data     = mics.getGasData(NH3);
    float no2data     = mics.getGasData(NO2);

    // sum to calculate average
    coSum     = coSum+codata;
    ch4Sum     = ch4Sum+ch4data;
    c2H5OHSum  = c2H5OHSum+c2H5OHdata;
    h2Sum      = h2Sum+h2data;
    nh3Sum     = nh3Sum+nh3data;
    no2Sum     = no2Sum+no2data;


    if (printReadings==1){
      
            Serial.println("----------------------- Plain Readings");
            Serial.print("Carbon Monox: ");
            Serial.print(codata,1);
            Serial.println(" PPM");
        
            Serial.print("Methane: ");
            Serial.print(ch4data,1);
            Serial.println(" PPM");
            
            Serial.print("Ethanol: ");
            Serial.print(c2H5OHdata,1);
            Serial.println(" PPM");
          
            Serial.print("Hydrogen: ");
            Serial.print(h2data,1);
            Serial.println(" PPM");
          
            Serial.print("Amonia: ");
            Serial.print(nh3data,1);
            Serial.println(" PPM");
          
            Serial.print("Nitrogen Dioxide: ");
            Serial.print(no2data,1);
            Serial.println(" PPM");
            Serial.println("");
    }
    

    // higher than max
    
    if (codata>coMax){
      coMax=codata;      
      }

    if (ch4data>ch4Max){
      ch4Max=ch4data;      
      }

    if (c2H5OHdata>c2H5OHMax){
      c2H5OHMax=c2H5OHdata;      
      }  

    if (h2data>h2Max){
      h2Max=h2data;      
      } 

    if (nh3data>nh3Max){
      nh3Max=nh3data;      
      } 

    if (no2data>no2Max){
      no2Max=no2data;      
      } 

    // lower than min
    
    if (codata>0 and (codata<coMin)){
      coMin=codata;      
      }

    if (ch4data>0 and (ch4data<ch4Min)){
      ch4Min=ch4data;      
      }

    if (c2H5OHdata>0 and (c2H5OHdata<c2H5OHMin)){
      c2H5OHMin=c2H5OHdata;      
      }  

    if (h2data>0 and (h2data<h2Min)){
      h2Min=h2data;      
      } 

    if (nh3data>0 and (nh3data<nh3Min)){
      nh3Min=nh3data;      
      } 

    if (no2data>0 and (no2data<no2Min)){
      no2Min=no2data;      
    } 
  
  
  }
  
 
  delay(measuresTimeFrame/measuresNumber);
}