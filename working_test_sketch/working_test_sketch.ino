/*!
Adapted from Bhopal 84 gas detector, Roni Bandini June 2022 - @RoniBandini
TinyML via Edge Impulse
MIT License
MiCS-4514 gas sensor https://www.dfrobot.com/product-2417.html
*/

//devices
#include "DFRobot_MICS.h"
#include <SPI.h>
#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"

//model
#include "logistic_regression_model.h" // Include the model file
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/kernels/micro_ops.h>
#include "tensorflow/lite/micro/micro_log.h"
#include <tensorflow/lite/micro/micro_interpreter.h>
//#include "tensorflow/lite/core/api/error_reporter.h"  
#include <tensorflow/lite/schema/schema_generated.h>

//data 
#include <float.h>
// Precomputed means and standard deviations (removed NO2 because it's 0)
const float mean_CO_avg = 910.58, std_CO_avg = 124.98;
const float mean_CH4_avg = 24814.80, std_CH4_avg = 1715.27;
const float mean_C2H5OH_avg = 440.09, std_C2H5OH_avg = 76.84;
const float mean_H2_avg = 862.47, std_H2_avg = 161.21;
const float mean_NH3_avg = 488.71, std_NH3_avg = 41.17;

const float mean_CO_min = 904.86, std_CO_min = 134.76;
const float mean_CH4_min = 24774.92, std_CH4_min = 1832.9;
const float mean_C2H5OH_min = 436.56, std_C2H5OH_min = 82.02;
const float mean_H2_min = 855.29, std_H2_min = 170.68;
const float mean_NH3_min = 487.1, std_NH3_min = 45.42;

const float mean_CO_max = 916.61, std_CO_max = 113.88;
const float mean_CH4_max = 24861.29, std_CH4_max = 1488.14;
const float mean_C2H5OH_max = 440.09, std_C2H5OH_max = 71.34;
const float mean_H2_max = 862.47, std_H2_max = 150.11;
const float mean_NH3_max = 488.71, std_NH3_max = 36.48;

// Array to hold the last N readings
const int N = 100;
float carbonMonoxide[N], methane[N], ethanol[N], hydrogen[N], ammonia[N], nitrogenDioxide[N];
int currentIndex = 0; // Current index for circular buffers


// TensorFlow Lite specific variables
namespace {
  tflite::ErrorReporter* error_reporter = nullptr; 
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
  constexpr int kTensorArenaSize = 8 * 1024; // allocates memory for testing, currently 1kb 
  static uint8_t tensor_arena[kTensorArenaSize];
}


// Device calibration / warm-up time 
#define CALIBRATION_TIME   1   

// I2C slave addresses for DFRobot_MICS_I2C:
// ADDRESS_0: 0x75  // I2C device address
// ADDRESS_1: 0x76
// ADDRESS_2: 0x77
// ADDRESS_3: 0x78  

//Initializing LCD 
Waveshare_LCD1602_RGB lcd(16,2);  //16 characters and 2 lines of show
int r,g,b,t=0;
#define SCREEN_ADDRESS 0x3E 


#define Mics_I2C_ADDRESS ADDRESS_0
DFRobot_MICS_I2C mics(&Wire, 0x75);

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
    // initialize
    lcd.init();
    lcd.send_string("Setup TensorFlow");


  // wait for serial
  Serial.begin(115200);
  //while(!Serial);

  // static tflite::MicroErrorReporter micro_error_reporter; // Error reporter
  // error_reporter = &micro_error_reporter;

  model = tflite::GetModel(logistic_regression_model); // Get the TFLite model from the model file
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model schema mismatch!");
    return;
  }

  // static tflite::MicroInterpreter static_interpreter(model, tensor_arena, kTensorArenaSize, error_reporter);
  // interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
       Serial.println("Failed to allocate tensors!");
  //   error_reporter->Report("Failed to allocate tensors!");
  //   return; // Stop execution if memory allocation failed
  }

  input = interpreter->input(0);
  output = interpreter->output(0);

  
  // Gas Sensor  

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
    lcd.setCursor(0,0);
    lcd.send_string("Warming up...");
  }
  
}

void loop() 
{

  
  if (measuresCounter==measuresNumber){
    
    // reached limit, make calculations
    
    measuresCounter=0;
    myCounter++;

    // Calculate averages, minimums, and maximums
    coAvg    =coSum/measuresNumber;
    ch4Avg    =ch4Sum/measuresNumber;
    c2H5OHAvg =c2H5OHSum/measuresNumber;
    h2Avg     =h2Sum/measuresNumber;
    nh3Avg    =nh3Sum/measuresNumber;
    no2Avg    =no2Sum/measuresNumber;
    line1="Series #"+String(myCounter);
    line2=String(coAvg)+"-"+String(c2H5OHAvg);
    line3=String(h2Avg)+"-"+String(nh3Avg);

    // Normalize the data for TensorFlow Lite input
//co
    input->data.f[0] = (coAvg - mean_CO_avg) / std_CO_avg;
    input->data.f[1] = (coMin - mean_CO_min) / std_CO_min;
    input->data.f[2] = (coMax - mean_CO_max) / std_CO_max;

//ch4
    input->data.f[3] = (ch4Avg - mean_CH4_avg) / std_CH4_avg;
    input->data.f[4] = (ch4Min - mean_CH4_min) / std_CH4_min;
    input->data.f[5] = (ch4Max - mean_CH4_max) / std_CH4_max;

//c2h5oh
    input->data.f[6] = (c2H5OHAvg - mean_C2H5OH_avg) / std_C2H5OH_avg;
    input->data.f[7] = (c2H5OHMin - mean_C2H5OH_min) / std_C2H5OH_min;
    input->data.f[8] = (c2H5OHMax - mean_C2H5OH_max) / std_C2H5OH_max;

//h2 - need to update
    input->data.f[9] = (h2Avg - mean_H2_avg) / std_H2_avg;
    input->data.f[10] = (h2Min - mean_H2_min) / std_H2_min;
    input->data.f[11] = (h2Max - mean_H2_max) / std_H2_max;
//nh3
    input->data.f[12] = (nh3Avg - mean_NH3_avg) / std_NH3_avg;
    input->data.f[13] = (nh3Min - mean_NH3_min) / std_NH3_min;
    input->data.f[14] = (nh3Max - mean_NH3_max) / std_NH3_max;

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



    // Run the TensorFlow Lite model
    if (interpreter->Invoke() == kTfLiteOk) {

      // Retrieve predictions from the output tensor
      float* predictions = output->data.f;
      int predicted_class = std::distance(predictions, std::max_element(predictions, predictions + 3));
      
      // Print the predicted class and its confidence level
      Serial.print("Predicted class: ");
      Serial.println(predicted_class);
      Serial.print("Confidence: ");
      Serial.println(predictions[predicted_class] * 100.0, 2);

    } else {
      Serial.println("Inference failed");
    }


     // Reset sums
     coSum      = 0;
     ch4Sum     = 0;
     c2H5OHSum  = 0;
     h2Sum      = 0;
     nh3Sum     = 0;
     no2Sum     = 0;
    // Reset minimums 
     coMin      = defaultMin;
     ch4Min     = defaultMin;
     c2H5OHMin  = defaultMin;
     h2Min      = defaultMin;
     nh3Min     = defaultMin;
     no2Min     = defaultMin;
    // Reset maximums
     coMax      = 0;
     ch4Max     = 0;
     c2H5OHMax  = 0;
     h2Max      = 0;
     nh3Max     = 0;
     no2Max     = 0;
    // Update the timestamp for each new measurement cycle
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
    
    // Update maximums
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

    // Update minimums
  
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